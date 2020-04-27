/*
  band_test
  This test demonstrates the capability to change frequency band
  at runtime for MKR WAN 1300/1310 LoRa module.
*/

#include <MKRWAN.h>

LoRaModem modem;

_lora_band reg_band;

String region;
int idx;
int freq;
int freq_read;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);   //115200
  while (!Serial);
  Serial.println("Welcome to MKRWAN1300/1310 first configuration sketch");
  Serial.println("Register to your favourite LoRa network and we are ready to go!");
  // change this to your regional band (eg. US915, AS923, ...)

  Serial.println("The available regions and bands are these:");
  Serial.println("Region   |  RX freqyency band");
  Serial.println("-----------------------------");
  Serial.println("AS923    |     923200000");
  Serial.println("AU915    |     923300000");
  Serial.println("CN470    |     505300000");
  Serial.println("CN779    |     786000000");
  Serial.println("EU433    |     434665000");
  Serial.println("EU868    |     869525000");
  Serial.println("KR920    |     921900000");
  Serial.println("IN865    |     866550000");
  Serial.println("US915    |     923300000");
  Serial.println("RU864    |     869100000");
}


void loop() {
  Serial.println("Select the desired region:");
  while (!Serial.available());
  region = Serial.readStringUntil('\n');   //.toInt();
  Serial.println(region);

  if (region=="AS923") {
    idx = 0;
    freq = 923200000;
    reg_band = AS923;
  }
  else if (region=="AU915"){
    idx = 1;
    freq = 923300000;
    reg_band = AU915;
  }
  else if (region=="CN470"){
    idx = 2;
    freq = 505300000;
    reg_band = CN470;
  }
  else if (region=="CN779"){
    idx = 3;
    freq = 786000000;
    reg_band = CN779;
  }
  else if (region=="EU433"){
    idx = 4;
    freq = 434665000;
    reg_band = EU433;
  }
  else if (region=="EU868"){
    Serial.println("region=EU868");
    idx = 5;
    freq = 869525000;
    reg_band = EU868;
  }
  else if (region=="IN865"){
    idx = 6;
    freq = 866550000;
    reg_band = IN865;
  }
  else if (region=="KR920"){
    idx = 7;
    freq = 921900000;
    reg_band = KR920;
  }
  else if (region=="US915"){
    Serial.println("region=US915");
    idx = 8;
    freq = 923300000;
    reg_band = US915;
  }
  else if (region=="RU864"){
    idx = 9;
    freq = 869100000;
    reg_band = RU864;
  }
  else {
    idx = 0;
    freq = 0;
    reg_band = EU868;
    Serial.println("Region not valid");
    return;
  }
  
  if (!modem.begin(reg_band)) {   //EU868
    Serial.println("Failed to start module");
    while (1) {}
  };
  freq_read = modem.getrxfreq();
  Serial.print("The frequency of the RX channel is: ");
  Serial.println(freq_read, DEC);
  if (freq_read != freq) {
    Serial.print("Error: region ");
    Serial.print(region);
    Serial.print(" should have frequency ");
    Serial.print(freq, DEC);
    Serial.print(", but it is now set for frequency ");
    Serial.println(freq_read, DEC);
  } else {
    Serial.print("Band of region ");
    Serial.print(region);
    Serial.print(" properly set to frequency ");
    Serial.println(freq_read, DEC);
  }

  delay(1000);

}
