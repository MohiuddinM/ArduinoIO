FastIO
======

This is an arduino library that I made for digital pin functions, it is faster than orignal functions and takes less memory.


Any pin of an arduino is repersented using an array. This array contains four things:

1. Pin mask for that pin
2. Address of the port to which the pin belongs
3. Timer mask (0x00 if pin is not PWM)
3. Address of timer control register (0x00 if not PWM)


In this implementation the digital IO functions will be passed a pointer to this definition array, rather than just a pin number. Hence speeding up the whole process.

Another positive point of this implementation is that in most cases it runs out of the box i.e. without making any changes to your sketch. 



Usage
-----

Copy the two files FastIO.h and FastIO.c to the arduino core directory (\arduino-1.6.10\hardware\arduino\avr\cores\arduino)

After this all you have to do is add one line on the top of any sketch you want
```sh
#include <FastIO.h>
```
