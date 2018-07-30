/*
 * Irene Terpstra
 * 7/21/2018 
 * Vibrator controled by IMU
 */
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BNO055.h>
#include <utility/imumaths.h>
#include <SPI.h>
#include <SD.h>
#include <Event.h>
#include <Timer.h>

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
double x2;
double y2;
double z2;

double zeroBX = 0;
double tempBX = 0;
double BX;
double BY;
double BZ;
double zeroBX1 = 0;
double tempBX1 = 0;
double BX1;
double BY1;
double BZ1;

int BNO055_SAMPLERATE_DELAY_MS = 100;

Adafruit_BNO055 bno = Adafruit_BNO055(56, (0x29));
Adafruit_BNO055 bno1 = Adafruit_BNO055(55, (0x28));


float calculateResistance(int pinout){
  float angle = 0;
  int flexADC = analogRead(pinout);
  float flexV = flexADC * VCC / 1023.0;
  float flexR = R_DIV * (VCC / flexV - 1.0);
  // Use the calculated resistance to estimate the sensor's bend angle:
  angle = map(flexR, STRAIGHT_RESISTANCE, BEND_RESISTANCE, 0, 90.0);
  return angle;
}

//---------------------------------------------------------------------------------------------------------
//  Setup
//---------------------------------------------------------------------------------------------------------
void setup(void)
{
  Serial.begin(9600);
  Serial.println(F("Orientation Sensor Test")); Serial.println();

  /* Initialise the sensor */
  if(!bno.begin())
  {
    Serial.print(F("Ooops, no BNO055 detected ... Check your wiring or I2C ADDR!"));
    while(1);
  }
  delay(500);
  if(!bno1.begin())
  {
    Serial.print(F("Ooops, no BNO055 1 detected ... Check your wiring or I2C ADDR!"));
    while(1);
  }
  delay(500);

  /* Display some basic information on this sensor */
  displaySensorDetails();
  bno.setExtCrystalUse(true);
  displaySensorDetails1();
  bno1.setExtCrystalUse(true);
  
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
  
  updateSensorData();
  updateSensorData1();
  calcElbowPos(28);
  calcHandPos(28);

  // vibration on : analogWrite(6, 153);
  // vibration off : analogWrite(6, 0);
  Serial.print("yaw : " + String(BX));
  Serial.print(" pitch : " + String(BZ));
  Serial.print(" roll : " + String(BY));
  Serial.print(" yaw1 : " + String(BX1));
  Serial.print(" pitch1 : " + String(BZ1));
  Serial.print(" roll1 : " + String(BY1));
  Serial.print(" x1 : " + String(x1));
  Serial.print(" y1 : " + String(y1));
  Serial.print(" z1 : " + String(z1));
  Serial.print("   X2 : " + String(x2));
  Serial.print("   Y2 : " + String(y2));
  Serial.println("   Z2 : " + String(z2));

  if ((x2 < 30 && x2 > 25) && (y2 < -5 && y2 > -10) && (z2 < 2 && z2 > -2)){
    analogWrite(6, 153);
  } 
//  else if((BX < 10) || (BX > -10)){ //Yaw
//    analogWrite(6, 153);
//    //Serial.print("Angle 1: " + String(angle1) + " Angle 2: " + String(angle2) + "  ");
//    Serial.print("Pitch: " + String(BZ) + "  ");
//    Serial.print("Yaw: " + String(BX) + "  ");
//    Serial.println("Roll: " + String(BY) + " : vibrator on");  
//  } 
//  else if((BY > 10) || (BY < -10)){ //Roll
//    analogWrite(6, 153);
//    Serial.print("Pitch: " + String(BZ) + "  ");
//    Serial.print("Yaw: " + String(BX) + "  ");
//    Serial.println("Roll: " + String(BY) + " : vibrator on");  
//  } 
  else {
    analogWrite(6, 0);
  }

}

