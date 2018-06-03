#include <Ultrasonic.h>
#include <Wire.h>

int FORWARD[4]  = {0,1,1,0};
int LEFT[4]     = {1,0,1,0};
int RIGHT[4]    = {0,1,0,1};
int BACKWARD[4] = {1,0,0,1};
int STOP[4]     = {0,0,0,0};

void go(int where[4]){
  for(int i=0;i<4;i++){
    digitalWrite(4+i,where[i]);
  }
}

void demo(){
  go(FORWARD);
  delay(1000);
  go(LEFT);
  delay(1000);
  go(BACKWARD);
  delay(1000);
  go(STOP);
}

Ultrasonic ultrasonic(2, 3);
int DMIN=5, DMAX=20;

unsigned int getDistance(){
  unsigned int distance = ultrasonic.distanceRead();
  distance = distance > 0 ? distance : 255;
  //*
  String sendRead = String(distance);
  Wire.beginTransmission(8);
  Wire.write(sendRead.c_str());
  Wire.write("\n");
  Wire.endTransmission();
  //*/
  return distance;
}

void lockIn(int dmin){
  while ( getDistance() > dmin)
    delay(100);
}

void lockOut(int dmax){
  while (getDistance() < dmax)
    delay(100);
}

void setup() {
  // put your setup code here, to run once:
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(13,OUTPUT);
  //*
  Wire.begin();
  Wire.beginTransmission(8);
  Wire.write("Wellcome");
  Wire.endTransmission();
  //*/
}

void loop() {
  // put your main code here, to run repeatedly:
  lockIn(DMIN);
  for(int i=0;i<10;i++){
    digitalWrite(13,HIGH);
    delay(50);
    digitalWrite(13,LOW);
    delay(100);
  }
  lockOut(DMAX);
  digitalWrite(13,HIGH);
  demo();
  digitalWrite(13,LOW);
}
