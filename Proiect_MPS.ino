#include "dht.h"
#include <ESP32Firebase.h>

#define temp_sensor 25
#define fan 5// 27
#define relay 32
#define _SSID "DIGI_71c7ca"          // WiFi SSID
#define _PASSWORD "bdbdbb0d"      // WiFi Password
#define REFERENCE_URL "https://tempcontrol-3864f-default-rtdb.firebaseio.com/"

//#define _SSID "DIGI-yeS3"
//#define _PASSWORD "zxgAG7pjEw"
dht DHT1;
float temp;
float tempReq;
Firebase firebase(REFERENCE_URL); 

void setup(){
  pinMode(fan, OUTPUT); 
  pinMode(temp_sensor, INPUT); 
  pinMode(relay,OUTPUT);
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  delay(1000);
   // Connect to WiFi
  Serial.println();
  Serial.println();
  Serial.print("Conectare la: ");
  Serial.println(_SSID);
  WiFi.begin(_SSID, _PASSWORD);
  Serial.begin(9600);
  delay(500);//Delay to let system boot.
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print("-");
  }

  Serial.println("");
  Serial.println("WiFi Conectat");
  temp = 0;
  tempReq = 0;
  delay(1000);//Wait before accessing Sensor
  
 
}
 
void loop(){
   
    DHT1.read11(temp_sensor);
    Serial.print("Temperatura actuala = ");
    temp = DHT1.temperature;
    Serial.print(temp); 
    Serial.println("C  ");
    firebase.setInt("Current Temperature", temp);
    tempReq = firebase.getInt("Temperature");
    Serial.print("Temperatura dorita = ");
    Serial.print(tempReq); 
    Serial.println("C  ");
    temperature_Check();
    int fanState = digitalRead(fan);
    Serial.print("Starea pinului 'fan': ");
    Serial.println(fanState);

    delay(2000);
 
}

void temperature_Check(void){
  if( temp > tempReq)
     {
        digitalWrite(fan, LOW);
     }
      else
      {
        digitalWrite(fan, HIGH);
    
      }

    if( temp < tempReq)
    {
      digitalWrite(relay, HIGH);
    }
    else
    {
      digitalWrite(relay, LOW);
    }   

}
