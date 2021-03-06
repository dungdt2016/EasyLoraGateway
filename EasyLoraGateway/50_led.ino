// ====================================
// LED
// ====================================
// LEDs are connected anode to +5, cathode to i/o pin. Aka: Active LOW.
// So pin set to LOW will on the LED
String LED_Status = "Not initalized";

void setupLED() {
  pinMode(LED, OUTPUT);
  digitalWrite(LED, HIGH);
  LED_Status = "OK";
}

void onLED() {
  digitalWrite(LED, LOW);
}

void offLED() {  
  digitalWrite(LED, HIGH);
}

void displayLEDErrorCode() {
  // Everything is OK
  if(ETH_Status == "OK" && MQTT_Status == "OK" && 
     LORA_Status == "OK" && WEBSERVER_Status == "OK") {
    Serial.println("[LED] Initialized OK for all modules.");
    for(int i=0; i < 18; i++) {
      onLED();
      delay(100);
      offLED();
      delay(100);
    }
  }
  else {
    // TODO: Display LED Code for each error
  }
}

void dataReceivedLED() {
  onLED();
  delay(50);
  offLED();  
}

