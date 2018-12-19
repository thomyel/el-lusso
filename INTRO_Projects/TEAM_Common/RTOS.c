/**
 * \file
 * \brief Real Time Operating System (RTOS) main program.
 * \author Erich Styger, erich.styger@hslu.ch
 */

#include "Platform.h"
#if PL_CONFIG_HAS_RTOS
#include "RTOS.h"
#include "FRTOS1.h"
#include "Event.h"
#include "Application.h"
#include "LED.h"
#include "KeyDebounce.h"

void RTOS_Init(void) {
	/*! \todo Create tasks here */
#if 0 /*---------------Begin Lab 19---------------*/
/* Task Creation a Blinky LED */
	BaseType_t res; 					/* local Variables */
	xTaskHandle taskHndl; 				/* local taskHandler */

	res = xTaskCreate(BlinkyTask, 		/* Task Function commit to local variables
										with required parameters, Function Name */
			"Blinky", 					/* Debug Name (for Kernel) */
			configMINIMAL_STACK_SIZE + 50, /* Stack size */
			(void*) NULL, 				/* Optional task parameter or NULL */
			tskIDLE_PRIORITY + 1, 		/* Task priority */
			&taskHndl); 				/* Optional Task handling or NULL */

	/*The task creation wasn't successful (nicht genügend Speicher?))? -> error Handling*/
	if (res != pdPASS) { /*error handling here*/}
	vTaskStartScheduler(); 				/* Start Scheduler */
#endif /*---------------End Lab 09---------------*/
}

void RTOS_Deinit(void) {
	/* nothing needed for now */
}

#endif /* PL_CONFIG_HAS_RTOS */
