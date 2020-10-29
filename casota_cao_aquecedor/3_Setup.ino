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

    // Tries to connect to Wifi 20 times
    for (int i = 0; i < 20; i++)  
    {
        if (WiFi.status() == WL_CONNECTED)
        {
            break;
        }
        else
        {
            Serial.print(".");
            delay(500);
        }
    }

    Serial.println();
    Serial.print("Connected");
    Serial.print("IP Address: ");
    Serial.println(WiFi.localIP());                               //prints local IP address
    Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);                 // connect to the firebase


    timeClient.begin();
    timeClient.setTimeOffset(3600); // time offset in seconds
    lastMinute = timeClient.getMinutes();
}
