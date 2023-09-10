int UV;
int light[12][3]={{0,255,0},
               {0,255,0},
               {0,255,0},
               {95,160,0},
               {95,160,0},
               {95,160,0},
               {160,95,0},
               {160,95,0},
               {255,0,0},
               {255,0,0},
               {255,0,0},
               {128,0,128}};
               
void setup() {
  pinMode(A3,OUTPUT);
  pinMode(A4,OUTPUT);
  pinMode(A5,OUTPUT);
  pinMode(A7,INPUT);

}

void loop() {
  UV=(analogRead(A7)/1000)*11;
  analogWrite(A3,255-light[UV][0]);
  analogWrite(A4,255-light[UV][1]);
  analogWrite(A5,255-light[UV][2]);
  delay(100);
}
