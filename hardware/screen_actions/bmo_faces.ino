#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_ST7735.h>

#define TFT_CS 10
#define TFT_DC 9
#define TFT_RST 8

#define BLACK 0x0000
#define BMO_COLOR 0x07FA //0,63,26
#define RED 0xF800
#define CHARCOL 0x0000

Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS, TFT_DC, TFT_RST);

void setup() {

  Serial.begin(9600);
  tft.initR(INITR_BLACKTAB);
  tft.fillScreen(BMO_COLOR);
   tft.setRotation(0);
}

void loop()
{
  bmo_speak();
  delay(1000);
  bmo_speak2();
  delay(1000);
}

void bmo_hello()
{
  uint16_t x=31;
  uint16_t y=40;
  uint16_t R=5;
  uint16_t r=3;
  tft.fillCircle(x, y, r, BLACK);
  tft.fillCircle(x, y*3, r, BLACK);
  //fillCircle(uint16_t x0, uint16_t y0, uint16_t r, uint16_t color);
  tft.fillCircle(x*2, y*2, R, BLACK);

}

void bmo_greeting()
{
  //void drawLine(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1, uint16_t color);
  uint16_t x=31;
  uint16_t y=40;
  uint16_t r=3;
  tft.fillCircle(x, y, r, BLACK);
  tft.fillCircle(x, y*3, r, BLACK);
  tft.drawLine(x*2,y+5,x*2,y*2.8,BLACK);
}

void bmo_ow()
{
  //void drawLine(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1, uint16_t color);
  uint16_t x=31;
  uint16_t y=40;
  uint16_t r=3;
  tft.fillCircle(x, y, r, BLACK);
  tft.fillCircle(x, y*3, r, BLACK);
  tft.drawCircle(x*2,y*2,r*4,BLACK);
}

void bmo_smile()
{
  uint16_t x=31;
  uint16_t y=40,r=3;

  eyes1(x,y,r);
   
   tft.drawLine(x*2,y+5,x*2.3,y*1.6,BLACK);
   tft.drawLine(x*2.3,y*2.3,x*2,y*2.8,BLACK);
   
   tft.drawLine(x*2.3,y*1.6,x*2.3,y*2.3,BLACK);
}

void idk()
{

 tft.setRotation(3);
 uint8_t tz=2;
 uint16_t v=10;
  tft.drawChar(5, v, 'D', CHARCOL, BMO_COLOR, tz);
  tft.drawChar(26, v, 'U', CHARCOL, BMO_COLOR, tz);
  tft.drawChar(50, v, 'D', CHARCOL, BMO_COLOR, tz);
  tft.drawChar(74, v, 'D', CHARCOL, BMO_COLOR, tz);
  tft.drawChar(98, v, 'D', CHARCOL, BMO_COLOR, tz);
  tft.drawChar(115, v, 'A', CHARCOL, BMO_COLOR, tz);
  tft.drawChar(133, v, 'P', CHARCOL, BMO_COLOR, tz);
  
  tft.drawChar(5, 42, 'P', CHARCOL, BMO_COLOR, tz);
  tft.drawChar(29, 42, 'D', CHARCOL, BMO_COLOR, tz);
  tft.drawChar(53, 42, 'D', CHARCOL, BMO_COLOR, tz);
  tft.drawChar(77, 42, 'D', CHARCOL, BMO_COLOR, tz);
  tft.drawChar(101, 42, 'F', CHARCOL, BMO_COLOR, tz);    
  tft.drawChar(125, 42, 'G', CHARCOL, BMO_COLOR, tz);
}

void bmo_speak()
{
  uint16_t x=31;
  uint16_t y=40;
  uint16_t R=5;
  uint16_t r=3;
   tft.fillRect(0,0,x*1.8,y*4,BMO_COLOR);
  tft.fillCircle(x*1.7, y*2, r*10, BLACK);
  tft.fillRect(0,0,x*1.8,y*4,BMO_COLOR);
  tft.fillRoundRect(x*2.3, y*1.8, 11, 18, 3, RED);
  eyes1(x,y,r);
  //tft.fillRect(x*2.1,0,x*3,y*4,BMO_COLOR);

}
void bmo_speak2()
{
  uint16_t x=31;
  uint16_t y=40;
  uint16_t R=5;
  uint16_t r=3;
  
  tft.fillCircle(x*1.7, y*2, r*10, BLACK);
  tft.fillRect(0,0,x*1.8,y*4,BMO_COLOR);
  tft.fillRoundRect(x*2.3, y*1.8, 11, 18, 3, RED);
  eyes1(x,y,r);
  tft.fillRect(x*2.1,0,x*3,y*4,BMO_COLOR);

}

void eyes1(uint16_t x,uint16_t y,uint16_t r){
  tft.fillCircle(x, y, r, BLACK);
  tft.fillCircle(x, y*3, r, BLACK);
}





