#include <stdlib.h>
#include <string.h>
#include <math.h>

#include <avr/pgmspace.h>
#include <avr/io.h>
#include <avr/interrupt.h>

#ifdef __cplusplus
extern "C"{
#endif

#define BIT_SET(a,b)   ((a) |= (1<<(b)))
#define BIT_CLEAR(a,b) ((a) &= ~(1<<(b)))
#define BIT_FLIP(a,b)  ((a) ^= (1<<(b)))
#define BIT_CHECK(a,b) (((a) & (1<<(b))) >> b)

#define sbi BIT_SET
#define cbi BIT_CLEAR

#define outport  *((uint8_t*)pp[1])
#define inport   *((uint8_t*)(pp[1] - 2))
#define dirport  *((uint8_t*)(pp[1] - 1))
#define timerReg *((uint8_t*)pp[3])

#define _pin  pp[0]
#define _port pp[1]
#define _tPin pp[2]
#define _tReg pp[3]

#define dw _digitalWrite
#define dt _digitalToggle
#define dr _digitalRead
#define pm _pinMode



void _digitalToggle(const uint8_t*);
uint8_t _digitalRead(const uint8_t*);
void _pinMode(const uint8_t*, uint8_t);
void _digitalWrite(const uint8_t*, uint8_t);

typedef uint8_t PIN[4];


#ifdef __cplusplus
} // extern "C"
#endif
