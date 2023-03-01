#include <SD.h>

const int chipSelect = 10; // Chip select pin for SD card

File dataFile; // File object for data file
String header = "Timestamp, Sensor Value"; // CSV file header

void setup() {
  Serial.begin(9600); // Start serial communication at 9600 baud rate

  // Initialize SD card
  pinMode(chipSelect, OUTPUT);
  if (!SD.begin(chipSelect)) {
    Serial.println("SD card initialization failed");
    return;
  }

  // Create new data file
  String filename = "data_" + String(millis()) + ".csv";
  dataFile = SD.open(filename, FILE_WRITE);
  if (dataFile) {
    dataFile.println(header);
    dataFile.close();
    Serial.println("Data file created: " + filename);
  } else {
    Serial.println("Data file creation failed");
  }
}

void loop() {
  int sensorValue = analogRead(A0); // Read sensor value
  String dataLine = String(millis()) + "," + String(sensorValue); // Create CSV data line with timestamp and sensor value

  // Append data line to data file
  if (dataFile) {
    dataFile = SD.open(dataFile.name(), FILE_WRITE);
    if (dataFile) {
      dataFile.println(dataLine);
      dataFile.close();
    } else {
      Serial.println("Data file append failed");
    }
  } else {
    Serial.println("Data file not open");
  }

  delay(1000); // Wait for 1 second
}
