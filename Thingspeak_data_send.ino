s#include <WiFi.h>
#include "ThingSpeak.h"

int sensor_pin = 26;
int value ;

const char* ssid = "Saud PC";   // your network SSID (name) 
const char* password = "12345678";   // your network password

WiFiClient  client;

unsigned long myChannelNumber = 1;
const char * myWriteAPIKey = "NQQO3JD4G74YAA5E";

// Timer variables
unsigned long lastTime = 0;
unsigned long timerDelay = 3000;

// Variable to hold temperature readings

//uncomment if you want to get temperature in Fahrenheit
//float temperatureF;

// Create a sensor object
//Adafruit_BME280 bme; //BME280 connect to ESP32 I2C (GPIO 21 = SDA, GPIO 22 = SCL)

//void initBME(){
//  if (!bme.begin(0x76)) {
//    Serial.println("Could not find a valid BME280 sensor, check wiring!");
//    while (1);
//  }
//}

void setup() {
  Serial.begin(115200);  //Initialize serial
  //initBME();
  //Serial.begin(9600);
  Serial.println("Reading");
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
    value= analogRead(sensor_pin);
    value = map(value,550,0,0,100);
    Serial.print("Moisture : ");
    Serial.print(value);
    Serial.println("%");
    
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
