#include <8051.h>
#include <stdbool.h>
//define KEY_PORT P0				// Optional
#include "keypadlib.c"

#define Byte unsigned char
#define LED_PORT P1
#define BUTTON P3_2
#define BTN_UP 1

//const char KeyCodes[] = "0123456789ABCDEF";	// Optional

Byte ascii2Byte(char c) {
  return (c >= 'A')? c-55: c-48;
}

// concat high digits and low digits to a byte
Byte concatByte(char a, char b) {
  a = ascii2Byte(a);
  b = ascii2Byte(b);
  return (a << 4) + b;
}

void main(void) {
  //key_setcodes(KeyCodes);			// Optional
  Byte summand, addend, sum;
  
  // a: high digits, b: low digits
  char a, b;
  
  while(true) {
    a = key_getch();
    b = key_getch();
    
    summand = concatByte(a, b);
    LED_PORT = ~summand;
    
    // wait until button is pressed
    while(BUTTON == BTN_UP);
    
    a = key_getch();
    b = key_getch();
    
    addend = concatByte(a, b);
    LED_PORT = ~addend;
    
    // wait until button is pressed
    while(BUTTON == BTN_UP);
    sum = summand + addend;
    LED_PORT = sum;
  }
}
