#include "IRremote.h"
#include "IRremoteInt.h"
#include "Functions.h"

#include <stdio.h>
#include <avr/io.h>
#include <avr/interrupt.h>


#define RECV_PIN PORTD7
#define FNV_PRIME_32 16777619
#define FNV_BASIS_32 2166136261

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

/* IDE SCHEMA
/////////////////////////////////
/////////////////////////////////
#include <IRremote.h>

int RECV_PIN = 11;
IRrecv irrecv(RECV_PIN);
decode_results results;

void setup()
{
  Serial.begin(9600);
  irrecv.enableIRIn(); // Start the receiver
}

void loop() {
  if (irrecv.decode(&results)) {
    Serial.println(results.value, HEX);
    irrecv.resume(); // Receive the next value
  }
}

/////////////////////////////////
/////////////////////////////////
*/



volatile irparams_t irparams;

void resume() {
  irparams.rcvstate = STATE_IDLE;
  irparams.rawlen = 0;
}

void enableIRIn() {
  cli();
  // setup pulse clock timer interrupt
  //Prescale /8 (16M/8 = 0.5 microseconds per tick)
  // Therefore, the timer interval can range from 0.5 to 128 microseconds
  // depending on the reset value (255 to 0)
  TIMER_CONFIG_NORMAL();

  //Timer2 Overflow Interrupt Enable
  TIMER_ENABLE_INTR;

  TIMER_RESET;

  sei();  // enable interrupts

  // initialize state machine variables
  irparams.rcvstate = STATE_IDLE;
  irparams.rawlen = 0;

  // set pin modes
  //pinMode(irparams.recvpin, INPUT);	
  //set pin recvpin as input with pull up
  
	DDRD &= ~(1 << DDD7); // Clear the PD0 pin
    // PD0 is now an input

	PORTD |= (1 << RECV_PIN); // turn On the Pull-up
    // PDO is now an input with pull-up enabled
}

int decode(decode_results *results) {
  results->rawbuf = irparams.rawbuf;
  results->rawlen = irparams.rawlen;
  if (irparams.rcvstate != STATE_STOP) {
    return ERR;
  }
#ifdef DEBUG
  Serial.println("Attempting NEC decode");
#endif
  if (decodeNEC(results)) {
    return DECODED;
  }
#ifdef DEBUG
  Serial.println("Attempting Sony decode");
#endif
  if (decodeSony(results)) {
    return DECODED;
  }
#ifdef DEBUG
  Serial.println("Attempting Sanyo decode");
#endif
  if (decodeSanyo(results)) {
    return DECODED;
  }
#ifdef DEBUG
  Serial.println("Attempting Mitsubishi decode");
#endif
  if (decodeMitsubishi(results)) {
    return DECODED;
  }
#ifdef DEBUG
  Serial.println("Attempting RC5 decode");
#endif  
  if (decodeRC5(results)) {
    return DECODED;
  }
#ifdef DEBUG
  Serial.println("Attempting RC6 decode");
#endif 
  if (decodeRC6(results)) {
    return DECODED;
  }
#ifdef DEBUG
    Serial.println("Attempting Panasonic decode");
#endif 
    if (decodePanasonic(results)) {
        return DECODED;
    }
#ifdef DEBUG
    Serial.println("Attempting LG decode");
#endif 
    if (decodeLG(results)) {
        return DECODED;
    }
#ifdef DEBUG
    Serial.println("Attempting JVC decode");
#endif 
    if (decodeJVC(results)) {
        return DECODED;
    }
#ifdef DEBUG
  Serial.println("Attempting SAMSUNG decode");
#endif
  if (decodeSAMSUNG(results)) {
    return DECODED;
  }
  // decodeHash returns a hash on any input.
  // Thus, it needs to be last in the list.
  // If you add any decodes, add them before this.
  if (decodeHash(results)) {
    return DECODED;
  }
  // Throw away and start over
  resume();
  return ERR;
}

void main(){
	
	decode_results results;
	
	//setup
	enableIRIn();
	
	//loop
	while(1){
		 if ( decode(&results)) {
			//Serial.println(results.value, HEX);
			resume(); // Receive the next value
				}
	}
	
	
}



