/*********************************************************************************

	File: Rs232.c
	Description: Serial Rs232 interface driver for the Atmega644x microcontroller

**********************************************************************************/

#include "Rs232.h"

struct TRs232Struct{
  TRs232Number Rs232Number;
  TRingBuffer SendBuffer;
  TRingBuffer RecieveBuffer;
};

TRs232 Rs232[ERS232_NO_LAST] = {NULL, NULL};


TRs232 Rs232Create(TRs232Number aRs232Number, unsigned long aCpuClk, TRs232Config aConfig);

void Rs232ConfigDefaultInit(TRs232Config * Config);

void Rs232Destroy(TRs232 aRs232);

unsigned char Rs232SendData(TRs232 aRs232, unsigned char * aBuffer, unsigned char aSize); 

unsigned char Rs232RecieveData(TRs232 aRs232, unsigned char * aBuffer, unsigned char aBufferSize);

unsigned int Rs232CalculateBaudrateRegisterValue(unsigned long aCpuClk, unsigned int aBaudrate, TBool * aDoubleSpeed);

//******************************definition of private functions ********************************

static void Rs232InitCon0(TRs232 aRs232, unsigned long aCpuClk, TRs232Config * aConfig){
	TBool doubleSpeed;	//U2X Bit int ... register
	UCSR0A = 0;
	UCSR0B = 0;
	UCSR0C = 0;

	UBRR0 = Rs232CalculateBaudrateRegisterValue(aCpuClk, aConfig->BaudRate, &doubleSpeed);
	
	if(doubleSpeed){
		UCSR0A |= (1 << U2X0);
	}
	
	UCSR0C |= (3 << UCSZ00);
	UCSR0B |= (1 << RXCIE0) | (1 << RXEN0) | (1 << TXEN0);
}

static void Rs232InitCon1(TRs232 aRs232, unsigned long aCpuClk, TRs232Config * aConfig){
	TBool doubleSpeed;	//U2X Bit int ... register
	UCSR1A = 0;
	UCSR1B = 0;
	UCSR1C = 0;

	UBRR0 = Rs232CalculateBaudrateRegisterValue(aCpuClk, aConfig->BaudRate, &doubleSpeed);
	
	if(doubleSpeed){
		UCSR1A |= (1 << U2X1);
	}
	
	UCSR1C |= (3 << UCSZ10);
	UCSR1B |= (1 << RXCIE1) | (1 << RXEN1) | (1 << TXEN1);
}

unsigned int Rs232CalculateBaudrateRegisterValue(unsigned long aCpuClk, unsigned int aBaudrate, TBool * aDoubleSpeed){
	unsigned int baudRateReg;
	
	*aDoubleSpeed = EFALSE;
	
	baudRateReg = (aCpuClk/(16UL * aBaudrate) - 1);
	
	if(baudRateReg > 4096){
		*aDoubleSpeed = ETRUE;
		baudRateReg = baudRateReg / 2;
	}
	
	return baudRateReg;
}

//********************************************************************************************

TRs232 Rs232Create(TRs232Number aRs232Number, unsigned long aCpuClk, TRs232Config aConfig){
  TRs232 rs232;
  
  if(aRs232Number >= ERS232_NO_LAST){
    return NULL;
	}
	
  rs232 = calloc(1, sizeof(struct TRs232Struct));
  
  if(rs232 == NULL){
    return NULL;
	}
  
  rs232->Rs232Number = aRs232Number;
  rs232->SendBuffer = RingBufferCreate(aConfig.SendBufferSize);
  rs232->RecieveBuffer = RingBufferCreate(aConfig.RecieveBufferSize);
  
  if(!rs232->SendBuffer || !rs232->RecieveBuffer){
    Rs232Destroy(rs232);
    return NULL;
  }
  
  cli();  //disable all interrupts
  
  switch(aRs232Number){
    case ERS232_NO_0:
    default:
      Rs232InitCon0(rs232, aCpuClk, &aConfig);
      break;
    case ERS232_NO_1:
      Rs232InitCon1(rs232, aCpuClk, &aConfig);
    break;
  }
  
  if(Rs232[aRs232Number]){
    Rs232Destroy(Rs232[aRs232Number]);
	}
  Rs232[aRs232Number] = rs232;
  
  sei();  //enable all interrupts
  
  return rs232;
}

void Rs232Destroy(TRs232 aRs232){
	
	if(!aRs232){
		return;
	}
	
	cli();
	
  if(aRs232->SendBuffer){
    RingBufferDestroy(aRs232->SendBuffer);
	}
	
  if(aRs232->RecieveBuffer){
    RingBufferDestroy(aRs232->RecieveBuffer);
	}

	switch(aRs232->Rs232Number){
		case ERS232_NO_0:
			UCSR0B = 0;
			break;
			
		case ERS232_NO_1:
			UCSR1B = 0;
			break;
		case ERS232_NO_LAST:
			break;
	}
	
	Rs232[aRs232->Rs232Number] = NULL;
	free(aRs232);

	sei();
}

unsigned char Rs232SendData(TRs232 aRs232, unsigned char * aBuffer, unsigned char aSize){
  unsigned char byteNum;
	
	for(byteNum = 0; byteNum < aSize; byteNum++){
		if(!RingBufferWrite(aRs232->SendBuffer, aBuffer[byteNum])){
			break;
		}
	}
	
	if(byteNum){
		switch(aRs232->Rs232Number){
			case ERS232_NO_0:
				UCSR0B |= (1 << UDRIE0);
				break;
				
			case ERS232_NO_1:
				UCSR1B |= (1 << UDRIE1);
				break;
		}
	}
	return byteNum;
}

unsigned char Rs232RecieveData(TRs232 aRs232, unsigned char * aBuffer, unsigned char aBufferSize){
	unsigned char data, i;
	
	for(i = 0; i < aBufferSize; i++){
		if(RingBufferRead(aRs232->RecieveBuffer, &data)){
			aBuffer[i] = data;
		}else{
			break;
		}
	}
	return i;
}


ISR(USART0_UDRE_vect){
	unsigned char data;
	
	if(RingBufferRead(Rs232[ERS232_NO_0]->SendBuffer, &data))
		UDR0 = data;
	else
		//disable Interrupt
		UCSR0B &= ~(1 << UDRIE0);
}

ISR(USART1_UDRE_vect){
	unsigned char data;
	
	if(RingBufferRead(Rs232[ERS232_NO_1]->SendBuffer, &data)){
		UDR1 = data;	
	}else{
		//disable Interrupt
		UCSR1B &= ~(1 << UDRIE1);
	}
}

ISR(USART0_RX_vect){
	RingBufferWrite(Rs232[ERS232_NO_0]->RecieveBuffer, UDR0);
}

ISR(USART1_RX_vect){
	RingBufferWrite(Rs232[ERS232_NO_1]->RecieveBuffer, UDR1);
}