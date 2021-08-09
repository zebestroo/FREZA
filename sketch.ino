#include <Stepper.h>
Stepper mystepz = Stepper(100,8,9);
Stepper mystepx = Stepper(100,2,3);
Stepper mystepy = Stepper(100,5,6);

void setup() {
  delay(7000); 
  //mystep.step(1000);
  //mystep.step(-1000);
  //mystep.setSpeed(2000);
  // put your setup code here, to run once:
/*
  mystep.setSpeed(1100);
  mystep.step(1000);
  delay(1000);
  */
  //mystep.setSpeed(1100);
  //mystep.step(-8000);
  //delay(1000);
  //mystep.setSpeed(900);
  //mystep.step(2000);  
  //delay(2000);
  //mystep.setSpeed(400);
  //mystep.step(2000);
  //delay(1000);

}

void loop() {
  // put your main code here, to run repeatedly:
  //mystep.step(1);
  mystepx.setSpeed(600);
  mystepy.setSpeed(600);
  mystepz.setSpeed(600);
  /*
  for(int i = 0; i < 1000; i++){
  mystepx.step(1);
  mystepy.step(1);
  mystepz.step(1);
  //delay(1000);
  }
  for(int i = 0; i < 1000; i++){
  mystepx.step(-1);
  mystepy.step(-1);
  mystepz.step(-1);
  //delay(1000);
  }
  */
  //mystepz.step(1500);
  //delay(500);
  //mystepx.step(1500);
  //delay(500);
  mystepz.step(500);
  delay(2000);
  mystepy.step(500);
  delay(2000);
  mystepz.step(-500);
  delay(2000);
  mystepy.step(-500);
  delay(2000);
  //mystepx.step(-1500);
  //delay(500);
  //mystepy.step(-1500);
  //delay(500);

  

}
