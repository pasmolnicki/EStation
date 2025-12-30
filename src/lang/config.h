#pragma once

/*

Folder /data contains font file, which is used in this project (not obligatory though).

To install it to ESP SPIFFS, simply download (If you haven't already) Arduino Plugin: Sketch Data Upload for ESP32 - ESP32FS

Then in Arudino IDE, open ESP-Chess.ino, then navigate to Tools > ESP32 Sketch Data Upload (look at the top bar).
If the file was uploaded sucessfully, then you are ready to upload the project.

If you don't have this file uploaded, it will detect that, and will use standard fonts, 
provided by amazing library TFT_eSPI by bodmer.

*/



#include <TFT_eSPI.h>
#include "./localizers/Localizer.h"

#include <vector>

/// @brief Initialize TFT_eSPI library
void init();

/// @brief Runs font file config, doesn't do anything right now
void config();