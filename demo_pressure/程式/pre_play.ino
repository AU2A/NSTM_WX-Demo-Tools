#include <Adafruit_NeoPixel.h>
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(16, 17, NEO_GRB + NEO_KHZ800);//rgb燈訊號線插在A3
#include "Seeed_BMP280.h"
#include <Wire.h>

BMP280 bmp280;
float startpre = 100000;
float pressure;
int gap;
//   r   g   b
int light[16][3] =
{ { 16,  0, 16},
  { 12,  0, 20},
  {  8,  0, 24},
  {  4,  0, 28},
  {  0,  0, 32},
  {  0,  8, 24},
  {  0, 16, 16},
  {  0, 24,  8},
  {  0, 32,  0},
  {  4, 28,  0},
  {  8, 24,  0},
  { 16, 16,  0},
  { 20, 12,  0},
  { 24,  8,  0},
  { 28,  4,  0},
  { 32,  0,  0},
};
int now[3];


void setup()
{
  Serial.begin(9600);
  if (!bmp280.init()) {
    Serial.println("Device error!");
  }
  pixels.begin();
  pixels.show();
}

void loop()
{
  pressure = bmp280.getPressure();
  //Serial.println(pressure);
  gap = 1 + int((pressure - 100000) / 1500);
  if (gap > 16)gap = 16;
  for (int i = 0; i < gap; i++) {
    pixels.setPixelColor(i, pixels.Color(light[i][0], light[i][1], light[i][2]));
  }
  for (int i = gap; i < 16;i++){
  pixels.setPixelColor(i, pixels.Color(0, 0, 0));
  }
  pixels.show();
  delay(1);
}
