// This code waits for a character and transmits the character back (with interrupts)
 //(ECHO program using interrupts)

#include <avr/io.h>
#include <stdint.h>   // needed for uint8_t
#include <util/delay.h>

#include <avr/interrupt.h>



#define FOSC 16000000    // Clock Speed
#define BAUD 9600                
#define MYUBRR FOSC/16/BAUD -1


volatile char ReceivedChar;


int main( void )
{
    /*Set baud rate */
    UBRR0H = (MYUBRR >> 8);
    UBRR0L = MYUBRR;
    
    UCSR0B |= (1 << RXEN0) | (1 << TXEN0);      // Enable receiver and transmitter
    UCSR0B |= (1 << RXCIE0);                    // Enable reciever interrupt
    UCSR0C |= (1 << UCSZ01) | (1 << UCSZ00);    // Set frame: 8data, 1 stp

    sei();                                      // enable interrupts
	
    while(1)
    {
		
		;										// Main loop, waiting for interrupt to show that a msg arrived
    }    
}

ISR (USART_RX_vect)
{	
    ReceivedChar = UDR0;                       // Read data from the RX buffer
    UDR0 = ReceivedChar;                       // Write the data to the TX buffer
}
