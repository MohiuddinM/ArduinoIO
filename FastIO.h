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

#include <stdlib.h>
#include <string.h>
#include <math.h>

#include <avr/pgmspace.h>
#include <avr/io.h>
#include <avr/interrupt.h>

#ifdef __cplusplus
extern "C"{
#endif

#if !(defined(__AVR_ATmega328P__) || defined(__AVR_ATmega8__) || defined(__AVR_ATmega168__))
#error "FastIO not compatible with current board"
#endif

#ifndef __FAST_IO
#define __FAST_IO



/***************************** Defines ***********************************************/

#define FASTIO_PINB    0x23
#define FASTIO_PINC    0x26
#define FASTIO_PIND    0x29

#define FASTIO_DDRB    0x24
#define FASTIO_DDRC    0x27
#define FASTIO_DDRD    0x2A

#define FASTIO_PORTB   0x25
#define FASTIO_PORTC   0x28
#define FASTIO_PORTD   0x2B


#define FASTIO_BIT0 0b00000001
#define FASTIO_BIT1 0b00000010
#define FASTIO_BIT2 0b00000100
#define FASTIO_BIT3 0b00001000
#define FASTIO_BIT4 0b00010000
#define FASTIO_BIT5 0b00100000
#define FASTIO_BIT6 0b01000000
#define FASTIO_BIT7 0b10000000

#define FASTIO_TCCR0A  0x44
#define FASTIO_TCCR0B  0x45
#define FASTIO_TCCR1A  0x80
#define FASTIO_TCCR1B  0x81
#define FASTIO_TCCR1C  0x82
#define FASTIO_TCCR2A  0xB0
#define FASTIO_TCCR2B  0xB1


#define FASTIO_BIT7_6 0b11000000
#define FASTIO_BIT5_4 0b00110000


#define  PIN_0    {FASTIO_BIT0, FASTIO_PORTD, 0x00, 0x00}
#define  PIN_1    {FASTIO_BIT1, FASTIO_PORTD, 0x00, 0x00}
#define  PIN_2    {FASTIO_BIT2, FASTIO_PORTD, 0x00, 0x00}
#define  PIN_3    {FASTIO_BIT3, FASTIO_PORTD, FASTIO_BIT5_4, FASTIO_TCCR2A}//oc2b
#define  PIN_4    {FASTIO_BIT4, FASTIO_PORTD, 0x00, 0x00}
#define  PIN_5    {FASTIO_BIT5, FASTIO_PORTD, FASTIO_BIT5_4, FASTIO_TCCR0A}//oc0b
#define  PIN_6    {FASTIO_BIT6, FASTIO_PORTD, FASTIO_BIT7_6, FASTIO_TCCR0A}//oc0a
#define  PIN_7    {FASTIO_BIT7, FASTIO_PORTD, 0x00, 0x00}

#define  PIN_8    {FASTIO_BIT0, FASTIO_PORTB, 0x00, 0x00}
#define  PIN_9    {FASTIO_BIT1, FASTIO_PORTB, FASTIO_BIT7_6, FASTIO_TCCR1A}//oc1a
#define  PIN_10   {FASTIO_BIT2, FASTIO_PORTB, FASTIO_BIT5_4, FASTIO_TCCR1A}//oc1b
#define  PIN_11   {FASTIO_BIT3, FASTIO_PORTB, FASTIO_BIT7_6, FASTIO_TCCR2A}//oc2a
#define  PIN_12   {FASTIO_BIT4, FASTIO_PORTB, 0x00, 0x00}
#define  PIN_13   {FASTIO_BIT5, FASTIO_PORTB, 0x00, 0x00}

#define  PIN_14   {FASTIO_BIT0, FASTIO_PORTC, 0x00, 0x00}
#define  PIN_15   {FASTIO_BIT1, FASTIO_PORTC, 0x00, 0x00}
#define  PIN_16   {FASTIO_BIT2, FASTIO_PORTC, 0x00, 0x00}
#define  PIN_17   {FASTIO_BIT3, FASTIO_PORTC, 0x00, 0x00}
#define  PIN_18   {FASTIO_BIT4, FASTIO_PORTC, 0x00, 0x00}
#define  PIN_19   {FASTIO_BIT5, FASTIO_PORTC, 0x00, 0x00}


#define PORT_PTR  *((uint8_t*)pp[1])
#define PIN_PTR   *((uint8_t*)(pp[1] - 2))
#define DDR_PTR   *((uint8_t*)(pp[1] - 1))
#define TMR_PTR   *((uint8_t*)pp[3])


#define PIN_MASK  (pp[0])
#define PORT_REG  (pp[1])
#define TMR_PIN   (pp[2])
#define TMR_REG   (pp[3])


/***************************** Globals ***********************************************/

typedef uint8_t PIN[4];
const PIN pins[20] = {PIN_0, PIN_1, PIN_2, PIN_3, PIN_4, PIN_5, PIN_6, PIN_7, PIN_8, PIN_9, PIN_10, PIN_11, PIN_12, PIN_13, PIN_14, PIN_15, PIN_16, PIN_17, PIN_18, PIN_19};


/***************************** Macros ***********************************************/

#define _BIT_SET(a,b)   ((a) |= (b))
#define _BIT_CLEAR(a,b) ((a) &= ~(b))
#define _BIT_FLIP(a,b)  ((a) ^= (b))
#define _BIT_CHECK(a,b) ((a) & (b))
#define _TMR_CLEAR(a,b) ((a) &= ~(b))

#define dw(pin, stat) _digitalWrite(pins[pin], stat)
#define pm(pin, stat) _pinMode(pins[pin], stat)
#define dr(pin)       _digitalRead(pins[pin])
#define dt(pin)       _digitalToggle(pins[pin])

#define digitalRead(pin)        dr(pin)
#define digitalWrite(pin, stat) dw(pin, stat)
#define pinMode(pin, stat)      pm(pin, stat)
#define digitalToggle(pin)      dt(pin)


/***************************** Functions ***********************************************/

void _digitalToggle(const uint8_t*);
uint8_t _digitalRead(const uint8_t*);
void _pinMode(const uint8_t*, uint8_t);
void _digitalWrite(const uint8_t*, uint8_t);


#endif  //include guard

#ifdef __cplusplus
} // extern "C"
#endif
