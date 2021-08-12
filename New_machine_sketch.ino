#include <SPI.h>
#include <SD.h>
#include <Stepper.h>
Stepper mystepz = Stepper(100,8,9);
Stepper mystepx = Stepper(100,2,3);
Stepper mystepy = Stepper(100,5,6);

const int PIN_CHIP_SELECT = 4;

void setup() {
  //delay(5000);
  // put your setup code here, to run once:

  Serial.begin(9600);
  Serial.print("Initializing SD card...");
 // Этот пин обязательно должен быть определен как OUTPUT
  pinMode(10, OUTPUT);

  
  // Пытаемся проинициализировать модуль
  Serial.write('\n');
  if (SD.begin(PIN_CHIP_SELECT)) {
    Serial.println("Success");
    // Если что-то пошло не так, завершаем работу:
  }
  delay(5000);
  
  //mystepx.setSpeed(600);
  //mystepy.setSpeed(600);
  //mystepz.setSpeed(600);

  File dataFile = SD.open("file1.txt", FILE_READ);
  int x = 0;
  int y = 0;
  int step_y = 25;
  int step_x = 25;
  // Если все хорошо, то записываем строку:
 if (dataFile) {
    Serial.println("Your file is open\n");
  char symbol = dataFile.read();// = dataFile.read();  
  bool flag = false;
  int dir = 1;
  char M[2000];
  for(int s = 0; s < 2000; s++){
    M[s] = '*';
  }
  int i = 0;
  while(dataFile.available()){
    while(symbol != 0){
      while(symbol != '\n'){
      M[i] = symbol;
      Serial.print(M[i]);
      symbol = dataFile.read();
      i++;
    }
    Serial.print('\n');
    i = 0;
    //Serial.print("Point");
    while(M[i] != '*'){
        
          //Serial.print(symbol);
          if(M[i] == '1' && flag == false)
          {
            flag = true;
            mystepz.step(500);
            //delay(1000);
          }
          if(M[i] == '0' && flag == true)
          {
            flag = false;
            mystepz.step((-1)*500);
            //delay(1000);
          }
          mystepy.step(step_y*dir);
          y += step_y*dir;
          i++;
          
    } 
        mystepx.step(-step_x);
        x -= step_x;
        dir *= -1;
        symbol = dataFile.read();
      
  }
  }
  mystepx.step(-x);
  mystepy.step(-y);
  delay(10000);

}

  else {

    Serial.println("error opening text.txt");

  }





  


  
}

void loop() {
  // put your main code here, to run repeatedly:

}
