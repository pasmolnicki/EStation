#pragma once

#include <Arduino.h>

#include "namespaces.h"
#include <functional>
#include <tuple>
#include <memory>

// `apply` implementation for tuples
#include "tuple.h"
// Locks
#include "lock.h"

BEGIN_TASKS_NAMESPACE


/**
  * Task parameters, used to create a task, has information about the task:
  * - stack size (default is 4096)
  * - priority (default is tskIDLE_PRIORITY)
  * - name (default is "Task")
  * - use pinned core (default is false)
  * - core (default is 0)
*/
struct TaskParams
{
    // stack size, default is 4096
    int stackSize = 4096;

    // priority of the task, default is tskIDLE_PRIORITY, probably shouldn't be changed
    int priority = tskIDLE_PRIORITY;

    // name of the task, default is "Task" + ID, ex. "Task15", ID = 15
    std::string name = "";

    // use pinned core, default is false
    bool usePinnedCore = false;

    // core to pin the task to (0 or 1), default is 0 (if usePinnedCore is true)
    int core = 0;
    
    TaskParams(
        int stackSize = 4096, 
        int priority = tskIDLE_PRIORITY, 
        std::string name = "", 
        bool usePinnedCore = false, 
        int core = 0
    ): stackSize(stackSize), priority(priority), name(name),
    usePinnedCore(usePinnedCore), core(core) {}
    
    TaskParams(const TaskParams& other){
        *this = other;
    }

    TaskParams& operator=(const TaskParams& other){
        stackSize = other.stackSize;
        priority = other.priority;
        name = other.name;
        usePinnedCore = other.usePinnedCore;
        core = other.core;
        return *this;
    }

    TaskParams& setStackSize(int size){
        stackSize = size;
        return *this;
    }

    TaskParams& setPriority(int p){
        priority = p;
        return *this;
    }

    TaskParams& setName(const std::string& n){
        name = n;
        return *this;
    }

    TaskParams& setUsePinnedCore(bool use){
        usePinnedCore = use;
        return *this;
    }

    // set the core to pin the task to, also sets `usePinnedCore` to true
    TaskParams& setCore(int c){
        core = c;
        usePinnedCore = true;
        return *this;
    }
};


/**
 * ## TaskSignal
 * 
 * An enum class that represents the signals that can be sent to a task.
*/
enum class _TaskSignal
{
    STOP = 1,
    PAUSE = 2,
    RUN = 3,
};

/**
 * Task data, used to store the task handle.
 * 
 * To pass the `TaskHandle_t` to the task function, we need to store it in the heap.
 * Also, we need to store the signal that was sent to the task, and a mutex to protect
 * the signal
*/
struct _AsyncTaskData
{
    TaskHandle_t _handle;
    _TaskSignal _signal;
    SemaphoreHandle_t _mutex;
    bool deleted = false;

    _AsyncTaskData(TaskHandle_t handle = NULL, _TaskSignal signal = _TaskSignal::RUN):
        _handle(handle), _signal(signal), _mutex(xSemaphoreCreateMutex()), deleted(false) {}

    ~_AsyncTaskData()
    {
        if (_mutex)
        {
            vSemaphoreDelete(_mutex);
        }
    }
};

// Forward declaration for `_deleteTask` function
template <typename... _ArgTypes>
class AsyncTask;

/**
 * @brief Delete the task and free the memory
 * @param p The task to be deleted
 * @param kill If true, the task will be killed, otherwise it will be left running
 * and returns the handle
*/
template <typename... _ArgTypes>
TaskHandle_t _deleteTask(AsyncTask<_ArgTypes...>* p, bool kill)
{
    TaskHandle_t handle = p->_data->_handle;

    // Set the flag
    xSemaphoreTake(p->_data->_mutex, portMAX_DELAY);
    p->_data->deleted = true;
    xSemaphoreGive(p->_data->_mutex);

    // delete the pointer
    delete p;

    if (kill)
    {
        vTaskDelete(handle);
    }

    return handle;
}

/**
 * Base class for AsyncTask, used to store parameters and the task data
*/
class BaseAsyncTask
{
  public:
    static int _task_id; // task counter

    // Default c'tor
    BaseAsyncTask(const TaskParams& params = TaskParams()): _params(params), _data(nullptr) 
    {
        if (_params.name.empty())
        {
            _params.name = "AsyncTask-" + std::to_string(_task_id);
        }
        _task_id++;
    }

    virtual ~BaseAsyncTask() = default;

    /**
     * @brief Stop the task, this will send a signal to the task to stop it, doesn't work immediately
    */
    void stop();

    /**
     * @brief Pause the task, you can resume the task using `resume()`
    */
    void pause();

    /**
     * @brief Resume the task, after it was paused
    */
    void resume();

    /**
     * @brief Join the task to the current thread, it waits for the task to finnish.
     */
    void join();

  protected:
    /**
     * @brief Wrapper for the task function, casts the task, runs it and deletes it
    */
    template <typename... _ArgTypes>
    static void _taskWrapper(void *param)
    {
        // Get the task from the parameter and cast it to the correct type.
        // This is probably the only way to do this, since we can't use lambdas
        // as task functions, and we can't use static_cast with lambdas.
        // The task also must be allocated on the heap, since there's a possibility
        // that the task will be deleted before it's done if it was on stack memory.
        auto task = static_cast<AsyncTask<_ArgTypes...>*>(param);

        // First, check if the task was stopped, using a mutex
        if (xSemaphoreTake(task->_data->_mutex, portMAX_DELAY) == pdTRUE)
        {
            // Must store the mutex in a local variable, since the task can be deleted
            SemaphoreHandle_t mutex = task->_data->_mutex;
            // If the task was stopped, delete it and return
            if (task->_data->_signal == _TaskSignal::STOP)
            {
                TaskHandle_t handle = _deleteTask<_ArgTypes...>(task, false);
                xSemaphoreGive(mutex);
                vTaskDelete(NULL);
            }
            xSemaphoreGive(mutex);
        }

        // Run the task on the current thread
        task->_runTask();
        
        // Delete the task after it's done, must be called after the task is done,
        // also terminates the FreeRTOS task
        _deleteTask<_ArgTypes...>(task, true);
    }

    // Friend function, used to delete the task, see above
    // Also, the Scheduler class can access the private members
    template <typename... _ArgTypes>
    friend TaskHandle_t _deleteTask(AsyncTask<_ArgTypes...>* p, bool kill);
    friend class Scheduler;

    std::shared_ptr<_AsyncTaskData> _data;
    TaskParams _params;
    TaskHandle_t *_async_handle;
};


/**
 * ## AsyncTask
 * 
 * A class that represents a task that can be run in the background.
 * The task is a one-time task, it can't be run multiple times.
 * 
*/
template <typename... _ArgTypes>
class AsyncTask : public BaseAsyncTask
{
    using _TaskType = std::function<void(_ArgTypes...)>;

    _TaskType _task;
    std::tuple<_ArgTypes...> _args;

public:
    AsyncTask() = default;
    AsyncTask(_TaskType task);
    AsyncTask(const TaskParams& params);
    AsyncTask(
      const TaskParams& params, 
      _TaskType task
    );
    AsyncTask(const AsyncTask& other);

    inline AsyncTask& setParams(const TaskParams& params)
    {
        _params = params;
        return *this;
    }

    inline AsyncTask& setTask(_TaskType task)
    {
        _task = task;
        return *this;
    }

    /**
     * @brief Run the task in the background
    */
    inline void run(_ArgTypes... args)
    {
        if (_task)
            return;
        
        _args = std::make_tuple(args...);
        _data.reset(new _AsyncTaskData());
        if (_params.usePinnedCore)
        {
            xTaskCreatePinnedToCore(
                _taskWrapper<_ArgTypes...>, _params.name.c_str(), _params.stackSize,
                copy(), _params.priority, &_data->_handle, _params.core
            );
            return;
        }
        xTaskCreate(
            _taskWrapper<_ArgTypes...>, _params.name.c_str(), _params.stackSize,
            copy(), _params.priority, &_data->_handle
        );
        _async_handle = &_data->_handle;
    }
    
    /**
     * @brief Same as `run(...)`, but with operator overloading
    */
    inline void operator()(_ArgTypes... args)
    {
        run(args...);
    }

    /**
     * @brief Run the task in the current thread, used internally
    */
    inline void _runTask()
    {
        if (_task)
            apply(_task, _args);
    }

    AsyncTask& operator=(const AsyncTask& other){
        _params = other._params;
        _task = other._task;
        _args = other._args;
        return *this;
    }

    /**
     * @brief Copy the task to the heap, used internally
    */
    AsyncTask* copy() const
    {
        auto ptr = new AsyncTask(*this);
        ptr->_data = _data;
        return ptr;
    }
};

template <typename... _ArgTypes>
AsyncTask<_ArgTypes...>::AsyncTask(_TaskType task): 
    AsyncTask(TaskParams(), task) {}

template <typename... _ArgTypes>
AsyncTask<_ArgTypes...>::AsyncTask(const TaskParams& params) : 
    AsyncTask(params, nullptr) {}

template <typename... _ArgTypes>
AsyncTask<_ArgTypes...>::AsyncTask(
  const TaskParams& params, 
  _TaskType task
) : BaseAsyncTask(params), _task(task) {}

template <typename... _ArgTypes>
AsyncTask<_ArgTypes...>::AsyncTask(const AsyncTask& other){
    *this = other;
}

/**
 * ## AsyncTask
 * 
 * A class that represents a task that can be run in the background.
 * The task is a one-time 'function', it can't be run multiple times.
 * 
*/
template <>
class AsyncTask<> : public BaseAsyncTask{

    using _TaskType = std::function<void()>;

    _TaskType _task;

public:
    AsyncTask();
    AsyncTask(_TaskType task);
    AsyncTask(const TaskParams& params);
    AsyncTask(const TaskParams& params, _TaskType task);
    AsyncTask(const AsyncTask& other);

    AsyncTask& setParams(const TaskParams& params);
    AsyncTask& setTask(_TaskType task);

    /**
     * @brief Run the task in the background
    */
    void run();

    /**
     * @brief Same as `run()`, but with operator overloading
    */
    void operator()();

    /**
     * @brief Run the task in the current thread, used internally
    */
    void _runTask();    

    AsyncTask& operator=(const AsyncTask& other);

    /**
     * @brief Copy the task to the heap, used internally
    */
    AsyncTask* copy() const;
};


END_TASKS_NAMESPACE