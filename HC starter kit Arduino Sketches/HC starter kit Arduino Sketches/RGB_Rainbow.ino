/* FILE:    RGB_Rainbow
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

/* Digital PWM pins used to control the red, green, & blue levels */
#define RED_LED 11
#define GRN_LED 10
#define BLU_LED 9

void setup()
{
}

void loop()
{
  /* Fade in red and fade out blue */
  for(byte i = 0; i < 255; i++)
  {
    analogWrite(RED_LED, i);
    analogWrite(BLU_LED, 255 - i);
    delay(10);
  }

  /* Fade in green and fade out red */
  for(byte i = 0; i < 255; i++)
  {
    analogWrite(GRN_LED, i);
    analogWrite(RED_LED, 255 - i);
    delay(10);
  }

  /* Fade in blue and fade out green */
  for(byte i = 0; i < 255; i++)
  {
    analogWrite(BLU_LED, i);
    analogWrite(GRN_LED, 255 - i);
    delay(10);
  }
}

