#include <SPI.h>
#include <SD.h>

unsigned long prev;
unsigned long start;
const unsigned long interval = 500;
const unsigned long limit = 2000000/interval;
int CS_PIN = 5;

struct Sample{
  int count;
  unsigned long time;
  int in1;
  int in2;
  int in3;
  int in4;
};

Sample* samples = nullptr;


void setup() {
  Serial.begin(9600);
  delay(5000);
  Serial.println("Initializing SD Card");
  SPI.begin(18, 19, 23, 5);
  if(!SD.begin(CS_PIN, SPI, 1000000)){
    Serial.println("SD initialization failed.");
     while(true);
  }
  for(int sampleCount = 1; sampleCount<=10; sampleCount++){
    String grips[] = {"A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L", "M", "N"};
    for(String s: grips){
      samples = new Sample[limit];
      Serial.println("Commencing data collection for " + s + String(sampleCount) + " grip in 3");
      delay(1000);
      Serial.println("2");
      delay(1000);
      Serial.println("1");
      delay(1000);
      Serial.println("RECORDING...");
      
      start = micros();
      prev = start;
      int count = 0;
      while(count<limit){
        unsigned long curr = micros();
        if(curr-prev>=interval){
          prev+=interval;
          samples[count].count = count;      
          samples[count].time = curr-start; 
          samples[count].in1 = analogRead(32);
          samples[count].in2 = analogRead(33);
          samples[count].in3 = analogRead(34);
          samples[count].in4 = analogRead(35);
          count++;
        }
      }
      Serial.println("Writing Data to SD Card...");
      File dataFile = SD.open("/"+s+String(sampleCount)+".csv", FILE_WRITE);
      if(dataFile){
        for(int i = 0; i<limit; i++){
          dataFile.print(samples[i].count);     dataFile.print(",");
          dataFile.print(samples[i].time);      dataFile.print(",");
          dataFile.print(samples[i].in1*3.3/4095);       dataFile.print(",");
          dataFile.print(samples[i].in2*3.3/4095);       dataFile.print(",");
          dataFile.print(samples[i].in3*3.3/4095);       dataFile.print(",");
          dataFile.println(samples[i].in4*3.3/4095);     
        }
        dataFile.close(); 
        Serial.println("Data successfully written to SD card!");
      }
      else {
          Serial.println("Error opening data.csv for writing!");
      }
      delete[] samples;
    }
  }
}

void loop() {

}
