#include <FirebaseArduino.h>
#include <ESP8266WiFi.h>  
// for rtc
#include <Wire.h>
#include <DS3231.h>

DS3231 clockRtc;
RTCDateTime dt;

const int soilPin=A0;

#define WIFI_SSID "changeUsername"       //replace SSID with your wifi username
#define WIFI_PASSWORD "changePassword"          //replace PWD with your wifi password

#define FIREBASE_HOST "soilmonitor.firebaseio.com"                         //link of api
#define FIREBASE_AUTH "o7tjBdJsuePLvtGLGTxkK0DfywY9NbzjFIjSOAzT"           //database secret



void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  clockRtc.begin();
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  //connect to wifi
  while (WiFi.status() != WL_CONNECTED) {           //wait till connected to WiFi
    Serial.println("CAN'T CONNECT TO WiFi");
    delay(1000);
  }

  Serial.println("");
  Serial.println("WiFi connected");

  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);             //connect to Database

}

void loop() {
  // put your main code here, to run repeatedly:
  int soilReading = analogRead(soilPin);
  soilReading = abs(soilReading-1024);

  float percentage = (soilReading/(1024.0-570.0))*100;
  if(percentage > 100){
      percentage = 100.00;
    }

  Serial.print(writeTimeStamp());
  firebaseWrite("/time/",writeTimeStamp());
  Serial.print("  - " + String(percentage) + "%");
  Serial.println();
  firebaseWrite("/reading/",String(percentage)+"%");
  delay(1000);
}

void firebaseWrite(String address, String value)
{
  Firebase.setString(address, value);
}

String writeTimeStamp(){
  dt = clockRtc.getDateTime();
  String dateTime = clockRtc.dateFormat("F j Y h:i:s a",  dt);//October 14 2019
  return dateTime;
}
