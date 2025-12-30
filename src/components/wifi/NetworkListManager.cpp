#include "NetworkListManager.h"


// Providers, global variables
extern WiFiProvider wifiProvider;
extern MemoryProvider memoryProvider;
extern WifiProps wifiProps;

namespace ui
{    
    static bool task_running = false;

    // Static function defitions
    void NetworkListManager::scanTask()
    {
        // Scan for networks
        Lock lock(getSemaphore(tasks::wifiScan));
        if (task_running)
            return;
        
        task_running = true;
        wifiProvider.scan();
        task_running = false;
    }

    void NetworkListManager::connectTask()
    {
        // Connect to the network
        Lock lock(getSemaphore(tasks::wifiConn));
        if (task_running)
            return;

        task_running = true;
        wifiProvider.connect();
        task_running = false;
    }

    void NetworkListManager::defaultOnClick(const WifiInfo&){}


    NetworkListManager::NetworkListManager(
        uint16_t x,
        uint16_t y,
        uint16_t w,
        uint16_t h,
        uint16_t bg
    ): 
        PosContainer(x, y, w, h),
        m_list(nullptr, x, y, w, h, bg),
        m_loading(
            x + (w - LOADING_ICON_SIZE) / 2, 
            y + (h - LOADING_ICON_SIZE) / 2, 
            LOADING_ICON_SIZE, bg
        ),
        m_task(scanTask)
    {
        // Create popup when trying to connect to a network
        m_list.setOnClickEvent(
            [&](const WifiInfo& chosen){
                // Set global ssid
                getWifiProps().ssid = chosen.ssid;

                // The network is not saved
                if(!chosen.isSaved){
                    m_onNotSavedEvent();
                    return;
                }

                // Try to connect to the network
                wifiProvider.begin(chosen.ssid, chosen.pass);
                AsyncTask<>(connectTask)
                    .setParams(TaskParams().setUsePinnedCore(true))
                    .run();

                // Create a popup to show the connection status
                constexpr auto popupWidth = 170, popupHeight = 100;
                ConnectPopup popup(
                    160 - popupWidth / 2, 
                    120 - popupHeight / 2, 
                    popupWidth, popupHeight, bg
                );
                popup.loop();

                // Call the event
                m_onConnectEvent(wifiProvider.connected());
            }
        );

        // Callback after the scan is finished, called on Core 0
        wifiProvider.setScanCallback([&](){
            auto wifis = wifiProvider.setScannedWifis()->wifis();
            
            // Read saved networks from memory
            memoryProvider.readNetworks();
            auto savedNetworks = memoryProvider.getNetworks();
            
            // Match the scanned networks with the saved ones
            for (int i = 0; i < wifis->size(); i++){
                for (int j = 0; j < savedNetworks->size(); j++){
                    if (wifis->at(i).ssid == savedNetworks->at(j).first){
                        wifis->at(i).isSaved = true;
                        wifis->at(i).pass = savedNetworks->at(j).second;
                    }
                }
            }

            // Update the list of networks
            m_list.setData(wifis);
        });
    }

    /**
     * @brief Scan for networks
     * @param loading If true, show the loading element
     */
    void NetworkListManager::runScan()
    {
        if (task_running)
            return;

        m_loading.setLoading(true);
        m_task.setTask(scanTask);
        m_task();
    }

    /**
     * @brief Sets the visibility of the loading element
     * @param loading If true, show the loading element, else hides it
     */
    void NetworkListManager::setLoading(bool loading)
    {
        m_loading.setLoading(loading);
        if (loading) {
            m_loading.draw();
        }
        else {
            m_loading.clear();
        }
    }

    /**
     * @brief Returns true if the scan task is running
     */
    bool NetworkListManager::isScanning() const
    {
        return task_running;
    }

    /**
     * @brief Joins the scan task
     */
    void NetworkListManager::preload()
    {
        m_task.join();
    }

    /**
     * @brief Draw the list of wifis
     */
    void NetworkListManager::draw()
    {
        m_list.draw();
    }

    /**
     * @brief Returns true if the element in list was clicked
     */
    bool NetworkListManager::eventListener(Point* touch) 
    {
        TryLock lock(getSemaphore(tasks::wifiScan), 2);
        if (!lock)
            return false;
        
        return m_list.eventListener(touch);
    }

    /**
     * @brief Update the state of the wifi list and loading element,
     * should be called frequently when scanning.
     */
    void NetworkListManager::updateState()
    {
        // Update the list of networks
        {
            TryLock lock(getSemaphore(tasks::wifiScan), 2);
            if (lock)
            {
                if (m_list.isUpdated()){ 
                    m_loading.setLoading(false);
                    m_loading.clear();
                }
                m_list.updateState();
            }
        }

        // Update the loading element
        m_loading.updateState();
    }

    // setters for events

    /**
     * @brief Sets the event for when trying to connect to a network, 
     * that's not saved in memory
     */
    void NetworkListManager::setOnNotSavedEvent(onBasicEvent event)
    {
        m_onNotSavedEvent = event;
    }

    /**
     * @brief Sets the event for when either the connection was successful or not.
     * The parameter in event indicates that (true = success, false = failure)
     */
    void NetworkListManager::setOnConnectEvent(onBoolEvent event)
    {
        m_onConnectEvent = event;
    }
}