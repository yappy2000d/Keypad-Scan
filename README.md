# 4×4 鍵盤掃描函式庫
一個高效且輕量的4×4鍵盤掃描函式庫。

## 特點

- 提供更高效的按鍵掃描方法：
    + 未按下按鍵時，執行速度為傳統方式的400%。
    + 在按下按鍵時，執行速度為傳統方式的200%。
- 每個函數皆有提供精簡的函數別名，方便使用。

## 使用方式

1. 將檔案放在與主程式相同的目錄，並在程式碼中加入語句：

    ```c
    #include "keypadlib.c"
    ```

2. 預設情況下，這個函式庫使用P2作為鍵盤的接腳。如果你想使用其他接腳，請在`#include`語句之前使用`#define`來定義`KEY_PORT`。

3. 按鍵順序的計算方式：Row * 4 + Column。預設對應到："0123456789ABCDEF"，共16個字元。如果想更改按鍵順序，可以使用`setKeyCodes()`函數。

使用的更多細節請參見[範例](/example/)。

## 定義
- `KEY_PORT`：鍵盤的接腳，預設為P2。
- `Byte`：`unsigned char`的別名。

## 函數

以下是這個函式庫提供的主要函數：

- `void setKeyCodes(char *newKeyCodes)`: 用於更改按鍵順序。  

    > 函數別名：`key_setCodes()`

    > 範例：更改按鍵順序
    > ```c
    > char KeyCodes[] = "FEDCBA0987654321";
    > key_setCodes(KeyCodes);
    > ```


- `Byte getKeyCode(void)`: 讀取按鍵，回傳1~16，分別對應到16個按鍵，若無按鍵按下則回傳`KEY_NULL`。
    > 等效函數：`key_get()`

    > 範例：持續等待，直到任一個按鍵被按下
    > ```c
    > while(!key_get());
    > /* continue */
    > ```

- `char getPressedKey(void)`: 回傳當前壓著的按鍵，若無按鍵按下則回傳`KEY_NULL`。

    > 等效函數：`key_check()`
    
    > 範例：檢查A鍵是否被按下。
    > ```c
    > if(key_check() == 'A') {
    >     /* more codes here */
    > }
    > ```

- `char waitForReleasedKey(void)`: 讀取按鍵，並等待直到按鍵放開後，再回傳。

    > 等效函數：`key_getch()`

    > 範例：輸入一個字元並將其存入變數「key」中。
    > ```c
    > char ch = key_getch();
    > ```

- `char waitForSpecificKeyRelease(char c)`: 持續等待直到特定鍵被釋放。

    > 等效函數：`key_until()`

    > 範例：等待直到「=」被按下，之後將其發送出去。
    > ```c
    > char ch = key_until('=');
    > uart_putch(ch);
    > ```

- `Byte key_getByte(void)`: 讀取一個Byte（按兩字鍵盤，分別為高低各四個位元）
- `unsigned int key_getWord`: 讀取一個Word。
- `unsigned int key_getInt(void)`: 讀取一個Int（兩Bytes）。

## 作者

- 作者：LSweetSour
- 最後編輯：2023/11/20
- 授權方式：MIT License

## 其他事項
如有任何問題或建議，請聯繫作者。
