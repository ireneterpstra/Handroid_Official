/*
 * Irene Terpstra
 * 7/21/2018 
 * 3 Vibrators controled by IMU
 */
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BNO055.h>
#include <utility/imumaths.h>
#include <SPI.h>
#include <SD.h>
#include <Event.h>
#include <Timer.h>
#include <math.h>

#define I2CADDR 0x70

const int chipSelect = 4;

// Measure the voltage at 5V and the actual resistance of your
// 47k resistor, and enter them below:
const float VCC = 4.98; // Measured voltage of Ardunio 5V line
const float R_DIV = 47500.0; // Measured resistance of 47k resistor
const float STRAIGHT_RESISTANCE = 37300.0; // resistance when straight
const float BEND_RESISTANCE = 90000.0; // resistance at 90 deg

const int FLEX_PIN1 = A0; // Pin connected to voltage divider output
const int FLEX_PIN2 = A1; // Pin connected to voltage divider output

int minBend = -20;
int maxBend = 95;
float angle1 = 0;
float angle2 = 0;

//double r = 0; // roll
//double p = 0; // pitch
//double y = 0; // yaw / spin

double x1;
double y1;
double z1;

double zeroBX = 0;
double tempBX = 0;
double BX;
double BY;
double BZ;

int BNO055_SAMPLERATE_DELAY_MS = 100;

//Adafruit_BNO055 bno = Adafruit_BNO055(56, (0x29));
Adafruit_BNO055 bno1 = Adafruit_BNO055(55, (0x28));
Adafruit_BNO055 bno2 = Adafruit_BNO055(56, (0x29));
//Adafruit_BNO055 bno3 = Adafruit_BNO055(55, (0x28));


float calculateResistance(int pinout){
  float angle = 0;
  int flexADC = analogRead(pinout);
  float flexV = flexADC * VCC / 1023.0;
  float flexR = R_DIV * (VCC / flexV - 1.0);
  // Use the calculated resistance to estimate the sensor's bend angle:
  angle = map(flexR, STRAIGHT_RESISTANCE, BEND_RESISTANCE, 0, 90.0);
  return angle;
}

void i2cselect(uint8_t i) {
  if (i > 7) return;
 
  Wire.beginTransmission(I2CADDR);
  Wire.write(1 << i);
  Wire.endTransmission();  
}

//---------------------------------------------------------------------------------------------------------
//  Setup
//---------------------------------------------------------------------------------------------------------
void setup(void)
{
  Serial.begin(9600);
  Serial.println("Orientation Sensor Test"); Serial.println();

  /* Initialise the sensor */
  i2cselect(0);
  if(!bno1.begin())
  {
    Serial.print(F("Ooops, no BNO055 1 detected ... Check your wiring or I2C ADDR!"));
    while(1);
  }
  delay(500);
  i2cselect(1);
  if(!bno2.begin())
  {
    Serial.print(F("Ooops, no BNO055 2 detected ... Check your wiring or I2C ADDR!"));
    while(1);
  }
  delay(500);
//  i2cselect(2);
//  if(!bno3.begin())
//  {
//    Serial.print(F("Ooops, no BNO055 3 detected ... Check your wiring or I2C ADDR!"));
//    while(1);
//  }
//  delay(500);

  /* Display some basic information on this sensor */
  i2cselect(0);
  displaySensorDetails1();
  bno1.setExtCrystalUse(true);
  i2cselect(1);
  displaySensorDetails2();
  bno2.setExtCrystalUse(true);
//  i2cselect(2);
//  displaySensorDetails3();
//  bno3.setExtCrystalUse(true);
  
  pinMode(6, OUTPUT);
  pinMode(FLEX_PIN1, INPUT);
  pinMode(FLEX_PIN2, INPUT);

}
//---------------------------------------------------------------------------------------------------------
//  Loop
//---------------------------------------------------------------------------------------------------------

void loop(void) {
//  Serial.println(F("Loop"));
  sensors_event_t event;  
  i2cselect(0);
  updateSensorData();

  calcElbowPos(10);

  // vibration on : analogWrite(6, 153);
  // vibration off : analogWrite(6, 0);
  Serial.print("yaw : " + String(BX));
  Serial.print(" pitch : " + String(BZ));
  Serial.print(" roll : " + String(BY));
  Serial.print(" X1 : " + String(x1));
  Serial.print(" Y1 : " + String(y1));
  Serial.println(" Z1 : " + String(z1));
  


}

