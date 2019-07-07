/************************ Adafruit IO Configuration *******************************/
#define IO_USERNAME    "your_username"
#define IO_KEY         "your_key"
/******************************* WIFI Configuration **************************************/
#define WIFI_SSID       "wifi_ssid"
#define WIFI_PASS       "password"

#include "AdafruitIO_WiFi.h"
AdafruitIO_WiFi io(IO_USERNAME, IO_KEY, WIFI_SSID, WIFI_PASS);

#include <ESP8266WiFi.h>
#include <AdafruitIO.h>
#include <Adafruit_MQTT.h>
#include <ArduinoHttpClient.h>

// These are used to set the direction of the bridge driver.
#define ENA D3      //ENA
#define leftMotorForward D4 //IN3
#define leftMotorBackward D5 //IN4
#define rightMotorForward D7 //IN1
#define rightMotorBackward D6 //IN2
#define ENB D8      //ENA

AdafruitIO_Feed *command = io.feed("voice_commands");

void setup() {
  // put your setup code here, to run once:
    pinMode(ENA, OUTPUT);
    pinMode(rightMotorForward, OUTPUT);
    pinMode(rightMotorBackward, OUTPUT);
    pinMode(ENB,OUTPUT);
    pinMode(leftMotorForward,OUTPUT);
    pinMode(leftMotorBackward,OUTPUT);

    digitalWrite(ENA,LOW);
    digitalWrite(ENB,LOW);

    Serial.begin(115200);

    Serial.print("Connecting to Adafruit IO");
    io.connect();

  // set up a message handler for the 'command' feed.
  // the handleMessage function (defined below)
  // will be called whenever a message is
  // received from adafruit io.
  command->onMessage(handleMessage);

  while(io.status() < AIO_CONNECTED) {
    Serial.print(".");
    delay(50);
  }

  // we are connected
  Serial.println();
  Serial.println(io.statusText());
}

void loop() {
    io.run();

}

void handleMessage(AdafruitIO_Data *data){

 String commandStr = data->toString();

  Serial.print("received <- ");
  Serial.println(commandStr);

  String cmd;
  int angle;

   for (int i = 0; i < commandStr.length(); i++) {
    if (commandStr.substring(i, i+1) == ":") {
      cmd = commandStr.substring(0, i);
      angle = commandStr.substring(i+1).toInt();
      break;
    }
  }
      

  if (cmd.equalsIgnoreCase("left")){
      Serial.println("Turning Left");
      digitalWrite(ENA,HIGH);
      digitalWrite(ENB,HIGH);
      digitalWrite(rightMotorForward,HIGH);
      digitalWrite(rightMotorBackward,LOW);
      digitalWrite(leftMotorForward,LOW);
      digitalWrite(leftMotorBackward,HIGH);
      delay(angle*15);
      Serial.println("Stop");
      digitalWrite(ENA,LOW);
      digitalWrite(ENB,LOW);
      digitalWrite(rightMotorForward,LOW);
      digitalWrite(rightMotorBackward,LOW);
      digitalWrite(leftMotorForward,LOW);
      digitalWrite(leftMotorBackward,LOW);
    }

    if (cmd.equalsIgnoreCase("right")){
      Serial.println("Turning right");
      digitalWrite(ENA,HIGH);
      digitalWrite(ENB,HIGH);
      digitalWrite(rightMotorForward,LOW);
      digitalWrite(rightMotorBackward,HIGH);
      digitalWrite(leftMotorForward,LOW);
      digitalWrite(leftMotorBackward,HIGH);
      delay(angle*15);
      Serial.println("Stop");
      digitalWrite(ENA,LOW);
      digitalWrite(ENB,LOW);
      digitalWrite(rightMotorForward,LOW);
      digitalWrite(rightMotorBackward,LOW);
      digitalWrite(leftMotorForward,LOW);
      digitalWrite(leftMotorBackward,LOW);
    }

    if (cmd.equalsIgnoreCase("forward")){
      Serial.println("Moving forward");
      digitalWrite(ENA,HIGH);
      digitalWrite(ENB,HIGH);
      digitalWrite(rightMotorForward,HIGH);
      digitalWrite(rightMotorBackward,LOW);
      digitalWrite(leftMotorForward,HIGH);
      digitalWrite(leftMotorBackward,LOW);
      delay(1000);
      digitalWrite(ENA,LOW);
      digitalWrite(ENB,LOW);
      digitalWrite(rightMotorForward,LOW);
      digitalWrite(rightMotorBackward,LOW);
      digitalWrite(leftMotorForward,LOW);
      digitalWrite(leftMotorBackward,LOW);
    }

    if (cmd.equalsIgnoreCase("back")){
      Serial.println("Moving Back");
      digitalWrite(ENA,HIGH);
      digitalWrite(ENB,HIGH);
      digitalWrite(rightMotorForward,LOW);
      digitalWrite(rightMotorBackward,HIGH);
      digitalWrite(leftMotorForward,LOW);
      digitalWrite(leftMotorBackward,HIGH);
      delay(1000);
      digitalWrite(ENA,LOW);
      digitalWrite(ENB,LOW);
      digitalWrite(leftMotorForward,LOW);
      digitalWrite(rightMotorForward,LOW);
      digitalWrite(rightMotorBackward,LOW);
      digitalWrite(leftMotorBackward,LOW);
    }
 }
