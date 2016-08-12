/*
    FastIO
    Copyright (C) 2016  Muhammad Mohiuddin
    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.
    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.
    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "Arduino.h"
#include "FastIO.h"

#include <stdlib.h>
#include <string.h>
#include <math.h>

#include <avr/pgmspace.h>
#include <avr/io.h>
#include <avr/interrupt.h>


void _pinMode(const uint8_t *pp, uint8_t stat)
{
    uint8_t _SREG = SREG;cli();
    if(stat == OUTPUT) {
        _BIT_SET(DDR_PTR, PIN_MASK);
    }
    else if(stat == INPUT_PULLUP) {
        _BIT_CLEAR(DDR_PTR, PIN_MASK);
        _BIT_SET(PORT_PTR, PIN_MASK);
    }
    else {
        _BIT_CLEAR(DDR_PTR, PIN_MASK);
        _BIT_CLEAR(PORT_PTR, PIN_MASK);
    }
    SREG = _SREG;
    return;

}

uint8_t _digitalRead(const uint8_t *pp)
{
    if(TMR_REG) {
        _TMR_CLEAR(TMR_PTR, TMR_PIN);
    }
    if(_BIT_CHECK(PIN_PTR, PIN_MASK) == 0) {
        return LOW;
    }

    return HIGH;
}
void _digitalToggle(const uint8_t *pp)
{
    uint8_t _SREG = SREG;cli();
    _BIT_FLIP(PORT_PTR, PIN_MASK);
    SREG = _SREG;
}

void _digitalWrite(const uint8_t *pp, uint8_t stat)
{
    if(TMR_REG) {
        _TMR_CLEAR(TMR_PTR, TMR_PIN);
    }
    uint8_t _SREG = SREG;cli();
    if(stat) {
        _BIT_SET(PORT_PTR, PIN_MASK);
    }
    else {
        _BIT_CLEAR(PORT_PTR, PIN_MASK);
    }
    SREG = _SREG;
}
