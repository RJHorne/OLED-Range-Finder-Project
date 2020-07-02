/* FILE:    Thermostat
   DATE:    19/09/16
   VERSION: 0.1
   AUTHOR:  Andrew Davies

19/09/16 version 0.1: Original version

THIS SOFTWARE IS PROVIDED "AS IS". HOBBY COMPONENTS MAKES NO WARRANTIES, WHETHER
EXPRESS, IMPLIED OR STATUTORY, INCLUDING, BUT NOT LIMITED TO, IMPLIED WARRANTIES OF
MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE, ACCURACY OR LACK OF NEGLIGENCE.
HOBBY COMPONENTS SHALL NOT, IN ANY CIRCUMSTANCES, BE LIABLE FOR ANY DAMAGES,
INCLUDING, BUT NOT LIMITED TO, SPECIAL, INCIDENTAL OR CONSEQUENTIAL DAMAGES FOR ANY
REASON WHATSOEVER.
*/

#define TOO_COLD 21 //Minimum temperature in Centigrade
#define TOO_HOT 24  //Maximum temperature in Centigrade

/* Pins for temperature sensor and LED's */
#define LM35 A0
#define BLU_LED 2
#define GRN_LED 3
#define RED_LED 4

void setup() 
{
  /* Set the analogue reference used by the ADC inputs to the internal 1.1V reference */
  analogReference(INTERNAL);

  /* Set the digital pins controlling the LED's to outputs */
  pinMode(BLU_LED, OUTPUT);
  pinMode(GRN_LED, OUTPUT);
  pinMode(RED_LED, OUTPUT);
}

void loop() 
{
  /* Read the current temperature from the temperature sensor */
  float Temperature = analogRead(LM35) / 9.31;

  if(Temperature < TOO_COLD) //If too cold then turn the blue led on
  {
    digitalWrite(BLU_LED, LOW);
    digitalWrite(GRN_LED, HIGH);
    digitalWrite(RED_LED, HIGH);
  }else
  if(Temperature <= TOO_HOT) //If just right then turn the green led on
  {
    digitalWrite(BLU_LED, HIGH);
    digitalWrite(GRN_LED, LOW);
    digitalWrite(RED_LED, HIGH);
  }else
  if(Temperature > TOO_HOT) //If too hot then turn the red led on
  {
    digitalWrite(BLU_LED, HIGH);
    digitalWrite(GRN_LED, HIGH);
    digitalWrite(RED_LED, LOW);
  }
  
  delay(500);
}
