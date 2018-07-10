#include <Adafruit_GFX.h>    // Core graphics library
#include <Adafruit_ST7735.h> // Hardware-specific library
#include <SPI.h>
#include <Wire.h>
#include "MAX30100_PulseOximeter.h"

//
// Screen coordinates
//      0        X (160)   159
//    0 +------------------>
//      |
//   Y  |
// (128)|
//      |
//  127 V
//

#define TFT_CS     10
#define TFT_RST    8  
#define TFT_DC     9

Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS,  TFT_DC, TFT_RST);
PulseOximeter pox;
MAX30100 sensor;

#define ADC_MAX_VAL 65535

float fScalingFactor = 0.0;

#define SCREEN_HEIGHT       128
#define SCREEN_WIDTH        160
#define PULSE_WINDOW_HEIGHT 100

unsigned char ucScreenIndex = 0;  // Index pointer used to control the scanning of the waveform from left to right in the waveform window

uint16_t IR_RawSignal = 0;  // Var used to hold the raw Phototransistor value
uint16_t RED_RawSignal = 0;
int iPulseValueIR = 0;
int iPulseValueIROld = 0;
char cStringArray[100];       // Temp string array used to print numbers to the TFT display
uint16_t lADC0MaxValue = 0;        // The calculated pulse wave mimimum with finger in place and IR source turned on
uint16_t lADC0MinValue = 0;        // The calculated pulse wave mimimum with finger in place and IR source turned on
uint16_t iADC0SpanValue = 0;       // The calculated pulse wave span (max-min) with finger in place and IR source turned on

int iBPM = 0;
int iBPMOld = 0;
int SPO2 = 0;
int SPO2Old = 0;
int iPulseTriggerLevelHigh = 0;
int iPulseTriggerLevelLow = 0;

#define UPPER_PULSE_RATE 220

int iSampleCount = 0; // Holds the incremental counter to be compared with that of below
int iSampleCountMax = 8; // This number dictates how many samples are thrown away before the screen is updated
uint32_t tsLastReport = 0;

#define REPORTING_PERIOD_MS 1000
#define SAMPLE_PERIOD_uS    1000 
#define MAX_UL 4294967295UL
unsigned long ulSamplePeriod = SAMPLE_PERIOD_uS;
unsigned long ulCurrentTime = 0;
unsigned long ulOldTime = 0;
unsigned long ulElapsedTime = 0;
unsigned long ulPulseCurrentTime = 0;
unsigned long ulPulseOldTime = 0;

int TempAudioValue = 0;
int MaxAudioValue = 0;
int MinAudioValue = 0;
uint32_t LastUpdate = 0;
boolean FirstUpdate = true;
#define UpdateAudioValue 10000

#define BLACK 0x0000
#define BMO_COLOR 0x07FA //0,63,26
#define RED 0xF800
#define WHITE 0xFFFF
#define CHARCOL 0x0000
#define TONGUE 0x4F8B //8,42,11
#define MOUTH  0x1BA8

const int analogInPin = A0;
int outputValue = 0;

void setup() {
 Serial.begin(115200);
 tft.initR(INITR_BLACKTAB);
 tft.fillScreen(BMO_COLOR);
 tft.setRotation(0);
}


void loop() {
  char buff = Serial.read();

  switch(buff) {
   case 'i':
    Serial.println("o");
   break;

   case 's':
   tft.setRotation(3);
    Serial.println("START");
    handleCalibration();
    setupFinalDisplay();
    //Serial.println('\n');
    //Serial.println(lADC0MinValue);
    //Serial.println((int)lADC0MinValue);
    ucScreenIndex = SCREEN_WIDTH;
    iADC0SpanValue = (lADC0MaxValue - lADC0MinValue);
    //Serial.println('\n');
    //Serial.println(iADC0SpanValue);
    fScalingFactor = (float)((float)(PULSE_WINDOW_HEIGHT)/(float)ADC_MAX_VAL);
    //Serial.println('\n');
    //Serial.println(fScalingFactor);
    ulOldTime = micros();
    iPulseTriggerLevelHigh = ((int)(((float)(lADC0MaxValue - lADC0MinValue)) * 0.10)) + lADC0MinValue;
    iPulseTriggerLevelLow  = ((int)(((float)(lADC0MaxValue - lADC0MinValue)) * 0.30)) + lADC0MinValue;
    
     while(Serial.read() != 'f') { 
      pox.update();
      sensor.update();
      ulCurrentTime = micros();
      if (ulCurrentTime >= ulOldTime)
       ulElapsedTime = ulCurrentTime - ulOldTime;
      else
       ulElapsedTime = (MAX_UL - ulOldTime) + ulCurrentTime;
    
      if (ulElapsedTime >= ulSamplePeriod) {
       ulOldTime = ulCurrentTime;

       sensor.getRawValues(&IR_RawSignal, &RED_RawSignal); // Read raw level from analogue input
       //Serial.println(IR_RawSignal);
       iPulseValueIR = (int) (((float)IR_RawSignal) * fScalingFactor); // Scaled waveform 0-5, 0-1023 => 0-PULSE_WINDOW_HEIGHT
       //Serial.println(iPulseValueIR);
       iPulseValueIR = iPulseValueIR - (PULSE_WINDOW_HEIGHT/2);
       //iPulseValueIR = (int)((float)iPulseValueIR * fAmplificationFactor);
       iPulseValueIR = iPulseValueIR + (PULSE_WINDOW_HEIGHT/2);
       iPulseValueIR = PULSE_WINDOW_HEIGHT - iPulseValueIR;
       //Serial.println(iPulseValueIR);
      
       if (millis() - tsLastReport > REPORTING_PERIOD_MS) {
        iBPM = pox.getHeartRate();
        Serial.println(iBPM);
        SPO2 = pox.getSpO2();
        //Serial.println(SPO2);
        tsLastReport = millis();
       }
      
       if (((iBPM != iBPMOld) && (iBPM < UPPER_PULSE_RATE)) | (SPO2 != SPO2Old)) {
        UpdateValues(47, 108, iBPMOld, iBPM);
        UpdateValues(115, 108, SPO2Old, SPO2);
        iBPMOld = iBPM;
        SPO2Old = SPO2;
       }
      
       if(iBPM > 100) // Adapt the sample rate to ensure sufficient pulses are displayed for a slower heart rate.
        iSampleCountMax = 12;  
       else
        iSampleCountMax = 8;  

       // Handle screen top and bottom clipping
       if (iPulseValueIR < 1) // If top of waveform clips, stop it from printing outside the screen and move next peak down by the same amount + some
        iPulseValueIR = 1;
       if (iPulseValueIR > PULSE_WINDOW_HEIGHT-3)  // If bottom of waveform clips, stop it from printing outside the screen and move next peak up by the same amount + some
        iPulseValueIR = PULSE_WINDOW_HEIGHT-3;

       // Handle screen update
       iSampleCount++;
       if (iSampleCount >= iSampleCountMax) {
        iSampleCount = 0;
        ucScreenIndex++;
        if (ucScreenIndex >= SCREEN_WIDTH) {
         ucScreenIndex = 1;
         iPulseValueIROld = (int)((float)((float)PULSE_WINDOW_HEIGHT) / 2.0);
         tft.drawFastVLine(ucScreenIndex, 1, PULSE_WINDOW_HEIGHT - 3, ST7735_BLACK); // drawFastVLine: Draw Fast Vertical Line; drawFastHLine: Draw Fast Horizontal Line
        }else {
         if (ucScreenIndex < (SCREEN_WIDTH-2)) {
          tft.drawFastVLine(ucScreenIndex, 1, PULSE_WINDOW_HEIGHT - 3, ST7735_BLACK);
          tft.drawLine(ucScreenIndex-1, iPulseValueIROld, ucScreenIndex, iPulseValueIR, ST7735_GREEN); //alterar escala aki!!!!!!!
          //Serial.println(iPulseValueIROld);
          //Serial.println(iPulseValueIR);
         }
        }
       iPulseValueIROld = iPulseValueIR;
      }
     }
    }
    pox.shutdown();
    Serial.println("POWEROFF");
    tft.fillScreen(BMO_COLOR);
   break;

   default:
    // read the analog in value:
    outputValue = analogRead(analogInPin);
    tft.setRotation(0);
   if((outputValue>=(MinAudioValue-5) && outputValue<=(MaxAudioValue+5))| FirstUpdate)
    bmo_smile();
   else {
     bmo_smile();
     delay(500);
     tft.fillRect(40, 0, 50, 159, BMO_COLOR);
     bmo_speak();
     delay(500);
     tft.fillRect(40, 0, 50, 159, BMO_COLOR);
     bmo_smile();
   }
   
    if (millis()-LastUpdate > UpdateAudioValue){

     for(int i; i<=100; i++){
      TempAudioValue = analogRead(analogInPin);
      Serial.println(TempAudioValue);
      if (TempAudioValue > MaxAudioValue)
        MaxAudioValue = TempAudioValue;

      if (TempAudioValue < MaxAudioValue)
        MinAudioValue = TempAudioValue;

      delay(10);
     }
    FirstUpdate = false;
    LastUpdate = millis();
   }
   break;
  }
}


void UpdateValues(int x, int y, int OldValue, int NewValue) {
  tft.setTextSize(2);
  tft.setCursor(x, y);
  tft.setTextColor(ST7735_BLACK);
  sprintf(cStringArray,"%d",OldValue);
  tft.println(cStringArray);
  tft.setCursor(x, y);
  tft.setTextColor(ST7735_YELLOW);
  sprintf(cStringArray,"%d",NewValue);
  tft.println(cStringArray);
}


void handleCalibration() {
#define CALIBRATION_DELAY 10

  int lCount = 0;
  int iCountDown = CALIBRATION_DELAY;
  char cCountDown[15];
  long  lADC0TempValue = 0;
  long  lSamplecounts = 0;
  uint16_t ir, red;

  
  iCountDown = CALIBRATION_DELAY;
  setupCalibrateDisplay1();
  tft.setTextSize(1);
  while (iCountDown > 0){  
    tft.setTextColor(ST7735_WHITE);
    tft.setCursor(110,100);
    sprintf(cCountDown,"%d Secs",iCountDown);
    tft.println(cCountDown);
    delay(1000);
    tft.setTextColor(ST7735_BLACK);
    tft.setCursor(110,100);
    sprintf(cCountDown,"%d Secs",iCountDown);
    tft.println(cCountDown);
    iCountDown--;
  };

  setupCalibrateDisplay2();
  tft.setTextSize(1);
  tft.setTextColor(ST7735_WHITE);
  tft.setCursor(45,100);
  tft.println("Calculating");
  tft.setTextColor(ST7735_WHITE);
  tft.setCursor(26,112);
  tft.println("Max and Min Values");

  tft.drawRect(2,75,158,10,ST7735_RED);
  lADC0MaxValue = 0;
  lADC0MinValue = ADC_MAX_VAL;

  lCount = 0;
  lSamplecounts = 10000L;
  
  //Start sensor Configuration
  if (!pox.begin()) {
        Serial.println("FAILED");
        for(;;);
   } else
        Serial.println("SUCCESS");
  pox.update();
  sensor.update();
  // Read the output of the sensor with IR applied and finger in place to determine max and min voltages at output. Used to scale the incoming waveform to ensure the
  // fit in the display window is maximised. 
  while (lCount < lSamplecounts){  
    pox.update();
    sensor.update();
    
    sensor.getRawValues(&ir, &red);
    lADC0TempValue = ir; //IR RAW READ
    //Serial.println(ir);
    
    if (lADC0TempValue > lADC0MaxValue)
      lADC0MaxValue = lADC0TempValue;

    if (lADC0TempValue < lADC0MaxValue)
      lADC0MinValue = lADC0TempValue;
         
    if ((lCount % 1000) == 0)
        tft.fillRect(3,76,(int16_t) (156 * (float)( (float)(lCount + 1) / (float) lSamplecounts)),8,ST7735_YELLOW);
     delay(1);
     lCount++;
  };
}


void setupCalibrateDisplay1() {
  tft.fillScreen(ST7735_BLACK);
  tft.setCursor(35, 5);
  tft.setTextColor(ST7735_YELLOW);
  tft.setTextSize(2);
  tft.println("Ranging");
  tft.setCursor(28, 28);
  tft.println("Required");

  tft.setCursor(13,60);
  tft.setTextColor(ST7735_GREEN);
  tft.setTextSize(1);
  tft.println("Keep finger in sensor");
  tft.setCursor(20,70);
  tft.println("during calculation");

  tft.setCursor(10,100);
  tft.setTextColor(ST7735_RED);
  tft.setTextSize(1);
  tft.println("Calculation in :");
}


void setupCalibrateDisplay2() {
  tft.fillScreen(ST7735_BLACK);
  tft.setTextColor(ST7735_YELLOW);
  tft.setTextSize(2);
  tft.setCursor(37, 15);
  tft.println("Ranging");
  tft.setCursor(15, 40);
  tft.println("In Progress");
}


void setupFinalDisplay() {
  tft.fillScreen(ST7735_BLACK);
  tft.drawRect(0, 0, SCREEN_WIDTH-1, PULSE_WINDOW_HEIGHT-1, ST7735_GREEN);
  tft.drawRect(0, PULSE_WINDOW_HEIGHT, SCREEN_WIDTH-1, SCREEN_HEIGHT - PULSE_WINDOW_HEIGHT, ST7735_GREEN);
  tft.setTextColor(ST7735_CYAN);
  tft.setTextSize(2);
  tft.setCursor(5,108);
  tft.println("BPM");
  tft.setCursor(85,108);
  tft.println("O2");
  tft.setCursor(140,108);
  tft.println("%");
}


void bmo_hello() {
  uint16_t x=34;
  uint16_t y=40;
  uint16_t R=6;
  uint16_t r=4;
  
  eyes(x,y,r);
  tft.fillCircle(x*2, y*2, R, BLACK);
}

void bmo_greeting() {
  //void drawLine(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1, uint16_t color);
  uint16_t x=34;
  uint16_t y=40;
  uint16_t r=4;

  eyes(x,y,r);
  tft.drawLine(x*2,y+5,x*2,y*3,BLACK);
}

void bmo_ow() {
  //void drawLine(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1, uint16_t color);
  uint16_t x=34;
  uint16_t y=40;
  uint16_t r=4;

  eyes(x,y,r);
  tft.drawCircle(x*2,y*2,r*4,BLACK);
}

void bmo_smile() {
  uint16_t x=34;
  uint16_t y=40,r=4;

  eyes(x,y,r);

//Lado Direito
//tft.fillRoundRect(x*2, y+5, altura, comprimento, angulo das laterais, BLACK);
   tft.fillRoundRect((x*2), (y+2)+5, 4, 8, 1, BLACK); //posicao inicial
   tft.fillRoundRect((x*2)+2, (y+5)+5, 4, 4, 1, BLACK);   // x + 2 ; y + 3
   for(int i = 2; i<7; i = i+2)
    tft.fillRoundRect((x*2)+1+i, (y+5)+i+4, 4, 4, 1, BLACK);

   tft.fillRoundRect((x*2)+9, (y+5)+12, 4, 4, 1, BLACK);
   tft.fillRoundRect((x*2)+11, (y+5)+14, 4, 4, 1, BLACK);
   tft.fillRoundRect((x*2)+12, (y+5)+15, 4, 4, 1, BLACK);
   tft.fillRoundRect((x*2)+13, (y+5)+17, 5, 4, 1, BLACK);
   
   tft.fillRoundRect((x*2)+15, (y+5)+19, 4, 8, 1, BLACK);

   tft.fillRoundRect((x*2)+16, (y+5)+25, 4, 12, 1, BLACK);
   tft.fillRoundRect((x*2)+16, (y+5)+34, 4, 12, 1, BLACK);
   
//Lado Esquerdo   
   tft.fillRoundRect((x*2)-1,(y*3)-9, 4, 8, 1, BLACK); //posicao inicial
   tft.fillRoundRect((x*2)+1, (y*3)-8, 4, 4, 1, BLACK);  
   for(int i = 2; i<7; i = i+2)
    tft.fillRoundRect((x*2)+1+i, (y*3)-8-i, 4, 4, 1, BLACK);

   tft.fillRoundRect((x*2)+9, (y*3)-16, 4, 4, 1, BLACK);
   tft.fillRoundRect((x*2)+11, (y*3)-18, 4, 4, 1, BLACK);
   tft.fillRoundRect((x*2)+12, (y*3)-19, 4, 4, 1, BLACK);
   tft.fillRoundRect((x*2)+13, (y*3)-21, 5, 4, 1, BLACK);

    tft.fillRoundRect((x*2)+15, (y*3)-27, 4, 8, 1, BLACK);

    tft.fillRoundRect((x*2)+16, (y*3)-35, 4, 10, 1, BLACK);
    tft.fillRoundRect((x*2)+16, (y*3)-43, 4, 11, 1, BLACK);
}

void idk() {
 tft.setRotation(3);
 uint8_t tz=2;
 uint16_t v=10;

  tft.drawChar(5, v, 'B', CHARCOL, BMO_COLOR, tz);
  tft.drawChar(26, v, 'A', CHARCOL, BMO_COLOR, tz);
  tft.drawChar(50, v, 'C', CHARCOL, BMO_COLOR, tz);
  tft.drawChar(74, v, 'K', CHARCOL, BMO_COLOR, tz);
  
  tft.drawChar(98, v, 'I', CHARCOL, BMO_COLOR, tz);
  tft.drawChar(115, v, 'N', CHARCOL, BMO_COLOR, tz);
  
  tft.drawChar(133, v, '1', CHARCOL, BMO_COLOR, tz);
  
  tft.drawChar(5, 42, 'M', CHARCOL, BMO_COLOR, tz);
  tft.drawChar(29, 42, 'I', CHARCOL, BMO_COLOR, tz);
  tft.drawChar(53, 42, 'N', CHARCOL, BMO_COLOR, tz);
  tft.drawChar(77, 42, 'U', CHARCOL, BMO_COLOR, tz);
  tft.drawChar(101, 42, 'T', CHARCOL, BMO_COLOR, tz);    
  tft.drawChar(125, 42, 'E', CHARCOL, BMO_COLOR, tz);
}


void bmo_troll() {
  uint16_t x=34;
  uint16_t y=40;
  uint16_t R=5;
  uint16_t r=4;

  //tft.fillRect(0,0,x*2,y*4,BMO_COLOR);
  tft.fillCircle(x*2, y*2, r*5, BLACK);
  //tft.fillRect(0,0,x*2,y*4,BMO_COLOR);
  tft.fillRoundRect(x*2, (y*2)-8, 11, 18, 3, RED);
  eyes(x,y,r);
  //tft.fillRect(x*2.1,0,x*3,y*4,BMO_COLOR);
}


void bmo_speak() {
  uint16_t x=34;
  uint16_t y=40;
  uint16_t R=5;
  uint16_t r=4;

  eyes(x,y,r);

//Lado Direito
//tft.fillRoundRect(x*2, y+5, altura, comprimento, angulo das laterais, BLACK);
   tft.fillRoundRect((x*2), (y+2)+5, 4, 70, 1, BLACK); //posicao inicial
   tft.fillRoundRect((x*2)+2, (y+5)+5, 4, 4, 1, BLACK);   // x + 2 ; y + 3
   for(int i = 2; i<7; i = i+2)
    tft.fillRoundRect((x*2)+1+i, (y+5)+i+4, 4, 4, 1, BLACK);

   tft.fillRoundRect((x*2)+9, (y+5)+12, 4, 4, 1, BLACK);
   tft.fillRoundRect((x*2)+11, (y+5)+14, 4, 4, 1, BLACK);
   tft.fillRoundRect((x*2)+12, (y+5)+15, 4, 4, 1, BLACK);
   tft.fillRoundRect((x*2)+13, (y+5)+17, 5, 4, 1, BLACK);
   
   tft.fillRoundRect((x*2)+15, (y+5)+19, 4, 8, 1, BLACK);

   tft.fillRoundRect((x*2)+16, (y+5)+25, 4, 12, 1, BLACK);
   tft.fillRoundRect((x*2)+16, (y+5)+34, 4, 12, 1, BLACK);
   
//Lado Esquerdo   
   tft.fillRoundRect((x*2),(y*3)-9, 2, 8, 1, BLACK); //posicao inicial
   tft.fillRoundRect((x*2)+1, (y*3)-8, 4, 4, 1, BLACK);  
   for(int i = 2; i<7; i = i+2)
    tft.fillRoundRect((x*2)+1+i, (y*3)-8-i, 4, 4, 1, BLACK);

   tft.fillRoundRect((x*2)+9, (y*3)-16, 4, 4, 1, BLACK);
   tft.fillRoundRect((x*2)+11, (y*3)-18, 4, 4, 1, BLACK);
   tft.fillRoundRect((x*2)+12, (y*3)-19, 4, 4, 1, BLACK);
   tft.fillRoundRect((x*2)+13, (y*3)-21, 5, 4, 1, BLACK);

    tft.fillRoundRect((x*2)+15, (y*3)-27, 4, 8, 1, BLACK);

    tft.fillRoundRect((x*2)+16, (y*3)-35, 4, 10, 1, BLACK);
    tft.fillRoundRect((x*2)+16, (y*3)-43, 4, 11, 1, BLACK);

//Preenchimento da boca
    tft.fillRect(72, 68, 14, 30, MOUTH);
    tft.fillTriangle(85, 67, 70, 52, 70, 67, MOUTH);
    tft.fillTriangle(85, 97, 70, 112, 70, 97, MOUTH);

//Dentes
tft.fillRoundRect(70, 56, 5, 53, 1, WHITE);


//Lingua
tft.fillRoundRect(80, 65, 5, 35, 1, TONGUE);
}

void eyes(uint16_t x,uint16_t y,uint16_t r) {
  tft.fillCircle(x, y-3, r, BLACK);
  tft.fillCircle(x, (y*3)+3, r, BLACK);
}
