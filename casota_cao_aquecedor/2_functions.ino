// heater control
void Heat(int temperature, int hours)
{
    if (hours < 9 && temperature < minimum_temperature ||
            hours >= 19 && temperature < minimum_temperature)
    {




        if (HeatingElementSafety())
        {
            return;
        }



        HOT_ELEMENT(true);

    }
    else
    {
        HOT_ELEMENT(false);
    }
}


int HeatingElementSafety (void)
{


    int probeTemperature = analogRead(heater_temperature_probe); // gets the heating element temperature

    probeTemperature = map(probeTemperature, 600, 1000, 15, 200); // maps to degrees centigrade
    Serial.print("Probe = ");
    Serial.println(probeTemperature);

    delay(1);


    if (probeTemperature > previousProbeTemperature + 3 ||
            probeTemperature  < previousProbeTemperature - 3 )
    {
        previousProbeTemperature = probeTemperature;
        FireBasePushData(4, probeTemperature);

    }

    if (probeTemperature >= maxElementTemperature)
    {
        HOT_ELEMENT(false);
        Serial.println("Heating element too hot");
        maxTemperatureReached = true;

        delay(10000); // debounce
        return 1;
    }


    return 0;
}




//push data to firebase
void FireBasePushData(int Reason, double VAR)
{

    switch (Reason)
    {
        case 1: // Heating element too hot
            Firebase.setBool(FireData, "/Casota Marilou/Heating", (bool)VAR);
            Firebase.setString(FireData, "/Casota Marilou/Last update ", timeClient.getFormattedTime());
            Serial.println("Updating Heating");
            break;

        case 2: // Air temperature change;
            Firebase.setFloat(FireData, "/Casota Marilou/Temperatura", VAR);
            Firebase.setString(FireData, "/Casota Marilou/Last update ", timeClient.getFormattedTime());
            Serial.println("Updating temperature");
            break;
        case 3:
            Firebase.setDouble(FireData, "/Casota Marilou/wattHora estimado" , VAR);
            Firebase.setString(FireData, "/Casota Marilou/Last update ", timeClient.getFormattedTime());
            Serial.println("Updating watt hour");
            break;
        case 4:
            Firebase.setInt(FireData, "/Casota Marilou/Sonda" , (int)VAR);
            Serial.println("Updating sonda");
            Firebase.setString(FireData, "/Casota Marilou/Last update ", timeClient.getFormattedTime());
            break;





    }


}

void HOT_ELEMENT (bool State)
{
    if (State && !maxTemperatureReached)
    {

        digitalWrite(Heater, LOW); // Heater ON
        Serial.println("HEAT ON");





        EnergyCounter(true);

    }
    else
    {
        digitalWrite(Heater, HIGH); // Heater OFF



        EnergyCounter(false);
    }
}

void EnergyCounter(bool State)
{

    if (State)
    {

        Heating_State_NOW = true;
        if (!Heating_State_THEN)
        {
            heater_now_ON = millis();
            FireBasePushData(1, 1);
            Serial.println("pushing HEATING");
        }
        Heating_State_THEN = Heating_State_NOW;
    }
    else
    {
        heater_now_OFF = millis();
        FireBasePushData(1, 0);
        Serial.println("pushing HEATING");
        Heating_State_NOW = false;
    }



    if (Heating_State_NOW != Heating_State_THEN)
    {
        Heating_State_THEN = Heating_State_NOW;
        heater_ON_duration += heater_now_OFF - heater_now_ON;
        heater_now_OFF = 0;
        heater_now_ON = 0;
    }

    double wattHour = (heater_ON_duration / 1000) * 0.0700000000;
    Serial.print("Heat ON duration in seconds = ");
    Serial.println(heater_ON_duration / 1000);
    Serial.print("WATTS HOUR = ");
    Serial.println(wattHour);
    if (wattHour > previousWattHour)
    {
        FireBasePushData(3, wattHour);
        previousWattHour = wattHour;
    }



}
