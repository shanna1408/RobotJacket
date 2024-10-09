#include <Adafruit_MPU6050.h>
#include <Wire.h>
#include <Adafruit_Sensor.h>


#define TCAADDR 0x70

Adafruit_MPU6050 mpu1;
Adafruit_MPU6050 mpu2;
Adafruit_MPU6050 mpu3;

Adafruit_Sensor *mpu_temp1, *mpu_accel1, *mpu_gyro1, *mpu_temp2, *mpu_accel2, *mpu_gyro2, *mpu_temp3, *mpu_accel3, *mpu_gyro3;
unsigned long Sensor[2] = {0,0};

// set up multiplexer
void tcaselect(uint8_t i) {
  if (i > 7) return;
  Wire.beginTransmission(TCAADDR);
  Wire.write(1 << i);
  Wire.endTransmission();
}

void setup(void) {
  Serial.begin(9600);
  while (!Serial)
    delay(10);

  //----------------------------- Sensor 1 initialize
  Wire.begin();                                                                                                                                                                                                                                                                 

  tcaselect(1); // select port on mux
  if (!mpu1.begin()) {
    Serial.println("Failed to find MPU6050 1 chip"); // <-------------- fails here it isn't able to initialize or read the sensor
    while (1) {
      delay(10);
    }
  }

  Serial.println("MPU6050 1 Found!");
  mpu_temp1 = mpu1.getTemperatureSensor();
  mpu_accel1 = mpu1.getAccelerometerSensor();
  mpu_gyro1 = mpu1.getGyroSensor();

  //------------------------------ Sensor 2 initialize
  tcaselect(0); // select port on mux
  if (!mpu2.begin()) {
    Serial.println("Failed to find MPU6050 2 chip");
    while (1) {
      delay(10);
    }
  } 

  Serial.print("MPU6050 2 Found!");
  mpu_temp2 = mpu2.getTemperatureSensor();
  mpu_accel2 = mpu2.getAccelerometerSensor();
  mpu_gyro2 = mpu2.getGyroSensor();

  //------------------------------ Sensor 3 initialize and text
  tcaselect(7); // select port on mux
  if (!mpu3.begin()) {
    Serial.println("Failed to find MPU6050 3 chip");
    while (1) {
      delay(10);
    }

  }

  Serial.println("MPU6050 3 Found!");
  mpu_temp3 = mpu3.getTemperatureSensor();
  mpu_accel3 = mpu3.getAccelerometerSensor();
  mpu_gyro3 = mpu3.getGyroSensor();
}

void loop() {
  //  /* Get a new normalized sensor event MPU 1 */
  //>------------------------------------ Sensor 1
  tcaselect(1);
  sensors_event_t accel1;
  sensors_event_t gyro1;
  sensors_event_t temp1;
  mpu_temp1->getEvent(&temp1);
  mpu_accel1->getEvent(&accel1);
  mpu_gyro1->getEvent(&gyro1);

  // Calculate and print magnitude
  double mag1 = sqrt(sq(gyro1.gyro.x)+sq(gyro1.gyro.y)+sq(gyro1.gyro.z));
  if (mag1>8){
    mag1 = 8;
  }
  int intVal1 = mag1*100;

  Serial.print(0); 
  Serial.print(" "); 
  Serial.println(intVal1);

  //>------------------------------------ Sensor 2
  tcaselect(0);
  sensors_event_t accel2;
  sensors_event_t gyro2;
  sensors_event_t temp2;
  mpu_temp1->getEvent(&temp2);
  mpu_accel1->getEvent(&accel2);
  mpu_gyro1->getEvent(&gyro2);

  // Calculate and print magnitude
  double mag2 = sqrt(sq(gyro2.gyro.x)+sq(gyro2.gyro.y)+sq(gyro2.gyro.z));
  if (mag2>8){
    mag2 = 8;
  } 
  int intVal2 = mag2*100;

  Serial.print(1); 
  Serial.print(" "); 
  Serial.println(intVal2);

  //>------------------------------------ Sensor 3
  tcaselect(7);
  sensors_event_t accel3;
  sensors_event_t gyro3;
  sensors_event_t temp3;
  mpu_temp1->getEvent(&temp3);
  mpu_accel1->getEvent(&accel3);
  mpu_gyro1->getEvent(&gyro3);

  // Calculate and print magnitude
  double mag3 = sqrt(sq(gyro3.gyro.x)+sq(gyro3.gyro.y)+sq(gyro3.gyro.z));
  if (mag3>8){
    mag3 = 8;
  }
  int intVal3 = mag3*100;
  
  Serial.print(2); 
  Serial.print(" "); 
  Serial.println(intVal3);

  delay(100);

}

