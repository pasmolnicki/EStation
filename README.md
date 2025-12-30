# EStation

EStation is a weather station for the ESP-32 microcontroller with an LCD display. It uses WiFi to fetch real-time weather data and shows it on a clean, easy-to-read interface. It's a great project for DIY enthusiasts or anyone who wants to build their own weather station.

## Key Features

- **Live Weather**: Shows current weather conditions.
- **Multi-language**: Comes with English and Polish support, and it's easy to add more.
- **Multithreading**: Uses the ESP-32's dual cores to fetch data without freezing the UI.
- **Locations**: Search for and save multiple locations.
- **WiFi Manager**: Connect to WiFi networks directly from the device.
- **Settings**: Change language and temperature units (C/F).
- **Screensaver**: Turns off the screen after inactivity to save power.
- **Error Handling**: Shows clear error messages if something goes wrong.

## Getting Started

### Prerequisites

- **Hardware**:
  - ESP-32 module with WiFi
  - LCD display with ILI9341 driver (320x240 resolution recommended)
- **Software**:
  - Arduino IDE (or similar)
  - ESP32 board support package
  - TFT_eSPI library by Bodmer

### Installation

1. **Get an API Key**: Sign up at [OpenWeatherMap](https://openweathermap.org/) and get a free API key.
2. **Download**: Clone or download this repository.
3. **Configure**: Open `src/client/WeatherClient.h` and paste your OpenWeatherMap API key.
4. **Upload**: Compile and upload the code to your ESP-32.

## Customization

### Adding New Languages

To add a new language, check the instructions in `src/lang/localizers/Localizer.h`. English and Polish are supported out of the box.

## License
MIT License. See `LICENSE` for details.