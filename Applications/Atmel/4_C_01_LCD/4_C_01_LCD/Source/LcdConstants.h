// Ansteuerung eines HD44780 kompatiblen LCD im 4-Bit-Interfacemodus

 
#ifndef LCDCONSTANTS_H
#define LCDCONSTANTS_H

#include <avr/io.h>
 
#define LCD_MAX_BUSY_COUNTER 1000 
////////////////////////////////////////////////////////////////////////////////
// Pinbelegung für das LCD, an verwendete Pins anpassen
// Alle LCD Pins müssen an einem Port angeschlossen sein und die 4
// Datenleitungen müssen auf aufeinanderfolgenden Pins liegen
 
//  LCD DB4-DB7 <-->  PORTA Bit PA0-PA3
#define LCD_PORT_DATA      PORTA
#define LCD_PIN_DATA       PINA
#define LCD_DDR_DATA       DDRA
#define LCD_DB             PA0          // Bit 0 of data-nibble

//  LCD RS      <-->  PORTA Bit PA4     (RS: 1=Data, 0=Command)
#define LCD_PORT_RS        PORTA
#define LCD_PIN_RS         PINA
#define LCD_DDR_RS         DDRA
#define LCD_RS             PA4

 // LCD R/WR     <-->  PORTA Bit PA5     (R: 1, WR: 0)
 #define LCD_PORT_RW       PORTA
 #define LCD_PIN_RW        PINA
 #define LCD_DDR_RW        DDRA
 #define LCD_RW            PA5

//  LCD EN      <-->  PORTA Bit PA6     (EN: 1-Impuls für Daten)
#define LCD_PORT_EN        PORTA
#define LCD_PIN_EN         PINA
#define LCD_DDR_EN         DDRA
#define LCD_EN             PA6
 
 
////////////////////////////////////////////////////////////////////////////////
// LCD Ausführungszeiten (MS=Millisekunden, US=Mikrosekunden)
 
#define LCD_BOOTUP_MS           15
#define LCD_ENABLE_US           10
#define LCD_WRITEDATA_US        46
#define LCD_COMMAND_US          42
 
#define LCD_SOFT_RESET_MS1      5
#define LCD_SOFT_RESET_MS2      1
#define LCD_SOFT_RESET_MS3      1
#define LCD_SET_4BITMODE_MS     5
 
#define LCD_CLEAR_DISPLAY_MS    2
#define LCD_CURSOR_HOME_MS      2
#define LCD_MIN_DELAY_US        5
 
////////////////////////////////////////////////////////////////////////////////
// Zeilendefinitionen des verwendeten LCD
// Die Einträge hier sollten für ein LCD mit einer Zeilenlänge von 16 Zeichen passen
// Bei anderen Zeilenlängen müssen diese Einträge angepasst werden
 
#define LCD_DDADR_LINE1         0x00
#define LCD_DDADR_LINE2         0x40
#define LCD_DDADR_LINE3         0x14
#define LCD_DDADR_LINE4         0x54 
 
////////////////////////////////////////////////////////////////////////////////
// LCD Befehle und Argumente.
// Zur Verwendung in lcd_command
 
// Clear Display -------------- 0b00000001
#define LCD_CLEAR_DISPLAY       0x01
 
// Cursor Home ---------------- 0b0000001x
#define LCD_CURSOR_HOME         0x02
 
// Set Entry Mode ------------- 0b000001xx
#define LCD_SET_ENTRY           0x04
 
#define LCD_ENTRY_DECREASE      0x00
#define LCD_ENTRY_INCREASE      0x02
#define LCD_ENTRY_NOSHIFT       0x00
#define LCD_ENTRY_SHIFT         0x01
 
// Set Display ---------------- 0b00001xxx
#define LCD_SET_DISPLAY         0x08
 
#define LCD_DISPLAY_OFF         0x00
#define LCD_DISPLAY_ON          0x04
#define LCD_CURSOR_OFF          0x00
#define LCD_CURSOR_ON           0x02
#define LCD_BLINKING_OFF        0x00
#define LCD_BLINKING_ON         0x01
 
// Set Shift ------------------ 0b0001xxxx
#define LCD_SET_SHIFT           0x10
 
#define LCD_CURSOR_MOVE         0x00
#define LCD_DISPLAY_SHIFT       0x08
#define LCD_SHIFT_LEFT          0x00
#define LCD_SHIFT_RIGHT         0x04
 
// Set Function --------------- 0b001xxxxx
#define LCD_SET_FUNCTION        0x20
 
#define LCD_FUNCTION_4BIT       0x00
#define LCD_FUNCTION_8BIT       0x10
#define LCD_FUNCTION_1LINE      0x00
#define LCD_FUNCTION_2LINE      0x08
#define LCD_FUNCTION_5X7        0x00
#define LCD_FUNCTION_5X10       0x04
 
#define LCD_SOFT_RESET          0x30
 
// Set CG RAM Address --------- 0b01xxxxxx  (Character Generator RAM)
#define LCD_SET_CGADR           0x40
 
#define LCD_GC_CHAR0            0
#define LCD_GC_CHAR1            1
#define LCD_GC_CHAR2            2
#define LCD_GC_CHAR3            3
#define LCD_GC_CHAR4            4
#define LCD_GC_CHAR5            5
#define LCD_GC_CHAR6            6
#define LCD_GC_CHAR7            7
 
// Set DD RAM Address --------- 0b1xxxxxxx  (Display Data RAM)
#define LCD_SET_DDADR           0x80
 
#endif  

