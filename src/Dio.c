#include "Dio.h"

/*
* Service Name: Dio_ReadChannel
* Service ID[hex]: 0x00
* Sync/Async: Synchronous
* Reentrancy: Reentrant
* Parameters (in): ChannelId - ID of DIO channel.
* Parameters (inout): None
* Parameters (out): None
* Return value: Dio_LevelType
* Description: Function to return the value of the specified DIO channel.
*/

Dio_LevelType Dio_ReadChannel (Dio_ChannelType ChannelId){
	Dio_LevelType lever = STD_LOW;
	switch(ChannelId){
		
		case DIO_CHANNEL_0:
				if(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_0)==Bit_SET){
					return STD_HIGH;
				}
		case DIO_CHANNEL_1:
				if(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_1)==Bit_SET){
					return STD_HIGH;
				}
		
		case DIO_CHANNEL_2:
				if(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_2)==Bit_SET){
					return STD_HIGH;
				}
		
		/*conf nhieu chanel chua kip viets*/
		default:
			break;
	}
	
}
/*
* Service Name: Dio_WriteChannel
* Service ID[hex]: 0x01
* Sync/Async: Synchronous
* Reentrancy: Reentrant
* Parameters (in): ChannelId - ID of DIO channel.
*                  Level - Value to be written.
* Parameters (inout): None
* Parameters (out): None
* Return value: None
* Description: Function to set a level of a channel.
*/
void Dio_WriteChannel(Dio_ChannelType channelId, Dio_LevelType level){
	GPIO_TypeDef * GPIO_Port;
	uint16_t GPIO_Pin;
	switch(channelId){
		
		case DIO_CHANNEL_0:
				GPIO_Port = GPIOA;
				GPIO_Pin = GPIO_Pin_0;
		case DIO_CHANNEL_1:
				GPIO_Port = GPIOA;
				GPIO_Pin = GPIO_Pin_0;
		case DIO_CHANNEL_2:
				GPIO_Port = GPIOA;
				GPIO_Pin = GPIO_Pin_0;
		/*conf nhieu chanel chua kip viets*/
		default:
			break;
	}
	if(level == STD_LOW){
		GPIO_WriteBit(GPIO_Port,GPIO_Pin,Bit_RESET);
	}else{
		GPIO_WriteBit(GPIO_Port,GPIO_Pin,Bit_SET);
	}

}

/*
Service Name: Dio_ReadPort
Service ID : 0x02
Sync/Async : Synchronous
Reentrancy : Reentrant
Parameters (in): PortId ID of DIO Port
Parameters (inout): None
Parameters (out): None
Return value: Dio_PortLevelType Level of all channels of that port
Description: Returns the level of all channels of that port
*/
Dio_PortLevelType Dio_ReadPort(Dio_PortType portId){

	Dio_LevelType level = STD_LOW;
switch(portId){
		
		case DIO_PORT_A:
				return GPIO_ReadInputData(GPIOA);
		case DIO_PORT_B:
				return GPIO_ReadInputData(GPIOB);
		case DIO_PORT_C:
				return GPIO_ReadInputData(GPIOC);
		/*conf nhieu port chua kip viets*/
		default:
			break;
	}

}

/*
Service Name: Dio_WritePort
Service ID : 0x03
Sync/Async : Synchronous
Reentrancy : Reentrant
Parameters (in): PortId - ID of DIO Port
								 Level 	- Value to be written
Parameters (inout): None
Parameters (out): None
Return value: None
Description: Service to set a value of the port.
*/
void Dio_WritePort(Dio_PortType portId, Dio_PortLevelType level)
{
	switch(portId){
		
		case DIO_PORT_A:
				GPIO_Write(GPIOA,level);
		case DIO_PORT_B:
				GPIO_Write(GPIOB,level);
		case DIO_PORT_C:
				GPIO_Write(GPIOC,level);
		/*conf nhieu port chua kip viets*/
		default:
			break;
	}

}

/*
Service Name: Dio_ReadChannelGroup
Service ID 	: 0x04
Sync/Async 	: Synchronous
Reentrancy 	; Reentrant
Parameters (in): ChannelGroupIdPtr Pointer to ChannelGroup
Parameters (inout): None
Parameters (out): None
Return value: Dio_PortLevelType Level of a subset of the adjoining bits of a port
Description	: This Service reads a subset of the adjoining bits of a port.
*/
Dio_PortLevelType Dio_ReadChannelGroup( const Dio_ChannelGroupType *channelGroupIdPtr ){
	
	Dio_LevelType level;

	level = Dio_ReadPort(channelGroupIdPtr->port) & channelGroupIdPtr->mask;

	level = level >> channelGroupIdPtr->offset;

	return level;


}

/*
Service Name :Dio_WriteChannelGroup
Service ID 	 : 0x05
Sync/Async : Synchronous
Reentrancy : Reentrant
Parameters (in)	ChannelGroupIdPtr - Pointer to ChannelGroup
								Level	- Value to be written
Parameters (inout): None
Parameters (out): None
Return value: None
Description : Service to set a subset of the adjoining bits of a port to a specified level.
*/
void Dio_WriteChannelGroup(const Dio_ChannelGroupType *channelGroupIdPtr, Dio_PortLevelType level){



	level = (level << channelGroupIdPtr->offset) & channelGroupIdPtr->mask;


	Dio_PortLevelType portVal = Dio_ReadPort(channelGroupIdPtr->port) & (~channelGroupIdPtr->mask);

	
	portVal |= level;

	Dio_WritePort(channelGroupIdPtr->port, portVal);

}
