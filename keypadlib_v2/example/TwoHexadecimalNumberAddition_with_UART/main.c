#include <8051.h>
#include <stdbool.h>
#include "lib/keypadlib.c"
#include "lib/uart.c"

#define LED_PORT P1
#define BUTTON P3_2
#define BTN_UP 1

typedef unsigned char Byte;

inline Byte ascii2Byte(char c) {
  return (c >= 'A')? c-55: c-48;
}

Byte concatByte(char a, char b) {
    a = ascii2Byte(a);
    b = ascii2Byte(b);
    return (a << 4) + b;
}

void main(void) {
  uart_initialize();
  Byte dataA, dataB;
  char a, b;
  while(true) {
    a = key_getch();
    uart_put_char(a);
    
    b = key_getch();
    uart_put_char(b);
    
    dataA = concatByte(a, b);
    
    while(BUTTON == BTN_UP);
    uart_put_char('+');
    
    a = key_getch();
    uart_put_char(a);
    
    b = key_getch();
    uart_put_char(b);
    
    dataB = concatByte(a, b);
    
    while(BUTTON == BTN_UP);
    uart_put_char('=');
    
    uart_put_byte(dataA + dataB);
    uart_put_string("\r\n");
  }
}
