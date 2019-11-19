#include <SPI.h>
#include <SD.h>

#define PIN_SD_CS 10

File myFile;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  while(!SD.begin(PIN_SD_CS)) Serial.println("initialization failed");
  Serial.println("initialization done");
  
}

void loop() {
  // put your main code here, to run repeatedly:
  myFile = SD.open("time.txt", FILE_WRITE);

  if(myFile){
    myFile.println(millis());
    myFile.close();
  }

}
