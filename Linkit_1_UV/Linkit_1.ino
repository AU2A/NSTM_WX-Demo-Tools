#include <Adafruit_NeoPixel.h>
#include <Wire.h>
#include <LWiFi.h>
#include <Arduino.h>
#include <MCS.h>
#include <Wire.h>
#include <SI114X.h>

//無密碼網路設定
//char _lwifi_ssid[] = "NSTM_Free_wifi";
//int status = WL_IDLE_STATUS;

//有密碼網路設定
char _lwifi_ssid[] = "Lets Try";
char _lwifi_pass[] = "077219590";

//MCS設定
MCSDevice mcs("DBqtJb10", "zSbPtm0xaxFD8OVm");
MCSDisplayInteger uv("uv");
MCSDisplayFloat windspeed("windspeed");
MCSDisplayFloat water("water");
MCSDisplayCategory direct("direct");

//設定LED燈條
Adafruit_NeoPixel windDirect = Adafruit_NeoPixel(16, 11, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel windSpd = Adafruit_NeoPixel(8, 13, NEO_GRB + NEO_KHZ800);

//設定SI1145(紫外線)
SI114X SI1145 = SI114X();

const byte dataPin = 3;
const byte latchPin = 4;
const byte clockPin = 5;
float wind = 0, water2 = 0;
int front, back;
int index = 0, windcheck = 0, watercheck = 0, UVgap = 0, UVdata = 0, windDir = 0, UVcheck = 0, windgap = 0;


void setup() {
  Serial.begin(9600);
  LinkitStatus();
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(dataPin, OUTPUT);
  pinMode(10, INPUT);//雨量輸入
  pinMode(12, INPUT);//風速輸入
  pinMode(14, INPUT);//風向輸入
  pinMode(15, OUTPUT);//紫外線輸入
  pinMode(16, OUTPUT);//紫外線輸入
  pinMode(17, OUTPUT);//紫外線輸入
}

void loop() {
  UVdata = 0;
  UVcheck = 0;
  McsTest();
  data();
  show_data();
  upload_data();
  Serial.println();
  wind = 0;
}
