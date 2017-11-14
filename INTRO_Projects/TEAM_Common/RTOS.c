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
	/*Task was created in Application.c File*/
	/* This function needs for a simple Task implementation - on beginning state*/
}


void RTOS_Deinit(void) {
  /* nothing needed for now */
}


#endif /* PL_CONFIG_HAS_RTOS */
