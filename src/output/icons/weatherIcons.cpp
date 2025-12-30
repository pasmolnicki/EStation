#include "weatherIcons.h"

extern TFT_eSPI tft;

namespace ui
{
    void SunIcon::draw(
        int16_t x, int16_t y,
        int16_t size, uint16_t color,
        uint16_t bg
    ){
        drawSun(x + 0.05f*size, y, size*0.9f, SUNNY, bg);
    }

    void MoonIcon::draw(
        int16_t x, int16_t y,
        int16_t size, uint16_t color,
        uint16_t bg
    ){
        drawMoon(x+0.05f*size,y,size*0.9f, MOON, bg);
    }

    void FewCloudsDayIcon::draw(
        int16_t x, int16_t y,
        int16_t size, uint16_t color,
        uint16_t bg
    ){
        drawSun(x + 0.05f*size, y, size*0.9f, SUNNY, bg);
        drawCloud(x+0.2f*size, y + 0.6f*size, 0.6f*size, MIST, CLOUDY, SUNNY, SUNNY, bg);
    }

    void FewCloudsNightIcon::draw(
        int16_t x, int16_t y,
        int16_t size, uint16_t color,
        uint16_t bg
    ){
        drawMoon(x + 0.1f*size, y, size*0.8f, MOON, bg);
        drawCloud(x+0.15f*size, y + 0.67f*size, 0.6f*size, MIST, CLOUDY, MOON, MOON, bg);
    }

    void CloudsDayIcon::draw(
        int16_t x, int16_t y,
        int16_t size, uint16_t color,
        uint16_t bg
    ){
        drawCloud(x,y+0.1f*size, 0.4f*size, CLOUDY, LIGHT_DARK_CLOUDS, bg, bg, bg);
        drawSun(x + 0.36f*size, y, size*0.6f, SUNNY, bg);
        drawCloud(x + 0.06f*size, y + 0.29f*size, 0.9f*size, MIST, CLOUDY, bg, SUNNY, bg);
    }

    void CloudsNightIcon::draw(
        int16_t x, int16_t y,
        int16_t size, uint16_t color,
        uint16_t bg
    ){
        drawMoon(x + 0.5f*size, y, size*0.4f, MOON, bg);
        drawCloud(x, y+0.1f*size, 0.4f*size, CLOUDY, LIGHT_DARK_CLOUDS, bg, bg, bg);
        drawCloud(x, y + 0.28f*size, 0.9f*size, MIST, CLOUDY, bg, MOON, bg);
    }

    void ManyCloudsIcon::draw(
        int16_t x, int16_t y,
        int16_t size, uint16_t color,
        uint16_t bg
    ){
        //on left
        drawCloud(x, y, 0.4f*size, CLOUDY, LIGHT_DARK_CLOUDS, bg, bg, bg);

        //on right
        drawCloud(x+0.34f*size,y+0.07f*size, 0.65f*size, LIGHT_DARK_CLOUDS, MIDDLE_DARK_CLOUDS, bg, bg, bg);

        //bottom
        drawCloud(x, y+0.25f*size, 0.9f*size, MIST, CLOUDY, bg, MIDDLE_DARK_CLOUDS, bg);
    }

    void StormIcon::draw(
        int16_t x, int16_t y,
        int16_t size, uint16_t color,
        uint16_t bg
    ){
        //Cloud drawing
        drawCloud(x, y, size, ALMOST_DARK_CLOUDS, DARK_CLOUDS,bg, bg, bg);

        // lightning drawing

        uint16_t ax = x+0.5f*size,
                ay = y + 0.2f*size,
                bx = ax - 0.05f*size,
                by = ay + 0.2f*size;
        tft.drawWideLine(ax, ay, bx, by, 0.05f*size, SUNNY, DARK_CLOUDS);

        ax = bx;
        ay = by;

        ax += 0.1f*size;
        by +=0.2f*size;
        bx += 0.05f*size;

        tft.drawWideLine(ax, ay, bx, by, 0.03f*size, SUNNY, bg);

        ax -= 0.02f*size;
        bx = ax;
        by = ay;
        ax -= 0.08f*size;
        
        tft.fillRect(ax, ay - 1, 0.1f*size, 0.04f*size, SUNNY);
    }

    void RainIcon::draw(
        int16_t x, int16_t y,
        int16_t size, uint16_t color,
        uint16_t bg
    ){
        //Cloud drawing

        drawCloud(x, y, size, CLOUDY,LIGHT_DARK_CLOUDS,bg, bg, bg);

        uint16_t ax = x + 0.3f*size,
                ay = y+0.45f*size,
                bx = ax - 0.07f*size,
                by = ay + 0.08f*size;

        for (uint8_t a = 0;a<3;a++)
        {
            tft.drawWideLine(ax,ay,bx,by, 0.03f*size, WATER, bg);
            ax += 0.2f*size;
            bx += 0.2f*size;
        }


        ay += 0.11f*size;
        ax = x+ 0.3f*size;
        bx = ax - 0.07f*size,
        by = ay + 0.08f*size;
        for (uint8_t a = 0;a<3;a++)
        {
            tft.drawWideLine(ax,ay,bx,by, 0.03f*size, WATER, bg);
            ax += 0.2f*size;
            bx += 0.2f*size;
        }
    }

    void BigRainIcon::draw(
        int16_t x, int16_t y,
        int16_t size, uint16_t color,
        uint16_t bg
    ){
        //Cloud drawing

        drawCloud(x, y, size, LIGHT_DARK_CLOUDS,MIDDLE_DARK_CLOUDS, bg, bg, bg);

        uint16_t ax = x + 0.3f*size,
                ay = y+0.45f*size,
                bx = ax - 0.15f*size,
                by = ay + 0.25f*size;

        for (uint8_t a = 0;a<3;a++)
        {
            tft.drawWideLine(ax,ay,bx,by,0.03f*size, WATER, bg);
            ax += 0.2f*size;
            bx += 0.2f*size;
        }
    }

    void SnowIcon::draw(
        int16_t x, int16_t y,
        int16_t size, uint16_t color,
        uint16_t bg
    ){
        drawCloud(x,y, size, CLOUDY, LIGHT_DARK_CLOUDS, bg, bg, bg);

        drawSnowflake(x + 0.3f*size, y+0.4f*size, size*0.4f, bg, SNOW_FLAKE, WATER);
    }

    void MistNightIcon::draw(
        int16_t x, int16_t y,
        int16_t size, uint16_t color,
        uint16_t bg
    ){
        drawMoon(x + 0.3f*size, y, size*0.65f, MOON, bg);
        drawMist(x+0.1f*size, y+ 0.1f*size, size*0.9f,MIST, bg);
    }

    void MistDayIcon::draw(
        int16_t x, int16_t y,
        int16_t size, uint16_t color,
        uint16_t bg
    ){
        drawSun(x + 0.2f*size, y, size*0.65f, SUNNY, bg);
        drawMist(x+0.1f*size, y+ 0.1f*size, size*0.9f,MIST, bg);
    }

    void SunriseIcon::draw(
        int16_t x, int16_t y,
        int16_t size, uint16_t color,
        uint16_t bg
    ){
        drawSunrise(x, y, size, bg);
    }

    void SunsetIcon::draw(
        int16_t x, int16_t y,
        int16_t size, uint16_t color,
        uint16_t bg
    ){
        drawSunset(x, y, size, bg);
    }
}