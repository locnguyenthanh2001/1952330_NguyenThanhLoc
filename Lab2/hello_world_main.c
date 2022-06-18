#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "sdkconfig.h"


#define ESP_INR_FLAG_DEFAULT 0
#define CONFIG_BUTTON_PIN 0

//Prioritized Pre-emptive Scheduling with Time Slicing.
TaskHandle_t myTask1Handle = NULL;  ///ISR = NULL
TaskHandle_t myTask2Handle = NULL;
TaskHandle_t IdleHandle = NULL;




//Task 1(high, event)
void IRAM_ATTR button_isr_handler(void *arg)
{
	xTaskResumeFromISR(myTask1Handle);
}


void task1(void* arg)
{
	while(1)
	{
		vTaskSuspend(NULL);
		printf("Button presseed. TASK1 HIHI\n");


	}


}


//Task(2, continuously)
void task2(void* arg)
{
	int count = 1;
	while(1)
	{
		if(count == 1)
		{
			printf("Task2 Greeting \n");
		}
	}
}
//Taskidle(0, continously)
void idletask(void *arg){
	int count = 1;
	while(1)
	{
		if(count == 1)
			{
			printf("This is idle task \n");
			}
	}
}


int app_main()
{
//	xTaskCreate(task1, "task1", 4096, NULL, 10, &myTask1Handle);
	gpio_pad_select_gpio(CONFIG_BUTTON_PIN);
	//set the correct direction
	gpio_set_direction(CONFIG_BUTTON_PIN, GPIO_MODE_INPUT);

	gpio_set_intr_type(CONFIG_BUTTON_PIN, GPIO_INTR_NEGEDGE);
	gpio_install_isr_service(ESP_INR_FLAG_DEFAULT);
	gpio_isr_handler_add(CONFIG_BUTTON_PIN, button_isr_handler, NULL);


	//Create event task
	xTaskCreate(task1, "button_task", 4096, NULL, 10, &myTask1Handle);
	xTaskCreate(task2, "task2", 4096, NULL, 0, &myTask2Handle);
	xTaskCreate(idletask, "idle", 4096, NULL, 0, &IdleHandle);
  return 0;
}
