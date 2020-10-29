#include <ESP8266WiFi.h>
#include <FirebaseESP8266.h>
#include <DHT.h>
#include <WiFiUdp.h>
#include <NTPClient.h>

const String FIREBASE_HOST = "https://house-c180e.firebaseio.com/"; // stuff
const String FIREBASE_AUTH = "yYYwUH8D8jG1YCyhDm1dElw6zbOq0qw0tWb7yvcz"; //stuff

const String WIFI_SSID = "NOS-9615"; //stuff
const String WIFI_PASSWORD = "5EUTNZQH"; //stuff

//const String WIFI_SSID = "NOS_Internet_Movel_9C0A"; //stuff
//const String WIFI_PASSWORD = "68134821"; //stuff

const int DHTPIN  = 4; //air temperature sensor pin
const int heater_temperature_probe = A0; //heating element temperature pin
const int Heater = 12; //heating element control pin
const int minimum_temperature = 18; // heater switches on at this temperature
int lastMinute; 
int maxElementTemperature = 190;
bool maxTemperatureReached = false;
bool Heating_State_NOW =  false;
bool Heating_State_THEN =  false;
float previousTemperature = 0;
double previousWattHour = 0;
int previousProbeTemperature = 0;
unsigned long heater_ON_duration = 0, heater_now_ON = 0, heater_now_OFF = 0;

#define DHTTYPE  DHT11 // using dth11 sensor

FirebaseData FireData;

WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP);

// Initialize dht type as DHT 11
DHT dht(DHTPIN, DHTTYPE);

void HOT_ELEMENT (bool State);
