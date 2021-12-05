#include <avr/io.h>
#include <string.h>
#include "Ringbuffer.h"
#include "Rs232.h"

#define CPU_CLK 16000000

void TestRS232_Send( void );
void TestRS232_SendReceive( void );

int main(void)
{
	TestRS232_SendReceive();
}

void
TestRS232_Send( void )
{
	TRS232 rs232;
	TRS232Config config;
	
	config.Baudrate = 9600;
	config.ReceiveBufferSize = 20;
	config.SendBufferSize = 20;
	
	rs232 = RS232Create( ERS232_NO_0, config, CPU_CLK );
	
	while(1)
	{
		RS232SendData( rs232, "12345 ", 6);
		delayMs( 1000 );
	}
}

void
TestRS232_SendReceive( void )
{
	TRS232 rs232;
	TRS232Config config;
	
	config.Baudrate = 9600;
	config.ReceiveBufferSize = 20;
	config.SendBufferSize = 20;
	
	rs232 = RS232Create( ERS232_NO_0, config, CPU_CLK);
	
	unsigned char receivedData[20];
	
	while(1)
	{		
		unsigned char received = RS232ReceiveData( rs232, (unsigned char *)receivedData, 20);
		delayMs(100);
		
		if(0 != received) {
			RS232SendData( rs232, (unsigned char *)receivedData, received );
			RS232SendData( rs232, " ", 1 );
		}
	}
}