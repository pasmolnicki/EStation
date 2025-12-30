WiFi
- [x] wifiProvider
  - [x] task on core 0
  - [x] possiblity to hook callback on scan finish

Screens

- ChooseWifi
  - [x] add text at the start of the scan (changed to loading spinner)
  - [x] saved networks
  
- PasswordInput
  - [x] Keyboard
  - [x] input field
  
- LocationInput
  - Saved locations
    - [x] fetch detail data about locations
    - [x] add delete button
  - New location
    - [x] search bar 
    - [x] after entering location, up to 4 list elements of city names

- Loading Screen 
  - [x] Update weather
  - [x] Update clock
  
- Settings
  - [x] language screen
  - [x] metric system screen (temp: C, F)
  - [ ] saved networks
    - [ ] info window, with scroll
    - [ ] delete / modify options

- ErrorScreen
  - [x] output given error
  
- Main Screens
  - [x] HomeScreen
  - [ ] HistoryScreen (*probably won't be implemented*)
  - [x] Forecasted Weather



# Notes

The first release of this project. Has some basic functionalities, as well as few *cool features*.

Sketch size: 1 122 553 bytes (85%) (/ 1 310 720 bytes), *(964 765 bytes without APPID key specified ~ 73%)*

**July 6th 2024**
---
- [x] Added easy way to add new language
- [x] Reworked localizer code, added global `getLocale()` function 
- [x] New screen for detailed graph of the forecasted weather
- [x] Initial loading screen
- [x] Refinement of the UI (better colors, reworked icons)

Sketch size: 1 182 925 bytes (90%) (/ 1 310 720 bytes)

Fixed:
- [x] Random crashes on the ChooseWifi screen

## Features
- Current weather view
- **Next 9 hours forecast view**
- **Next 3 days forecast view**
- **Forecasted weather graph, detail view**
- Customizable settings:
  - language
  - unit system
- Location search
- Saving provided network passwords and locations
- **Saving user preferences (language & unit system)**
- Sleep screen, activating after 2 minutes of inactivity
- Verbose error screen, on Core 0 (backend) exception.


**April 22nd 2025**

- [x] Added verbose error messages on invalid eeprom memory layout, and fail on data fetch

- [ ] Added a settings screen in the Weather screen, to:
  - [ ] change the unit system
  - [ ] change the language
  - [ ] change network
  - [ ] manage saved networks

Created a bug: AsyncTask with template arguments does not run, (however, works fine without them)


## Known Issues
- Smooth fonts not fully supported