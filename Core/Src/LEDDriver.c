/*
 * LEDDriver.c
 *
 *  Created on: Jul 14, 2025
 *      Author: Kacper
 */


#include "LEDDriver.h"

static void Color_ToRGB(Color_t color, uint8_t rgb[3]);

static uint8_t Brightness = 0;

void LEDDriver_Init(void)
{
	uint8_t TXData[4];
	uint8_t RXData[4];

	TXData[0] = CONTROL_REG;
	I2C_TransmitData(IS31FL3205_ADDR, (uint8_t *)TXData, 1);
	I2C_ReceiveData(IS31FL3205_ADDR, (uint8_t *)RXData, 1);

	RXData[0] |= 0x01;
	RXData[0] |= 0x03 << 4;

	TXData[1] = RXData[0];
	I2C_TransmitData(IS31FL3205_ADDR, (uint8_t *)TXData, 2);

	TXData[0] = CURRENT_CONTROL;
	TXData[1] = 0xFF;
	I2C_TransmitData(IS31FL3205_ADDR, (uint8_t *)TXData, 2);

	for(uint8_t i = 0; i < 12; i++)
	{
		TXData[0] = LED_SCALING + i;
		TXData[1] = 100;
		I2C_TransmitData(IS31FL3205_ADDR, (uint8_t *)TXData, 2);
	}

	for(uint8_t i = 0; i < 12; i++)
	{
		TXData[0] = PWM_REG + i*2;
		TXData[1] = 0x00;
		I2C_TransmitData(IS31FL3205_ADDR, (uint8_t *)TXData, 2);
	}

	SetStatusLED(PURPLE);
	SetWirelessLED(OFF);
	SetDirectonLED(OFF);
	SetActiveEnergyLED(0);
	SetReactiveEnergyLED(0);
 }

static void Color_ToRGB(Color_t color, uint8_t rgb[3])
{
    switch(color)
    {
        case OFF:
            rgb[0] = 0;   rgb[1] = 0;   rgb[2] = 0;
            break;

        case RED:
            rgb[0] = 255; rgb[1] = 0;   rgb[2] = 0;
            break;

        case GREEN:
            rgb[0] = 0;   rgb[1] = 255; rgb[2] = 0;
            break;

        case BLUE:
            rgb[0] = 0;   rgb[1] = 0;   rgb[2] = 255;
            break;

        case YELLOW:       // czerwony + zielony
            rgb[0] = 255; rgb[1] = 255; rgb[2] = 0;
            break;

        case PURPLE:       // czerwony + niebieski
            rgb[0] = 255; rgb[1] = 0;   rgb[2] = 255;
            break;

        case CYAN:         // zielony + niebieski
            rgb[0] = 0;   rgb[1] = 255; rgb[2] = 255;
            break;

        case WHITE:
            rgb[0] = 255; rgb[1] = 255; rgb[2] = 255;
            break;

        case ORANGE:
            rgb[0] = 255; rgb[1] = 165; rgb[2] = 0;
            break;

        case PINK:
            rgb[0] = 255; rgb[1] = 105; rgb[2] = 180;
            break;

        default:          // zabezpieczenie
            rgb[0] = 0;   rgb[1] = 0;   rgb[2] = 0;
            break;
    }
}

void SetStatusLED(Color_t color)
{
	uint8_t TXData[4];
	uint8_t RGB[3];

	Color_ToRGB(color, RGB);

	TXData[0] = LED1_R;
	TXData[1] = RGB[0];
	I2C_TransmitData(IS31FL3205_ADDR, (uint8_t *)TXData, 2);
	TXData[0] = LED1_G;
	TXData[1] = RGB[1];
	I2C_TransmitData(IS31FL3205_ADDR, (uint8_t *)TXData, 2);
	TXData[0] = LED1_B;
	TXData[1] = RGB[2];
	I2C_TransmitData(IS31FL3205_ADDR, (uint8_t *)TXData, 2);

	TXData[0] = UPDATE_REG;
	TXData[1] = 0;
	I2C_TransmitData(IS31FL3205_ADDR, (uint8_t *)TXData, 2);
}

void SetWirelessLED(Color_t color)
{
	uint8_t TXData[4];
	uint8_t RGB[3];

	Color_ToRGB(color, RGB);

	TXData[0] = LED2_R;
	TXData[1] = RGB[0];
	I2C_TransmitData(IS31FL3205_ADDR, (uint8_t *)TXData, 2);
	TXData[0] = LED2_G;
	TXData[1] = RGB[1];
	I2C_TransmitData(IS31FL3205_ADDR, (uint8_t *)TXData, 2);
	TXData[0] = LED2_B;
	TXData[1] = RGB[2];
	I2C_TransmitData(IS31FL3205_ADDR, (uint8_t *)TXData, 2);

	TXData[0] = UPDATE_REG;
	TXData[1] = 0;
	I2C_TransmitData(IS31FL3205_ADDR, (uint8_t *)TXData, 2);
}

void SetDirectonLED(Color_t color)
{
	uint8_t TXData[4];
	uint8_t RGB[3];

	Color_ToRGB(color, RGB);

	TXData[0] = LED3_R;
	TXData[1] = RGB[0];
	I2C_TransmitData(IS31FL3205_ADDR, (uint8_t *)TXData, 2);
	TXData[0] = LED3_G;
	TXData[1] = RGB[1];
	I2C_TransmitData(IS31FL3205_ADDR, (uint8_t *)TXData, 2);
	TXData[0] = LED3_B;
	TXData[1] = RGB[2];
	I2C_TransmitData(IS31FL3205_ADDR, (uint8_t *)TXData, 2);

	TXData[0] = UPDATE_REG;
	TXData[1] = 0;
	I2C_TransmitData(IS31FL3205_ADDR, (uint8_t *)TXData, 2);
}

void SetActiveEnergyLED(uint8_t Level)
{
	uint8_t TXData[4];
	TXData[0] = LED4;
	TXData[1] = Level;
	I2C_TransmitData(IS31FL3205_ADDR, (uint8_t *)TXData, 2);

	TXData[0] = UPDATE_REG;
	TXData[1] = 0;
	I2C_TransmitData(IS31FL3205_ADDR, (uint8_t *)TXData, 2);
}

void SetReactiveEnergyLED(uint8_t Level)
{
	uint8_t TXData[4];
	TXData[0] = LED5;
	TXData[1] = Level;
	I2C_TransmitData(IS31FL3205_ADDR, (uint8_t *)TXData, 2);

	TXData[0] = UPDATE_REG;
	TXData[1] = 0;
	I2C_TransmitData(IS31FL3205_ADDR, (uint8_t *)TXData, 2);
}

void LEDHandler(void)
{

}
