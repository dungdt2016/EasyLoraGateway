// https://github.com/256dpi/arduino-mqtt
#define mqttBrokerServer "broker.shiftr.io"
#define mqttNamespace "vinhdat82~easyloragateway"
#define mqttUsername "iotthinks"
#define mqttSecret "easyloragateway"
MQTTClient mqttClient;

unsigned long lastMillis = 0;

String MQTT_STATUS = "Not Initialized";
String MQTT_LASTSENT_MSG;

void setupMQTT() {
  // Should be connected to internet
  mqttClient.begin(mqttBrokerServer, netClient);
  mqttClient.onMessage(mqttMessageReceived);

  connectToMQTT();
}

void connectToMQTT() {
  Serial.print("Checking ethernet...");
  while (!eth_connected) {
    Serial.println("ETH not connected. Try to reconnect ETH.");
    setupEthernet();
    delay(1000);
  }

  while (!mqttClient.connect(mqttNamespace, mqttUsername, mqttSecret)) {
    Serial.print("MQTT not connected. Try to reconnect to MQTT.");
    delay(1000);
  }

  Serial.println("MQTT is connected");
  MQTT_STATUS = "OK";
  
  mqttClient.subscribe("/hello");
  // mqttClient.unsubscribe("/hello");
}

void mqttMessageReceived(String &topic, String &payload) {
  Serial.println("incoming: " + topic + " - " + payload);
}

void publishToMQTT(String message) {
  //The loop() function is a built in function that will read the receive and send buffers
  // and process any messages it finds.
  mqttClient.loop(); // Why need this?
  delay(10);
  
  if (!mqttClient.connected()) {
    connectToMQTT();
  }

  mqttClient.publish("/hello", message);
  MQTT_LASTSENT_MSG = message;
}

void testMQTT() {
  mqttClient.loop(); // Why need this?
  delay(10);  // <- fixes some issues with WiFi stability. Why need this?

  if (!mqttClient.connected()) {
    connectToMQTT();
  }

  // publish a message roughly every second.
  if (millis() - lastMillis > 1000) {
    lastMillis = millis();
    mqttClient.publish("/hello", "Easy Lora Gateway");
  }
}