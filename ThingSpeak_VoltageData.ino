#include <WiFi.h>
#include "ThingSpeak.h"

int VOut = 34;

float voltage = 0;
float current = 0;
float V = 0;
float I = 0;


const float adc = (3.3/4095.0);
const float G = 47/9.9;
const float R = 12;
const int N = 4;   // Number of Batteries (max 8). 



const char* ssid = "Saud PC";   // your network SSID (name) 
const char* password = "12345678";   // your network password

WiFiClient  client;

unsigned long myChannelNumber = 1;
const char * myWriteAPIKey = "NQQO3JD4G74YAA5E";

// Timer variables
unsigned long lastTime = 0;
unsigned long timerDelay = 3000;


void setup() {
  Serial.begin(115200);  //Initialize serial
  Serial.println("Starting...");
  delay(2000);

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
      Serial.println("\nConnected.");
    }

    // Get a new temperature reading
    voltage = analogRead(VOut)*adc*G;
    // voltage = map(voltage, 550,0,0,100);

    // ThingSpeak.setField(i+1, voltage);      
    Serial.print(" Votage: ");
    Serial.println(voltage);
    delay(3000);
    
    
    // Write to ThingSpeak. There are up to 8 fields in a channel, allowing you to store up to 8 different
    // pieces of information in a channel.  Here, we write to field 1.
    int x = ThingSpeak.writeField(myChannelNumber, 1, voltage, myWriteAPIKey);
    //uncomment if you want to get temperature in Fahrenheit
    //int x = ThingSpeak.writeField(myChannelNumber, 1, temperatureF, myWriteAPIKey);

    if(x == 200){
      Serial.println("Channel update successful.");
    }
    else{
      Serial.println("Problem updating channel. HTTP error code " + String(x));
    }
    lastTime = millis();
  }
}
