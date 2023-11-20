

#include <Arduino.h>

#include <Wire.h>
#include <RTClib.h>
#include <time.h>
//#include <SD.h>
//#include "save_data.h"
//#include "save_data.h"


#define SD_CS 45 

#define MY_SCLK     36
#define MY_MISO     37
#define MY_MOSI     35


// void printDate(DateTime date);

int setTime_date_static(int Hour,int Min,int Sec,int Day,int Month,int Year);
void get_timer_();
int initialice_timer_RTC();
int initialice_SD_card();
void printDate(DateTime now_local);
String get_timer_return();
void get_timer_return(char* buffer );
void get_timer_return_ISO(char* buffer);
String getTimestamp_rename_file();
