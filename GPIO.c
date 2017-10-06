/**
	\file
	\brief
		This is the source file for the GPIO device driver for Kinetis K64.
		It contains all the implementation for configuration functions and runtime functions.
		i.e., this is the application programming interface (API) for the GPIO peripheral.
	\author J. Luis Pizano Escalante, luispizano@iteso.mx
	\date	7/09/2014
	\todo
	    Interrupts are not implemented in this API implementation.
 */
#include "MK64F12.h"
#include "GPIO.h"

GPIO_interruptFlags_t GPIO_intrStatusFlag;

uint8 GPIO_getIRQStatus(GPIO_portNameType gpio)
{
	switch (gpio) {
		case GPIO_A:
			return(GPIO_intrStatusFlag.flagPortA);
			break;
		case GPIO_B:
			return(GPIO_intrStatusFlag.flagPortB);
			break;
		case GPIO_C:
			return(GPIO_intrStatusFlag.flagPortC);
			break;
		case GPIO_D:
			return(GPIO_intrStatusFlag.flagPortD);
			break;
		case GPIO_E:
			return(GPIO_intrStatusFlag.flagPortE);
			break;
		default:
			return(ERROR);
			break;
	}

}

uint8 GPIO_clearIRQStatus(GPIO_portNameType gpio)
{
	switch (gpio) {
		case GPIO_A:
			GPIO_intrStatusFlag.flagPortA = FALSE;
			break;
		case GPIO_B:
			GPIO_intrStatusFlag.flagPortB = FALSE;
			break;
		case GPIO_C:
			GPIO_intrStatusFlag.flagPortC = FALSE;
			break;
		case GPIO_D:
			GPIO_intrStatusFlag.flagPortD = FALSE;
			break;
		case GPIO_E:
			GPIO_intrStatusFlag.flagPortE = FALSE;
			break;
		default:
			return(ERROR);
			break;
	}

	return(TRUE);

}


void GPIO_clearInterrupt(GPIO_portNameType portName)
{
	switch(portName)/** Selecting the GPIO for clock enabling*/
	{
		case GPIO_A: /** GPIO A is selected*/
			PORTA->ISFR=0xFFFFFFFF;
			break;
		case GPIO_B: /** GPIO B is selected*/
			PORTB->ISFR=0xFFFFFFFF;
			break;
		case GPIO_C: /** GPIO C is selected*/
			PORTC->ISFR = 0xFFFFFFFF;
			break;
		case GPIO_D: /** GPIO D is selected*/
			PORTD->ISFR=0xFFFFFFFF;
			break;
		default: /** GPIO E is selected*/
			PORTE->ISFR=0xFFFFFFFF;
			break;

	}// end switch
}
uint8 GPIO_clockGating(GPIO_portNameType portName)
{
	switch(portName)/** Selecting the GPIO for clock enabling*/
			{
				case GPIO_A: /** GPIO A is selected*/
					SIM->SCGC5 |= GPIO_CLOCK_GATING_PORTA; /** Bit 9 of SIM_SCGC5 is  set*/
					break;
				case GPIO_B: /** GPIO B is selected*/
					SIM->SCGC5 |= GPIO_CLOCK_GATING_PORTB; /** Bit 10 of SIM_SCGC5 is set*/
					break;
				case GPIO_C: /** GPIO C is selected*/
					SIM->SCGC5 |= GPIO_CLOCK_GATING_PORTC; /** Bit 11 of SIM_SCGC5 is set*/
					break;
				case GPIO_D: /** GPIO D is selected*/
					SIM->SCGC5 |= GPIO_CLOCK_GATING_PORTD; /** Bit 12 of SIM_SCGC5 is set*/
					break;
				case GPIO_E: /** GPIO E is selected*/
					SIM->SCGC5 |= GPIO_CLOCK_GATING_PORTE; /** Bit 13 of SIM_SCGC5 is set*/
					break;
				default: /**If doesn't exist the option*/
					return(FALSE);
			}// end switch
	/**Successful configuration*/
	return(TRUE);
}// end function

uint8 GPIO_pinControlRegister(GPIO_portNameType portName,uint8 pin,const GPIO_pinControlRegisterType*  pinControlRegister)
{

	switch(portName)
		{
		case GPIO_A:/** GPIO A is selected*/
			PORTA->PCR[pin] = *pinControlRegister;
			break;
		case GPIO_B:/** GPIO B is selected*/
			PORTB->PCR[pin] = *pinControlRegister;
			break;
		case GPIO_C:/** GPIO C is selected*/
			PORTC->PCR[pin] = *pinControlRegister;
			break;
		case GPIO_D:/** GPIO D is selected*/
			PORTD->PCR[pin] = *pinControlRegister;
			break;
		case GPIO_E: /** GPIO E is selected*/
			PORTE->PCR[pin]= *pinControlRegister;
		default:/**If doesn't exist the option*/
			return(FALSE);
		break;
		}
	/**Successful configuration*/
	return(TRUE);

}


void GPIO_writePORT(GPIO_portNameType portName, uint32 Data ){

	switch(portName)
		{
		case GPIO_A:/** GPIO A is selected*/
			GPIOA->PDOR = Data;
			break;
		case GPIO_B:/** GPIO B is selected*/
			GPIOB->PDOR = Data;
			break;
		case GPIO_C:/** GPIO C is selected*/
			GPIOC->PDOR = Data;
			break;
		case GPIO_D:/** GPIO D is selected*/
			GPIOD->PDOR = Data;
			break;
		case GPIO_E: /** GPIO E is selected*/
			GPIOE->PDOR = Data;
			break;
		default:/**If doesn't exist the option*/
			break;
		}
}

uint32 GPIO_readPORT(GPIO_portNameType portName){

	uint32 Data = 0;

	switch(portName)
		{
		case GPIO_A:/** GPIO A is selected*/
			Data = GPIOA->PDIR;
			break;
		case GPIO_B:/** GPIO B is selected*/
			Data = GPIOB->PDIR;
			break;
		case GPIO_C:/** GPIO C is selected*/
			Data = GPIOC->PDIR;
			break;
		case GPIO_D:/** GPIO D is selected*/
			Data = GPIOD->PDIR;
			break;
		case GPIO_E: /** GPIO E is selected*/
			Data = GPIOE->PDIR;
			break;
		default:/**If doesn't exist the option*/
			break;
		}
	return (Data);
}

uint8 GPIO_readPIN(GPIO_portNameType portName, uint8 pin){
	uint32 PinToBeRead = 0;
	PinToBeRead = ((1)<<(pin));
	switch(portName)
			{
			case GPIO_A:/** GPIO A is selected*/
				if (PinToBeRead && GPIOA->PDIR){
					return (TRUE);
				}else {
					return (FALSE);
				}
				break;
			case GPIO_B:/** GPIO B is selected*/
				if (PinToBeRead && GPIOB->PDIR){
					return (TRUE);
				}else {
					return (FALSE);
				}
				break;
			case GPIO_C:/** GPIO C is selected*/
				if (PinToBeRead && GPIOC->PDIR){
					return (TRUE);
				}else {
					return (FALSE);
				}
				break;
			case GPIO_D:/** GPIO D is selected*/
				if (PinToBeRead && GPIOD->PDIR){
					return (TRUE);
				}else {
					return (FALSE);
				}
				break;
			case GPIO_E: /** GPIO E is selected*/
				if (PinToBeRead && GPIOE->PDIR){
					return (TRUE);
				}else {
					return (FALSE);
				}
				break;
			default:
				break;
			}
	return 0;
}
void GPIO_setPIN(GPIO_portNameType portName, uint8 pin){
	uint32 pinToBeSet = 0;
	pinToBeSet = ((1)<<(pin));
	switch(portName)
			{
			case GPIO_A:/** GPIO A is selected*/
				GPIOA->PSOR = pinToBeSet;
				break;
			case GPIO_B:/** GPIO B is selected*/
				GPIOB->PSOR = pinToBeSet;
				break;
			case GPIO_C:/** GPIO C is selected*/
				GPIOC->PSOR = pinToBeSet;
				break;
			case GPIO_D:/** GPIO D is selected*/
				GPIOD->PSOR = pinToBeSet;
				break;
			case GPIO_E: /** GPIO E is selected*/
				GPIOE->PSOR = pinToBeSet;
				break;
			default:
				break;
			}

}
void GPIO_clearPIN(GPIO_portNameType portName, uint8 pin){
	uint32 pinToBeCleared = 0;
	pinToBeCleared = ((1)<<(pin));
	switch(portName)
			{
			case GPIO_A:/** GPIO A is selected*/
				GPIOA->PCOR = pinToBeCleared;
				break;
			case GPIO_B:/** GPIO B is selected*/
				GPIOB->PCOR = pinToBeCleared;
				break;
			case GPIO_C:/** GPIO C is selected*/
				GPIOC->PCOR = pinToBeCleared;
				break;
			case GPIO_D:/** GPIO D is selected*/
				GPIOD->PCOR = pinToBeCleared;
				break;
			case GPIO_E: /** GPIO E is selected*/
				GPIOE->PCOR = pinToBeCleared;
				break;
			default:
				break;
			}
}
void GPIO_tooglePIN(GPIO_portNameType portName, uint8 pin){
	uint32 pinToBeToggled = 0;
	pinToBeToggled = ((1)<<(pin));
	switch(portName)
			{
			case GPIO_A:/** GPIO A is selected*/
				GPIOA->PTOR = pinToBeToggled;
				break;
			case GPIO_B:/** GPIO B is selected*/
				GPIOB->PTOR = pinToBeToggled;
				break;
			case GPIO_C:/** GPIO C is selected*/
				GPIOC->PTOR = pinToBeToggled;
				break;
			case GPIO_D:/** GPIO D is selected*/
				GPIOD->PTOR = pinToBeToggled;
				break;
			case GPIO_E: /** GPIO E is selected*/
				GPIOE->PTOR = pinToBeToggled;
				break;
			default:
				break;
			}
}
void GPIO_dataDirectionPORT(GPIO_portNameType portName ,uint32 direction){

	switch(portName)/** Selecting the GPIO for clock enabling*/
	{
		case GPIO_A: /** GPIO A is selected*/
			if (FALSE == direction){
				GPIOA->PDDR = 0xFFFFFFFF;
			}else if (TRUE == direction){
				GPIOA->PDDR = 0x00000000;
			}
			break;
		case GPIO_B: /** GPIO B is selected*/
			if (FALSE == direction){
				GPIOB->PDDR = 0xFFFFFFFF;
			}else if (TRUE == direction){
				GPIOB->PDDR = 0x00000000;
			}
			break;
		case GPIO_C: /** GPIO C is selected*/
			if (FALSE == direction){
		    	GPIOC->PDDR = 0xFFFFFFFF;
			}else if (TRUE == direction){
				GPIOC->PDDR = 0x00000000;
			}
			break;
		case GPIO_D: /** GPIO D is selected*/
			if (FALSE == direction){
				GPIOD->PDDR = 0xFFFFFFFF;
			}else if (TRUE == direction){
				GPIOD->PDDR = 0x00000000;
			}
			break;
		case GPIO_E:
			if (FALSE == direction){
				GPIOE->PDDR = 0xFFFFFFFF;
			}else if (TRUE == direction){
				GPIOE->PDDR = 0x00000000;
			}
			break;
		default:
			break;

	}
}
void GPIO_dataDirectionPIN(GPIO_portNameType portName, uint8 State, uint8 pin){

	uint32 dataDirectionPin = 0;
	dataDirectionPin = ((1)<<(pin));

	switch(portName)/** Selecting the GPIO for clock enabling*/
	{
		case GPIO_A: /** GPIO A is selected*/
			if (TRUE == State){
				GPIOA->PDDR &=  ~(dataDirectionPin);
			}else if(FALSE == State){
				GPIOA->PDDR |= dataDirectionPin;
			}
			break;
		case GPIO_B: /** GPIO B is selected*/
			if (TRUE == State){
				GPIOA->PDDR &=  ~(dataDirectionPin);
			}else if(FALSE == State){
				GPIOA->PDDR |= dataDirectionPin;
			}
			break;
		case GPIO_C: /** GPIO C is selected*/
			if (TRUE == State){
				GPIOA->PDDR &=  ~(dataDirectionPin);
			}else if(FALSE == State){
				GPIOA->PDDR |= dataDirectionPin;
			}
			break;
		case GPIO_D: /** GPIO D is selected*/
			if (TRUE == State){
				GPIOA->PDDR &=  ~(dataDirectionPin);
			}else if(FALSE == State){
				GPIOA->PDDR |= dataDirectionPin;
			}
			break;
		case GPIO_E:
			if (TRUE == State){
				GPIOA->PDDR &=  ~(dataDirectionPin);
			}else if(FALSE == State){
				GPIOA->PDDR |= dataDirectionPin;
			}
			break;
		default:
			break;

	}
}




