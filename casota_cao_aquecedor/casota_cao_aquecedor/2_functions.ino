// heater control
void Heat(int coolingDown, int hours)
{

    if (!coolingDown)
    {
        if (hours < 9 && temperature < minimum_temperature ||
                hours >= 19 && temperature < minimum_temperature)
        {

            digitalWrite(Heater, LOW);
            Heating_State_NOW = true;
#ifdef DEBUG
            Serial.println("HEAT IS ON");
#endif
        }
    }
    else
    {
        digitalWrite(Heater, HIGH);
        Heating_State_NOW = false;
#ifdef DEBUG
        Serial.println("HEAT IS OFF");
#endif
    }


}


bool HeatingElementHysteresis (void)
{


    probeTemperature = analogRead(heater_temperature_probe); // gets the heating element temperature

    probeTemperature = map(probeTemperature, 600, 1000, 15, 200); // maps to degrees centigrade

#ifdef DEBUG
    Serial.print("Probe = ");
    Serial.println(probeTemperature);
#endif


    if ( maxTemperatureReached && probeTemperature > 150)
    {
        return true;
    }

    if (probeTemperature >= maxElementTemperature)
    {
#ifdef DEBUG
        Serial.println("Heating element too hot");
#endif
        maxTemperatureReached = true;
        return true;
    }

    if (maxTemperatureReached && probeTemperature < 150)
    {
        maxTemperatureReached = false;
        return false;
    }

    return false;

}




//push data to firebase
void pushData(void)
{

    Firebase.setBool(FireData, "/Casota Marilou/Heating", Heating_State_NOW);
    Firebase.setFloat(FireData, "/Casota Marilou/Temperatura", temperature);
    Firebase.setInt(FireData, "/Casota Marilou/Sonda" , probeTemperature);
    Firebase.setString(FireData, "/Casota Marilou/Last update ", timeClient.getFormattedTime());
}



bool connectToWifi(void)
{
    for (int i = 0; i < 30; i++)
    {
        if (WiFi.status() == WL_CONNECTED)
        {
#ifdef DEBUG
            Serial.print("Connected");
            Serial.print("IP Address: ");
            Serial.println(WiFi.localIP());
#endif
            return true;
        }
        else
        {
            Serial.print(".");
            delay(500);
        }
    }

    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
#ifdef DEBUG
    Serial.print("Connecting to ");
    Serial.println(WIFI_SSID);
#endif
    return false;
}
