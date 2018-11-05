void checkForUpdates() {
  String mac = WiFi.macAddress();
  //String scriptname = "blink";
  String fwURL = String( fwUrlBase );
  fwURL.concat(mac);
  String fwVersionURL = fwURL;
  fwVersionURL.concat( ".version" );

  Serial.println( "Checking for firmware updates." );
  //Serial.print( "MAC address: " );
  //Serial.print( "Script Name: " );
  //Serial.println(scriptname);
  Serial.print( "Firmware version URL: " );
  Serial.println( fwVersionURL );

  HTTPClient httpClient;
  httpClient.begin( fwVersionURL );
  int httpCode = httpClient.GET();
  if( httpCode == 200 ) {
    String newFWVersion = httpClient.getString();

    Serial.print( "Current firmware version: " );
    Serial.println( FW_VERSION );
    Serial.print( "Available firmware version: " );
    Serial.println( newFWVersion );

    float newVersion = newFWVersion.toFloat();

    if( newVersion > FW_VERSION ) {
      Serial.println( "Preparing to update" );
      client.publish("esp/status", "Preparing to update", false);

      String fwImageURL = fwURL;
      fwImageURL.concat( ".bin" );
      t_httpUpdate_return ret = ESPhttpUpdate.update( fwImageURL );

      switch(ret) {
        case HTTP_UPDATE_FAILED:
          Serial.printf("HTTP_UPDATE_FAILD Error (%d): %s", ESPhttpUpdate.getLastError(), ESPhttpUpdate.getLastErrorString().c_str());
          break;

        case HTTP_UPDATE_NO_UPDATES:
          Serial.println("HTTP_UPDATE_NO_UPDATES");
          break;
      }
    }
    else {
      Serial.println( "Already on latest version" );
      client.publish("esp/status", "Already on latest version", false);
    }
  }
  else {
    Serial.print( "Firmware version check failed, got HTTP response code " );
    client.publish("esp/status", "Firmware version check failed", false);
    Serial.println( httpCode );
  }
  httpClient.end();
}
