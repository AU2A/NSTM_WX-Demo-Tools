#include <DHT.h>
#include <LWiFi.h>
#include <MCS.h>
#include <Wire.h>

//有密碼網路設定
char _lwifi_ssid[] = "Lets Try";
char _lwifi_pass[] = "077219590";

//無密碼網路設定
//char _lwifi_ssid[] = "NSTM_Free_wifi";
//int status = WL_IDLE_STATUS;

MCSDevice mcs("DBqtJb10", "zSbPtm0xaxFD8OVm");
MCSDisplayInteger humidity("humidity");
MCSDisplayFloat temperature("temperature");

DHT dht22_p2(13, DHT22);

const byte dataPin = 17;
const byte latchPin = 16;
const byte clockPin = 15;
int ledPin[10] = {2, 3, 4, 5, 7, 8, 9, 10, 11, 12};
float temp;
int front, back, humd,now;

int hash(int i) {
  int a = i / 10, b = i % 10;
  return a * 16 + b;
}


void setup() {
  Serial.begin(9600);
  mcs.addChannel(humidity);
  mcs.addChannel(temperature);
  //設定網路
  Serial.println("Wi-Fi 開始連線");
  //有密碼網路
  while (WiFi.begin(_lwifi_ssid, _lwifi_pass) != WL_CONNECTED) {
    delay(1000);
  }
  //無密碼網路
  /*while (status != WL_CONNECTED) {
    Serial.print("Attempting to connect to open SSID: ");
    Serial.println(_lwifi_ssid);
    status = WiFi.begin(_lwifi_ssid);
    delay(1000);
    }*/
  Serial.println("Wi-Fi 連線成功");

  //MCS連線測試
  while (!mcs.connected()) {
    mcs.connect();
  }
  Serial.println("MCS 連線成功");
  Serial.println("DHTxx test!");
  dht22_p2.begin();
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(dataPin, OUTPUT);
  for (int i = 0; i < 10; i++) {
    pinMode(ledPin[i], OUTPUT);
  }
  for (int i = 0; i < 10; i++) {
    digitalWrite(ledPin[i], HIGH);
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
  temp = dht22_p2.readTemperature();
  humd = dht22_p2.readHumidity();
  Serial.print(temp);
  Serial.print("  ");
  Serial.println(humd);
  front = int(temp);
  back = int(int(temp * 10) % 10);
  digitalWrite(latchPin, LOW);
  shiftOut(dataPin, clockPin, LSBFIRST, hash(front) );
  shiftOut(dataPin, clockPin, LSBFIRST, hash(back) );
  digitalWrite(latchPin, HIGH);
  for (int i = 9; i > 9 - humd / 10; i--) {
    digitalWrite(ledPin[i], LOW);
  }
  for (int i = 9 - humd / 10; i >= 0; i--) {
    digitalWrite(ledPin[i], HIGH);
  }
  }
  now = millis();
  humidity.set(int(humd));
  temperature.set(temp);
}
