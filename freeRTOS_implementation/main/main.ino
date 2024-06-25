#include "DistanceSensor.h"
#include "WLAN.h"
#include "MQTT.h"

#define TRIG_PIN 12
#define ECHO_PIN 11
#define WLAN_CONNECTED_LED_PIN 7
#define PUBLISH_TO_CONVEYER_BELT_LED_PIN 6
#define SUBSCRIBE_TO_COLOR_SENSOR_LED_PIN 5
#define NEAR_THRESHOLD_CMS 18


//set interval for sending messages (milliseconds)
const long interval = 1000;
unsigned long previousMillis = 0;

DistanceSensor distanceSensor(TRIG_PIN, ECHO_PIN);

void setup() {
  
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(WLAN_CONNECTED_LED_PIN, OUTPUT);
  pinMode(PUBLISH_TO_CONVEYER_BELT_LED_PIN, OUTPUT);
  pinMode(SUBSCRIBE_TO_COLOR_SENSOR_LED_PIN, OUTPUT);
  
  connectToWifi();

  connectToMQTTBroker();

  digitalWrite(LED_BUILTIN, HIGH);

  subscribeToTopic("RoboticArm");

}


void loop() {

  if(!mqttClient.connected()){

    digitalWrite(LED_BUILTIN, LOW);

    connectToWifi();

    connectToMQTTBroker();

  } else {

    digitalWrite(LED_BUILTIN, HIGH);

    unsigned long currentMillis = millis();
  
    if(distanceSensor.isObjectDetected(NEAR_THRESHOLD_CMS) && currentMillis - previousMillis >= interval){

      // save the last time a message was sent
      previousMillis = currentMillis;

      publishMessage("1", "BoxDetection");
      
    }

    mqttClient.poll();

  }

  delay(100); 

}
