#pragma once

#include "../output/icons/icons.h"

extern char* NORMAL_FONT;
extern char* DETAIL_FONT;
extern char* TITLE_FONT;
extern char* CLOCK_FONT;

template <class T>
T* createDefaultIfNull(T* __p){
    return __p ? __p : new T();
}

typedef struct{
    String ssid;
    String pass;
} WifiProps;

typedef struct{
    String location;
    String country;
    int index;
} LocationProps;

WifiProps& getWifiProps();
LocationProps& getLocationProps();

enum class direction{
    row,
    column
};

typedef struct {
    direction dir = direction::row;
    int x = 0;
    int y = 0;
    int spacing = 0;
} RenderProps;


enum class placement{
    start,
    middle,
    end
};

enum class fonts{
    detail,
    title,
    normal,
    clock
};

inline char* useFont(const fonts& font){
    switch(font){
        case fonts::detail:
            return DETAIL_FONT;
        case fonts::title:
            return TITLE_FONT;
        case fonts::clock:
            return CLOCK_FONT;
        default:
            return NORMAL_FONT;
    }
}


class Props
{
    public:
    Props(const placement&, uint16_t bg);
    Props(const Props& other);
    Props& operator=(const Props& other);

    placement location;
    int16_t x;
    int16_t y;
    uint16_t bg;
};

class TextProps: public Props
{
    public:
    TextProps(
        const String& text = "",
        const placement& = placement::start,
        const uint16_t& bg = TFT_BLACK,
        char* font = NORMAL_FONT,
        uint16_t color = TFT_LIGHTGREY
    );

    TextProps(
        const TextProps& other
    );

    TextProps& operator=(const TextProps& other);

    char* font;
    String text;
    uint16_t color;
};

class IconProps: public Props
{
    public:
    IconProps(
        ui::Icon* icon = nullptr,
        int16_t size = 30,
        uint16_t bg = TFT_BLACK,
        uint16_t color = TFT_WHITE,
        const placement& = placement::end
    );
    IconProps(const IconProps& other);
    IconProps& operator=(const IconProps& other);

    ~IconProps();

    ui::Icon* icon;
    int16_t size;
    uint16_t color;
};

void prepareButtonIconProps(
    int16_t x, int16_t y, 
    int16_t width, int16_t height, 
    IconProps* _icon_props
);

