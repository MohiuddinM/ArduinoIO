ArduinoIO
=========

This is an arduino library that I made for digital pin functions, it is faster than orignal functions and takes less memory.


<<<<<<< HEAD
Any pin of an arduino is repersented using an array. This array contains four things:
1. Pin mask for that pin
2. Address of the port to which the pin belongs
3. Timer mask (0x00 if pin is not PWM)
3. Address of timer control register (0x00 if not PWM)
=======
Any pin is represented using an array that contains, the port address and the pin number. For pins with timer functions, it also contains timer address, and enable bit number.
>>>>>>> origin/master


<<<<<<< HEAD
In this implementation the digital IO functions will be passed a pointer to this definition array, rather than just a pin number. Hence speeding up the whole process.

Another positive point of this implementation is that in most cases it runs out of the box i.e. without making any changes to your sketch. 



Usage
-----

Copy the two files FastIO.h and FastIO.c to the arduino core directory (\arduino-1.6.10\hardware\arduino\avr\cores\arduino)

After this all you have to do is add one line on the top of any sketch you want
```sh
#include <FastIO.h>
```
=======
All the pins could be defined in the variants like
```sh
#define  PIN_13 {0x07, 0x25, 0x00, 0x44}    // { pin number, port address, timer output, timer address }
```
In the sketch one could simply do
```sh
const PIN led = PIN_13;
_pinMode(led, OUTPUT);
_digitalWrite(led, HIGH);
```

TODO
----

Instead of providing pin numbers, provide pin masks
>>>>>>> origin/master
