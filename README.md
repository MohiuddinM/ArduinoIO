ArduinoIO
=========

This is an arduino library that I made for digital pin functions, it is faster than orignal functions and takes less memory.


Any pin is repersented using an array that contains, the port address and the pin number. For pins with timer functions, it also contains timer address, and enable bit number.

This array can then be repersented as a new type 'PIN' which is only a uint8_t[4]

All the pins could be defined in the variants like
```sh
#define  PIN_13 {0x07, 0x25, 0x00, 0x44}
```
In the sketch one could simply do
```sh
const PIN led = PIN_13;
_pinMode(led, OUTPUT);
_digitalWrite(led, HIGH);
```
