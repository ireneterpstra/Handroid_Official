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

double r = 0; // roll
double p = 0; // pitch
double y = 0; // yaw / spin

double zeroBX = 0;
double tempBX = 0;
double BX;
double BY;
double BZ;

int BNO055_SAMPLERATE_DELAY_MS = 100;

//Adafruit_BNO055 bno = Adafruit_BNO055(55, (0x29));


float calculateResistance(int pinout){
  float angle = 0;
  int flexADC = analogRead(pinout);
  float flexV = flexADC * VCC / 1023.0;
  float flexR = R_DIV * (VCC / flexV - 1.0);
  // Use the calculated resistance to estimate the sensor's bend angle:
  angle = map(flexR, STRAIGHT_RESISTANCE, BEND_RESISTANCE, 0, 90.0);
  return angle;
}

/**************************************************************************/
/*
    Displays some basic information on this sensor from the unified
    sensor API sensor_t type (see Adafruit_Sensor for more information)
*/
/**************************************************************************/
//void displaySensorDetails(void)
//{
//  sensor_t sensor;
//  bno.getSensor(&sensor);
//  Serial.println(F("------------------------------------"));
//  Serial.print  (F("Sensor:       ")); Serial.println(sensor.name);
//  Serial.print  (F("Driver Ver:   ")); Serial.println(sensor.version);
//  Serial.print  (F("Unique ID:    ")); Serial.println(sensor.sensor_id);
//  Serial.print  (F("Max Value:    ")); Serial.println(sensor.max_value);
//  Serial.print  (F("Min Value:    ")); Serial.println(sensor.min_value);
//  Serial.print  (F("Resolution:   ")); Serial.println(sensor.resolution);
//  Serial.println(F("------------------------------------"));
//  Serial.println();
//  delay(500);
//}

/**************************************************************************/
/*
    Display sensor calibration status
*/
/**************************************************************************/
//void displayCalStatus(void)
//{
//  /* Get the four calibration values (0..3) Any sensor data reporting 0 should be ignored, 3 means 'fully calibrated" */
//  uint8_t system, gyro, accel, mag;
//  system = gyro = accel = mag = 0;
//  bno.getCalibration(&system, &gyro, &accel, &mag);
//
//  /* The data should be ignored until the system calibration is > 0 */
//  Serial.print(F("\t"));
//  if (!system)
//  {
//    Serial.print(F("! "));
//  }
//}
//
//void updateSensorData(){
//  sensors_event_t event;
//  bno.getEvent(&event);
//
//  angle1 = calculateResistance(FLEX_PIN1);
//  angle2 = calculateResistance(FLEX_PIN2);
//  
//  if (angle2 > 50){
//    zeroBX = event.orientation.x;
//  }
//  if ((event.orientation.x - zeroBX) > 0){
//    tempBX = event.orientation.x - zeroBX;
//  } else {
//    tempBX = 360 + (event.orientation.x - zeroBX);
//  }
//  
//  if(tempBX <= 180){
//    BX = tempBX;
//  } else {
//    BX = tempBX - 360;
//  }
//  
//  BZ = event.orientation.z;
//  BY = event.orientation.y;
//}

//---------------------------------------------------------------------------------------------------------
//  Setup
//---------------------------------------------------------------------------------------------------------
void setup(void)
{
  Serial.begin(9600);
  Serial.println(F("Orientation Sensor Test")); Serial.println();

  /* Initialise the sensor */
//  if(!bno.begin())
//  {
//    Serial.print(F("Ooops, no BNO055 detected ... Check your wiring or I2C ADDR!"));
//    while(1);
//  }
//  delay(500);
//
//  /* Display some basic information on this sensor */
//  displaySensorDetails();
//  bno.setExtCrystalUse(true);
  
  pinMode(6, OUTPUT);
  pinMode(FLEX_PIN1, INPUT);
  pinMode(FLEX_PIN2, INPUT);

}

//---------------------------------------------------------------------------------------------------------
//  Loop
//---------------------------------------------------------------------------------------------------------

void loop(void) {
//  Serial.println(F("Loop"));
//  sensors_event_t event;
////  bno.getEvent(&event);
////  BX = event.orientation.x;
////  BZ = event.orientation.z;
////  BY = event.orientation.y;
//  
//  updateSensorData();
//
  sensors_event_t event;
//  bno.getEvent(&event);

  angle1 = calculateResistance(FLEX_PIN1);
  angle2 = calculateResistance(FLEX_PIN2);


  if (angle1 > 20 || angle2 > 20){ //Pitch
    analogWrite(6, 153);
    Serial.println("Angle 1: " + String(angle1) + " Angle 2: " + String(angle2) + "  ");
//    Serial.print("Pitch: " + String(BZ) + "  ");
//    Serial.print("Yaw: " + String(BX) + "  ");
//    Serial.println("Roll: " + String(BY) + " : vibrator on");
  } 
//  if ((BZ - BY) < 10 && (BZ - BY > -10)){ //Pitch
//    analogWrite(6, 153);
//    //Serial.print("Angle 1: " + String(angle1) + " Angle 2: " + String(angle2) + "  ");
//    Serial.print("Pitch: " + String(BZ) + "  ");
//    Serial.print("Yaw: " + String(BX) + "  ");
//    Serial.println("Roll: " + String(BY) + " : vibrator on");
//  } 
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
    Serial.println("Angle 1: " + String(angle1) + " Angle 2: " + String(angle2) + "  ");
//    Serial.print("Pitch: " + String(BZ) + "  ");
//    Serial.print("Yaw: " + String(BX) + "  ");
//    Serial.println("Roll: " + String(BY) + " : vibrator off");
  }

}
