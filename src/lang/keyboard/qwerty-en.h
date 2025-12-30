#pragma once

#include <Arduino.h>

constexpr int qwertySize = 27;

constexpr auto width = 30;
constexpr auto height = 45;
constexpr auto delWidth = 40;
constexpr auto delMarginRight = 27;
constexpr auto spaceWidth = 150;
constexpr auto marginTop = 2;

constexpr auto startX = 2;
constexpr auto startY = 240 - 4 * (height + marginTop) - marginTop;
constexpr auto lastRowY = 240 - 2*marginTop - height;

void inline buildQwertyEnLayout(int16_t& x, int16_t& y, int index){
    int marginLeft = 2;
    switch(index){
        case 9:
            x = 16; // (320 - 9 * (width (30) + marginLeft (2))) / 2 = 32 / 2 = 16
            y += height + marginTop;
            break;
        case 18:
            y += height + marginTop;
            x = delMarginRight; // (320 - 7 * width (30) - 8 * marginLeft(2) - delWidth) / 2 = 22 / 2 = 11
            break;
        case 25:
            y += height + marginTop;
            x = (320 - spaceWidth)*0.5f;
            break;
        default:
            x += width + marginLeft;
    }
}

const String qwertyEn[] = {
    "q", "w", "e", "r", "t", "y", "u", "i", "o", "p", // [9], y = 70
     "a", "s", "d", "f", "g", "h", "j", "k", "l",  // [18], y = 112
        "z", "x", "c", "v", "b", "n", "m", " " // delete button here, y = 154
        // "ABC",  "Space", "Capitalize", y = 196
};

const String qwertyEnCapitalized[] = {
    "Q", "W", "E", "R", "T", "Y", "U", "I", "O", "P",
     "A", "S", "D", "F", "G", "H", "J", "K", "L", 
        "Z", "X", "C", "V", "B", "N", "M", " "
};

const String qwertyEnSpecialChar[] = {
    "1", "2", "3", "4", "5", "6", "7", "8", "9", "0",
     "-", "@", "#", "%", "^", "$", "&", "*", "_",
        "!", ".", ",", "?", ";", "'", "/", " "
};

const String qwertyEnSwitchToChar = "ABC";
const String qwertyEnSwitchToSpecial = "123";
const String qwertyEnSpace = "Space";
