/**
 * \file
 * \brief Main application file
 * \author Erich Styger, erich.styger@hslu.ch
 *
 * This provides the main application entry point.
 */

#define ROBO_USE_TEL	(1) /* Elmiger benutzt Robo*/
#define ROBO_USE_FLU	(0)	/* Lussi benutzt Robo */

#define LAB_09_LED (0)
#define LAB_13_EVENT_HANDLE (0)
#define LAB_15_KEYS (0)
#define LAB_18_DEBOUNCING (0)
#define LAB_19_FRTOS (0)
#define LAB_21_TASK (1)
#define LAB_27_SENSOR (1)
#define LAB_34_TURN (0)
#define LAB_xx_LINE_FOLLOWING (0)
#define LAB_SUMO (1)

#include "Platform.h"
#include "Application.h"
#include "Event.h"
#include "LED.h"
#include "WAIT1.h"
#include "CS1.h"
#include "KeyDebounce.h"
#include "CLS1.h"
#include "KIN1.h"
#if PL_CONFIG_HAS_KEYS
#include "Keys.h"
#endif
#if PL_CONFIG_HAS_SHELL
#include "CLS1.h"
#include "Shell.h"
#include "RTT1.h"
#endif
#if PL_CONFIG_HAS_BUZZER
#include "Buzzer.h"
#endif
#if PL_CONFIG_HAS_RTOS
#include "FRTOS1.h"
#include "RTOS.h"
#endif
#if PL_CONFIG_HAS_QUADRATURE
#include "Q4CLeft.h"
#include "Q4CRight.h"
#endif
#if PL_CONFIG_HAS_MOTOR
#include "Motor.h"
#endif
#if PL_CONFIG_HAS_TURN
#include "Turn.h"
#include "Drive.h"
#endif
#if PL_CONFIG_BOARD_IS_ROBO_V2
#include "PORT_PDD.h"
#endif
#if PL_CONFIG_HAS_LINE_FOLLOW
#include "LineFollow.h"
int race_mode = 1;
#endif
#if PL_CONFIG_HAS_LCD_MENU
#include "LCD.h"
#endif
#if PL_CONFIG_HAS_SNAKE_GAME
#include "Snake.h"
#endif
#if PL_CONFIG_HAS_REFLECTANCE
#include "Reflectance.h"
#endif
#include "Sumo.h"

#if PL_CONFIG_HAS_EVENTS

static void BtnMsg(int btn, const char *msg) {
#if PL_CONFIG_HAS_SHELL
#if PL_CONFIG_HAS_SHELL_QUEUE
	uint8_t buf[48];

	UTIL1_strcpy(buf, sizeof(buf), "Button pressed: ");
	UTIL1_strcat(buf, sizeof(buf), msg);
	UTIL1_strcat(buf, sizeof(buf), ": ");
	UTIL1_strcatNum32s(buf, sizeof(buf), btn);
	UTIL1_strcat(buf, sizeof(buf), "\r\n");
	SHELL_SendString(buf);
#else
	CLS1_SendStr("Button pressed: ", CLS1_GetStdio()->stdOut);
	CLS1_SendStr(msg, CLS1_GetStdio()->stdOut);
	CLS1_SendStr(": ", CLS1_GetStdio()->stdOut);
	CLS1_SendNum32s(btn, CLS1_GetStdio()->stdOut);
	CLS1_SendStr("\r\n", CLS1_GetStdio()->stdOut);
#endif
#endif
}



void APP_EventHandler(EVNT_Handle event) {
	/*! \todo handle events */
	switch (event) {
	case EVNT_STARTUP: {
		int i;
		for (i = 0; i < 5; i++) {
			LED1_Neg();
			WAIT1_Waitms(50);
		}
		LED1_Off();
	}
		break;
	case EVNT_LED_HEARTBEAT:
		LED1_Neg();
		break;
#if PL_CONFIG_NOF_KEYS>=1
	case EVNT_SW1_PRESSED:
		BtnMsg(1, "pressed");
		LED2_Neg();
		#if LAB_SUMO
		if (race_mode){
			race_mode = 0;
			SUMO_StartSumo();
		} else {
			SUMO_StopSumo();
			race_mode = 1;
		}
		#endif
		#if PL_CONFIG_HAS_LINE_FOLLOW && LAB_xx_LINE_FOLLOWING
		if (race_mode){
			race_mode = 0;
			LF_StartFollowing();
		} else{
			LF_StopFollowing();
			race_mode = 1;
		}
		#endif
		break;
	case EVNT_SW1_LPRESSED:
		BtnMsg(1, "long pressed");
		#if PL_CONFIG_HAS_BUZZER
			BUZ_Beep(600, 1000);
		#endif
		#if PL_CONFIG_HAS_MOTOR
			REF_CalibrateStartStop();
		#endif
		break;
	case EVNT_SW1_RELEASED:
		BtnMsg(1, "released");
		BUZ_Beep(1200, 500);
		break;
#endif

#if PL_CONFIG_NOF_KEYS>=2
		case EVNT_SW2_PRESSED:
		BtnMsg(2, "pressed");
		break;
		case EVNT_SW2_LPRESSED:
		BtnMsg(2, "long pressed");
		break;
		case EVNT_SW2_RELEASED:
		BtnMsg(2, "released");
		break;
#endif

#if PL_CONFIG_NOF_KEYS>=3
		case EVNT_SW3_PRESSED:
		BtnMsg(3, "pressed");
		break;
		case EVNT_SW3_LPRESSED:
		BtnMsg(3, "long pressed");
		break;
		case EVNT_SW3_RELEASED:
		BtnMsg(3, "released");
		break;
#endif
#if PL_CONFIG_NOF_KEYS>=4
		case EVNT_SW4_PRESSED:
		BtnMsg(4, "pressed");
		break;
		case EVNT_SW4_LPRESSED:
		BtnMsg(4, "long pressed");
		break;
		case EVNT_SW4_RELEASED:
		BtnMsg(4, "released");
		break;
#endif

#if PL_CONFIG_NOF_KEYS>=5
		case EVNT_SW5_PRESSED:
		BtnMsg(5, "pressed");
		break;
		case EVNT_SW5_LPRESSED:
		BtnMsg(5, "long pressed");
		break;
		case EVNT_SW5_RELEASED:
		BtnMsg(5, "released");
		break;
#endif

#if PL_CONFIG_NOF_KEYS>=6
		case EVNT_SW6_PRESSED:
		BtnMsg(6, "pressed");
		break;
		case EVNT_SW6_LPRESSED:
		BtnMsg(6, "long pressed");
		break;
		case EVNT_SW6_RELEASED:
		BtnMsg(6, "released");
		break;
#endif

#if PL_CONFIG_NOF_KEYS>=7
		case EVNT_SW7_PRESSED:
		BtnMsg(7, "pressed");
		break;
		case EVNT_SW7_LPRESSED:
		BtnMsg(7, "long pressed");
		break;
		case EVNT_SW7_RELEASED:
		BtnMsg(7, "released");
		break;
#endif
	default:
		break;
	} /* switch */
} /* APP_EventHandler */
#endif /* PL_CONFIG_HAS_EVENTS */

#if PL_CONFIG_HAS_MOTOR /* currently only used for robots */
static const KIN1_UID RoboIDs[] = {
/* 0: L34, V2 */{ { 0x00, 0x0E, 0x00, 0x00, 0x67, 0xCD, 0xB8, 0x21, 0x4E, 0x45, 0x32, 0x15, 0x30, 0x02, 0x00, 0x13 } }, //TEL
		/* 0: L20, V2 *//*{{0x00,0x03,0x00,0x00,0x67,0xCD,0xB7,0x21,0x4E,0x45,0x32,0x15,0x30,0x02,0x00,0x13}},
		/* 1: L14, V2 */{ { 0x00, 0x30, 0x00, 0x00, 0x67, 0xCD, 0xB6, 0x31, 0x4E, 0x45, 0x32, 0x15, 0x30, 0x02, 0x00, 0x13 } }, //FLU
		/* 2: L4, V1  */{ { 0x00, 0x0B, 0xFF, 0xFF, 0x4E, 0x45, 0xFF, 0xFF, 0x4E, 0x45, 0x27, 0x99, 0x10, 0x02, 0x00, 0x24 } },
		/* 3: L23, V2 */{ { 0x00, 0x0A, 0x00, 0x00, 0x67, 0xCD, 0xB8, 0x21, 0x4E, 0x45, 0x32, 0x15, 0x30, 0x02, 0x00, 0x13 } },
		/* 4: L11, V2 */{ { 0x00, 0x19, 0x00, 0x00, 0x67, 0xCD, 0xB9, 0x11, 0x4E, 0x45, 0x32, 0x15, 0x30, 0x02, 0x00, 0x13 } },
		/* 5: L5, V2 */{ { 0x00, 0x38, 0x00, 0x00, 0x67, 0xCD, 0xB5, 0x41, 0x4E, 0x45, 0x32, 0x15, 0x30, 0x02, 0x00, 0x13 } },
		/* 6: L3, V1 */{ { 0x00, 0x33, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x4E, 0x45, 0x27, 0x99, 0x10, 0x02, 0x00, 0x0A } },
		/* 7: L1, V1 */{ { 0x00, 0x19, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x4E, 0x45, 0x27, 0x99, 0x10, 0x02, 0x00, 0x25 } },
};
#endif

static void APP_AdoptToHardware(void) {
	KIN1_UID id;
	uint8_t res;

	res = KIN1_UIDGet(&id);
	if (res != ERR_OK) {
		for (;;)
			; /* error */
	}
#if PL_CONFIG_HAS_MOTOR
	if (KIN1_UIDSame(&id, &RoboIDs[0])) { /* L20 */
#if PL_CONFIG_HAS_QUADRATURE
		(void) Q4CRight_SwapPins(TRUE);
#endif
		MOT_Invert(MOT_GetMotorHandle(MOT_MOTOR_LEFT), FALSE); /* invert left motor */
		MOT_Invert(MOT_GetMotorHandle(MOT_MOTOR_RIGHT), TRUE); /* invert rigth motor */
	} else if (KIN1_UIDSame(&id, &RoboIDs[1])) { /* V2 L21 */
		MOT_Invert(MOT_GetMotorHandle(MOT_MOTOR_RIGHT), TRUE); /* invert rigth motor */
	#if PL_CONFIG_HAS_QUADRATURE
    (void)Q4CRight_SwapPins(TRUE);
	#endif
	} else if (KIN1_UIDSame(&id, &RoboIDs[2])) { /* V1 L4 */
		MOT_Invert(MOT_GetMotorHandle(MOT_MOTOR_LEFT), TRUE); /* revert left motor */
#if PL_CONFIG_HAS_QUADRATURE
		(void) Q4CLeft_SwapPins(TRUE);
		(void) Q4CRight_SwapPins(TRUE);
#endif
	} else if (KIN1_UIDSame(&id, &RoboIDs[3])) { /* L23 */
#if PL_CONFIG_HAS_QUADRATURE
		(void) Q4CRight_SwapPins(TRUE);
#endif
		MOT_Invert(MOT_GetMotorHandle(MOT_MOTOR_LEFT), TRUE); /* invert left motor */
		MOT_Invert(MOT_GetMotorHandle(MOT_MOTOR_RIGHT), FALSE); /* invert rigth motor */
	} else if (KIN1_UIDSame(&id, &RoboIDs[4])) { /* L11 */
#if PL_CONFIG_HAS_QUADRATURE
		(void) Q4CRight_SwapPins(TRUE);
#endif
	} else if (KIN1_UIDSame(&id, &RoboIDs[5])) { /* L5, V2 */
		MOT_Invert(MOT_GetMotorHandle(MOT_MOTOR_RIGHT), TRUE); /* invert right motor */
		(void) Q4CRight_SwapPins(TRUE);
	} else if (KIN1_UIDSame(&id, &RoboIDs[6])) { /* L3, V1 */
		MOT_Invert(MOT_GetMotorHandle(MOT_MOTOR_LEFT), TRUE); /* invert right motor */
#if PL_CONFIG_HAS_QUADRATURE
		(void) Q4CLeft_SwapPins(TRUE);
		(void) Q4CRight_SwapPins(TRUE);
#endif
	} else if (KIN1_UIDSame(&id, &RoboIDs[7])) { /* L1, V1 */
		MOT_Invert(MOT_GetMotorHandle(MOT_MOTOR_LEFT), TRUE); /* invert right motor */
#if PL_CONFIG_HAS_QUADRATURE
		(void) Q4CLeft_SwapPins(TRUE);
		(void) Q4CRight_SwapPins(TRUE);
#endif
	}
#endif
#if PL_CONFIG_HAS_QUADRATURE && PL_CONFIG_BOARD_IS_ROBO_V2
	/* pull-ups for Quadrature Encoder Pins */
	PORT_PDD_SetPinPullSelect(PORTC_BASE_PTR, 10, PORT_PDD_PULL_UP);
	PORT_PDD_SetPinPullEnable(PORTC_BASE_PTR, 10, PORT_PDD_PULL_ENABLE);
	PORT_PDD_SetPinPullSelect(PORTC_BASE_PTR, 11, PORT_PDD_PULL_UP);
	PORT_PDD_SetPinPullEnable(PORTC_BASE_PTR, 11, PORT_PDD_PULL_ENABLE);
	PORT_PDD_SetPinPullSelect(PORTC_BASE_PTR, 16, PORT_PDD_PULL_UP);
	PORT_PDD_SetPinPullEnable(PORTC_BASE_PTR, 16, PORT_PDD_PULL_ENABLE);
	PORT_PDD_SetPinPullSelect(PORTC_BASE_PTR, 17, PORT_PDD_PULL_UP);
	PORT_PDD_SetPinPullEnable(PORTC_BASE_PTR, 17, PORT_PDD_PULL_ENABLE);
#endif
}

#if LAB_19_FRTOS
static void BlinkyTask(void *pvParameters) {
	 //Blinky Task with vTaskDealy	 --> 	// - avoid starving other tasks
	 for (;;) {							    // - set number of ticks from current tick count
		 LED1_Neg();
		 vTaskDelay(500/portTICK_PERIOD_MS);
	 }
	//Blinky Task with vTaskDelayUntil -->	// - avoid starving other tasks and stored the heap adress
	TickType_t xLastWakeTime = xTaskGetTickCount();	// - return current tick counter
	for (;;) {
		LED1_Neg();

		// can delay from previous tick counter
		//vTaskDelayUntil(&xLastWakeTime, 50/portTICK_PERIOD_MS);

		// independent of task overhead
		vTaskDelayUntil(&xLastWakeTime, pdMS_TO_TICKS(100));
	}
}
#endif


#if LAB_21_TASK
static void MyAppTask(void *pvParam) {
	for (;;) {
#if PL_CONFIG_HAS_DEBOUNCE
		KEYDBNC_Process();
#else
		KEY_Scan(); /* scan keys and set events */
#endif
		//WAIT1_WaitOSms(50);
		EVNT_HandleEvent(APP_EventHandler, TRUE);
		vTaskDelay(pdMS_TO_TICKS(10));
	}
}
#endif


#if LAB_27_SENSOR
#if PL_CONFIG_HAS_MOTOR
static void DriveTask(void *pvParam) {

#if ROBO_USE_TEL
	MOT_MotorDevice motorLeft;
	MOT_MotorDevice motorRight;

	motorLeft = *MOT_GetMotorHandle(MOT_MOTOR_LEFT);
	motorRight = *MOT_GetMotorHandle(MOT_MOTOR_RIGHT);

	for (;;) {
	#if 0
		if (REF_IsReady()) {
			MOT_SetSpeedPercent(&motorLeft, 50);
			MOT_SetSpeedPercent(&motorRight, 50);
			//int x = REF_GetLineValue();
			REF_LineKind r = REF_GetLineKind();

			if (r == REF_LINE_FULL) {
				MOT_SetDirection(&motorLeft, MOT_DIR_FORWARD);
				MOT_SetDirection(&motorRight, MOT_DIR_FORWARD);
			} else {
				MOT_SetDirection(&motorLeft, MOT_DIR_BACKWARD);
				MOT_SetDirection(&motorRight, MOT_DIR_FORWARD);
				vTaskDelay(pdMS_TO_TICKS(200));
			}
	#endif
	#if 0
			if(r == REF_LINE_STRAIGHT) {
				MOT_SetSpeedPercent(&motorLeft, 70);
				MOT_SetSpeedPercent(&motorRight, 70);
			} else if(r == REF_LINE_LEFT) {
				MOT_SetDirection(&motorLeft, MOT_DIR_BACKWARD);
				MOT_SetDirection(&motorRight, MOT_DIR_FORWARD);
			} else if(r == REF_LINE_RIGHT) {
				MOT_SetDirection(&motorLeft, MOT_DIR_FORWARD);
				MOT_SetDirection(&motorRight, MOT_DIR_BACKWARD);
			} else {
				MOT_SetDirection(&motorLeft, MOT_DIR_BACKWARD);
				MOT_SetDirection(&motorRight, MOT_DIR_FORWARD);
			}
		}
	#endif

	#if LAB_34_TURN
		if (REF_IsReady()){
			MOT_SetSpeedPercent(&motorLeft, 30);
			MOT_SetSpeedPercent(&motorRight, 30);
			REF_LineKind r = REF_GetLineKind();

			switch (r) {
			case REF_LINE_NONE: /* no line, sensors do not see a line */
				//to do
				TURN_Turn(TURN_LEFT180, NULL);
				DRV_SetMode(DRV_MODE_NONE); /* disable position mode */
				//MOT_SetDirection(&motorLeft, MOT_DIR_FORWARD);
				//MOT_SetDirection(&motorRight, MOT_DIR_FORWARD);
				break;
			case REF_LINE_STRAIGHT: /* forward line |, sensors see a line underneath */
				// to do
				break;
			case REF_LINE_LEFT: /* left half of sensors see line */
				// to do
				break;
			case REF_LINE_RIGHT: /* right half of sensors see line */
				// to do
				break;
			case REF_LINE_FULL: /* all sensors see a line */
				// to do
				MOT_SetDirection(&motorLeft, MOT_DIR_FORWARD);
				MOT_SetDirection(&motorRight, MOT_DIR_FORWARD);
				break;
			default:
				break;
			} /* switch */
		} /* if */
	#endif /* LAB_34_TURN */


		vTaskDelay(pdMS_TO_TICKS(10));
	} /* for */
#endif /* ROBO_USE_TEL */


#if ROBO_USE_FLU
	/* to do*/
#endif /* ROBO_USE_FLU */
}
#endif /* PL_CONFIG_HAS_MOTOR */
#endif /* LAB_27_SENSOR */


void APP_Start(void) {
	PL_Init();
	APP_AdoptToHardware();
	__asm volatile("cpsid i"); /* disable interrupts */
	//__asm volatile("cpsie i"); /* enable interrupts */

	#if LAB_19_FRTOS /*---------------Begin Lab 19---------------*/
	//Task Creation Blinky LED
	BaseType_t res;						// local Variables
	xTaskHandle taskHndl;				// local taskHandler

	res = xTaskCreate(BlinkyTask, // Task Function commit to local variables with required parameters, Function Name
			"Blinky", 					// Debug Name (for Kernel)
			configMINIMAL_STACK_SIZE + 50, 	// Stack size
			(void*) NULL, 				// Optional task parameter or NULL
			tskIDLE_PRIORITY + 1, 			// Task priority
			&taskHndl); 					// Task handling

	// The task creation wasn't successful? --> error Handling
	if (res != pdPASS) { /*error handling here*/}
	vTaskStartScheduler(); // Start Scheduler
	#endif /*---------------End Lab 09---------------*/


	#if LAB_21_TASK /* Begin Lab 21 */
		if (xTaskCreate(MyAppTask, "App", configMINIMAL_STACK_SIZE + 100, NULL, tskIDLE_PRIORITY, NULL) != pdPASS) {
			for (;;) {/* error? */}
		}
		#if 0
		vTaskStartScheduler(); // Start Scheduler
		#endif
	#endif /* End Lab 21 */


	#if LAB_27_SENSOR /* Begin Lab 27 */
		#if PL_CONFIG_HAS_MOTOR
		if (xTaskCreate(DriveTask, "App", configMINIMAL_STACK_SIZE + 100, NULL, tskIDLE_PRIORITY, NULL) != pdPASS) {
			for (;;) {/* error? */}
		}
		#endif
		vTaskStartScheduler(); // Start Scheduler
	#endif /* End Lab 27 */


	#if LAB_09_LED /* Begin Lab 09 */
		for (;;){
			LED1_On();
			WAIT1_Waitms(300);
			LED2_On();
			WAIT1_Waitms(1000);
			LED1_Off()
			LED2_Off();
			WAIT1_Waitms(500);
		}
	#endif /* End Lab 09 */


	#if LAB_13_EVENT_HANDLE /* Begin Lab 13 */
		for (;;) {
			WAIT1_Waitms(50);
			EVNT_HandleEvent(APP_EventHandler, 1);
		}
	#endif /* End Lab 13 */


	#if LAB_15_KEYS /* Begin Lab 15 */
		for(;;){
			KEY_Scan();
			EVNT_HandleEvent(APP_EventHandler, 1);
		}
	#endif /* End Lab 15 */


	#if LAB_18_DEBOUNCING /* Begin Lab 18 */
		for (;;){
			#if PL_CONFIG_HAS_DEBOUNCE
			KEYDBNC_Process();
			#else
			KEY_Scan(); /* scan keys and set events */
			#endif
			EVNT_HandleEvent(APP_EventHandler, 1);*/
		}
	#endif /* End Lab 18 */

} /* End App_Start() */
