 #include <Wire.h> 
   
float  Roll,Pitch, Yaw; //Declare global variable
float  CalibrationYaw, CalibrationPitch,  CalibrationRoll; //Calibration variables
int CalibrationNumber;

void gyro_signal(void) {
  // Gyroscope register configuration
  Wire.beginTransmission(0x68);
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

  // Request data from the gyroscope
  Wire.requestFrom(0x68, 6);
  
  // Read gyroscope data
  int16_t GyroX = Wire.read() << 8 | Wire.read();
  int16_t GyroY = Wire.read() << 8 | Wire.read();
  int16_t GyroZ = Wire.read() << 8 | Wire.read();
  
  // Convert raw data to angles
  Roll = (float)GyroX / 65.5;
  Pitch = (float)GyroY / 65.5;
  Yaw = (float)GyroZ / 65.5;
} 
void setup() {
  Serial.begin(9600);
  Wire.setClock(400000);
  Wire.begin();
  delay(250);

  // Initialize gyroscope
  Wire.beginTransmission(0x68);
  Wire.write(0x6B);
  Wire.write(0x00);
  Wire.endTransmission();

  // Calibration loop
  for (CalibrationNumber = 0; CalibrationNumber < 2000; CalibrationNumber++) {
    gyro_signal();
    CalibrationYaw += Yaw;
    CalibrationPitch += Pitch;
    CalibrationRoll += Roll;
    
    delay(1);
  }

  // Calculate average calibration values
  CalibrationYaw /= 2000;
  CalibrationRoll /= 2000;
  CalibrationPitch /= 2000;
}
void loop() {
  gyro_signal();

  // Compensate for calibration values
  Yaw -= CalibrationYaw;
  Pitch -= CalibrationPitch;
  Roll -= CalibrationRoll;

  // Print angles to Serial Monitor
  //Serial.print("Yaw = ");
  //Serial.println(Yaw);
  
  //Serial.print(" Pitch  = ");
  //Serial.println(Pitch);
  
  Serial.print(" Roll  = ");
  Serial.println(Roll);

  delay(1000);  // Wait for a second
}
