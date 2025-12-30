#pragma once

#include <WiFi.h>
#include <vector>
#include "../data_structures/WifiInfo.h"

class WiFiProvider
{
    typedef std::function<void(void)> Callback;

    String _ssid;
    String _pass;
    bool _startConnection;
    bool _startScan;
    int _scannedNetworks;
    Callback _scanCallback;
    Callback _connectCallback;
public:
    static WiFiProvider& getInstance();

    WiFiProvider();

    /// @brief Scans networks on the same core as the task is running on
    void
    scan();

    /// @brief Sets the callback function, which will be called after completing the scan
    /// @param  callback
    void 
    setScanCallback(Callback);

    /// @brief Sets the callback function, which will be called after successful connection to wifi
    /// @param  callback
    void 
    setConnectionCallback(Callback);

    /// @brief Copies from WiFi class info about wifi to vector
    /// @return this pointer
    WiFiProvider*
    setScannedWifis();

    /// @attention must be called after `setScannedWifis()`
    /// @return pointer to vector of scanned wifis
    std::vector<WifiInfo>*
    wifis();

    /// @brief Sets the ssid and password for the connection
    void
    begin(const String& ssid, const String& pass);

    /// @brief Connects to the wifi
    void
    connect();

    /// @return true if the connection is established
    bool 
    connected();

    void 
    reset();
};