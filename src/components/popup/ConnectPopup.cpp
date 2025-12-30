#include "ConnectPopup.h"

extern WifiProps wifiProps;
extern WiFiProvider wifiProvider;

namespace ui
{

    static bool connectLoopCondition(uint32_t elapsed_ms){
        TryLock lock(getSemaphore(tasks::wifiConn), 2);
        if (!lock){
            return true;
        }
        return elapsed_ms < 5000 ? !wifiProvider.connected() : false;
    }

    ConnectPopup::ConnectPopup(
        int16_t x,
        int16_t y,
        int16_t w,
        int16_t h,
        uint16_t bg
    ): LoadingPopup(x, y, w, h, bg) {

        auto truncateProps = new TextProps(wifiProps.ssid, placement::middle, popupColor, useFont(fonts::detail));
        truncateProps->text = truncateText(truncateProps, 90);

        this
        ->addButton(
            new TextButton(170 / 2, 100 - 25, 
                new TextProps(getLocale()->CONNECTING + "...", placement::middle, popupColor, useFont(fonts::detail))
        ))
        ->addButton(
            new TextButton(170 / 2, 5, truncateProps
        ))
        ->setLoopConidition(connectLoopCondition);
    }
}