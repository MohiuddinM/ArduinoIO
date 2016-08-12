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

#define PINB    0x23
#define PINC    0x26
#define PIND    0x29

#define DDRB    0x24
#define DDRC    0x27
#define DDRD    0x2A

#define PORTB   0x25
#define PORTC   0x28
#define PORTD   0x2B


#define BIT0 0b00000001
#define BIT1 0b00000010
#define BIT2 0b00000100
#define BIT3 0b00001000
#define BIT4 0b00010000
#define BIT5 0b00100000
#define BIT6 0b01000000
#define BIT7 0b10000000

#define TCCR0A  0x44
#define TCCR0B  0x45
#define TCCR1A  0x80
#define TCCR1B  0x81
#define TCCR1C  0x82
#define TCCR2A  0xB0
#define TCCR2B  0xB1


#define BIT7_6 0b11000000
#define BIT5_4 0b00110000


#define  PIN_0    {BIT0, PORTD, 0x00, 0x00}
#define  PIN_1    {BIT1, PORTD, 0x00, 0x00}
#define  PIN_2    {BIT2, PORTD, 0x00, 0x00}
#define  PIN_3    {BIT3, PORTD, BIT5_4, TCCR2A}//oc2b
#define  PIN_4    {BIT4, PORTD, 0x00, 0x00}
#define  PIN_5    {BIT5, PORTD, BIT5_4, TCCR0A}//oc0b
#define  PIN_6    {BIT6, PORTD, BIT7_6, TCCR0A}//oc0a
#define  PIN_7    {BIT7, PORTD, 0x00, 0x00}

#define  PIN_8    {BIT0, PORTB, 0x00, 0x00}
#define  PIN_9    {BIT1, PORTB, BIT7_6, TCCR1A}//oc1a
#define  PIN_10   {BIT2, PORTB, BIT5_4, TCCR1A}//oc1b
#define  PIN_11   {BIT3, PORTB, BIT7_6, TCCR2A}//oc2a
#define  PIN_12   {BIT4, PORTB, 0x00, 0x00}
#define  PIN_13   {BIT5, PORTB, 0x00, 0x00}

#define  PIN_14   {BIT0, PORTC, 0x00, 0x00}
#define  PIN_15   {BIT1, PORTC, 0x00, 0x00}
#define  PIN_16   {BIT2, PORTC, 0x00, 0x00}
#define  PIN_17   {BIT3, PORTC, 0x00, 0x00}
#define  PIN_18   {BIT4, PORTC, 0x00, 0x00}
#define  PIN_19   {BIT5, PORTC, 0x00, 0x00}


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
