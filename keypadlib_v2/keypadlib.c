// -*- coding: utf-8 -*-

/*
    * 這是一個簡單的4×4鍵盤掃描函式庫，需要高版本的SDCC才能運行（目前以在4.3.0測試過）。
    * 
    * 說明：
    *   1. 此函式庫是KeypadLib的第二個版本。
    *   2. 此函式庫比傳統的掃描方式快4倍，最差也能快將近2倍。
    * 
    * 注意事項：
    *   1. 這個函式庫預設使用P2作為鍵盤的接腳，若要更改，請於#include之前使用#define來定義KEY_PORT。
    *   2. 預設鍵盤的按鍵順序為"0123456789ABCDEF"（Row * 4 + Column）。若要更改，請使用setKeyCodes()函數。
    *   3. 使用方式與第一版KeypadLib略有不同，請參考範例。
    * 
    * 作者(Author): LSweetSour
    * 最後編輯(Last Updated): 2023/11/02
    * License: MIT License
    * 
*/
#include <8051.h>
#include <stdbool.h>

// 定義KeyPad接腳
#ifndef KEY_PORT
#define KEY_PORT P2
#endif

#define KEY_NULL 0

typedef unsigned char Byte;
static char _keyCodes[] = "0123456789ABCDEF";

// 函數別名
void (*key_setcodes)(char*) = setKeyCodes;
char (*key_get)(void) = getKeyCode;
char (*key_check)(void) = getPressedKey;
char (*key_getch)(void) = waitForReleasedKey;
char (*key_until)(char) = waitForSpecificKeyRelease;

// 更改對應按鍵（用於按鍵順序與預設不同時）
void setKeyCodes(char *newKeyCodes) {
    for (int i = 0; i < 15; i++) {
        _keyCodes[i] = newKeyCodes[i];
    }
}

// 讀取按鍵，回傳1~16，分別對應到16個按鍵（若無任何按鍵按下則回傳KEY_NULL）
Byte getKeyCode(void) {
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
char getPressedKey(void) {
    Byte result = getKeyCode();
    return (result == KEY_NULL) ? KEY_NULL : _keyCodes[result - 1];
}

// 讀取按鍵，並等待直到按鍵放開後，再回傳
char waitForReleasedKey(void) {
    char result;
    while (!(result = getPressedKey()));    // 等待按鍵按下並讀取
    while (getKeyCode());                   // 等待按鍵放開
    return result;
}

// 持續等待直到該鍵被釋放
char waitForSpecificKeyRelease(char c) {
    while (c != getPressedKey());           // 等待按鍵按下
    while (getKeyCode());                   // 等待按鍵放開
    return c;
}
