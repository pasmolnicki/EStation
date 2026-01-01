#include "LoadingScreen.h"

extern WeatherProvider wProvider;
extern DateTimeProvider dateProvider;
extern ErrorProvider errorProvider;

extern LocationProps locProps;

// create a scheduler
auto scheduler = Scheduler();

namespace ui
{
    void createScheduler(){
        // Weather update task and clock update task
        scheduler.addTask([](){
                // Weather update task, updates the weather and forecast data
                Lock lock(getSemaphore(tasks::weather));
                Lock errorlock(getSemaphore(tasks::error));

                errorProvider.catchFn([](){
                    wProvider.update();
                });
                if (errorProvider.caught()){
                    errorProvider.log();
                    errorProvider.code(
                        String(__FILE__) + ":" + String(__LINE__) + " -> weather task"
                    );
                }
            },
            TaskParams().setUsePinnedCore(true), 
            ScheduleParams(5, TimeUnit::Minutes)
        ).addTask([](){
                // Clock task, simply adds a second to the time
                Lock lock(getSemaphore(tasks::clock));
                dateProvider.addSecond();
            }, 
            TaskParams().setUsePinnedCore(true), 
            ScheduleParams(1, TimeUnit::Seconds)
        ).run();
    }

    void clockUpdateTask(){
        Lock lock(getSemaphore(tasks::clock));
        Lock weatherLock(getSemaphore(tasks::weather));
        
        auto timezone = wProvider.weather()->_timezone;
        lock.unlock(); // unlock before fetching time
        dateProvider.init(timezone);
        while(!dateProvider.synced()){
            dateProvider.fetchTime();
            delay(300);
        }
    }

    void createWeatherUpdateTask(){
        Lock lock(getSemaphore(tasks::weather));
        Lock errorlock(getSemaphore(tasks::error));

        errorProvider.catchFn([&](){
            wProvider.update();
            while(!wProvider.synced()){
                wProvider.update();
                delay(300);
            }
        });

        if(errorProvider.caught()){
            errorProvider.log();
            errorProvider.code("LoadingScreen::LoadingScreen() -> weather task");
        }

        // create clock task
        AsyncTask<>(clockUpdateTask)
        .setParams(TaskParams().setUsePinnedCore(true))
        .run();
    }

    LoadingScreen::LoadingScreen():
    _spinner(new LoadingElement(160  - 100 / 2, 100 - 100 / 2, 100, BASE_SCREEN_BG)),
    _weatherLoaded(false) {
        _size = 2;

        auto locale = getLocale();

        _items = new TextElement*[_size] {
            new TextElement(160, 160, 
                new TextProps(locale->FETCHING_WEATHER_DATA + "...", placement::middle, BASE_SCREEN_BG, useFont(fonts::detail))),
            new TextElement(160, 190, 
                new TextProps(locale->FETCHING_TIME_DATA + "...", placement::middle, BASE_SCREEN_BG, useFont(fonts::detail))),
        };

        AsyncTask<>(createWeatherUpdateTask)
            .setParams(TaskParams().setUsePinnedCore(true))
            .run();
    }

    LoadingScreen::~LoadingScreen(){
        tft.fillScreen(BASE_SCREEN_BG);
        createScheduler();
    }

    void LoadingScreen::draw(){
        DataBaseScreen<TextElement>::draw();
        _spinner->draw();
    }

    void LoadingScreen::loop(){

        // setup touchscreen for sleep
        

        while(!_exited){
            _spinner->updateState();

            TryLock weather(getSemaphore(tasks::weather), 5);

            if (!weather){
                continue;
            }
            if (wProvider.synced() && !_weatherLoaded){
                _items[0]->setProps(
                    new TextProps(getLocale()->FETCHING_WEATHER_DATA + " OK", 
                        placement::middle, BASE_SCREEN_BG, useFont(fonts::detail), TFT_GREEN)
                );
                _items[0]->draw();

                // createClockTask();
                _weatherLoaded = true;
            }

            TryLock clock(getSemaphore(tasks::clock), 5);
            
            if (!clock){
                continue;
            }
            if (dateProvider.synced() && _weatherLoaded){
                _items[1]->setProps(
                    new TextProps(getLocale()->FETCHING_TIME_DATA + " OK", 
                        placement::middle, BASE_SCREEN_BG, useFont(fonts::detail), TFT_GREEN)
                );
                _items[1]->draw();
                route(path::HOME);
            }
        }
    }
}