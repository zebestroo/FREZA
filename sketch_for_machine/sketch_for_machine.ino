#include <SPI.h>
#include <SD.h>
#include <Stepper.h>
Stepper mystepz = Stepper(100,8,9);
Stepper mystepx = Stepper(100,2,3);
Stepper mystepy = Stepper(100,5,6);

const int PIN_CHIP_SELECT = 4;

void setup() {
  delay(5000);
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
  
  mystepx.setSpeed(600);
  mystepy.setSpeed(600);
  mystepz.setSpeed(600);

  File dataFile = SD.open("file.txt", FILE_READ);
  int x = 0;
  int y = 0;
  int step_y = 25;
  int step_x = 25;
  // Если все хорошо, то записываем строку:
 if (dataFile) {
    Serial.println("Your file is open\n");
  char symbol = '0';// = dataFile.read();  
  bool flag = false;
  int dir = 1; 
    while (dataFile.available()) {
      Serial.println("Go!");
      while(symbol != -1){

        
        while(symbol == '0' || symbol == '1'){
          Serial.print(symbol);
          if(symbol == '1' && flag == false)
          {
            flag = true;
            mystepz.step(500);
            //delay(1000);
          }
          if(symbol == '0' && flag == true)
          {
            flag = false;
            mystepz.step((-1)*500);
            //delay(1000);
          }
          mystepy.step(step_y*dir);
          y += step_y*dir;
          //delay(1000);
          symbol = dataFile.read();

        }

        Serial.print('\n');
        mystepx.step(-step_x);
        x -= step_x;
        dir *= -1;
        symbol = dataFile.read();
      }
      dataFile.close();
    }

  mystepx.step(-x);
  mystepy.step(-y);
  delay(10000);

}

  // if the file isn't open, pop up an error:

  else {

    Serial.println("error opening text.txt");

  }





  


  
}

void loop() {
  // put your main code here, to run repeatedly:

}
