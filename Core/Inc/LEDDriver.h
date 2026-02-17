/*
 * LEDDriver.h
 *
 *  Created on: Jul 14, 2025
 *      Author: Kacper
 */

#ifndef INC_LEDDRIVER_H_
#define INC_LEDDRIVER_H_

#include "main.h"

#define IS31FL3205_ADDR		0x68

#define CONTROL_REG			0x00
#define PWM_REG				0x07
#define UPDATE_REG			0x49
#define LED_SCALING			0x4D
#define CURRENT_CONTROL		0x6E
#define PHASE_DELAY			0x70
#define DETECT_ENABLE		0x71
#define LED_OPEN_SHORT		0x72
#define TEMP_REG			0x77
#define SS_REG				0x78
#define RESET_REG			0x7F

#define LED1_B				0x07
#define LED1_G				0x09
#define LED1_R 				0x0B

#define LED2_B				0x0D
#define LED2_G				0x0F
#define LED2_R 				0x11

#define LED3_B				0x13
#define LED3_G				0x15
#define LED3_R 				0x17

#define LED4				0x19
#define LED5				0x1B
#define LED6				0x1D

typedef enum Color_t
{
    OFF = 0,
    RED,
    GREEN,
    BLUE,
    YELLOW,
    PURPLE,
    CYAN,
    WHITE,
    ORANGE,
    PINK
} Color_t;

void LEDDriver_Init(void);
void SetStatusLED(Color_t color);
void SetWirelessLED(Color_t color);
void SetDirectonLED(Color_t color);
void SetActiveEnergyLED(uint8_t Level);
void SetReactiveEnergyLED(uint8_t Level);
void LEDHandler(void);

#endif /* INC_LEDDRIVER_H_ */
