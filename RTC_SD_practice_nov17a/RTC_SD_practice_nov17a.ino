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

  if(!SD.begin(PIN_SD_CS)) { 
    Serial.println("SD card initialization failed - insert SD card");
    while(1);
  }
  Serial.println("initialization done");

  while(!rtc.begin()) {
    Serial.println("Cannot find real time clock");
    while(1);
  }
  while(!rtc.initialized()){
    Serial.println("RTC is NOT running");
    // This line sets the RTC with an explicit date & time, for example to set
    // January 21, 2014 at 3am you would call:
    // rtc.adjust(DateTime(2014, 1, 21, 3, 0, 0));
  }
}

void loop() {
  // put your main code here, to run repeatedly:
  rtc_date = "";
  rtc_time = "";
  DateTime now = rtc.now();

  rtc_date += now.year(); rtc_date += "/";
  if(now.month() < 10) rtc_date += '0';
  rtc_date += now.month(); rtc_date += "/";
  if(now.day() < 10) rtc_date += '0';
  rtc_date += now.day();

  if(now.hour() < 10) rtc_time += '0';
  rtc_time += now.hour(); rtc_time += ":";
  if(now.minute() < 10) rtc_time += '0';
  rtc_time += now.minute(); rtc_time += ":";
  if(now.second() < 10) rtc_time += '0';
  rtc_time += now.second();

  Serial.print(rtc_date);
  Serial.print(" ");
  Serial.println(rtc_time);
  
  // Writes information to file on SD card
  my_file = SD.open("pit.txt", FILE_WRITE);
  if(my_file){
    my_file.print(rtc_date);
    my_file.print(' ');
    my_file.println(rtc_time);
    my_file.close();
  }

}
