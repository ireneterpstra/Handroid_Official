/**************************************************************************/
/*
    Displays some basic information on this sensor from the unified
    sensor API sensor_t type (see Adafruit_Sensor for more information)
*/
/**************************************************************************/
void displaySensorDetails1(void)
{
  sensor_t sensor;
  bno1.getSensor(&sensor);
  Serial.println(F("------------------------------------"));
  Serial.print  (F("Sensor:       ")); Serial.println(sensor.name);
  Serial.print  (F("Driver Ver:   ")); Serial.println(sensor.version);
  Serial.print  (F("Unique ID:    ")); Serial.println(sensor.sensor_id);
  Serial.print  (F("Max Value:    ")); Serial.println(sensor.max_value);
  Serial.print  (F("Min Value:    ")); Serial.println(sensor.min_value);
  Serial.print  (F("Resolution:   ")); Serial.println(sensor.resolution);
  Serial.println(F("------------------------------------"));
  Serial.println();
  delay(500);
}
void displaySensorDetails2(void)
{
  sensor_t sensor;
  bno2.getSensor(&sensor);
  Serial.println(F("------------------------------------"));
  Serial.print  (F("Sensor:       ")); Serial.println(sensor.name);
  Serial.print  (F("Driver Ver:   ")); Serial.println(sensor.version);
  Serial.print  (F("Unique ID:    ")); Serial.println(sensor.sensor_id);
  Serial.print  (F("Max Value:    ")); Serial.println(sensor.max_value);
  Serial.print  (F("Min Value:    ")); Serial.println(sensor.min_value);
  Serial.print  (F("Resolution:   ")); Serial.println(sensor.resolution);
  Serial.println(F("------------------------------------"));
  Serial.println();
  delay(500);
}
//void displaySensorDetails3(void)
//{
//  sensor_t sensor;
//  bno3.getSensor(&sensor);
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
void displayCalStatus1(void)
{
  /* Get the four calibration values (0..3) Any sensor data reporting 0 should be ignored, 3 means 'fully calibrated" */
  uint8_t system, gyro, accel, mag;
  system = gyro = accel = mag = 0;
  bno1.getCalibration(&system, &gyro, &accel, &mag);

  /* The data should be ignored until the system calibration is > 0 */
  Serial.print(F("\t"));
  if (!system)
  {
    Serial.print(F("! "));
  }
}
void displayCalStatus2(void)
{
  /* Get the four calibration values (0..3) Any sensor data reporting 0 should be ignored, 3 means 'fully calibrated" */
  uint8_t system, gyro, accel, mag;
  system = gyro = accel = mag = 0;
  bno2.getCalibration(&system, &gyro, &accel, &mag);

  /* The data should be ignored until the system calibration is > 0 */
  Serial.print(F("\t"));
  if (!system)
  {
    Serial.print(F("! "));
  }
}
//void displayCalStatus3(void)
//{
//  /* Get the four calibration values (0..3) Any sensor data reporting 0 should be ignored, 3 means 'fully calibrated" */
//  uint8_t system, gyro, accel, mag;
//  system = gyro = accel = mag = 0;
//  bno3.getCalibration(&system, &gyro, &accel, &mag);
//
//  /* The data should be ignored until the system calibration is > 0 */
//  Serial.print(F("\t"));
//  if (!system)
//  {
//    Serial.print(F("! "));
//  }
//}

void updateSensorData(){
  sensors_event_t event;
  bno1.getEvent(&event);

  angle1 = calculateResistance(FLEX_PIN1);
  angle2 = calculateResistance(FLEX_PIN2);
  
  if (angle2 > 50){
    zeroBX = event.orientation.x;
  }
  if ((event.orientation.x - zeroBX) > 0){
    tempBX = event.orientation.x - zeroBX;
  } else {
    tempBX = 360 + (event.orientation.x - zeroBX);
  }
  
  if(tempBX <= 180){
    BX = tempBX;
  } else {
    BX = tempBX - 360;
  }
  
  BZ = event.orientation.z;
  BY = event.orientation.y;
}
