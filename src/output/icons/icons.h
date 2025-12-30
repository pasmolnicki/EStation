#pragma once

#include "icon.h"
#include "flags/flags.h"

namespace ui
{
    class SettingsIcon : public Icon
    {
    public:
        void
        draw(
            int16_t x, int16_t y,
            int16_t size, uint16_t color,
            uint16_t bg
        );
    };

    class GoBackIcon : public Icon
    {
    public:
        void
        draw(
            int16_t x, int16_t y,
            int16_t size, uint16_t color,
            uint16_t bg
        );
    };

    class GoForwardIcon : public Icon
    {
    public:
        void
        draw(
            int16_t x, int16_t y,
            int16_t size, uint16_t color,
            uint16_t bg
        );
    };

    class ExpandIcon : public Icon
    {
    public:
        void
        draw(
            int16_t x, int16_t y,
            int16_t size, uint16_t color,
            uint16_t bg
        );
    };

    class CapsLockIcon : public Icon
    {
    public:
        void
        draw(
            int16_t x, int16_t y,
            int16_t size, uint16_t color,
            uint16_t bg
        );
    };

    class DeleteIcon : public Icon
    {
    public:
        void
        draw(
            int16_t x, int16_t y,
            int16_t size, uint16_t color,
            uint16_t bg
        );
    };

    class ExitIcon : public Icon
    {
    public:
        void draw(
            int16_t x, int16_t y,
            int16_t size, uint16_t color,
            uint16_t bg
        );
    };

    class TrashIcon : public Icon
    {
    public:
        void
        draw(
            int16_t x, int16_t y,
            int16_t size, uint16_t color,
            uint16_t bg
        );
    };

    class RefreshIcon: public Icon
    {
    public:
        void 
        draw(
            int16_t x, int16_t y,
            int16_t size, uint16_t color,
            uint16_t bg
        );
    };

    class WiFiStrongIcon : public Icon
    {
    public:
        void
        draw(
            int16_t x, int16_t y,
            int16_t size, uint16_t color,
            uint16_t bg
        );
    };

    class WiFiGreatIcon: public Icon
    {
    public:
        void
        draw(
            int16_t x, int16_t y,
            int16_t size, uint16_t color,
            uint16_t bg
        );
    };

    class WiFiMediumIcon : public Icon
    {
    public:
        void
        draw(
            int16_t x, int16_t y,
            int16_t size, uint16_t color,
            uint16_t bg
        );
    };

    class WiFiWeakIcon : public Icon
    {
    public:
        void
        draw(
            int16_t x, int16_t y,
            int16_t size, uint16_t color,
            uint16_t bg
        );
    };

    class WiFiLostIcon : public Icon
    {
    public:
        void
        draw(
            int16_t x, int16_t y,
            int16_t size, uint16_t color,
            uint16_t bg
        );
    };

    class LockerLocked : public Icon
    {
    public:
        void
        draw(
            int16_t x, int16_t y,
            int16_t size, uint16_t color,
            uint16_t bg
        );
    };

    class LockerUnlocked : public Icon
    {
    public:
        void
        draw(
            int16_t x, int16_t y,
            int16_t size, uint16_t color,
            uint16_t bg
        );
    };

    class DropletEmpty : public Icon
    {
    public:
        void
        draw(
            int16_t x, int16_t y,
            int16_t size, uint16_t color,
            uint16_t bg
        );
    };

    class DropletSmall : public Icon
    {
    public:
        void
        draw(
            int16_t x, int16_t y,
            int16_t size, uint16_t color,
            uint16_t bg
        );
    };

    class DropletMedium : public Icon
    {
    public:
        void
        draw(
            int16_t x, int16_t y,
            int16_t size, uint16_t color,
            uint16_t bg
        );
    };

    class DropletHigh : public Icon
    {
    public:
        void
        draw(
            int16_t x, int16_t y,
            int16_t size, uint16_t color,
            uint16_t bg
        );
    };

    class DropletFull : public Icon
    {
    public:
        void
        draw(
            int16_t x, int16_t y,
            int16_t size, uint16_t color,
            uint16_t bg
        );
    };
}