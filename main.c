/**
	\file
	\brief
		This proyect shows how to build a state machine using a structure and a pointer to fucntions.
	\author J. Luis Pizano Escalante, luispizano@iteso.mx
	\date	13/09/2015
 */
#include "MK64F12.h"
#include "GPIO.h"
#include "GlobalFunctions.h"


typedef enum {VERDE, AZUL, MORADO, ROJO, AMARILLO, BLANCO}ColorStateType;



typedef struct State
{
	uint32 out;

	void(*fptrPort)(uint32);
	uint16 wait;

	void (*fptrDelay)(uint16);
	const struct State* next[4];
}StateType;

const StateType FSM_Moore[4]=
		{
				{VERDE		,GPIO_writePORT,65000,delay,{VERDE,AZUL,AMARILLO,BLANCO}}, /**Verde*/
				{AZUL 		,GPIO_writePORT,65000,delay,{AZUL,MORADO, VERDE,BLANCO}},/**Azul*/
				{MORADO     ,GPIO_writePORT,65000,delay,{MORADO,ROJO,AZUL,BLANCO}},/**Morado*/
				{ROJO       ,GPIO_writePORT,65000,delay,{ROJO,AMARILLO,MORADO,BLANCO}},/**Rojo*/
				{AMARILLO   ,GPIO_writePORT,65000,delay,{AMARILLO, VERDE,ROJO,BLANCO}},/**Amarillo*/
				{BLANCO     ,GPIO_writePORT,65000,delay,{BLANCO,VERDE, AMARILLO,BLANCO}} /**Blanco*/
		};

int main(void)
{

	uint32 inputValue_sw1 = 0;
	uint32 inputValue_sw2 = 0;
	uint8 x = 1;
	uint8 temp = 0;


	uint8 currentState = VERDE;
	uint32 output=0,input=0;
	uint16 delayValue = 0;
	GPIO_pinControlRegisterType pinControlRegister = GPIO_MUX1|GPIO_PE|GPIO_PS;
	GPIO_pinControlRegisterType pinControlRegisterLeds = GPIO_MUX1;



	SIM->SCGC5 |= GPIO_CLOCK_GATING_PORTB;
    SIM->SCGC5 |= GPIO_CLOCK_GATING_PORTC;
    SIM->SCGC5 |= GPIO_CLOCK_GATING_PORTA;
    SIM->SCGC5 |= GPIO_CLOCK_GATING_PORTE;


	PORTB->PCR[BIT21]= pinControlRegisterLeds;
	PORTB->PCR[BIT22]= pinControlRegisterLeds;
	PORTE->PCR[BIT26]= pinControlRegisterLeds;

	PORTC->PCR[BIT6] = pinControlRegister;
	PORTA->PCR[BIT4] = pinControlRegister;

	GPIO_dataDirectionPIN(GPIO_B, GPIO_OUTPUT, BIT21);
	GPIO_dataDirectionPIN(GPIO_B, GPIO_OUTPUT, BIT22);
	GPIO_dataDirectionPIN(GPIO_E, GPIO_OUTPUT, BIT26);
	GPIO_dataDirectionPIN(GPIO_C, GPIO_INPUT, BIT6);
	GPIO_dataDirectionPIN(GPIO_B, GPIO_INPUT, BIT4);

	GPIO_setPIN(GPIO_B, BIT21);
	GPIO_setPIN(GPIO_B, BIT22);
	GPIO_setPIN(GPIO_E, BIT26);

	GPIO_setPIN(GPIO_C, BIT6);
	GPIO_setPIN(GPIO_A, BIT4);

	delay(3000);

	for(;;) {

		output = FSM_Moore[currentState].out;
		FSM_Moore[currentState].fptrPort(output);
		delayValue = FSM_Moore[currentState].wait;
		FSM_Moore[currentState].fptrDelay(delayValue);
		input = GPIOC->PDIR;
		input &=(0x40);
		input = input?1:0;
		currentState = FSM_Moore[currentState].next[input];


	}// end for

}// end main
