void loop()
{
    float temperature =  dht.readTemperature() - 3.0;                              // get air temperature

    if (isnan(temperature))                                     // Checking sensor working
    {
        Serial.println(F("Failed to read from DHT sensor!"));

    }

    Serial.print("Temperature: ");
    Serial.print(temperature);
    Serial.println("°C ");


    timeClient.update();


    int hours = timeClient.getHours();
    int minutes = timeClient.getMinutes();

    Serial.print("Time: ");
    Serial.print(hours);
    Serial.print(":");
    Serial.println(minutes);





    // update database on air temperature change
    if ( temperature > previousTemperature + 0.1 ||
            temperature < previousTemperature - 0.1)
    {
        FireBasePushData(2, temperature);
        previousTemperature = temperature;
    }

    // 40C hysteresis once the heating element reaches 190c
    if(maxTemperatureReached && previousProbeTemperature < 150)
    {
       maxTemperatureReached = false;
    }

    //heater control
    Heat(temperature, hours);
    delay(5000);
}
