#include <WiFi.h>
#include "ThingSpeak.h"

int A33 = 33;

float voltage = 0;
float current = 0;
float V = 0;
float I = 0;

const int S0 = 13;
const int S1 = 12;
const int S2 = 14;
const int EN = 5;

const float adc = (3.3/4095.0);
const float G = 47/9.8;
const float R = 12;
const int N = 4;   // Number of Batteries (max 8). 



const char* ssid = "Saud PC";   // your network SSID (name) 
const char* password = "12345678";   // your network password

WiFiClient  client;

unsigned long myChannelNumber = 1;
const char * myWriteAPIKey = "YMKE7SJR54WL4V0N";

// Timer variables
unsigned long lastTime = 0;
unsigned long timerDelay = 3000;


void setup() {
  Serial.begin(115200);  //Initialize serial
  Serial.println("Starting...");
  delay(2000);

  pinMode(S0, OUTPUT);
  pinMode(S1, OUTPUT);
  pinMode(S2, OUTPUT);
  pinMode(EN, OUTPUT);

  WiFi.mode(WIFI_STA);   
  
  ThingSpeak.begin(client);  // Initialize ThingSpeak
}

void loop() {
  if ((millis() - lastTime) > timerDelay) {
    
    // Connect or reconnect to WiFi
    if(WiFi.status() != WL_CONNECTED){
      Serial.print("Attempting to connect");
      while(WiFi.status() != WL_CONNECTED){
        WiFi.begin(ssid, password); 
        delay(5000);     
      } 
      Serial.println("\n Connected.");
    }
    
    for (int i = 0; i < N; i++) {
      digitalWrite(S0, i & 0b001);
      digitalWrite(S1, i & 0b010);
      digitalWrite(S2, i & 0b100);
      digitalWrite(EN, LOW);  
      delay(1000);
      
      voltage = analogRead(A33)*adc*G;
      voltage = map(voltage, 550,0,0,100);

      ThingSpeak.setField(i+1, voltage);
      
      Serial.print("B");
      Serial.print(i+1);
      Serial.print(" Votage: ");
      Serial.println(voltage, 4);

      int x = ThingSpeak.writeField(myChannelNumber, i+1, voltage, myWriteAPIKey);
      
      if(x == 200){
        Serial.println("Channel update successful.");
      }
      else{
        Serial.println("Problem updating channel. HTTP error code " + String(x));
      }
      
      lastTime = millis();
    
    }
    delay(1000);
    Serial.println("");
    Serial.println("");
    delay(1000);
  }
}
