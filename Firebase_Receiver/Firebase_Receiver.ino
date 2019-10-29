//firebase and d1 mini
#include <FirebaseArduino.h>
#include <ESP8266WiFi.h>
// for sd card module
#include <SD.h>
#include <SPI.h>



#define WIFI_SSID "ETPIEvoAirRoom13"             //replace SSID with your wifi username
#define WIFI_PASSWORD "password"           //replace PWD with your wifi password

#define FIREBASE_HOST "soilmonitor.firebaseio.com"                         //link of api
#define FIREBASE_AUTH "o7tjBdJsuePLvtGLGTxkK0DfywY9NbzjFIjSOAzT"           //database secret



int CS_PIN = D4;
int redLED = D0;
int goodLED = D3;
String prevReading = "";
File myFile;

void setup(){
   Serial.begin(9600);
   pinMode(redLED, OUTPUT);
   pinMode(goodLED, OUTPUT);
   WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  //connect to wifi
   while (WiFi.status() != WL_CONNECTED) { 
    Serial.println("CONNECT TO WiFi!!");          
    delay(1000);
   }

  Serial.println("");
  Serial.println("WiFi connected");

  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);             //connect to Database
  
//*********** CODE FOR SD CARD MODULE ************************************************ 
  while(!SD.begin(CS_PIN)) {
    Serial.println("Initialization failed! Insert SD CARD!");
    delay(2000);
  }
   if (!SD.exists("DATA.txt")) {
     Serial.println("CREATING DATA.TXT");
     myFile = SD.open("DATA.txt", FILE_WRITE);
     myFile.close();
  } 
   else {
    Serial.println("DATA.txt ALREADY EXIST");
  }
}

void loop() {
  // put your main code here, to run repeatedly:
  String timeStamp = Firebase.getString("time");
  String currentReading = Firebase.getString("reading");
  int dataValue = currentReading.toInt();
  Serial.print(timeStamp + "  - ");
  Serial.println(currentReading + "%");
  if(currentReading != prevReading){
    writeToSD(timeStamp, currentReading);
    prevReading = currentReading;
  }
  if(dataValue <= 50){
    digitalWrite(redLED, HIGH);
    digitalWrite(goodLED, LOW);
  }
  else{
    digitalWrite(redLED, LOW);
    digitalWrite(goodLED, HIGH);
    
  }
//  readSD();
  delay(1000);
}

void writeToSD(String Stamp, String DATA){
  myFile = SD.open("DATA.txt", FILE_WRITE);
  
  if(myFile){
    myFile.println(Stamp + "  - " + DATA);
       
  } 
  else {
    // if the file didn't open, print an error:
    Serial.println("error opening test.txt");
  }
  myFile.close(); // close the file:
}
