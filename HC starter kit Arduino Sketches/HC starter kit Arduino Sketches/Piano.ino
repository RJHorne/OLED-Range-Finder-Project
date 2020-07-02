/* FILE:    Piano
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

/* Digital pin for speaker output */
#define SPEAKER 5 

/* Digital inputs for the 8 buttons */
#define BUT_C1 6
#define BUT_D 7
#define BUT_E 8
#define BUT_F 9
#define BUT_G 10
#define BUT_A 11
#define BUT_B 12
#define BUT_C2 13

void setup() 
{
  /* Set all push button pins to inputs with a pullup resistor */
  pinMode(BUT_C1, INPUT_PULLUP);
  pinMode(BUT_D, INPUT_PULLUP);
  pinMode(BUT_E, INPUT_PULLUP);
  pinMode(BUT_F, INPUT_PULLUP);
  pinMode(BUT_G, INPUT_PULLUP);
  pinMode(BUT_A, INPUT_PULLUP);
  pinMode(BUT_B, INPUT_PULLUP);
  pinMode(BUT_C2, INPUT_PULLUP);
}

void loop() 
{
  /* Check each button and if one is pressed play the corresponding note */
  if(!digitalRead(BUT_C1))
    tone(SPEAKER, 262, 15);
  if(!digitalRead(BUT_D))
    tone(SPEAKER, 294, 15);
  if(!digitalRead(BUT_E))
    tone(SPEAKER, 330, 15);
  if(!digitalRead(BUT_F))
    tone(SPEAKER, 349, 15);
  if(!digitalRead(BUT_G))
    tone(SPEAKER, 392, 15);
  if(!digitalRead(BUT_A))
    tone(SPEAKER, 440, 15);
  if(!digitalRead(BUT_B))
    tone(SPEAKER, 494, 15);
  if(!digitalRead(BUT_C2))
    tone(SPEAKER, 523, 15);
}
