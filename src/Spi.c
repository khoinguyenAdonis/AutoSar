
#include "Spi.h"
/*
	*	name: Spi_Init
	* Parameters (in): ConfigPtr - r Pointer to configuration set
	* Parameters (out): None
	* Return value: None
	* Description:Service for SPI initialization.
*/
void Spi_Init (const Spi_ConfigType* ConfigPtr){
	SPI_InitTypeDef SPI_InitStruct;
	
	SPI_InitStruct.SPI_Mode = ConfigPtr->SPI_Mode;
	SPI_InitStruct.SPI_BaudRatePrescaler = ConfigPtr->SPI_BaudRatePrescaler;
	SPI_InitStruct.SPI_CPHA = ConfigPtr->SPI_CPHA;
	SPI_InitStruct.SPI_CPOL = ConfigPtr->SPI_CPOL;
	SPI_InitStruct.SPI_CRCPolynomial = ConfigPtr->SPI_CRCPolynomial;
	SPI_InitStruct.SPI_DataSize = ConfigPtr->SPI_DataSize;
	SPI_InitStruct.SPI_FirstBit = ConfigPtr->SPI_FirstBit;
	SPI_InitStruct.SPI_NSS = ConfigPtr->SPI_NSS;
	
	SPI_Init(SPI1,&SPI_InitStruct);
	SPI_Cmd(SPI1,ENABLE); // vd doi vs spi1

}

/*
* Service Name: Spi_DeInit
* Service ID[hex]: 0x01
* Sync/Async: Synchronous
* Reentrancy: Non reentrant
* Parameters (in): None
* Parameters (inout): None
* Parameters (out): None
* Return value: Std_ReturnType -E_OK: de-initialisation command has been accepted
															 -E_NOT_OK: de-initialisation command has not been accepted
* Description: Function to Initialize the Dio module.
*/
Std_ReturnType Spi_DeInit (void){

	SPI_I2S_DeInit(SPI1); // vd dpo voi spi 1
	return E_OK;

}


/*
* Service Name: e Spi_WriteIB
* Service ID[hex]: 0x02
* Sync/Async: Synchronous
* Reentrancy: reentrant
* Parameters (in): Channel 			 - 	Channel ID.
									 DataBufferPtr -  Pointer to source data buffer. If this pointer is null, it is assumed that
																		the data to be transmitted is not relevant and the default transmit
																		value of this channel will be used instead.
* Parameters (inout): None
* Parameters (out): None
* Return value: Std_ReturnType 	 -  E_OK: de-initialisation command has been accepted
																 -  E_NOT_OK: de-initialisation command has not been accepted
* Description: Service for writing one or more data to an IB SPI Handler/Driver Channel specified
							 by parameter.
*/
Std_ReturnType Spi_WriteIB (Spi_ChannelType Channel,const Spi_DataBufferType* DataBufferPtr)
{
	
	  
    if (DataBufferPtr == NULL) {
        return E_NOT_OK;
    }
    
   
    if (Channel < 0 || Channel >= 1) {
        return E_NOT_OK; 
    }
    
   
    SPI_SendData(SPI1, *DataBufferPtr); 
    
    return E_OK;
}

/*
* Service Name: Spi_SetupEB
* Service ID[hex]: 0x05
* Sync/Async: Synchronous
* Reentrancy: reentrant
* Parameters (in): 	Channel 			 		- Channel ID.
										SrcDataBufferPtr 	-	Pointer to source data buffer
										Length						-	Length (number of data elements) of the data to be transmitted from
																				SrcDataBufferPtr and/or received from DesDataBufferPtr Min.: 1 Max.:
																				Max of data specified at configuration for this channel
* Parameters (inout): DesDataBufferPtr-	Pointer to destination data buffer in RAM.
* Parameters (out): None
* Return value: Std_ReturnType 	 			-  E_OK: de-initialisation command has been accepted
																			-  E_NOT_OK: de-initialisation command has not been accepted
* Description: Service to setup the buffers and the length of data for the EB SPI Handler/Driver
							Channel specified.
*/
Std_ReturnType Spi_SetupEB(const Spi_ConfigType* ConfigPtr, const Spi_DataBufferType *SrcDataBufferPtr, uint8_t* DesDataBufferPtr, uint16_t Length) {
    if (ConfigPtr == NULL || SrcDataBufferPtr == NULL || DesDataBufferPtr == NULL) {
        return E_NOT_OK;
    }
		Spi_ChannelType Channel =1;
    for (uint16_t i = 0; i < Length; i++) {
 
        if (Spi_WriteIB(Channel,SrcDataBufferPtr++) != E_OK) {
            return E_NOT_OK; // Return error code if data transmission fails
        }

        // Wait until data is received
        while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_RXNE) == RESET);

        // Receive data into destination buffer
        DesDataBufferPtr[i] = SPI_I2S_ReceiveData(SPI1);
    }

    // Return success status
    return E_OK;
}

/*
* Service Name: Spi_GetStatus
* Service ID[hex]: 0x06
* Sync/Async: Synchronous
* Reentrancy: reentrant
* Parameters (in): 		NONE
* Parameters (inout): NONE
* Parameters (out): 	None
* Return value: Spi_StatusType
* Description: Service returns the SPI Handler/Driver software module status
*/
Spi_StatusType Spi_GetStatus(void) {
    // Check the status of SPI
    if (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_BSY) == SET) {
        return SPI_BUSY; // Return error code if SPI is busy
    } else {
        return E_OK; // Return success status if SPI is not busy
    }
}


/*
* Service Name: Spi_SyncTransmit
* Service ID[hex]: 0x0a
* Sync/Async: Synchronous
* Reentrancy: reentrant
* Parameters (in): 	Sequence					-	Sequence ID.
* Parameters (inout): None
* Parameters (out): None
* Return value: Std_ReturnType 	 			-  E_OK: de-initialisation command has been accepted
																			-  E_NOT_OK: de-initialisation command has not been accepted
* Description: Service to transmit data on the SPI bus
*/
Std_ReturnType Spi_SyncTransmit(const Spi_SequenceType Sequence) {
    // Check the validity of the sequence
    if (Sequence >= 5) {
        return E_NOT_OK; // Return error code if the sequence is invalid
    }

    // Perform data transmission and reception according to the sequence
    // Wait until the process is completed

    // Return the result
    return E_OK;
}

/*
Service Name: Spi_Cancel
Service ID 	: 0x0c
Sync/Async 	:Asynchronous
Reentrancy 	:Reentrant
Parameters (in) 	:Sequence Sequence ID.
Parameters (inout): None
Parameters (out)	: None
Return value 			: None
Description	: Service cancels the specified on-going sequence transmission.
*/
Std_ReturnType Spi_Cancel(Spi_SequenceType Sequence) {
    // Perform cancellation of data transmission or reception for the specified sequence
    
    // Check the validity of the sequence
    if (Sequence < 5) {
        // Perform necessary actions to cancel data transmission or reception for the sequence
        
        // Return success status
        return E_OK;
    } else {
        // Return error code if the sequence is invalid
        return E_NOT_OK;
    }
}


/*
Service Name: Spi_SetAsyncMode
Service ID 	: 0x0d
Sync/Async 	: Synchronous
Reentrancy 	: Non Reentrant
Parameters (in)		: Mode New mode required.
Parameters(inout) : None
Parameters (out)	: None
Return value :	Std_ReturnType 	E_OK: Setting command has been done
																E_NOT_OK: setting command has not been accepted
Description: Service to set the a
*/
Std_ReturnType Spi_SetAsyncMode(Spi_HWUnitType HWUnit, Spi_AsyncModeType Mode) {
    // Set asynchronous mode of operation for the specified SPI hardware unit
    
    // Check the validity of the SPI hardware unit and mode
    if (HWUnit < 3 && (Mode == SPI_POLLING_MODE || Mode == SPI_INTERRUPT_MODE || Mode == SPI_DMA_MODE)) {
        // Perform necessary actions to set asynchronous mode of operation for the SPI hardware unit
 
        // Return success status
        return E_OK;
    } else {
        // Return error code if the hardware unit or mode is invalid
        return E_NOT_OK;
    }
}

/*
Service Name : Spi_GetJobResult
Service ID 	 : 0x07
Sync/Async 	: Synchronous
Reentrancy 	: Reentrant
Parameters (in): Job Job ID. An invalid job ID will return an undefined result.
Parameters (inout): None
Parameters (out)	: None
Return value 			:Spi_JobResultType Spi_JobResultType
Description 	: This service returns the last transmission result of the specified Job.
*/ 
Std_ReturnType Spi_GetJobResult(void) {
    // Check the state of the SPI to determine the result
    if (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_BSY) == RESET) {
        return E_OK;  
    } else {
        return E_NOT_OK;  
    }
}

/*
Service Name Spi_AsyncTransmit
Service ID  0x03
Sync/Async Asynchronous
Reentrancy Reentrant
Parameters (in) Sequence Sequence ID.
Parameters(inout) None
Parameters (out) None
Return value Std_ReturnType		-E_OK: Transmission command has been accepted
															-E_NOT_OK: Transmission command has not been accepted
Description Service to transmit data on the SPI bus
*/
Std_ReturnType Spi_AsyncTransmit(Spi_SequenceType Sequence) {
    // Check if the SPI peripheral is valid
    // Modify this part according to your SPI peripheral configuration
    SPI_TypeDef* SPIx = SPI1; // Example: using SPI1
    if (SPIx == NULL) {
        return E_NOT_OK;
    }

    // Check if the SPI transmit buffer is empty
    if ((SPIx->SR & SPI_SR_TXE) != RESET) {
        // Write data to the SPI data register
        // Modify this part according to your data
        SPIx->DR = Sequence;
        
        // Return E_OK indicating successful start of asynchronous transmission
        return E_OK;
    }

    // Return E_NOT_OK if the transmit buffer is not empty
    return E_NOT_OK;
}

/*
Service Name: Spi_ReadIB
Service ID 	: 0x04
Sync/Async 	: Synchronous
Reentrancy 	:Reentrant
Parameters (in): Channel Channel ID.
Parameters(inout): None
Parameters(out) :DataBufferPointer Pointer to destination data buffer in RAM
Return value: Std_ReturnType -E_OK: read command has been accepted
														-E_NOT_OK: read command has not been accepted
Description Service for reading synchronously one or more data from an IB SPI Handler/
Driver Channel specified by parameter
*/
Std_ReturnType Spi_ReadIB(Spi_ChannelType Channel, Spi_DataBufferType* DataBufferPointer) {
    // Check if DataBufferPointer is valid
    if (DataBufferPointer == NULL) {
        return E_NOT_OK; // Return error if DataBufferPointer is NULL
    }
    // Wait until receive buffer is not empty
    while (!(SPI1->SR & SPI_SR_RXNE));
    
    // Read data from the SPI data register
    *DataBufferPointer = SPI1->DR;
    
    return E_OK; // Return E_OK indicating successful data read
}

