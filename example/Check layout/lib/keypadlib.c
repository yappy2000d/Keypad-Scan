// -*- coding: utf-8 -*-

/*
    * keypadlib v1.1.2 - A 4×4 keypad-scaning library. 
    * 
    * 支援SDCC版本3.0.1，適用於MCU 89S52。
    * 
    * 作者(Author): LSweetSour
    * 最後編輯(Last Updated): 2023/11/21
    * License: MIT License
    * 
*/
#ifndef _KEYPADLIB_C_
#define _KEYPADLIB_C_

#include <8051.h>
#include <stdbool.h>
#include <ctype.h>

// 定義KeyPad接腳
#ifndef KEY_PORT
#define KEY_PORT P2
#endif

// 定義Byte別名
typedef unsigned char Byte;

enum KEY_CONSTANT {
  KEY_NULL
};

static char _keyCodes[] = "0123456789ABCDEF";

// ASCII轉Byte
Byte _ascii2Byte(char c) {
  return (c >= 'A')? c-55: c-48;
}

// 更改對應按鍵（用於按鍵順序與預設不同時）
void key_setCode(char *newKeyCodes) {
    int i = 0;
    for (i = 0; i < 15; i++) {
        _keyCodes[i] = newKeyCodes[i];
    }
}

// 讀取按鍵，回傳1~16，分別對應到16個按鍵（若無任何按鍵按下則回傳KEY_NULL）
Byte key_get(void) {
    Byte key = KEY_NULL;

    // 檢查Rows，並決定Byte的前兩個bits
    KEY_PORT = 0xF0; // 將Columns全設為High
    switch (KEY_PORT) {
        case 0x70:
            key |= 0x0C; // Row 0被按下（F~C）
            break;
        case 0xB0:
            key |= 0x08; // Row 1被按下（B~8）
            break;
        case 0xD0:
            key |= 0x04; // Row 2被按下（7~4）
            break;
        case 0xE0:
            key |= 0x00; // Row 3被按下（3~0）
            break;
        default:
            return KEY_NULL; // 無按下
    }

    // 檢查Columns，並決定Byte的後兩個bits
    KEY_PORT = 0x0F; // 將Rows全設為High
    switch (KEY_PORT) {
        case 0x07:
            key |= 0x03; // Column 0被按下
            break;
        case 0x0B:
            key |= 0x02; // Column 1被按下
            break;
        case 0x0D:
            key |= 0x01; // Column 2被按下
            break;
        case 0x0E:
            key |= 0x00; // Column 3被按下
            break;
        default:
            return KEY_NULL; // 無按下（理論上不會執行到這）
    }
    return key + 1;
}

// 回傳當前壓著的按鍵（若無任何按鍵按下則回傳KEY_NULL）
char key_check(void) {
    Byte result = key_get();
    return (result == KEY_NULL) ? KEY_NULL : _keyCodes[result - 1];
}

// 讀取按鍵，並等待直到按鍵放開後，再回傳
char key_getChar(void) {
    char result;
    unsigned int i = 65536;
    while (!(result = key_check()));    // 等待按鍵按下並讀取
    while (key_get());                  // 等待按鍵放開
    while(i--);
    return result;
}

// 持續等待直到該鍵被釋放
char key_waitFor(char c) {
    while (c != key_check());           // 等待按鍵按下
    while (key_get());                  // 等待按鍵放開
    return c;
}


// 輸入兩個數字，回傳一個Byte
Byte key_getByte(void) {
  char a = key_getChar();
  char b = key_getChar();
  
  a = _ascii2Byte(a);
  b = _ascii2Byte(b);
  
  return (a << 4) + b;
}

unsigned int key_getWord(void) {
  return key_getByte()*256 + key_getByte();
}

// 輸入介於0~6553的十進位數字，當按下任一非數字鍵時，結束輸入並回傳
int key_getInt(void) {
  int value = 0;
  char key;
  while( isdigit(key=key_getChar()) ) {
    value = value*10 + _ascii2Byte(key);
  }
  return value;
}
#endif
