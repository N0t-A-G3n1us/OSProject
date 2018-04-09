#include <util/delay.h>
#include <avr/io.h>

/*	BIT MATH OPERATIONS MACRO */
//get the bit in bit_pos position in reg register
#define bit_get(reg,bit_pos) ((reg) & (1<<(bit_pos) ))	
//set the bit in bit_pos position in reg register
#define bit_set(reg,bit_pos) ((reg) |= (1<<(bit_pos) ))	
//clear the bit in bit_pos position in reg register
#define bit_clear(reg,bit_pos) ((reg) &= ~(1<<(bit_pos) ))	
//flip the bit in bit_pos position in reg register
#define bit_flip(reg,bit_pos) ((reg) ^= (1<<(bit_pos) ))	
//check if the bit in bit_pos in the reg register is one (1) or zero (0)
#define bit_is_one(reg,bit_pos) (( (reg) & (1<<(bit_pos) ) )> 0)

/*	PORTS MACRO	*/
#define LED PORTB5


int main(void) {
  bit_set(DDRB, LED);
  for/*ever*/(;;) {
    bit_set(PORTB,LED);	//led off
    _delay_ms(3000);
    bit_clear(PORTB, LED);	//led on
    _delay_ms(3000);
  }
}
