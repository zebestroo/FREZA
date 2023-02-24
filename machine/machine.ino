#include <SPI.h>
#include <SD.h>
#include <Stepper.h>
#include <AccelStepper.h>


AccelStepper mystepz(1, 9, 8);
AccelStepper mystepx(1, 3, 2);
AccelStepper mystepy(1, 6, 5);


File instructions;

void setup() {
  
  int pin0 = 0;
  int pin1 = 1;
  pinMode(pin0, OUTPUT);
  pinMode(pin1, OUTPUT);
  digitalWrite(pin0, HIGH);
  digitalWrite(pin1, HIGH);

  
  mystepx.setMaxSpeed(1200);
  mystepy.setMaxSpeed(1200);
  mystepz.setMaxSpeed(1200);

  mystepx.setSpeed(1200);
  mystepy.setSpeed(1200);
  mystepz.setSpeed(1200);

  Serial.begin(9600);
  Serial.println("Initializing SD card...");

  if (!SD.begin(10)) {
    Serial.println("initialization failed!");
    while (1);
  }
  
  Serial.println("initialization done.");

  instructions = SD.open("file.txt");

  int steps_for_z = 200;
  int X;
  int Y;
  int std_speed = 600;
  //int current_x = 0;
  //int current_y = 0;
  int step_y = 4;
  int step_x = 4;
  char symbol;

  delay(5000);
  Serial.println("Uploaded. Turn on machine!!!");
  delay(5000);
  Serial.println("Let's start:)");
  bool set_speed_flag = true;
  
  while(instructions.available()){
    symbol = instructions.read();
    String action = "";
    while(symbol >= 'a' && symbol <= 'z'){
      action += symbol;
      symbol = instructions.read();
    }
    
    if(action == "move"){
      String x = "";
      String y = "";
      while((symbol = instructions.read()) <= '9' && symbol >= '0'){
        x += symbol;
      }
    
      Y = x.toInt();
      //X *= step_x;
      
      while((symbol = instructions.read()) <= '9' && symbol >= '0'){
        y += symbol;
      }
    
      X = y.toInt();
      Y *= step_y;
      X *= step_x;
      Serial.print(X);
      Serial.print(' ');
      Serial.print(Y);
      Serial.println();

      //mystepx.step((X-mystepx.currentPosition())*step_x);
      //mystepy.step((Y-mystepy.currentPosition())*step_y);
      //float delta_x = abs(X-mystepx.currentPosition());
      //float delta_y = abs(Y-mystepy.currentPosition());
      
      
        Serial.println("took if");
        mystepx.moveTo(X);
        mystepx.setSpeed(std_speed);
        mystepy.moveTo(Y);
        // SHIT IS HERE! TODO: FIXME
        /*
        Serial.print("Speed : ");
        float delta_x = abs(X-mystepx.currentPosition());
        float delta_y = abs(Y-mystepy.currentPosition());
        Serial.println(std_speed*delta_y/delta_x);
        mystepy.setSpeed(std_speed*delta_y/delta_x);        
        */
        mystepy.setSpeed(std_speed);
    
      

      Serial.print("Current x: ");
      Serial.print(mystepx.currentPosition());
      Serial.println();
      Serial.print("Current y: ");
      Serial.print(mystepy.currentPosition());
      Serial.println();

      Serial.print("GoTo x: ");
      Serial.print(X);
      Serial.println();
      Serial.print("GoTo y: ");
      Serial.print(Y);
      Serial.println();
      Serial.println();


      
      //current_x = X;
      //current_y = Y;

      while(mystepx.distanceToGo() != 0 || mystepy.distanceToGo() != 0){
          mystepx.runSpeedToPosition();
          mystepy.runSpeedToPosition();
        }
        
        /*
      do
      {
        //if (mystepx.distanceToGo() != 0) {
          mystepx.runSpeedToPosition();
          //mystepx.run();
          //Serial.println("X to move");        
        //}
        
        //if (mystepy.distanceToGo() != 0) {
          //Serial.println("Y to move");
          //mystepy.run();
          mystepy.runSpeedToPosition();
        //}
      } while (mystepx.distanceToGo() != 0 || mystepy.distanceToGo() != 0);
      */
      //delay(100);
      
      Serial.print("Current x after move: ");
      Serial.print(mystepx.currentPosition());
      Serial.println();
      Serial.print("Current y after move: ");
      Serial.print(mystepy.currentPosition());
      Serial.println();      
      
        
    }
    
    if(action == "down"){
      //mystepz.step(steps_for_z);

      mystepz.moveTo(-steps_for_z);
      mystepz.setSpeed(std_speed);
            
      while(mystepz.distanceToGo() != 0){
          mystepz.runSpeedToPosition();
        }
      //delay(100);
      
    }

    if(action == "up"){
      //mystepz.step(steps_for_z * (-1));
      mystepz.moveTo(steps_for_z);
      mystepz.setSpeed(std_speed);
      
      while(mystepz.distanceToGo() != 0){
          mystepz.runSpeedToPosition();
        }
      //delay(100);
    }
  }
  

  
    //mystepz.step((-5)*steps_for_z);
  //mystepx.step((0-current_x)*step_x);
  //mystepy.step((0-current_y)*step_y);

  mystepx.moveTo(0);
  mystepy.moveTo(0);
      
  while(mystepx.distanceToGo() != 0 || mystepy.distanceToGo() != 0){
    mystepx.runSpeedToPosition();
    mystepy.runSpeedToPosition();
  }
  
  instructions.close();
  Serial.println("Task was completed");
  delay(120000);

}

void loop() {
  // put your main code here, to run repeatedly:

}
