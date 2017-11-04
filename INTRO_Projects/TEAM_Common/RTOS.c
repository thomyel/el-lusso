/**
 * \file
 * \brief Real Time Operating System (RTOS) main program.
 * \author Erich Styger, erich.styger@hslu.ch
 */

#include "Platform.h"
#if PL_CONFIG_HAS_RTOS
#include "RTOS.h"
#include "FRTOS1.h"
#include "Application.h"
#include "LED.h"

static void BlinkyTask(void *pvParameters) {

	/*//Blinky Task with vTaskDealy	 --> 	// - avoid starving other tasks
	for (;;) {							    // - set number of ticks from current tick count
		LED1_Neg();
		vTaskDelay(500/portTICK_PERIOD_MS);
	}//*/

	//Blinky Task with vTaskDelayUntil -->	// - avoid starving other tasks and stored the heap adress
	TickType_t xLastWakeTime = xTaskGetTickCount();				// - return current tick counter
	for(;;) {
		LED1_Neg();
		vTaskDelayUntil(&xLastWakeTime, 50/portTICK_PERIOD_MS); // - can delay from previous tick counter
	}//*/								//pdMS_TO_TICKS(50)		// - independent of task overhead
}

void RTOS_Init(void) {
  /*! \todo Create tasks here */

	BaseType_t res;
	xTaskHandle taskHndl;

	res = xTaskCreate(BlinkyTask, 	// Task Function
	"Blinky", 						// Debug Name (for Kernel)
	configMINIMAL_STACK_SIZE+50, 	// Stack size
	(void*)NULL, 					// Optional task parameter or NULL
	tskIDLE_PRIORITY, 				// Priority
	&taskHndl); 					// Task handling

	if (res !=pdPASS) { /*error handling here*/ }

	vTaskStartScheduler();			// Start Scheduler
}



void RTOS_Deinit(void) {
  /* nothing needed for now */
}

#endif /* PL_CONFIG_HAS_RTOS */
