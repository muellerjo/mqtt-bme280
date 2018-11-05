void json(){


StaticJsonBuffer<400> jsonBuffer;


// DATA JSON #############################################
JsonObject& json_data = jsonBuffer.createObject();
json_data["SensorID"] = clientID;
json_data["MAC"] = WiFi.macAddress();
json_data["Firmware"] = FW_VERSION;
json_data["latitude"] = latitude;
json_data["longitude"] = longitude;


JsonObject& data = json_data.createNestedObject("data");
data.set("temperature", bme.readTemperature());
data.set("humidity", bme.readHumidity());
data.set("pressure", bme.readPressure()/100);

//root.printTo(Serial);
//Serial.println(); //Zeilenumbruchh für seriellen Monitor


  json_data.printTo(JSONmessageBuffer, sizeof(JSONmessageBuffer));
  Serial.print("JSON Data Output: ");
  Serial.println(JSONmessageBuffer);
  Serial.println();

}
