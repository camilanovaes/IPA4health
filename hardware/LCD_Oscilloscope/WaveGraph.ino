#include <SPI.h>
#include <SD.h>
#include "Adafruit_ST7735.h"

#define TFT_CS 10
#define TFT_DC 9
#define TFT_RST 8 // RST can be set to -1 if you tie it to Arduino's reset

#define LTBLUE    0xB6DF
#define LTTEAL    0xBF5F
#define LTGREEN   0xBFF7
#define LTCYAN    0xC7FF
#define LTRED     0xFD34
#define LTMAGENTA 0xFD5F
#define LTYELLOW  0xFFF8
#define LTORANGE  0xFE73
#define LTPINK    0xFDDF
#define LTPURPLE  0xCCFF
#define LTGREY    0xE71C

#define BLUE      0x001F
#define TEAL      0x0438
#define GREEN     0x07E0
#define CYAN      0x07FF
#define RED       0xF800
#define MAGENTA   0xF81F
#define YELLOW    0xFFE0
#define ORANGE    0xFC00
#define PINK      0xF81F
#define PURPLE    0x8010
#define GREY      0xC618
#define WHITE     0xFFFF
#define BLACK     0x0000

#define DKBLUE    0x000D
#define DKTEAL    0x020C
#define DKGREEN   0x03E0
#define DKCYAN    0x03EF
#define DKRED     0x6000
#define DKMAGENTA 0x8008
#define DKYELLOW  0x8400
#define DKORANGE  0x8200
#define DKPINK    0x9009
#define DKPURPLE  0x4010
#define DKGREY    0x4A49

#define ADJ_PIN A0

Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS, TFT_DC, TFT_RST);

boolean display1 = true;
double ox, oy, x, y;

void setup() {

  Serial.begin(9600);

  pinMode(ADJ_PIN, INPUT);
  tft.initR(INITR_BLACKTAB);
  tft.fillScreen(BLACK);
  tft.setRotation(3);
}


void loop(void) {
  for (x = 0; x <= 80; x +=.1) {
    y = analogRead(ADJ_PIN) * (10.0 / 1023.0);
    Graph(tft, x, y, 40, 95, 95, 80, 0, 60, 15, 0, 5, 1, "", "Tempo(s)", "Tensao(v)", DKBLUE, RED, GREEN, WHITE, BLACK, display1);
    delay(10);
  }
  tft.fillRect(30, 15, 130, 81, BLACK);
  DrawGrid(tft, x, y, 40, 95, 95, 80, 0, 60, 15, 0, 5, 1, DKBLUE, RED);
}

/*
  function to draw a cartesian coordinate system and plot whatever data you want
  just pass x and y and the graph will be drawn

  huge arguement list
  &d name of your display object
  x = x data point
  y = y datapont
  gx = x graph location (lower left)
  gy = y graph location (lower left)
  w = width of graph
  h = height of graph
  xlo = lower bound of x axis
  xhi = upper bound of x asis
  xinc = division of x axis (distance not count)
  ylo = lower bound of y axis
  yhi = upper bound of y asis
  yinc = division of y axis (distance not count)
  title = title of graph
  xlabel = x asis label
  ylabel = y asis label
  gcolor = graph line colors
  acolor = axi ine colors
  pcolor = color of your plotted data
  tcolor = text color
  bcolor = background color
  &redraw = flag to redraw graph on fist call only
*/


void Graph(Adafruit_ST7735 &d, double x, double y, double gx, double gy, double w, double h, double xlo, double xhi, double xinc, double ylo, double yhi, double yinc, String title, String xlabel, String ylabel, unsigned int gcolor, unsigned int acolor, unsigned int pcolor, unsigned int tcolor, unsigned int bcolor, boolean &redraw) {
  double i, temp;
  
  if (redraw == true) {

    redraw = false;
    ox = (x - xlo) * ( w) / (xhi - xlo) + gx;
    oy = (y - ylo) * (gy - h - gy) / (yhi - ylo) + gy;
    // draw y scale
    for ( i = ylo; i <= yhi; i += yinc) {
      // compute the transform
      temp =  (i - ylo) * (gy - h - gy) / (yhi - ylo) + gy;

      if (i == 0) {
        d.drawLine(gx-10, temp, gx + w + 20, temp, acolor);
      }
      else {
        d.drawLine(gx-10, temp, gx + w + 20, temp, gcolor);// DrawGrid
      }

      d.setTextSize(1);
      d.setTextColor(tcolor, bcolor);
      d.setCursor(gx - 40, temp);
      // precision is default Arduino--this could really use some format control
      d.println(i);
    }
    // draw x scale
    for (i = xlo; i <= xhi; i += xinc) {
      // compute the transform
      temp =  (i - xlo) * ( w) / (xhi - xlo) + gx;
      if (i == 0) {
        d.drawLine(temp-10, gy, temp-10, gy - h, acolor);
      }
      else {
        d.drawLine(temp-10, gy, temp-10, gy - h, gcolor);// DrawGrid
      }

      d.setTextSize(1);
      d.setTextColor(tcolor, bcolor);
      d.setCursor(temp-10, gy + 10);
      // precision is default Arduino--this could really use some format control
      d.println(i/10);
    }

    //now draw the labels
    d.setTextSize(2);
    d.setTextColor(tcolor, bcolor);
    d.setCursor(gx , gy - h - 30);
    d.println(title);

    d.setTextSize(1);
    d.setTextColor(acolor, bcolor);
    d.setCursor(gx - 10, gy + 20);
    d.println(xlabel);

    d.setTextSize(1);
    d.setTextColor(acolor, bcolor);
    d.setCursor(gx - 30, gy - h - 10);
    d.println(ylabel);
  }

  //graph drawn now plot the data
  // the entire plotting code are these few lines...
  // recall that ox and oy are initialized as static above
  x =  (x - xlo) * ( w) / (xhi - xlo) + gx;
  y =  (y - ylo) * (gy - h - gy) / (yhi - ylo) + gy;
  d.drawPixel(x-10, y, pcolor);
}


void DrawGrid(Adafruit_ST7735 &d, double x, double y, double gx, double gy, double w, double h, double xlo, double xhi, double xinc, double ylo, double yhi, double yinc, unsigned int gcolor, unsigned int acolor){
  double i, temp;
  ox = (x - xlo) * (w) / (xhi - xlo) + gx;
  oy = (y - ylo) * (gy - h - gy) / (yhi - ylo) + gy;
  // draw y scale
  for ( i = ylo; i <= yhi; i += yinc) {
    // compute the transform
    temp =  (i - ylo) * (gy - h - gy) / (yhi - ylo) + gy;

    if (i == 0) {
      d.drawLine(gx-10, temp, gx + w + 20, temp, acolor);
    }
      else {
      d.drawLine(gx-10, temp, gx + w + 20, temp, gcolor);// DrawGrid
    }
  }

  // draw x scale
  for (i = xlo; i <= xhi; i += xinc) {
    // compute the transform
    temp =  (i - xlo) * (w) / (xhi - xlo) + gx;
    if (i == 0) {
      d.drawLine(temp-10, gy, temp-10, gy - h, acolor);
    }
     else {
      d.drawLine(temp-10, gy, temp-10, gy - h, gcolor);// DrawGrid
     }
  }
}
