/**
  ******************************************************************************
  * @file    Dio.h
  * @author  Nguyen Khoi
  * @date    29-2-2022
  * @brief   This file contains Header file for Microcontroller - Dio Driver
  ******************************************************************************
  */

#ifndef __DIO_H
#define	__DIO_H
#include "main.h"
#include "stm32f4xx_gpio.h"


typedef enum {

	DIO_CHANNEL_0 = GPIO_Pin_0,
	DIO_CHANNEL_1 = GPIO_Pin_1,           
	DIO_CHANNEL_2 = GPIO_Pin_2,           
	DIO_CHANNEL_3 = GPIO_Pin_3,
	DIO_CHANNEL_4 = GPIO_Pin_4,
	DIO_CHANNEL_5 = GPIO_Pin_5,           
	DIO_CHANNEL_6 = GPIO_Pin_6,           
	DIO_CHANNEL_7 = GPIO_Pin_7, 
	DIO_CHANNEL_8 = GPIO_Pin_8,
	DIO_CHANNEL_9 = GPIO_Pin_9,           
	DIO_CHANNEL_10 = GPIO_Pin_10,           
	DIO_CHANNEL_11 = GPIO_Pin_11, 
	DIO_CHANNEL_12 = GPIO_Pin_12,
	DIO_CHANNEL_13 = GPIO_Pin_13,           
	DIO_CHANNEL_14 = GPIO_Pin_14,           
	DIO_CHANNEL_15 = GPIO_Pin_15 	

}Dio_ChannelType;



typedef enum
{
	DIO_PORT_A = 0x01,
	DIO_PORT_B = 0x02,
	DIO_PORT_C = 0x03,
	DIO_PORT_D = 0x04,
	DIO_PORT_E = 0x05,
	DIO_PORT_F = 0x06 
}Dio_PortType;

typedef struct
{
  Dio_PortType port;
  uint8_t offset;
  uint32_t mask;
} Dio_ChannelGroupType;

typedef enum {
	
	STD_LOW = 0x00,
	STD_HIGH = 0x01

}Dio_LevelType;


typedef uint16_t Dio_PortLevelType;


Dio_LevelType Dio_ReadChannel(Dio_ChannelType channelId);


void Dio_WriteChannel(Dio_ChannelType channelId, Dio_LevelType level);


Dio_PortLevelType Dio_ReadPort(Dio_PortType portId);


void Dio_WritePort(Dio_PortType portId, Dio_PortLevelType level);


Dio_PortLevelType Dio_ReadChannelGroup( const Dio_ChannelGroupType *channelGroupIdPtr );


void Dio_WriteChannelGroup(const Dio_ChannelGroupType *channelGroupIdPtr, Dio_PortLevelType level);

#endif