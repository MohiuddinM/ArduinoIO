#include "Arduino.h"
#include "digitalIO.h"

#include <stdlib.h>
#include <string.h>
#include <math.h>

#include <avr/pgmspace.h>
#include <avr/io.h>
#include <avr/interrupt.h>




uint8_t _SREG;


void _pinMode(const uint8_t *pp, uint8_t stat)
{
    //if (_port == 0) return;
    _SREG = SREG;cli();
    if(stat == 1)//output == 1
    {
        sbi(dirport, _pin);
    }
    else if(stat == 2)    //input_pullup == 2
    {
        cbi(dirport, _pin);
        sbi(outport, _pin);
    }
    else                 //input == 0
    {
        cbi(dirport, _pin);
        cbi(outport, _pin);
    }
    SREG = _SREG;
    return;

}
uint8_t _digitalRead(const uint8_t *pp)
{
    //if (_port == 0) return LOW;

    // If the pin that support PWM output, we need to turn it off
    // before getting a digital reading.
    if(_tReg) cbi(timerReg, _tPin);
    return BIT_CHECK(inport, _pin);
}
void _digitalToggle(const uint8_t* pp)
{
    _SREG = SREG;cli();
    BIT_FLIP(outport, _pin);
    SREG = _SREG;
}
void _digitalWrite(const uint8_t* pp, uint8_t stat)
{
    // pp = {[timer],[timerpin],[port],[portpin]};
    //if (_port == 0) return;
    if(_tReg) cbi(timerReg, _tPin);
    _SREG = SREG;cli();
    if(stat) sbi(outport, _pin);
    else cbi(outport, _pin);
    SREG = _SREG;
}
