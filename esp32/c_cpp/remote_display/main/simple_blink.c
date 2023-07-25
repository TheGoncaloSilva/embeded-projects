#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "esp_log.h"

#define PIN 2

/* Start by making a simple program that interacts with the I2C 
 * to create characters
*/

void operate_led(){

    gpio_reset_pin(PIN);
    gpio_set_direction(PIN, GPIO_MODE_OUTPUT);
    while (1)
    {
        gpio_set_level(PIN, 1);
        vTaskDelay(1000 / portTICK_PERIOD_MS); // sleep task for 1s and let's other tasks execute in background
        gpio_set_level(PIN,0);
        vTaskDelay(1000 / portTICK_PERIOD_MS); // sleep task for 1s and let's other tasks execute in background
        /* 
        * vTaskDealy doesn't delay for seconds or milliseconds, but for tick cycles not clock cycles
        * Tick cycles are the counters frequency.
        * So we neeed to divide by the conversion rate of sys ticks and milliseconds
        */
    }
}



void change_to_app_main(void)
{
    char *task = pcTaskGetName(NULL);

    ESP_LOGI(task, "Hello, starting program");
    operate_led();
}

