#include <SPI.h>
#include <SD.h>
#include <Stepper.h>
//#include <AccelStepper.h>
/*
AccelStepper mystepx(1, 2, 3);
AccelStepper mystepy(1, 5, 6);
AccelStepper mystepz(1, 8, 9);
*/

Stepper mystepz = Stepper(100,8,9);
Stepper mystepx = Stepper(100,2,3);
Stepper mystepy = Stepper(100,5,6);


File instructions;

void setup() {
  /*
  mystepx.setMaxSpeed(600);
  mystepy.setMaxSpeed(600);
  mystepz.setMaxSpeed(600);
  */

  mystepx.setSpeed(800);
  mystepy.setSpeed(800);
  mystepz.setSpeed(800);

  Serial.begin(9600);
  Serial.println("Initializing SD card...");

  if (!SD.begin(10)) {
    Serial.println("initialization failed!");
    while (1);
  }
  
  Serial.println("initialization done.");

  instructions = SD.open("file.txt");
  int steps_for_z = 500;
  int X;
  int Y;
  int current_x = 0;
  int current_y = 0;
  int step_y = 25;
  int step_x = 25;
  char symbol;
  delay(5000);
  Serial.println("Uploaded. Turn on machine!!!");
  delay(3000);
  Serial.println("Let's start:)");
  while (instructions.available()) {
    
    String x = "";
    String y = "";
    while((symbol = instructions.read()) <= '9' && symbol >= '0'){
      x += symbol;
    }
    
    X = x.toInt();
    
    while((symbol = instructions.read()) <= '9' && symbol >= '0'){
      y += symbol;
    }
    
    Y = y.toInt();

    Serial.print(X);
    Serial.print(' ');
    Serial.print(Y);
    Serial.println();
    mystepx.step((X-current_x)*step_x);
    //delay(500);
    mystepy.step((Y-current_y)*step_y);
    //delay(500);
    mystepz.step(steps_for_z);
    steps_for_z = steps_for_z * (-1);
    //delay(500);

    current_x = X;
    current_y = Y;
    
  }
  
  mystepx.step((0-current_x)*step_x);
  mystepx.step((0-current_y)*step_y);
  
  instructions.close();
  Serial.println("Task was completed");
  delay(10000);

}

void loop() {
  // put your main code here, to run repeatedly:

}
