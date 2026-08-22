void setup() {
  Serial.begin(9600);
}

void loop() {
  Serial.println("Reference:1.65");
  Serial.print("Channel1:");
  Serial.println(analogRead(32)*3.3/4095);  
  Serial.print("Channel2:");
  Serial.println(analogRead(33)*3.3/4095);  
  Serial.print("Channel3:");
  Serial.println(analogRead(34)*3.3/4095);  
  Serial.print("Channel4:");
  Serial.println(analogRead(35)*3.3/4095);  
}
