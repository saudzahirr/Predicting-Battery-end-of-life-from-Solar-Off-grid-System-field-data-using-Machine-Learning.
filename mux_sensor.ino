const int S0 = 8;
const int S1 = 9;
const int S2 = 10;
const int S3 = 11;
const int EN = 12;
const float adc = (5.0/1023.0);
const float G = 8.0;
const float R = 12;
const int N = 16;


int S = 66; // Sensitivity
int adc_val = 0;
int Vo = 2500;
double Vadc = 0;


void setup() {
Serial.begin(9600);
pinMode(S0, OUTPUT);
pinMode(S1, OUTPUT);
pinMode(S2, OUTPUT);
pinMode(S3, OUTPUT);
pinMode(EN, OUTPUT);
}


void loop() {
  double voltage = 0;
  double current = 0;
  double V = 0;
  double I = 0;

  adc_val = analogRead(A1);
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
}
