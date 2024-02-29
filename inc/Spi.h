/**
  ******************************************************************************
  * @file    Spi.h
  * @author  Nguyen Khoi
  * @date    29-2-2022
  * @brief   This file contains The SPI Handler/Driver provides services for 
	*reading from and writing to devices connected via SPI busses for autosar
  ******************************************************************************
  */

#ifndef __SPI_H
#define __SPI_H

#include "Std_Types.h"
#include "main.h"
#include "stm32f4xx_spi.h"


typedef enum {
	SPI_UNINIT = 0x00,
	SPI_IDLE	 = 0x01,
	SPI_BUSY   = 0x02

}Spi_StatusType;


typedef enum {
    SPI_POLLING_MODE,
    SPI_INTERRUPT_MODE,
    SPI_DMA_MODE
} Spi_AsyncModeType;

typedef enum {
    SPI_HWUnit_0,
    SPI_HWUnit_1,
    SPI_HWUnit_2
} Spi_HWUnitType;

/** 
  * @brief  SPI Init structure definition for autosar  
  */
typedef struct {

	uint16_t SPI_Direction;           /*!< Specifies the SPI unidirectional or bidirectional data mode.
                                         This parameter can be a value of @ref SPI_data_direction */

  uint16_t SPI_Mode;                /*!< Specifies the SPI operating mode.
                                         This parameter can be a value of @ref SPI_mode */

  uint16_t SPI_DataSize;            /*!< Specifies the SPI data size.
                                         This parameter can be a value of @ref SPI_data_size */

  uint16_t SPI_CPOL;                /*!< Specifies the serial clock steady state.
                                         This parameter can be a value of @ref SPI_Clock_Polarity */

  uint16_t SPI_CPHA;                /*!< Specifies the clock active edge for the bit capture.
                                         This parameter can be a value of @ref SPI_Clock_Phase */

  uint16_t SPI_NSS;                 /*!< Specifies whether the NSS signal is managed by
                                         hardware (NSS pin) or by software using the SSI bit.
                                         This parameter can be a value of @ref SPI_Slave_Select_management */
 
  uint16_t SPI_BaudRatePrescaler;   /*!< Specifies the Baud Rate prescaler value which will be
                                         used to configure the transmit and receive SCK clock.
                                         This parameter can be a value of @ref SPI_BaudRate_Prescaler
                                         @note The communication clock is derived from the master
                                               clock. The slave clock does not need to be set. */

  uint16_t SPI_FirstBit;            /*!< Specifies whether data transfers start from MSB or LSB bit.
                                         This parameter can be a value of @ref SPI_MSB_LSB_transmission */

  uint16_t SPI_CRCPolynomial;       /*!< Specifies the polynomial used for the CRC calculation. */
	
}Spi_ConfigType;




typedef uint8_t Spi_ChannelType;

typedef uint16_t Spi_DataBufferType;

typedef uint8_t Spi_SequenceType;



void Spi_Init (const Spi_ConfigType* ConfigPtr);
/*  Function used to set the SPI configuration to the default reset state *****/ 
Std_ReturnType Spi_DeInit (void);

Std_ReturnType Spi_WriteIB (Spi_ChannelType Channel,const Spi_DataBufferType* DataBufferPtr);

Std_ReturnType Spi_AsyncTransmit (Spi_SequenceType Sequence);

Std_ReturnType Spi_SetupEB(const Spi_ConfigType* ConfigPtr, const Spi_DataBufferType *SrcDataBufferPtr, uint8_t* DesDataBufferPtr, uint16_t Length);

Std_ReturnType Spi_GetJobResult(void);

Spi_StatusType Spi_GetStatus (void);

Std_ReturnType Spi_GetSequenceResult(void);

Std_ReturnType Spi_SyncTransmit(const Spi_SequenceType Sequence);

Std_ReturnType Spi_Cancel(Spi_SequenceType Sequence);

Std_ReturnType Spi_SetAsyncMode(Spi_HWUnitType HWUnit, Spi_AsyncModeType Mode);

Std_ReturnType Spi_ReadIB(Spi_ChannelType Channel, Spi_DataBufferType* DataBufferPointer);

#endif