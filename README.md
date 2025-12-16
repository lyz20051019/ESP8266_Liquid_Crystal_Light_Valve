此项目用于实现在手机端访问wifi即可操作液晶屏幕实现液晶光阀的效果。
首先需要在arduino中安装esp8266以及tft_eSPI相关依赖，替换tft_eSPI中的User_Setup.h为相应屏幕的文件，即可通过编译main中的main.ino生成通用的二进制文件。\
其中接线如下所示\

```language
ST7735(1.44inch)

// For NodeMCU - use pin numbers in the form PIN_Dx where Dx is the NodeMCU pin designation
#define TFT_MISO  PIN_D7  // Automatically assigned with ESP8266 if not defined
#define TFT_MOSI  PIN_D7  // Automatically assigned with ESP8266 if not defined
#define TFT_SCLK  PIN_D5  // Automatically assigned with ESP8266 if not defined

#define TFT_CS    PIN_D8  // Chip select control pin D8
#define TFT_DC    PIN_D3  // Data Command control pin
#define TFT_RST   -1  // Reset pin (could connect to NodeMCU RST, see next line)
```
即SDA(MOSI)接D7\
SCL接D5\
CS接D8\
DC接D3\
RST接主板RST引脚\
VCC接3.3V\
GND接GND\
其他屏幕类似\

```language
ST7789(有CS引脚,1.5inch)

// For NodeMCU - use pin numbers in the form PIN_Dx where Dx is the NodeMCU pin designation
#define TFT_MISO  PIN_D6  // Automatically assigned with ESP8266 if not defined
#define TFT_MOSI  PIN_D7  // Automatically assigned with ESP8266 if not defined
#define TFT_SCLK  PIN_D5  // Automatically assigned with ESP8266 if not defined

#define TFT_CS    PIN_D8  // Chip select control pin D8
#define TFT_DC    PIN_D3  // Data Command control pin
#define TFT_RST   PIN_D4  // Reset pin (could connect to NodeMCU RST, see next line)
// #define TFT_RST  -1     // Set TFT_RST to -1 if the display RESET is connected to NodeMCU RST or 3.3V
```


```language
ST7789(无CS引脚,1.3inch)

// For NodeMCU - use pin numbers in the form PIN_Dx where Dx is the NodeMCU pin designation
#define TFT_MISO  PIN_D6  // Automatically assigned with ESP8266 if not defined
#define TFT_MOSI  PIN_D7  // Automatically assigned with ESP8266 if not defined
#define TFT_SCLK  PIN_D5  // Automatically assigned with ESP8266 if not defined

#define TFT_CS    -1  // Chip select control pin D8
#define TFT_DC    PIN_D3  // Data Command control pin
#define TFT_RST   PIN_D4  // Reset pin (could connect to NodeMCU RST, see next line)
```
