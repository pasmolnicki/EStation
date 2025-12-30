#include "config.h"

auto USE_CUSTOM_FONT = false;

extern TFT_eSPI tft = TFT_eSPI();

/**
 * ### Disclaimer
 * CUSTOM FONTS AREN'T CURRENTLY USED
 * 
 * When changing variable names here, you must also alter them in the /data_structures/Props.h
 * `char* useFont(const fonts& font)` function, since all view screens use it to load fonts.
*/
auto TITLE_FONT = "Ubuntu35";
auto DETAIL_FONT = "UbuntuLight18";
auto NORMAL_FONT = "UbuntuLight26";
auto CLOCK_FONT = "UbuntuLight38";

const String FILE_EXTENTION = ".vlw";

void init(){
    Serial.begin(115200);
    tft.init();
    tft.setRotation(3);
}

void config(){
    Serial.println("\n----------------------------------------");
    Serial.println("\t\tCONFIG");

    if(SPIFFS.begin(true)){
        fs::FS fs = SPIFFS;
        fs::File root = fs.open("/");
        if(!root){
            Serial.println("Failed to open directory: /");
            return;
        }

        auto file = root.openNextFile();

        std::vector<String> compare {
            TITLE_FONT + FILE_EXTENTION,
            DETAIL_FONT + FILE_EXTENTION,
            NORMAL_FONT + FILE_EXTENTION,
            CLOCK_FONT + FILE_EXTENTION,
        };
        std::vector<String> all_files;

        bool found = true;
        Serial.println("Looking for files: ");
        const int _compareSize = compare.size();

        for (int i = 0; i < _compareSize; i++){
            Serial.print(compare[i] + " ");
        }
        Serial.println("\nListing other files: ");

        // Find custom font file name
        while(file){
            if (!file.isDirectory()){
                Serial.printf("\t %s %d bytes \n", file.name(), file.size());
                all_files.push_back(file.name());
            }
            else{
                root = fs.open(file.name());
                if (!root){
                    Serial.printf("Failed to open directory: %s", file.name());
                    break;
                }
            }
            file = root.openNextFile(); 
        }

        const int _filesLen = all_files.size();
        String not_found;
        for (int i = 0; i < _compareSize; i++){
            bool find = false;
            for (int j = 0; j < _filesLen; j++){
                if (all_files[j] == compare[i]){
                    find = true;
                    break;
                }
            }
            if (!find){
                found = false;
                not_found = compare[i];
                break;
            }
        }

        if (found){
            USE_CUSTOM_FONT = true;
            Serial.println("\nAll files successfully found.");
        }
        else{
            Serial.println("\nCould not find file: " + not_found);
        }
    }
    else{
        Serial.println("SPIFFS initialisation failed. Using standard fonts");
    }
    USE_CUSTOM_FONT = false; // Currently not using custom fonts
}