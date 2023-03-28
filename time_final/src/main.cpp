#include <Arduino.h>
#include <WiFi.h>
#include <string.h>
#include <stdio.h>
#include "TimeLib.h"
#include "time.h"
#include "TinyGPS++.h"
#include "SoftwareSerial.h"

#define GPS_RX_PIN 17
#define GPS_TX_PIN 16

const char* ssid     = "id";
const char* password = "pw";

const char* ntpServer = "pool.ntp.org";
const long  gmtOffset_sec = 0;
const int   daylightOffset_sec = 0;

struct tm timeinfo;

TinyGPSPlus gps;
SoftwareSerial gpsSerial(GPS_TX_PIN, GPS_RX_PIN);

void getLocalTime()
{
  
  if(!getLocalTime(&timeinfo)){
    Serial.println("Failed to obtain time");
    return;
  }
}


void time_string(char time_str[])
{
  char hr[3], min[4], sec[10],sec1[3],sec2[7], yr[5],mn[3],d[3];
  sprintf(yr, "%d", year());
  strcat(time_str,yr);
  strcat(time_str,"-");
  sprintf(mn, "%d", month());
  if (month() < 10)
  {
    strcat(time_str,"0");
    strcat(time_str,mn);
  }
  else
  strcat(time_str,mn);
  strcat(time_str,"-");
  sprintf(d, "%d", day());
  if (day() < 10)
  {
    strcat(time_str,"0");
    strcat(time_str,d);
  }
  else
  strcat(time_str,d);
  strcat(time_str," ");
  sprintf(hr, "%d", hour());
  if (hour() < 10)
  {
    strcat(time_str,"0");
    strcat(time_str,hr);
  }
  else
  strcat(time_str,hr);
  sprintf(min, "%d", minute());
  strcat(time_str,":");
  if (minute() < 10)
  {
    strcat(time_str,"0");
    strcat(time_str,min);
  }
  else
  strcat(time_str,min);
  sprintf(sec, "%f", (float)second()); 
  strcat(time_str,":");
  strncpy(sec1,sec,2);
  strncpy(sec2,sec+3,6);
  if (second() < 10)
  {
    strcat(time_str,"0");
    strcat(time_str,sec1);
  }
  else
  strcat(time_str,sec1);
  strcat(time_str,":");
  strcat(time_str,sec2);
}


void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  
  if (gps.location.isValid())
  {
    setTime((int)gps.time.hour(),(int)gps.time.minute(),(int)gps.time.second(),(int)gps.date.day(),(int)gps.date.month(),(int)gps.date.year());
  }

  //connect to WiFi
  Serial.printf("Connecting to %s ", ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
      delay(500);
      Serial.print(".");
  }
  Serial.println(" CONNECTED");
  
  //init and get the time
  configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);
  getLocalTime();
  Serial.println("Fetching the timefrom NTP serverand storing in time library");
  setTime(timeinfo.tm_hour, timeinfo.tm_min, timeinfo.tm_sec,timeinfo.tm_mday,timeinfo.tm_mon,timeinfo.tm_year+1900);
}
time_t prevDisplay = 0;

void loop()
{  
  char time_str[27]="";
  if (timeStatus() != timeNotSet) {
    if (now() != prevDisplay) { //update the display only if time has changed
      prevDisplay = now();
      time_string(time_str); 
      Serial.println(time_str);
      delay(1000);  
    }
  }
}

