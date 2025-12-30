#ifndef HSV_TO_RGB_H
#define HSV_TO_RGB_H

#define TEMP_RANGE 35

#include <Arduino.h>

class HSV
{
public:
    float hue;
    float satrutaion;
    float value;
};

inline uint32_t to_rgb(uint8_t r, uint8_t g, uint8_t b)
{
    uint32_t RGB;
    r = (r >> 3);
    g = (g >> 2);
    b = (b >> 3);

    RGB = RGB | (r << 11);
    RGB = RGB | (g << 5);
    RGB = RGB | (b);

    return RGB;
}

inline uint32_t HSV_RGB(HSV& color)
{
    float s = color.satrutaion / 100;
    float v = color.value / 100;

    float C = s * v;
    float X = C * (1 - abs(fmod(color.hue / 60, 2) - 1));
    float m = v - C;

    float r, g, b;

    switch((int)color.hue / 60){
        case 0: // < 60
            r = C, g = X, b = 0;
            break;
        case 1: // < 120
            r = X, g = C, b = 0;
            break;
        case 2: // < 180
            r = 0, g = C, b = X;
            break;
        case 3: // < 240
            r = 0, g = X, b = C;
            break;
        case 4: // < 300
            r = X, g = 0, b = C;
            break;
        default: // <= 360
            r = C, g = 0, b = X;
    }

    return to_rgb(
        (r + m) * 255,
        (g + m) * 255,
        (b + m) * 255);
}

inline uint16_t convert_to_idx(int16_t t)
{
    int16_t temp = t + 10;
    temp = temp > TEMP_RANGE ? TEMP_RANGE : temp;
    temp = temp < 0 ? 0 : temp;
    return temp;
}

inline uint16_t* create_grayscale(uint16_t items, HSV hsv) {
    uint16_t *scale = new uint16_t[items];
    float itr = 90.0f / static_cast<float>(items);
    hsv.value = 100;

    for (uint16_t i = 0; i < items; i++) {
        *scale = HSV_RGB(hsv);
        hsv.value -= itr;
        scale++;
    }
    scale -= items;
    return scale;
}

inline uint16_t *set_text_colors()
{
    uint16_t *temp_text_colors = new uint16_t[TEMP_RANGE];
    HSV *hsv = new HSV;

    hsv->hue = 0;
    hsv->satrutaion = 47;
    hsv->value = 100;

    float itr = (float)250 / TEMP_RANGE;

    for (int8_t t = TEMP_RANGE - 1; t >= 0; t--)
    {
        temp_text_colors[t] = HSV_RGB(*hsv);
        hsv->hue += itr;
    }

    delete hsv;
    return temp_text_colors;
}

inline uint16_t get_text_color(int16_t temp, uint16_t *temp_text_colors)
{
    return temp_text_colors[convert_to_idx(temp)];
}

#endif