/* FILE:    Light_Meter
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


/* Digital pins for the 6 LEDs */
#define GRN1_LED 13
#define GRN2_LED 12
#define YEL1_LED 11
#define YEL2_LED 10
#define RED1_LED 9
#define RED2_LED 8

/* Analogue pin for the light dependant resistor */
#define LDR A0

#define OFF HIGH //LED OFF state.    
#define ON LOW   //LED ON state. 


void setup() 
{
  /* Set all LED pins to outputs */
  pinMode(GRN1_LED, OUTPUT);
  pinMode(GRN2_LED, OUTPUT);
  pinMode(YEL1_LED, OUTPUT);
  pinMode(YEL2_LED, OUTPUT);
  pinMode(RED1_LED, OUTPUT);
  pinMode(RED2_LED, OUTPUT);
}


void loop() 
{
  unsigned int Level;

  /* Get the current light level. The value will be between 0 and 1023 */
  Level = analogRead(LDR);

  /* Turn the LED's on or off depending on the light level */
  if(Level > 146)
    digitalWrite(GRN1_LED, ON);
  else
    digitalWrite(GRN1_LED, OFF);

  if(Level > 293)
    digitalWrite(GRN2_LED, ON);
  else
    digitalWrite(GRN2_LED, OFF);
    
  if(Level > 439)
    digitalWrite(YEL1_LED, ON);
  else
    digitalWrite(YEL1_LED, OFF);

  if(Level > 585)
    digitalWrite(YEL2_LED, ON);
  else
    digitalWrite(YEL2_LED, OFF);

  if(Level > 731)
    digitalWrite(RED1_LED, ON);
  else
    digitalWrite(RED1_LED, OFF);

  if(Level > 877)
    digitalWrite(RED2_LED, ON);
  else
    digitalWrite(RED2_LED, OFF);
}
