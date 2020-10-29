void loop()
{
    temperature =  dht.readTemperature() - 3.0;                              // get air temperature

#ifdef DEBUG
    Serial.print("Temperature: ");
    Serial.print(temperature);
    Serial.println("°C ");
#endif


    timeClient.update();
    int hours = timeClient.getHours();
    int minutes = timeClient.getMinutes();

#ifdef DEBUG
    Serial.print("Time: ");
    Serial.print(hours);
    Serial.print(":");
    Serial.println(minutes);
#endif




    //heater control
    Heat(HeatingElementHysteresis(), hours);
    
    pushData();

    delay(5000);
}
