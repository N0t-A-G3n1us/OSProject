// This code waits for a character and transmits the character back (No interrupts)
 

#include <avr/io.h>
#include <stdint.h>                     // needed for uint8_t


#define FOSC 16000000                       // Clock Speed
#define BAUD 115200                
#define MYUBRR FOSC/16/BAUD -1


char ReceivedChar;


int main( void )
{
    /*Set baud rate */
    UBRR0H = (MYUBRR >> 8);
    UBRR0L = MYUBRR;
    
    UCSR0B |= (1 << RXEN0) | (1 << TXEN0);      // Enable receiver and transmitter
    UCSR0C |= (1 << UCSZ01) | (1 << UCSZ00);    // Set frame: 8data, 1 stp


    while(1)
    {
        while ( !(UCSR0A & (1 << RXC0)) )  // Wait until data is received
        
        ReceivedChar = UDR0;                    // Read the data from the RX buffer
        
        while ( !(UCSR0A & (1 << UDRE0)) ) // Wait until buffer is empty

        UDR0 = ReceivedChar;                    // Send the data to the TX buffer
    }    
}
