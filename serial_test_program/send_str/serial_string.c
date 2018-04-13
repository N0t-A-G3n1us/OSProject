// This code waits for a character and transmits the character back (with interrupts)
 //(ECHO program using interrupts)


#include <stdint.h>   // needed for uint8_t
#include <stdio.h>
#include <stdlib.h>

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#define VERSION_INT	-1	//-1 => no interrupt else interrput version

#define FOSC 16000000    // Clock Speed
#define BAUD 9600                
#define MYUBRR FOSC/16/BAUD -1

#define MAX_LENGHT 100

volatile char ReceivedChar;


void send_char(char c){
	char temp;
	while ((UCSR0A & (1 << UDRE0)) == 0) {};	
	temp=UDR0;
	UDR0 = c;
	}

void send_char_noint(char c){
	
	while ( !(UCSR0A & (1 << RXC0)) )  // Wait until data is received
        
	ReceivedChar = UDR0;                    // Read the data from the RX buffer
	
	while ( !(UCSR0A & (1 << UDRE0)) ) // Wait until buffer is empty

	UDR0 = ReceivedChar;                    // Send the data to the TX buffer

	}

void send_string(char s[]){
	int i =0;
	
	while (s[i] != 0x00)
	{
		send_char(s[i]);
		i++;
	}
}

int send_string_noint(const char * str){
	int status = -1;
 
    if (str != NULL) {
        status = 0;
 
         while (*str != '\0') {
            /* Wait for the transmit buffer to be ready */
			while ((UCSR0A & (1 << UDRE0)) == 0) {};	
 
            /* Transmit data */
            char temp= UDR0;	//to free the flag
            UDR0= *str;
 
            /* If there is a line-feed, add a carriage return */
            if (*str == '\n') {
                /* Wait for the transmit buffer to be ready */
			while ( !(UCSR0A & (1 << UDRE0)) ) // Wait until buffer is empty
                UCA0TXBUF = '\r';
            }
 
            str++;
        }
    }
 
    return status;
	}

int main( void )
{
    /*Set baud rate */
    UBRR0H = (MYUBRR >> 8);
    UBRR0L = MYUBRR;
    
    UCSR0B |= (1 << RXEN0) | (1 << TXEN0);      // Enable receiver and transmitter
    UCSR0B |= (1 << RXCIE0);                    // Enable reciever interrupt
    UCSR0C |= (1 << UCSZ01) | (1 << UCSZ00);    // Set frame: 8data, 1 stp


	//////////VERSIONE INTERRUPTED
	#if VERSION_INT
		sei();                                      // enable interrupts
		
		char ready_str[MAX_LENGHT]="board ready to comunicate \n";
		send_string(ready_str);
		
		while(1)
		{
			//work
					
			;										// Main loop, waiting for interrupt to show that a msg arrived
		}
			//////////VERSIONE NON INTERRUPTED
	#else 
		char * string = malloc(sizeof(char)*100);	
		
		
    #endif    
}




ISR(USART_RX_vect)
{	
    ReceivedChar = UDR0;                       // Read data from the RX buffer
    UDR0 = ReceivedChar;
    
    
    //TODO aggiungere un char '\n' al carattere ReceivedChar in una nuova stringa e chiamare la send_string passandola come parametro;	
    // Write the data to the TX buffer
	
	
}


	
