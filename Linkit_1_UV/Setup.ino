void McsTest() {
  //MCS連線測試
  while (!mcs.connected()) {
    mcs.connect();
    if (mcs.connected()) {
      Serial.println("MCS 已重新連線");
    }
  }
  mcs.process(100);
}
int hash(int i) {
  int a = i / 10, b = i % 10;
  return a * 1 + b * 16;
}
void LinkitStatus() {
  //設定上傳數據通道
  mcs.addChannel(uv);
  mcs.addChannel(windspeed);
  mcs.addChannel(water);
  mcs.addChannel(direct);


  //設定網路
  Serial.println("Wi-Fi 開始連線");
  //無密碼網路
  while (WiFi.begin(_lwifi_ssid, _lwifi_pass) != WL_CONNECTED) {
    delay(1000);
  }
  //有密碼網路
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


  //Si1145測試
  Serial.println("Si1145測試");
  while (!SI1145.Begin()) {
    Serial.println("Si1145 is not ready!");
    delay(100);
  }
  Serial.println("Si1145 連線成功");
}
