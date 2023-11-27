#include <8051.h>
#include <stdbool.h>
//define KEY_PORT P0
#include "lib/keypadlib.c"
#include "lib/uart.c"

const char KeyCodes[] = "0123456789ABCDEF";

void main(void) {
  char key;

  key_setKeys(KeyCodes);
  uart_initialize();

  while(true) {
    key = key_getChar();
    uart_put_char(key);
  }
}
