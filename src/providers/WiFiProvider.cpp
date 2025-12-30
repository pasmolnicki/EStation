#include "WiFiProvider.h"

extern WiFiProvider wifiProvider = WiFiProvider();

static std::vector<WifiInfo> _wifis = std::vector<WifiInfo>();

void doNothing(){
    return;
}

// Get the global instance of the WiFiProvider
WiFiProvider& WiFiProvider::getInstance(){
    return wifiProvider;
}

WiFiProvider::WiFiProvider(): _scanCallback(doNothing), _connectCallback(doNothing), _scannedNetworks(-1), _startScan(false) {}

void WiFiProvider::setScanCallback(Callback callback){
    _scanCallback = callback;
}

void WiFiProvider::setConnectionCallback(Callback callback){
    _connectCallback = callback;
}

void WiFiProvider::scan(){
    _startScan = true;
    _scannedNetworks = WiFi.scanNetworks();
    if (_scannedNetworks < 0){
        return;
    }
    setScannedWifis();
    _scanCallback();
    _startScan = false;
}

WiFiProvider* WiFiProvider::setScannedWifis(){
    if (_scannedNetworks < 0){
        return this;
    }
    _wifis.clear();
    _wifis.assign(_scannedNetworks, {String(), int8_t(0), false, String()});
    for (int i=0; i < _scannedNetworks; i++){
        _wifis.at(i) = {WiFi.SSID(i), int8_t(WiFi.RSSI(i)), false, String()};
    }
    return this;
}

std::vector<WifiInfo>*
WiFiProvider::wifis(){
    return &_wifis;
}

void WiFiProvider::
begin(const String& ssid, const String& pass){
    _ssid = ssid;
    _pass = pass;
    _startConnection = true;
}

void WiFiProvider::
connect(){
    if (!_startConnection){
        return;
    }
    WiFi.begin(_ssid.c_str(), _pass.c_str());
    WiFi.waitForConnectResult(10e3);
    _connectCallback();
    _startConnection = false;
}


bool WiFiProvider::
connected(){
    return WiFi.status() == WL_CONNECTED;
}

void WiFiProvider::reset(){
    WiFi.mode(WIFI_STA);
    WiFi.disconnect();
}