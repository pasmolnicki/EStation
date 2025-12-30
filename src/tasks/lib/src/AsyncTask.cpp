#include "AsyncTask.h"

BEGIN_TASKS_NAMESPACE

// void AsyncTask specializations with no parameters

using _TaskType = std::function<void()>;

// Set the task id to 0
int BaseAsyncTask::_task_id = 0;


void BaseAsyncTask::stop()
{
    // The task can be deleted only in the `taskWrapper` function, so we must
    // send a signal to the task to stop it, and then delete it in the `taskWrapper`
    if (_data && _data->_signal == _TaskSignal::RUN)
    {
        Lock guard(_data->_mutex);
        _data->_signal = _TaskSignal::STOP;
    }
}

void BaseAsyncTask::pause()
{
    if (_data && _data->_signal == _TaskSignal::RUN)
    {
        Lock guard(_data->_mutex);
        vTaskSuspend(_data->_handle);
        _data->_signal = _TaskSignal::PAUSE;
    }
}

void BaseAsyncTask::resume()
{
    if(_data && _data->_signal == _TaskSignal::PAUSE)
    {
        Lock guard(_data->_mutex);
        vTaskResume(_data->_handle);
        _data->_signal = _TaskSignal::RUN;
    }
}

void BaseAsyncTask::join()
{
    if (!_data)
        return;
    
    while(true)
    {
        Lock guard(_data->_mutex);
        auto stop = _data->deleted;
        if (stop)
            break;
    }
}

AsyncTask<>::AsyncTask():
    AsyncTask(TaskParams(), nullptr) {}

AsyncTask<>::AsyncTask(_TaskType task):
    AsyncTask(TaskParams(), task) {}

AsyncTask<>::AsyncTask(const TaskParams& params):
    AsyncTask(params, nullptr) {}

AsyncTask<>::AsyncTask(const TaskParams& params, _TaskType task):
    BaseAsyncTask(params), _task(task) {}

AsyncTask<>::AsyncTask(const AsyncTask& other)
{
    *this = other;
}

AsyncTask<>& AsyncTask<>::setParams(const TaskParams& params)
{
    _params = params;
    return *this;
}

AsyncTask<>& AsyncTask<>::setTask(_TaskType task)
{
    _task = task;
    return *this;
}


void AsyncTask<>::run()
{
    if (!_task)
        return;

    _data.reset(new _AsyncTaskData());
    if(_params.usePinnedCore)
    {
        xTaskCreatePinnedToCore(
            _taskWrapper<>, _params.name.c_str(), _params.stackSize,
            copy(), _params.priority, &_data->_handle, _params.core
        );
        return;
    }
    xTaskCreate(
        _taskWrapper<>, _params.name.c_str(), _params.stackSize,
        copy(), _params.priority, &_data->_handle
    );
    _async_handle = &_data->_handle;
}

void AsyncTask<>::operator()()
{
    run();
}

void AsyncTask<>::_runTask()
{
    if(_task)
    {
        _task();
    }
}

AsyncTask<>& AsyncTask<>::operator=(const AsyncTask<>& other)
{
    _params = other._params;
    _task = other._task;
    return *this;
}

AsyncTask<>* AsyncTask<>::copy() const
{
    auto ptr = new AsyncTask<>(*this);
    ptr->_data = _data;
    return ptr;
}


END_TASKS_NAMESPACE

