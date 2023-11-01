# 程式範例：16進制加法
兩個8bits的數字做16進制的加法，同時透過UART介面顯示在PC上。

## 前置需求
+ [uart.c](https://bit.nkust.edu.tw/~csshieh/teach/112A/mc/advanced/uart.zip) by [Chin-Shiuh Shieh](https://bit.nkust.edu.tw/~csshieh/).
+ Small Device C Compiler（SDCC）ver 4.3.0


## 目錄架構
```
/example/
   │  /lib/
   │    ├── uart.c
   │    └── keypadlib.c
   ├── main.c
   └── README.md
``` 

## 電路配置
+ Port 1：LEDs
+ Port 2：4×4 Keypad
    - Pin2.0：Row 0
    - Pin2.1：Row 1
    - Pin2.2：Row 2
    - Pin2.3：Row 3
    - Pin2.4：Column 3
    - Pin2.5：Column 2
    - Pin2.6：Column 1
    - Pin2.7：Column 0
+ Pin3.2：Button

## 操作說明
1. 輸入兩個數字來作為被加數（16進制）
2. 按一下按鈕
3. 再輸入兩個數字來作為被加數（也是16進制）
4. 按一下按鈕
5. 此時應能在終端上看到兩個數字的和（也可能溢位）

