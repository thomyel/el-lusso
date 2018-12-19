/**
 * \file
 * \brief Semaphore usage
 * \author Erich Styger, erich.styger@hslu.ch
 *
 * Module using semaphores.
 */

/**
 * \file
 * \brief Semaphore usage
 * \author Erich Styger, erich.styger@hslu.ch
 *
 * Module using semaphores.
 */

#include "Platform.h" /* interface to the platform */
#if PL_CONFIG_HAS_SEMAPHORE
#include "FRTOS1.h"
#include "Sem.h"
#include "LED.h"

#if 0
static xSemaphoreHandle sem = NULL;

static void vSlaveTask(void *pvParameters) {
  /*! \todo Implement functionality */
	/* Slave Task with the required parameters */
	TickType_t xLastWakeTime = xTaskGetTickCount();
	for(;;){
		xSemaphoreTake(sem, 0);	/* Take the Semaphore */
		LEDPin2_NegVal(); /* toggle LED */
		vTaskDelayUntil(&xLastWakeTime, pdMS_TO_TICKS(1500));
	}						/* wait for 1.5s */
}
static void vMasterTask(void *pvParameters) {
  /*! \todo send semaphore from master task to slave task */
	// Master Task with the required parameters
	TickType_t xLastWakeTime = xTaskGetTickCount();
	for(;;){
		xSemaphoreGive(sem); /* Give the Semaphore */
		vTaskDelayUntil(&xLastWakeTime, pdMS_TO_TICKS(1500));
	}						/* wait for 1.5s */
}
#endif
void SEM_Deinit(void) {

}

/*! \brief Initializes module */
void SEM_Init(void) {
#if 0
	  // Task creation for SlaveTask - it takes the semaphore for LED Blink
	  if (xTaskCreate(vSlaveTask, "Slave Task", configMINIMAL_STACK_SIZE+100, NULL, tskIDLE_PRIORITY, NULL)!=pdPASS) {
		  for(;;) {} /* error? */
	  }//if (xTaskCreate)

	  //  Task creation for MasterSlave - it gives the semaphore to other Task --> SlaveTask
	  if (xTaskCreate(vMasterTask, "Master Task", configMINIMAL_STACK_SIZE+100, NULL, tskIDLE_PRIORITY, NULL)!=pdPASS) {
		  for(;;) {} /* error? */
	  }//if (xTaskCreate)

	  // Create a Binary Semaphore
	  sem = xSemaphoreCreateBinary();
	  if(sem == NULL){	// Check if the Sempahore exist, when no, then goes to endless-loop
		  for(;;) {} /* error handling */
	  }
#endif
}
#endif /* PL_CONFIG_HAS_SEMAPHORE */
