#pragma once

#include <Arduino.h>
#include <vector>
#include "EEPROM.h"

constexpr int eepromSize = 512;

constexpr int networkSsidMaxLen = 20;
constexpr int networkPassMaxLen = 20;

constexpr int citiesMaxLen = 20;
constexpr int maxCitiesCount = 2;
constexpr int citiesStartAddress = eepromSize - maxCitiesCount * (citiesMaxLen + 2); 

constexpr int networkStartAddress = 10;
constexpr int maxNetworks = 
    (citiesStartAddress - 1 - networkStartAddress) / (networkSsidMaxLen + networkPassMaxLen + 2);


constexpr int LANGUAGE_ADDR = 8,
              SYSTEM_ADDR = 9;

/// @brief Provides memory storage for locations and networks
class MemoryProvider
{
public:

    enum MemoryError {
        MEMORY_OK = 0,

        // Number of cities is bigger than maxCitiesCount
        BIG_CITIES_COUNT = 1, 

        // Same as INVALID_CITIES_COUNT, but for networks
        BIG_NETWORKS_COUNT = 2,

        // Means number of saved cities != actual number of cities
        MISMATCH_CITIES_COUNT = 4,

        // Same as MISMATCH_CITIES_COUNT, but for networks
        MISMATCH_NETWORKS_COUNT = 8
    };


    typedef std::vector<std::pair<String, int>> location_list_t;
    typedef std::vector<std::pair<String, String>> network_list_t;
    typedef std::function<bool(int, String, int)> location_callback_t;
    typedef std::function<bool(String, String, int)> network_callback_t;

    static MemoryProvider& getInstance();

    MemoryProvider();

    void 
    checkIntegrity(bool resetEeprom = false);

    int 
    isValid(bool earse = false);

    std::vector<String>
    getErrors(int err);

    void 
    readLocations();

    void 
    readNetworks();

    location_list_t*
    getLocations();

    /// @brief First -> ssid, second -> password
    network_list_t*
    getNetworks();

    bool 
    writeLocation(const String&, const int& index);

    bool 
    writeNetwork(const String& ssid, const String& pass);

    void 
    eraseNetwork(const String& ssid);

    void 
    eraseLocation(const String& loc);

    void 
    resetLocations();

    void 
    resetNetworks();

    uint8_t get(int addr);
    
    void set(int addr, uint8_t val);

    bool setIfDifferent(int addr, uint8_t val);

    void iterate_locations(
        location_callback_t callback
    );

    void iterate_networks(
        network_callback_t callback
    );

private:

    bool _safe;
    location_list_t _location;
    network_list_t _networks;
};