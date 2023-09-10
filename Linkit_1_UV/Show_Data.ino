int light[12][3] =
{ {0, 255, 0},
  {0, 255, 0},
  {0, 255, 0},
  {95, 160, 0},
  {95, 160, 0},
  {95, 160, 0},
  {160, 95, 0},
  {160, 95, 0},
  {255, 0, 0},
  {255, 0, 0},
  {255, 0, 0},
  {128, 0, 128}
};

void show_data() {

  //紫外線數據顯示
  index = 11 * UVdata / 1000;
  if (index > 11)index = 11;
  analogWrite(17, 255 - light[index][0]);
  analogWrite(15, 255 - light[index][1]);
  analogWrite(16, 255 - light[index][2]);

  //風向數據顯示
  for (int i = 0; i < windDir; i++) {
    windDirect.setPixelColor(i, windDirect.Color(0, 0, 0));
  }
  windDirect.setPixelColor(windDir, windDirect.Color(10, 10, 10));
  for (int i = windDir + 1; i < 16; i++) {
    windDirect.setPixelColor(i, windDirect.Color(0, 0, 0));
  }
  windDirect.show();

  //風速數據顯示
  if (wind >= 8)wind = 8;
  for (int i = 0; i < wind; i++) {
    windSpd.setPixelColor(i, windSpd.Color(10, 10, 10));
  }
  for (int i = wind; i < 8; i++) {
    windSpd.setPixelColor(i, windSpd.Color(0, 0, 0));
  }
  windSpd.show();

  back = int(water2 * 0.2794)%10;
  front = int(water2 * 0.2794) / 10;
  digitalWrite(latchPin, LOW);
  shiftOut(dataPin, clockPin, LSBFIRST, hash(front) );
  shiftOut(dataPin, clockPin, LSBFIRST, hash(back));
  digitalWrite(latchPin, HIGH);
}
