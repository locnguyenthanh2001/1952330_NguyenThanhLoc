/* Hello World Example

   This example code is in the Public Domain (or CC0 licensed, at your option.)

   Unless required by applicable law or agreed to in writing, this
   software is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
   CONDITIONS OF ANY KIND, either express or implied.
*/
#include <stdio.h>
#include "sdkconfig.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_system.h"
#include "esp_spi_flash.h"
#include <esp_event.h>
#include <esp_event_loop.h>
#include <esp_wifi.h>
#include <esp_err.h>
#include <nvs_flash.h>
#include <tcpip_adapter.h>


#define STA_PASSWORD "Loc05062001"
#define AP_PASSWORD "thaonhi04072001"




//-----------------Access Point-----------------//
// int app_main ( void ){
//     nvs_flash_init();
//     tcpip_adapter_init();
//     wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT();
//     ESP_ERROR_CHECK(esp_wifi_init(&cfg)) ;
//    ESP_ERROR_CHECK( esp_wifi_set_mode(WIFI_MODE_AP)) ;
//    wifi_config_t apConfig = {
//     .ap = {
//         .ssid ="Xiaohu",
//         .ssid_len =0 ,
//         .password = AP_PASSWORD,
//         .channel =0 ,
//         .authmode = WIFI_AUTH_OPEN ,
//         .ssid_hidden =0 ,
//         .max_connection =4 ,
//         .beacon_interval =100
//         }
//     };
//     esp_wifi_set_config(WIFI_IF_AP, &apConfig);
//     ESP_ERROR_CHECK(esp_wifi_start());
//     while(1){vTaskDelay(3000/portTICK_RATE_MS);}
//     return 0;
// }


//-----------------Station-----------------//
int app_main ( void ){
    nvs_flash_init();
    tcpip_adapter_init();
    wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT();
    ESP_ERROR_CHECK(esp_wifi_init(&cfg));
    ESP_ERROR_CHECK( esp_wifi_set_mode(WIFI_MODE_STA)) ;
    wifi_config_t sta_config = {
        .sta = {
            .ssid = "SoftDrink56", 
            .password = STA_PASSWORD,
            .bssid_set = 0
            }
    };
    ESP_ERROR_CHECK(esp_wifi_set_config(ESP_IF_WIFI_STA , &sta_config));
    ESP_ERROR_CHECK(esp_wifi_start());
    printf("Connecting...!\n");
    ESP_ERROR_CHECK(esp_wifi_connect());
    while(1){vTaskDelay(3000/portTICK_RATE_MS);}
    return 0;
}
