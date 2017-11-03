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
	for (;;) {
		LED1_Neg();
		vTaskDelay (500/ portTICK_PERIOD_MS) ;
	}
}

void RTOS_Init(void) {
  /*! \todo Create tasks here */
	BaseType_t res ;
	xTaskHandle taskHndl ;
	res = xTaskCreate(BlinkyTask, 	// f u n c t i o n
	"Blinky", 						// Kernel awareness name
	configMINIMAL_STACK_SIZE+50, // stack
	(void*)NULL, 		// task parameter
	tskIDLE_PRIORITY, 	// p r i o r i t y
	&taskHndl); 			// handle

	if (res !=pdPASS) { /* e r r o r handl ing here */ }

	vTaskStartScheduler();
}



void RTOS_Deinit(void) {
  /* nothing needed for now */
}

#endif /* PL_CONFIG_HAS_RTOS */
