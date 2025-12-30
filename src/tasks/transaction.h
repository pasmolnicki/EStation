#pragma once

#include <Arduino.h>

enum class tasks{
    weather,
    clock,
    wifi,
    wifiScan,
    wifiConn,
    error
};

/// @brief Get semaphore for given task
/// @param task name of the task
/// @return Semaphore handle
SemaphoreHandle_t getSemaphore(const tasks& task);