#include <8051.h>
#include <stdbool.h>
//define KEY_PORT P0
#include "lib/keypadlib.c"
#include "lib/uart.c"

const char KeyCodes[] = "0123456789ABCDEF";

void main(void) {
  key_setcodes(KeyCodes);
  uart_initialize();

  char key;

  while(true) {
    key = key_getch();
    uart_put_char(key);
  }
}
