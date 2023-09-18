#include "main.h"

#define LOG_LEVEL_LOCAL ESP_LOG_VERBOSE
#include "esp_log.h"
#define LOG_TAG "MAIN"

// obligatory main esp32 (transform to C language)
extern "C" void app_main(void){
    while(true)
    {
        // "LOGI" for information message
        ESP_LOGI(LOG_TAG, "Hello World!");
        vTaskDelay(1000); // -> in ticks
    }
}