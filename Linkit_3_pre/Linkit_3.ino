#include "Seeed_BMP280.h"
#include <LWiFi.h>
#include <MCS.h>
#include <Wire.h>
BMP280 bmp280;

int mode = 1; //1為有密碼，2為無密碼

//有密碼網路設定
char _lwifi_ssid[] = "Lets Try";  //wifi帳號
char _lwifi_pass[] = "077219590"; //wifi密碼

//無密碼網路設定
char _lwifi_ssid_free[] = "NSTM_Free_wifi";  //wifi帳號
int status = WL_IDLE_STATUS;  //不須調整

//mcs帳號密碼
MCSDevice mcs("DBqtJb10", "zSbPtm0xaxFD8OVm");
MCSDisplayInteger pressure("pressure");



const byte dataPin = 2;
const byte latchPin = 3;
const byte clockPin = 4;
float pressureData;
int front, back;
int now;

int hash(int i) {
  int a = i / 10, b = i % 10;
  return a * 16 + b;
}



void setup() {
  Serial.begin(9600);
  mcs.addChannel(pressure);
  //設定網路
  Serial.println("Wi-Fi 開始連線");
  if (mode == 1) {
    //有密碼網路
    while (WiFi.begin(_lwifi_ssid, _lwifi_pass) != WL_CONNECTED) {
      delay(1000);
    }
  }
  else {
    //無密碼網路
    while (status != WL_CONNECTED) {
      Serial.print("Attempting to connect to open SSID: ");
      Serial.println(_lwifi_ssid_free);
      status = WiFi.begin(_lwifi_ssid_free);
      delay(1000);
    }
  }
  Serial.println("Wi-Fi 連線成功");

  //MCS連線測試
  while (!mcs.connected()) {
    mcs.connect();
  }
  Serial.println("MCS 連線成功");

  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(dataPin, OUTPUT);

  if (!bmp280.init()) {
    Serial.println("Device error!");
  }
  now = millis();

}
void loop() {
  while (millis() - now <= 5000) {
    while (!mcs.connected()) {
      mcs.connect();
      if (mcs.connected()) {
        Serial.println("MCS 已重新連線");
      }
    }
    mcs.process(100);
    pressureData = bmp280.getPressure();
    front = (int(pressureData) / 10000) ;
    back = int(pressureData / 100) % 100;
    digitalWrite(latchPin, LOW);
    shiftOut(dataPin, clockPin, LSBFIRST, hash(front) );
    shiftOut(dataPin, clockPin, LSBFIRST, hash(back) );
    digitalWrite(latchPin, HIGH);
  }
  now = millis();
  Serial.println(pressureData);
  pressure.set(int(pressureData) / 100);
}
