#include <util/delay.h>
#include <avr/io.h>

#define LED PORTB5

int main(void) {
  DDRB |= (1 << LED);
  for/*ever*/(;;) {
    PORTB |= (1 << LED);	//led off
    _delay_ms(3000);
    PORTB &= (0 << LED);	//led on
    _delay_ms(3000);
  }
}
