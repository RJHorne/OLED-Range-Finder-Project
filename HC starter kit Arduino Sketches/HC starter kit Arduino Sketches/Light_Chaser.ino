/* FILE:    Light_Chaser
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

#define OFF HIGH //LED OFF state.    
#define ON LOW   //LED ON state. 

#define FIRST_LED 2 //Digital pin number for the first LED
#define LAST_LED 9  //Digital pin number for the last LED


void setup() 
{
  /* Steps through each pin, sets it to an output, and then turns the LED off */
  for(int i = FIRST_LED; i <= LAST_LED; i ++)
  {
    pinMode(i, OUTPUT);
    digitalWrite(i, OFF);
  }
}

void loop() 
{
  /* Step forward though each pin and turn just its LED on */
  for(byte i = FIRST_LED; i <= LAST_LED; i++)
    Set_LED(i);

  /* Step backwards through each pin and turn just its LED on */
  for(byte i = LAST_LED; i >= FIRST_LED; i--)
    Set_LED(i);
}

/* This is the function that turns on just one of the LEDs */
void Set_LED(byte PIN)
{
  /* First turn off all the LEDs */
  for(int i = FIRST_LED; i <= LAST_LED; i ++)
    digitalWrite(i, OFF);

  /* Turn on just the LED we want */
  digitalWrite(PIN, ON);
  delay(30);
}

