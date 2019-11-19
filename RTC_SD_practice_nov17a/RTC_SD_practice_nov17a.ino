#include <SPI.h>
#include <SD.h>
#include "RTClib.h"

#define PIN_SD_CS 10

File my_file;
RTC_PCF8523 rtc;
String rtc_date = "";
String rtc_time = "";

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  while(!SD.begin(PIN_SD_CS)) Serial.println("SD card initialization failed - insert SD card");
  Serial.println("initialization done");

  while(!rtc.begin()) Serial.println("Cannot find real time clock");
  while(!rtc.initialized()){
    Serial.println("RTC is NOT running");
    // This line sets the RTC with an explicit date & time, for example to set
    // January 21, 2014 at 3am you would call:
    // rtc.adjust(DateTime(2014, 1, 21, 3, 0, 0));
  }
}

void loop() {
  // put your main code here, to run repeatedly:
  DateTime now = rtc.now();

  rtc_date += now.year(); rtc_date += "/";
  rtc_date += now.month(); rtc_date += "/";
  rtc_date += now.day(); rtc_date += " ";
  Serial.println(rtc_date);
  // Writes information to file on SD card
  my_file = SD.open("time.txt", FILE_WRITE);
  if(my_file){
    my_file.println(millis());
    my_file.close();
  }

}
