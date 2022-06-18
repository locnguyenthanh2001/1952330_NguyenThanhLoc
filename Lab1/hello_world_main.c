#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_wifi.h"
#include "esp_system.h"
#include "esp_event.h"
#include "nvs_flash.h"
#include "driver/gpio.h"



//define pin
#define ESP_INTR_FLAG_DEFAULT 0
#define CONFIG_BUTTON_PIN 0


int count = 0;

void identifier(void* args)
{

	printf("1952330_Nguyen_Thanh_Loc\n");
	vTaskSuspend(NULL);
	vTaskDelay (1000 / portTICK_RATE_MS ) ;
}


TaskHandle_t ISR = NULL;

TaskHandle_t task1 = NULL;



void IRAM_ATTR button_isr_handler(void* arg) {

 xTaskResumeFromISR(ISR);
//portYIELD_FROM_ISR(  );
}

// task that will react to button clicks
 void button_task(void *arg)
{
 while(1){
	vTaskSuspend(NULL);
	printf("ESP32\n");
	}
}///////////////////////////////////////////////////////////////////

void app_main()
{

    gpio_pad_select_gpio(CONFIG_BUTTON_PIN);

  // set the correct direction
  gpio_set_direction(CONFIG_BUTTON_PIN, GPIO_MODE_INPUT);

  // enable interrupt on falling (1->0) edge for button pin
  gpio_set_intr_type(CONFIG_BUTTON_PIN, GPIO_INTR_NEGEDGE);


  //Install the drivers GPIO ISR handler service, which allows per-pin GPIO interrupt handlers.
  // install ISR service with default configuration
  gpio_install_isr_service(ESP_INTR_FLAG_DEFAULT);

  // attach the interrupt service routine
  gpio_isr_handler_add(CONFIG_BUTTON_PIN, button_isr_handler, NULL);


//Create and start stats task

xTaskCreate( button_task, "button_task", 4096, NULL , 10,&ISR );
while(1){
xTaskCreate(identifier, "task1", 4096, NULL , 10,&task1 );
vTaskDelay (1000 / portTICK_RATE_MS ) ;
}
}
