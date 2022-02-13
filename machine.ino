#include <SPI.h>
#include <SD.h>
#include <Stepper.h>


Stepper mystepz = Stepper(100,8,9);
Stepper mystepx = Stepper(100,2,3);
Stepper mystepy = Stepper(100,5,6);


File instructions;

void setup() {
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

  int steps_for_z = 400;
  int X;
  int Y;
  int current_x = 0;
  int current_y = 0;
  int step_y = 25;
  int step_x = 25;
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
      mystepy.step((Y-current_y)*step_y);

      current_x = X;
      current_y = Y;
    
    }

    if(action == "down"){
      mystepz.step(steps_for_z);
    }

    if(action == "up"){
      mystepz.step(steps_for_z * (-1));
    }

    if(action == "movesmth"){
      if(set_speed_flag){
        mystepx.setSpeed(300);
        mystepy.setSpeed(300);
        mystepz.setSpeed(300);
        set_speed_flag = false;
      }
      
      String x = "";
      String y = "";
      Serial.print("Smth: ");
      
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
      
      for(int i = 0; i < 25; i++){
        mystepx.step(X-current_x);
        mystepy.step(Y-current_y);
      }
      current_x = X;
      current_y = Y;
    }
  }
  
  
  
  
  
  
  
  
  
  
  
  /*
  int steps_for_z = 400;
  int X;
  int Y;
  int current_x = 0;
  int current_y = 0;
  int step_y = 25;
  int step_x = 25;
  char symbol;
  bool st = true;
  bool smoothing_flag = false;
  String smoothing = "";
  delay(5000);
  Serial.println("Uploaded. Turn on machine!!!");
  delay(5000);
  Serial.println("Let's start:)");
  while (instructions.available()) {
    String x = "";
    String y = "";
    if(smoothing == "Smoothing"){
      Serial.print("Smth: ");
    }
    while((symbol = instructions.read()) <= '9' && symbol >= '0'){
      x += symbol;
    }
    
    X = x.toInt();
    
    while((symbol = instructions.read()) <= '9' && symbol >= '0'){
      y += symbol;
    }
    
    Y = y.toInt();
    if(symbol > '9' || symbol < '0'){
      while((symbol <= 'Z' && symbol >= 'A') || (symbol >= 'a' && symbol <= 'z')){
        smoothing += symbol;
        symbol = instructions.read();
        Serial.println("reading!!!");
      }
      
    }
    

    Serial.print(X);
    Serial.print(' ');
    Serial.print(Y);
    Serial.println();
    */
/*
    if(smoothing == "Smoothing"){
      for(int i = 0; i < 25; i++){
        mystepx.step(X-current_x);
        mystepy.step(Y-current_y);
      }
    }
    else{
      mystepx.step((X-current_x)*step_x);
      mystepy.step((Y-current_y)*step_y);
    }
    
    
    if(st){
      mystepz.step(5*steps_for_z);
      st = false;
    }
    mystepz.step(steps_for_z);
    steps_for_z = steps_for_z * (-1);
    
    current_x = X;
    current_y = Y;
    
  }
  */
  
  //mystepz.step((-5)*steps_for_z);
  mystepx.step((0-current_x)*step_x);
  mystepy.step((0-current_y)*step_y);
  
  instructions.close();
  Serial.println("Task was completed");
  delay(120000);

}

void loop() {
  // put your main code here, to run repeatedly:

}
