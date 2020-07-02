/* FILE:    Temperature_Controlled_Fan
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

#define TOO_HOT 24        //Maximum temperature in Centigrade

#define LM35_PIN   A0     //Temperature sensor pin
#define MOTOR_PIN 9       //Digital motor pin

void setup() 
{
  /* Set the analogue reference used by the ADC inputs to the internal 1.1V reference */
  analogReference(INTERNAL);
}


void loop() 
{
  /* Read the current temperature from the temperature sensor */
  float Temperature = analogRead(LM35_PIN) / 9.31;

  if(Temperature >= TOO_HOT)        //If the temperature is too hot then turn the fan on.
    digitalWrite(MOTOR_PIN, HIGH);
  else                              //Else turn it off
    digitalWrite(MOTOR_PIN, LOW);
}
