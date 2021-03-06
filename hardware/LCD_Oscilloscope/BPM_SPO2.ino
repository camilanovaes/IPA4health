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


void setup(void) {
  Serial.begin(115200);
  tft.initR(INITR_BLACKTAB);   // initialize a ST7735S chip, black tab (works for red tab also)
  tft.setRotation(3);
  tft.fillScreen(ST7735_BLACK);
}


void loop(){
  handleCalibration();
  setupFinalDisplay();
  Serial.println('\n');
  Serial.println(lADC0MinValue);
  Serial.println((int)lADC0MinValue);
  ucScreenIndex = SCREEN_WIDTH;
  iADC0SpanValue = (lADC0MaxValue - lADC0MinValue);
  Serial.println('\n');
  Serial.println(iADC0SpanValue);
  fScalingFactor = (float)((float)(PULSE_WINDOW_HEIGHT)/(float)ADC_MAX_VAL);
  Serial.println('\n');
  Serial.println(fScalingFactor);
  ulOldTime = micros();
  iPulseTriggerLevelHigh = ((int)(((float)(lADC0MaxValue - lADC0MinValue)) * 0.10)) + lADC0MinValue;
  iPulseTriggerLevelLow  = ((int)(((float)(lADC0MaxValue - lADC0MinValue)) * 0.30)) + lADC0MinValue;
      
  while (1){ 
    pox.update();
    sensor.update();
    ulCurrentTime = micros();
    if (ulCurrentTime >= ulOldTime)
      ulElapsedTime = ulCurrentTime - ulOldTime;
    else
      ulElapsedTime = (MAX_UL - ulOldTime) + ulCurrentTime;
    
    if (ulElapsedTime >= ulSamplePeriod){
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
        Serial.println(SPO2);
        tsLastReport = millis();
    }
      
    if (((iBPM != iBPMOld) && (iBPM < UPPER_PULSE_RATE)) | (SPO2 != SPO2Old)){
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
      if (iSampleCount >= iSampleCountMax){
        iSampleCount = 0;
        ucScreenIndex++;
        if (ucScreenIndex >= SCREEN_WIDTH){
          ucScreenIndex = 1;
          iPulseValueIROld = (int)((float)((float)PULSE_WINDOW_HEIGHT) / 2.0);
          tft.drawFastVLine(ucScreenIndex, 1, PULSE_WINDOW_HEIGHT - 3, ST7735_BLACK);
        } else {
          if (ucScreenIndex < (SCREEN_WIDTH-2)){
            tft.drawFastVLine(ucScreenIndex, 1, PULSE_WINDOW_HEIGHT - 3, ST7735_BLACK);
            tft.drawLine(ucScreenIndex-1, iPulseValueIROld, ucScreenIndex, iPulseValueIR, ST7735_GREEN); //alterar escala aki!!!!!!!
          }
        }
        iPulseValueIROld = iPulseValueIR;
      }
    }
   }
}



void UpdateValues(int x, int y, int OldValue, int NewValue){
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

void handleCalibration(void){
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
    Serial.println(ir);
    
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




void setupCalibrateDisplay1(void){
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


void setupCalibrateDisplay2(void){
  tft.fillScreen(ST7735_BLACK);
  tft.setTextColor(ST7735_YELLOW);
  tft.setTextSize(2);
  tft.setCursor(37, 15);
  tft.println("Ranging");
  tft.setCursor(15, 40);
  tft.println("In Progress");
}


void setupFinalDisplay(void){
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
