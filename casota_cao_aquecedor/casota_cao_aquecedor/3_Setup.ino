void setup()
{
    Serial.begin(115200); 
    dht.begin(); 
    pinMode(heater_temperature_probe, INPUT);
    pinMode(Heater, OUTPUT);
    digitalWrite(Heater,HIGH);



    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
    Serial.print("Connecting to ");
    Serial.print(WIFI_SSID);

    connectToWifi();



    Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);                 // connect to the firebase


    timeClient.begin();
    timeClient.setTimeOffset(3600); // time offset in seconds
    

    delay(1000);
}
