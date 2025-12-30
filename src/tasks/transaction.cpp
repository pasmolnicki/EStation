#include "transaction.h"

static SemaphoreHandle_t taskWeatherUpdateMutex = xSemaphoreCreateMutex();
static SemaphoreHandle_t taskClockMutex = xSemaphoreCreateMutex();
static SemaphoreHandle_t taskWifiScanMutex = xSemaphoreCreateMutex();
static SemaphoreHandle_t taskWifiConnectMutex = xSemaphoreCreateMutex();
static SemaphoreHandle_t errorMutex = xSemaphoreCreateMutex();

SemaphoreHandle_t getSemaphore(const tasks& task){
    switch(task){
        case tasks::clock:
            return taskClockMutex;
        case tasks::wifiScan:
            return taskWifiScanMutex;
        case tasks::wifiConn:
            return taskWifiConnectMutex;
        case tasks::error:
            return errorMutex;
        default:
            return taskWeatherUpdateMutex;
    }
}
