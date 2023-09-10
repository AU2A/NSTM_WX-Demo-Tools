void data() {
  while (millis() % 1000 != 0) {
    //讀取雨量
    if (digitalRead(10) == true && watercheck == 0)
    {
      watercheck = 1;
    }
    if (digitalRead(10) == false && watercheck == 1)
    {
      water2 = water2 + 1.00;
      watercheck = 0;
    }

    //讀取風速
    if (digitalRead(12) == true && windcheck == 0)
    {
      windcheck = 1;
    }
    if (digitalRead(12) == false && windcheck == 1)
    {
      wind = wind + 1.00;
      windcheck = 0;
    }

    //讀取紫外線
    UVdata += SI1145.ReadUV();
    UVcheck++;
  }
  UVdata /= UVcheck; 

  //讀取風向
  if     (analogRead(14) >= 4050)windDir = 0;
  else if (3750 > analogRead(14) && analogRead(14) > 3600)windDir = 2;
  else if (2600 > analogRead(14) && analogRead(14) > 2300)windDir = 4;
  else if (810 > analogRead(14) && analogRead(14) > 730)windDir = 6;
  else if (135 > analogRead(14) && analogRead(14) > 60)windDir = 8;
  else if (260 > analogRead(14) && analogRead(14) > 180)windDir = 10;
  else if (440 > analogRead(14) && analogRead(14) > 350)windDir = 12;
  else if (1420 > analogRead(14) && analogRead(14) > 1340)windDir = 14;
  windDir = windDir < 12 ? windDir + 4 : windDir - 12;
}
