/*
 * Square.ino
 * Created by Fabio de Albuquerque Dela Antonio
 * fabio914 at gmail.com
 * 
 * An OpenGL example that draws a rotated and scaled square.
 */
#include "SPI.h"
#include "ILI9488_t3.h"

// For the Adafruit shield, these are the default.
#define TFT_DC  9
#define TFT_CS 10

// Use hardware SPI (on Uno, #13, #12, #11) and the above for CS/DC
ILI9488_t3 tft = ILI9488_t3(&SPI,TFT_CS, TFT_DC, 8);


void setup() {
  tft.begin();
  tft.fillScreen(ILI9488_BLACK);
  tft.setTextColor(ILI9488_YELLOW);
  tft.setTextSize(2);
  tft.println("Waiting for Arduino Serial Monitor...");

  Serial.begin(9600);
  while (!Serial) ; // wait for Arduino Serial Monitor
  Serial.println("OpenGL Test!"); 

  delay(1000);

  /* Pass the canvas to the OpenGL environment */
  tft.glClear(ILI9488_BLACK);
  tft.glPointSize(4);
    
  tft.glMatrixMode(GL_PROJECTION);
  tft.glLoadIdentity();
  tft.gluOrtho2D(-5.0, 5.0, -5.0, 5.0);
    
  tft.glMatrixMode(GL_MODELVIEW);
}

void loop() {

  /* Read the rotation angle from a potentiometer attached to pin A0 */
  float angle = .4 * 360.f;
  
  static float scale = 3.0, scaleInc = 0.4;
  const float maxScale = 8.0, minScale = 2.0;

  tft.glClear(ILI9488_BLACK); 
  
  tft.glLoadIdentity();
  tft.glRotatef(angle, 0.f, 0.f, 1.f);
  tft.glScalef(scale, scale, 0.f);
  tft.glTranslatef(-0.5f, -0.5f, 0.f);
  
  tft.glBegin(GL_POINTS);
    tft.glVertex3f(0.f, 1.f, 0.f);
    tft.glVertex3f(0.f, 0.f, 0.f);
    tft.glVertex3f(1.f, 0.f, 0.f);
    tft.glVertex3f(1.f, 1.f, 0.f);
  tft.glEnd();

  tft.glBegin(GL_POLYGON);
    tft.glVertex3f(0.f, 1.f, 0.f);
    tft.glVertex3f(0.f, 0.f, 0.f);
    tft.glVertex3f(1.f, 0.f, 0.f);
    tft.glVertex3f(1.f, 1.f, 0.f);
  tft.glEnd();

  scale += scaleInc;

  if(scale > maxScale)
    scaleInc *= -1.f;

  if(scale < minScale)
    scaleInc *= -1.f;
  
  delay(1);
}
