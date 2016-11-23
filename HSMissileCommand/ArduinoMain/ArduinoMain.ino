/************************************************************
 * Arduino Main
 * 
 * @description   This arduino sketch controls the accelerometer, 
 *                and speaker.
 *              
 * @author        Harrison Statham
 */

#include <stdint.h>

const byte gameOverSignal = 2;
const byte newGameSignal  = 3;
const byte missileHit     = 4;
const byte shipCityHit    = 5;

void setup() {

  // Connect to the serial port.
  Serial.begin(9600);


  
  pinMode(13, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:

  digitalWrite(13, HIGH);
}
