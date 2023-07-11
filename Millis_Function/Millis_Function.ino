#include<Sevro.h>
int digits[10][7] = {
                      {1,1,1,1,1,1,0},//0
                      {0,1,1,0,0,0,0},//1
                      {1,1,0,1,1,0,1},//2
                      {1,1,1,1,0,0,1},//3
                      {0,1,1,0,0,1,1},//4
                      {1,0,1,1,0,1,1},//5
                      {1,0,1,1,1,1,1},//6
                      {1,1,1,0,0,0,0},//7
                      {1,1,1,1,1,1,1},//8
                      {1,1,1,1,0,1,1},//9
                     };
unsigned long previousTime = 0;
unsigned long Interval = 1000;
int d = 0 ;
void setup() {
  Serial.begin(9600);
    for(int i = 13; i>7; i--){
      pinMode(i,OUTPUT);
    }
    pinMode(2,OUTPUT);
    servo1.attatch(6);
}

void loop() {
  unsigned currentTime = millis();

  if(currenrTime - previousTime >= Interval 0){
    previousTime = currentTime;
  }
  for(int i=13; i>= 7; i--){
    digitalWrite(i, digits[d][13-i]);
    d++;
  }
  if(digitalRead(2)==LOW||d == 10){
    d=0;
  }

}
