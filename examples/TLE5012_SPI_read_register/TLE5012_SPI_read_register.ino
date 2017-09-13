#include <SPI.h>

#define CS1 4 //P0.1 for CS1 Boot Kit 1100
#define SPEED 500000
#define DELAYuS 100
#define DUMMY 0xFFFF

int16_t command; 
int16_t value_X;
int16_t value_Y;
int16_t vector;
uint16_t angle;
int16_t Status;
int16_t safety;

void setup() {
  pinMode(CS1,OUTPUT);
  SPI.begin();
  Serial.begin(9600);
  while(!Serial);
  digitalWrite(CS1,HIGH);

 }

void loop() {
  

command=0x8101;        // read X raw
value_X = read16bitFromsensor(command); 

command=0x8111;        // read Y raw
value_Y = read16bitFromsensor(command);

command=0xC8001;        // read Status
Status = read16bitFromsensor(command);

command=0x8141;        // read Vectorlength
vector = read16bitFromsensor(command);
vector<<=1;            // remove bit[16]
vector >>=1;           // unsigned 15-Bit value

command=0x8021;       // read angle
angle = read16bitFromsensor(command);
angle <<=1;           // remove bit[16]
angle >>=1;           // unsigned 15-Bit value

 
 Serial.print("X: "); 
 Serial.print(value_X);
 Serial.print("\t");
 Serial.print("Y: "); 
 Serial.print(value_Y);
 Serial.print("\t");
 Serial.print("Vectorlength: ");
 Serial.print(vector*64); // scaled to 16bit
 Serial.print("\t");
 Serial.print("Status: ");
 Serial.print(Status, HEX);
 Serial.print("\t");
 Serial.print("Winkel: ");
 Serial.println(angle*360.0/32768.0);
}



uint16_t read16bitFromsensor(int16_t command)
{
uint16_t readreg=0;
digitalWrite(CS1,LOW);
delayMicroseconds(DELAYuS);
SPI.beginTransaction(SPISettings(SPEED,MSBFIRST,SPI_MODE1));
SPI.transfer16(command);
readreg=SPI.transfer16(0xFFFF);
safety=SPI.transfer16(0xFFFF);
SPI.endTransaction();  
delayMicroseconds(DELAYuS);
digitalWrite(CS1,HIGH);

return readreg;
}




