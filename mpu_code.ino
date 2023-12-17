#include <Wire.h>
float Yaw, Pitch, Roll; //Declare global variable

void gyro_signal(void){
  Wire.beginTransmission(0x68); //  Start i2c COmmunication with  
  Wire.write(0x1A);
  Wire.write(0x05);
  Wire.endTransmission();
  Wire.beginTransmission(0x68);
  Wire.write(0x1B);
  Wire.write(0x08);
  Wire.endTransmission();
  Wire.beginTransmission(0x68);
  Wire.write(0x43);
  Wire.endTransmission(); 
  Wire.requestFrom(0x68,6);
  
  int16_t GyroX=Wire.read()<<8 | Wire.read(); //Read gyroscope value along the x-axis
  int16_t GyroY=Wire.read()<<8 | Wire.read(); //Read gyroscope value along the y-axis
  int16_t GyroZ=Wire.read()<<8 | Wire.read(); //Read gyroscope value along the z-axis
  
  Roll=(float)GyroX/65.5; //convert the measurement unit to degree/sec
  Pitch=(float)GyroY/65.5; //convert the measurement unit to degree/sec
  Yaw=(float)GyroZ/65.5; //convert the measurement unit to degree/sec
  }
  
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600); // open the serial monitor
  Wire.setClock(400000); //set the clock speeed
  Wire.begin();
  delay(250);
  
Wire.beginTransmission(0x68); // start the gyro in power mode
  Wire.write(0x6B);
  Wire.write(0x00);
  Wire.endTransmission();
  }
 

void loop() {
  gyro_signal(); // call the function to read gyro measurement
  
  Serial.print("Yaw  = ");
  Serial.print(Yaw); // print the Yaw
  
  Serial.print("  Pitch  = ");
  Serial.print(Pitch); //print the pitch
  
  Serial.print("  Roll  = ");
  Serial.println(Roll); //print the roll
  
  delay(500);

}
