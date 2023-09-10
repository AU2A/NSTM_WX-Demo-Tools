#include <DHT.h>
DHT dht22_p2(19, DHT22);
#include<math.h>
float temp = 0, humd = 0;
int a, b, c;
int num[10][4] = {
  {0, 0, 0, 0},
  {0, 0, 0, 1},
  {0, 0, 1, 0},
  {0, 0, 1, 1},
  {0, 1, 0, 0},
  {0, 1, 0, 1},
  {0, 1, 1, 0},
  {0, 1, 1, 1},
  {1, 0, 0, 0},
  {1, 0, 0, 1}
};
int apin = A0, bpin = A1, datapin = A2, latchpin = A3, clockpin = A4;

void setup() {
  Serial.begin(9600);
  dht22_p2.begin();
  for (int i = 2; i <= 13; i++) {
    pinMode(i, OUTPUT);
    digitalWrite(i, LOW);
  }
  pinMode(apin, OUTPUT);
  pinMode(bpin, OUTPUT);
  pinMode(datapin, OUTPUT);
  pinMode(latchpin, OUTPUT);
  pinMode(clockpin, OUTPUT);
}

void loop() {
  temp = dht22_p2.readTemperature();
  humd = dht22_p2.readHumidity();
  Serial.println(temp);
  showTemp(temp);
  showhumd(humd);
  delay(50);
  if (temp > 99.9)temp = 0;
  temp += 0.1;
}



void showhumd(float H) {
  int gap = H / 10;
  if (gap == 9) {
    digitalWrite(bpin, HIGH);
    digitalWrite(bpin, LOW);
  }
  else if (gap == 10) {
    digitalWrite(apin, HIGH);
    digitalWrite(bpin, HIGH);
  }
  else {
    digitalWrite(apin, LOW);
    digitalWrite(bpin, LOW);
  }
  digitalWrite(latchpin, LOW);
  shiftOut(datapin, clockpin, LSBFIRST, int(pow(2,gap)));
  digitalWrite(latchpin, HIGH);
}

void showTemp(float T) {
  a = int(T) / 10;
  b = int(T) % 10;
  c = int(T * 10) % 10;
  digitalWrite(3, num[a][0]);//8
  digitalWrite(4, num[a][1]);//4
  digitalWrite(5, num[a][2]);//2
  digitalWrite(2, num[a][3]);//1
  digitalWrite(7, num[b][0]);//8
  digitalWrite(8, num[b][1]);//4
  digitalWrite(9, num[b][2]);//2
  digitalWrite(6, num[b][3]);//1
  digitalWrite(11, num[c][0]);//8
  digitalWrite(12, num[c][1]);//4
  digitalWrite(13, num[c][2]);//2
  digitalWrite(10, num[c][3]);//1
}
