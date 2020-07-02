/* FILE:    Motor_Speed_Control
   DATE:    16/10/17
   VERSION: 0.1
   AUTHOR:  Andrew Davies

16/10/17 version 0.1: Original version

THIS SOFTWARE IS PROVIDED "AS IS". HOBBY COMPONENTS MAKES NO WARRANTIES, WHETHER
EXPRESS, IMPLIED OR STATUTORY, INCLUDING, BUT NOT LIMITED TO, IMPLIED WARRANTIES OF
MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE, ACCURACY OR LACK OF NEGLIGENCE.
HOBBY COMPONENTS SHALL NOT, IN ANY CIRCUMSTANCES, BE LIABLE FOR ANY DAMAGES,
INCLUDING, BUT NOT LIMITED TO, SPECIAL, INCIDENTAL OR CONSEQUENTIAL DAMAGES FOR ANY
REASON WHATSOEVER.
*/


#define POT_PIN   A0    //Analogue potentiometer pin
#define MOTOR_PIN 9     //Digital PWM motor pin

void setup() 
{
}

void loop() 
{
  //Get the current position of the potentiometer.
  int Speed = analogRead(POT_PIN);

  //Value of pot will be between 0 and 1023 but the analogWrite 
  //function needs a value between 0 and 254 so divide the value by 4.
  Speed = Speed / 4;

  //Update the PWM pin connected to the motor with the new Speed value. 
  analogWrite(MOTOR_PIN, Speed);
}
