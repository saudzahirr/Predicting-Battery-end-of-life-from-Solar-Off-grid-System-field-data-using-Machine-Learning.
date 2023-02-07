const int S0 = 8;
const int S1 = 9;
const int S2 = 10;
const int S3 = 11;
const int EN = 12;
const float adc = (5.0/1023.0);
const float G = 6.0;
const int N = 16;


void setup() {
Serial.begin(9600);
pinMode(S0, OUTPUT);
pinMode(S1, OUTPUT);
pinMode(S2, OUTPUT);
pinMode(S3, OUTPUT);
pinMode(EN, OUTPUT);
}


void loop() {
  float voltage = 0;


for (int i = 0; i < N; i++) {
  digitalWrite(S0, i & 0b0001);
  digitalWrite(S1, i & 0b0010);
  digitalWrite(S2, i & 0b0100);
  digitalWrite(S3, i & 0b1000);
  digitalWrite(EN, LOW);  
  delay(500);

  voltage = analogRead(A0)*adc*G;
  Serial.println(voltage);
  }
}
