void upload_data() {
  //上傳數據
  uv.set(UVdata / 100);
  windspeed.set(((wind * 4) / 3));
  water.set(water2 * 0.2794);
  if (windDir == 0)
  {
    direct.set("N ");
  }
  else if (windDir == 2)
  {
    direct.set("NE");
  }
  else if (windDir == 4)
  {
    direct.set("E ");
  }
  else if (windDir == 6)
  {
    direct.set("SE");
  }
  else if (windDir == 8)
  {
    direct.set("S");
  }
  else if (windDir == 10)
  {
    direct.set("SW");
  }
  else if (windDir == 12)
  {
    direct.set("W ");
  }
  else if (windDir == 14)
  {
    direct.set("NW");
  }
}
