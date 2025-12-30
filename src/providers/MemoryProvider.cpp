#include "MemoryProvider.h"

extern MemoryProvider memoryProvider = MemoryProvider();

// Get the global instance of the MemoryProvider
MemoryProvider& MemoryProvider::getInstance(){
    return memoryProvider;
}

MemoryProvider::MemoryProvider(): _safe(false) {}


/**
 * @brief Checks the integrity of the EEPROM, if reset is true, erases all data
 */
void MemoryProvider::checkIntegrity(bool reset){
    
    EEPROM.begin(eepromSize);

    if (reset){
        for (int i = networkStartAddress; i < eepromSize; i++){
            EEPROM.write(i, 0);
        }
       EEPROM.commit();
       EEPROM.end();
       return;
    }

    // Check sizes
    if (EEPROM.read(citiesStartAddress) > maxCitiesCount){
        EEPROM.write(citiesStartAddress, 0);
        EEPROM.commit();
    }

    if (EEPROM.read(networkStartAddress) > maxNetworks){
        EEPROM.write(networkStartAddress, 0);
        EEPROM.commit();
    }

    _safe = true;

    EEPROM.end();
}

/**
 * @brief Iterates over the locations stored in EEPROM, if the return value of the callback is false, stops iterating\
 * @warning EEPROM should be in transaction mode
 * @param callback Callback function to be called for each location
 */
void MemoryProvider::iterate_locations(location_callback_t callback)
{
    auto size = EEPROM.read(citiesStartAddress);

    for (int i = 0, addr = citiesStartAddress; 
            i < size && i < maxCitiesCount && addr <= eepromSize; 
                addr += 2 + citiesMaxLen)
    {
        auto location = EEPROM.readString(addr + 2);

        // Memory might be fragmented, because of erasing, checking if that's a valid location
        if (location.isEmpty()){
            continue;
        }

        auto index = EEPROM.read(addr + 1);
        if (!callback(index, location, addr)){
            break;
        }
    }
}

/**
 * @brief Iterates over the networks stored in EEPROM, if the return value of the callback is false, stops iterating
 * @warning EEPROM should be in transaction mode
 * @param callback Callback function to be called for each network
 */
void MemoryProvider::iterate_networks(network_callback_t callback)
{
    auto size = EEPROM.read(networkStartAddress);

    for (int i = 0, addr = networkStartAddress + 1; 
            i < size && i < maxNetworks && addr < citiesStartAddress; 
                addr += 2 + networkSsidMaxLen + networkPassMaxLen)
    {
        auto ssid = EEPROM.readString(addr);
        // Memory might be fragmented, because of erasing, checking if that's a valid ssid
        if (ssid.isEmpty()){
            continue;
        }

        auto pass = EEPROM.readString(addr + networkSsidMaxLen + 1);
        if (!callback(ssid, pass, addr)){
            break;
        }
    }
}

/**
 * @brief Checks if the network and cities count is valid
 * @param erase if true, erase corrupted data to preserve functionality
 * @return MEMORY_OK if memory is valid, otherwise returns a bitwise OR of the errors
 */
int MemoryProvider::isValid(bool erase)
{
    int error = MEMORY_OK;
    EEPROM.begin(eepromSize);

    // Check sizes
    auto n_cities = EEPROM.read(citiesStartAddress);

    if (n_cities > maxCitiesCount){
        error |= BIG_CITIES_COUNT;

        if (erase)
            EEPROM.write(citiesStartAddress, 0);
    }

    // Assert the cities names' length is valid
    int valid_cities = 0;
    std::vector<int> cities_to_erase;

    // Check if the cities names are valid
    iterate_locations(
        [&valid_cities, &cities_to_erase](int city_index, String location, int addr){
            if (location.length() > citiesMaxLen || city_index > 4)
                cities_to_erase.push_back(addr);
            else 
                valid_cities++;

            Serial.println(location + " " + String(city_index) + " " + String(addr));
            return true;
    });

    // Check if the number of valid cities is equal to the number of cities
    if (valid_cities != n_cities){
        error |= MISMATCH_CITIES_COUNT;
    }

    // Read networks
    auto n_networks = EEPROM.read(networkStartAddress);

    // Check if the number of network is correct
    if (n_networks > maxNetworks){
        error |= BIG_NETWORKS_COUNT;

        if (erase)
            EEPROM.write(networkStartAddress, 0);
    }

    int valid_networks = 0;
    std::vector<int> networks_to_erase;

    // Check if the networks are valid
    iterate_networks(
        [&valid_networks, &networks_to_erase](String ssid, String pass, int addr){
            if (ssid.length() > networkSsidMaxLen || pass.length() > networkPassMaxLen)
                networks_to_erase.push_back(addr);        
            else
                valid_networks++;

            Serial.println(ssid + " " + pass + " " + String(addr));
            return true;
    });

    // Check if the number of valid networks is equal to the number of networks
    if (valid_networks != n_networks){
        error |= MISMATCH_NETWORKS_COUNT;
    }

    // Erase invalid networks / cities
    if (erase)
    {
        // Write the new number of networks / cities
        EEPROM.write(citiesStartAddress, valid_cities);
        EEPROM.write(networkStartAddress, valid_networks);

        // Erase the invalid networks / cities
        for (auto addr : cities_to_erase){
            EEPROM.writeString(addr + 2, "");
            EEPROM.write(addr + 1, 0);
        }

        for (auto addr : networks_to_erase){
            EEPROM.writeString(addr, "");
            EEPROM.writeString(addr + networkSsidMaxLen + 1, "");
        }

        EEPROM.commit();
    }

    EEPROM.end();

    return error;
}

/**
 * @brief Returns the errors as a vector of strings
 * @param err Error code (bitwise OR of the MemoryError enum)
 * @return Vector of strings with the errors
 */
std::vector<String> MemoryProvider::getErrors(int err){
    std::vector<String> errors;
    errors.reserve(4);

    if (err & BIG_CITIES_COUNT)
        errors.push_back("Too many cities saved");
    if (err & BIG_NETWORKS_COUNT)
        errors.push_back("Too many networks saved");
    if (err & MISMATCH_CITIES_COUNT)
        errors.push_back("Mismatch between saved and actual number of cities");
    if (err & MISMATCH_NETWORKS_COUNT)
        errors.push_back("Mismatch between saved and actual number of networks");

    return errors;
}

/**
 * @brief Reads location data from EEPROM
 */
void MemoryProvider::readLocations(){
    /* 
    
    By default: (Same for networks, but instead of index, there is String with ssid)

     (start)          <------  20  ----->
    |  468  |  469  |  470  | ... |  490  |  491  |  492  | ... |  512  |
       ^^^     ^^^     ^^^           ^^^     ^^^     ^^^           ^^^
    number    index   start         last     index   start         last
    of saved (uint8)  of loc.       char             loc.          char
    loc.              name          of loc.          name           (0)
    (ex. 2)                          name (0)
    */

    if (!_safe){
        checkIntegrity();
    }

    EEPROM.begin(eepromSize);
    _location.clear();
    _location.assign(
        std::min<int>(EEPROM.read(citiesStartAddress), maxCitiesCount), 
        std::pair<String, uint8_t>("null", 0)
    );

    location_list_t* locations_ptr = &_location;
    int i = 0;

    // Read the locations from EEPROM
    iterate_locations(
        [&locations_ptr, &i](int index, String location, int addr){
            locations_ptr->at(i).first = location;
            locations_ptr->at(i).second = index;
            i++;
            return true;
    });

    EEPROM.end();
}

/**
 * @brief Reads network data from EEPROM
 */
void MemoryProvider::readNetworks(){
    if (!_safe){
        checkIntegrity();
    }

    EEPROM.begin(eepromSize);

    // auto size = EEPROM.read(networkStartAddress);
    _networks.clear();
    _networks.assign(
        std::min<int>(EEPROM.read(networkStartAddress), maxNetworks), 
        std::pair<String, String>("null", "null")
    );

    network_list_t* networks_ptr = &_networks;
    int i = 0;

    // Read the networks from EEPROM
    iterate_networks(
        [&networks_ptr, &i](String ssid, String pass, int addr){
            networks_ptr->at(i).first = ssid;
            networks_ptr->at(i).second = pass;
            i++;
            return true;
    });

    EEPROM.end();
}

std::vector<std::pair<String, int>>* MemoryProvider::
getLocations(){
    return &_location;
}

std::vector<std::pair<String, String>>* MemoryProvider::
getNetworks(){
    return &_networks;
}

/**
 * @brief Writes location data to EEPROM
 * @param loc Location to write
 * @param index Index of the location
 * @return true if the location was written successfully (there was enough space in EEPROM)
 */
bool MemoryProvider::
writeLocation(const String& loc, const int& index){

    if (loc.length() >= citiesMaxLen){
        return false;
    }

    if (!_safe){
        checkIntegrity();
    }

    EEPROM.begin(eepromSize);

    auto size = EEPROM.read(citiesStartAddress);
    bool written = false;

    // Serial.println("writing location... " + loc);
    for(int i = 0, addr = citiesStartAddress; addr < 512; addr += 2 + citiesMaxLen){

        if (!EEPROM.readString(addr + 2).isEmpty()){
            // Serial.printf("Blocking: %s %i \n", EEPROM.readString(addr + 2).c_str(), addr);
            continue;
        }

        // is empty
        EEPROM.write(addr + 1, index);
        EEPROM.writeString(addr + 2, loc);
        EEPROM.write(citiesStartAddress, size + 1);
        // Serial.printf("Successfuly written %i", EEPROM.commit());
        written = true;
        break;
    }

    EEPROM.end();
    return written;
}

/**
 * @brief Writes network data to EEPROM
 * @param ssid SSID of the network
 * @param pass Password of the network
 * @return true if the network was written successfully (there was enough space in EEPROM)
 */
bool MemoryProvider::
writeNetwork(const String& ssid, const String& pass){
    if (ssid.length() >= networkSsidMaxLen || pass.length() >= networkPassMaxLen){
        return false;
    }

    if (!_safe){
        checkIntegrity();
    }

    EEPROM.begin(eepromSize);

    auto size = EEPROM.read(networkStartAddress);
    bool written = false;

    for(int i = 0, addr = networkStartAddress + 1; addr < citiesStartAddress; addr += 2 + networkSsidMaxLen + networkPassMaxLen){

        if (!(EEPROM.readString(addr).isEmpty() || EEPROM.readString(addr) == ssid)){
            continue;
        }

        // is empty or already saved (updating pass)

        EEPROM.writeString(addr, ssid);
        EEPROM.writeString(addr + networkSsidMaxLen + 1, pass);
        EEPROM.write(networkStartAddress, size + 1);
        EEPROM.commit();
        written = true;
        break;
    }

    EEPROM.end();
    return written;
}

/**
 * @brief Erases location data from EEPROM, if the given value is found
 * @param loc Location to erase
 */
void MemoryProvider::eraseLocation(const String& loc){
    if (!_safe){
        checkIntegrity();
    }

    EEPROM.begin(eepromSize);

    auto size = EEPROM.read(citiesStartAddress);

    for(int addr = citiesStartAddress; addr <= 512; addr += 2 + citiesMaxLen){


        // Linear search for given location
        if (EEPROM.readString(addr + 2) != loc){
            continue;
        }

        // Found location, erasing it
        EEPROM.writeString(addr + 2, "");
        EEPROM.write(citiesStartAddress, size - 1);
        EEPROM.commit();
        break;
    }

    EEPROM.end();
}

/**
 * @brief Erases network data from EEPROM, if the given value is found
 * @param ssid SSID of the network to erase
 */
void MemoryProvider::eraseNetwork(const String& ssid){
    if (!_safe){
        checkIntegrity();
    }

    EEPROM.begin(eepromSize);

    auto size = EEPROM.read(networkStartAddress);

    for(int addr = networkStartAddress + 1; addr < citiesStartAddress; addr += 2 + networkPassMaxLen + networkSsidMaxLen){
        // Linear search for given ssid
        if (EEPROM.readString(addr) != ssid){
            continue;
        }

        // Found location, erasing it
        EEPROM.writeString(addr, "");
        EEPROM.write(networkStartAddress, size - 1);
        EEPROM.commit();
        break;
    }

    EEPROM.end();
}

/**
 * @brief Erases all locations stored in EEPROM
 */
void MemoryProvider::
resetLocations(){
    EEPROM.begin(eepromSize);

    for (int addr = citiesStartAddress; addr <= eepromSize; addr += 2 + citiesMaxLen){
        if (EEPROM.readString(addr + 2).isEmpty()){
            continue;
        }
        EEPROM.writeString(addr + 2, "");
    }
    EEPROM.write(citiesStartAddress, 0);
    EEPROM.commit();
    EEPROM.end();
}

/**
 * @brief Erases all networks stored in EEPROM
 */
void MemoryProvider::
resetNetworks(){
    EEPROM.begin(eepromSize);

    for(int addr = networkStartAddress + 1; addr < citiesStartAddress; addr += 2 + networkPassMaxLen + networkSsidMaxLen){
        // Search for valid networks
        if (EEPROM.readString(addr).isEmpty()){
            continue;
        }
        // Found network, erasing it
        EEPROM.writeString(addr, "");
    }
    EEPROM.write(networkStartAddress, 0);
    EEPROM.commit();
    EEPROM.end();
}

/**
 * @brief Gets value at given address, doesn't check the validity of the address
 */
uint8_t MemoryProvider::get(int addr){
    EEPROM.begin(eepromSize);
    auto val = EEPROM.read(addr);
    EEPROM.end();
    return val;
}

/**
 * @brief Sets value at given address, doesn't check the validity of the address
 */
void MemoryProvider::set(int addr, uint8_t val){
    EEPROM.begin(eepromSize);
    EEPROM.write(addr, val);
    EEPROM.commit();
    EEPROM.end();
}

/**
 * @brief Sets value at given address if it's different from the current one
 * @return true if value was set, false otherwise
 */
bool MemoryProvider::setIfDifferent(int addr, uint8_t val){
    EEPROM.begin(eepromSize);
    auto old = EEPROM.read(addr);
    if (old == val){
        EEPROM.end();
        return false;
    }
    EEPROM.write(addr, val);
    EEPROM.commit();
    EEPROM.end();
    return true;
}