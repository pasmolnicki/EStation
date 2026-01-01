#include "src/router/Router.h"
#include "src/lang/config.h"
#include "src/output/initial-scene/loading.h"

Router router;
extern MemoryProvider memoryProvider;
extern Localizer localizer;
String CURRENT_VER = "1.1.0";

static SemaphoreHandle_t scene_mutex = xSemaphoreCreateMutex();
static bool keep_loading = true;

void asyncLoading(){
    for(;;){
        drawInitialSceneFrame();
        Lock lock(scene_mutex);
        if(!keep_loading){
            break;
        }
    }
}

void stopLoading(){
    Lock lock(scene_mutex);
    keep_loading = false;
}

void setupEerpom(){
    // Load language and system from memory (previously chosen by the user)
    auto lang = memoryProvider.get(LANGUAGE_ADDR);
    auto system = memoryProvider.get(SYSTEM_ADDR);

    // Quietly set the localizer to the default language and system
    if (lang < NUMBER_OF_LOCALIZERS || system < 3){
        localizer.setLocalizer((locales)lang);
        localizer.setUnitSystem((unitSystem)system);
    }

    // If the memory is corrupted, then erase it
    auto err = memoryProvider.isValid(true);
    if (err != MemoryProvider::MEMORY_OK) {
        String reason = "";
        auto errors = memoryProvider.getErrors(err);
        for (auto& e : errors) 
            reason += e + "\n";
        // Display error screen
        ui::makeErrorPage("EEPROM corrupted", reason);
    }
}

void setup(){
    // Initialize the display, prepare for the loading screen, and set up the localizer
    init();
    setupEerpom();
    initScene();
    drawInitialSceneFrame();

    // Create async task for loading screen, while the main thread is setting up
    AsyncTask<> task(
        TaskParams().setUsePinnedCore(true),
        asyncLoading
    );
    task();

    // config and preload screen
    config();
    router.preload();

    // Stop loading screen, after everything is loaded
    stopLoading();

    // Wait for the loading screen task to stop
    task.join();
}

void loop(){
    // Main loop
    router.loop();
}