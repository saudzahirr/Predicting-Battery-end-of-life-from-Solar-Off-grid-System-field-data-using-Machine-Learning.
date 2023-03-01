#include <WiFi.h>
#include "ThingSpeak.h"

int sensor_pin = 26;
int A26 = 26;
int value ;

const int S0 = 8;
const int S1 = 9;
const int S2 = 10;
const int S3 = 11;
const int EN = 12;
const float adc = (3.3/4095.0);
const float G = 47/9.8;
const float R = 12;
const int N = 16;


int S = 66; // Sensitivity
int adc_val = 0;
int Vo = 2500;
double Vadc = 0;

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

  pinMode(S0, OUTPUT);
  pinMode(S1, OUTPUT);
  pinMode(S2, OUTPUT);
  pinMode(S3, OUTPUT);
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

    // Get a new temperature reading
    value = analogRead(sensor_pin);
    value = map(value, 550,0,0,100);
    Serial.print("Moisture : ");
    Serial.print(value);
    Serial.println("%");

    double voltage = 0;
    double current = 0;
    double V = 0;
    double I = 0;

    adc_val = analogRead(A26);
    Vadc = (adc_val / 1024.0) * 5000;
    I = ((Vadc - Vo) / S);
    
    for (int i = 0; i < N; i++) {
      digitalWrite(S0, i & 0b0001);
      digitalWrite(S1, i & 0b0010);
      digitalWrite(S2, i & 0b0100);
      digitalWrite(S3, i & 0b1000);
      digitalWrite(EN, LOW);  
      delay(1000);
      
      voltage = analogRead(A0)*adc*G;
      V += voltage;
      
      Serial.print("B");
      Serial.print(i+1);
      Serial.print(" Votage: ");
      Serial.println(voltage, 4);
    }
    delay(1000);
    // current = V/R;
    Serial.print("BAT Current: ");
    Serial.println(I, 4);
    // Serial.println(current);
    Serial.println("");
    Serial.println("");
    delay(1000);
    
    //uncomment if you want to get temperature in Fahrenheit
    /*temperatureF = 1.8 * bme.readTemperature() + 32;
    Serial.print("Temperature (ºC): ");
    Serial.println(temperatureF);*/
    
    
    // Write to ThingSpeak. There are up to 8 fields in a channel, allowing you to store up to 8 different
    // pieces of information in a channel.  Here, we write to field 1.
    int x = ThingSpeak.writeField(myChannelNumber, 1, value, myWriteAPIKey);
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
