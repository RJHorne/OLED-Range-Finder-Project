/* FILE:    Countdown_Timer
   DATE:    19/11/17
   VERSION: 0.1
   AUTHOR:  Andrew Davies

19/11/17 version 0.1: Original version

THIS SOFTWARE IS PROVIDED "AS IS". HOBBY COMPONENTS MAKES NO WARRANTIES, WHETHER
EXPRESS, IMPLIED OR STATUTORY, INCLUDING, BUT NOT LIMITED TO, IMPLIED WARRANTIES OF
MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE, ACCURACY OR LACK OF NEGLIGENCE.
HOBBY COMPONENTS SHALL NOT, IN ANY CIRCUMSTANCES, BE LIABLE FOR ANY DAMAGES,
INCLUDING, BUT NOT LIMITED TO, SPECIAL, INCIDENTAL OR CONSEQUENTIAL DAMAGES FOR ANY
REASON WHATSOEVER.
*/


/* Include the 7 segment display library */
#include "HC7Seg.h"

/* Pins used for push buttons and buzzer */
#define BUT_MIN 14
#define BUT_SEC 15
#define BUT_START 16
#define BUZZER 17

/* Digital pins used to drive each digit and digit segment of your display. */
#define SEG_A   8
#define SEG_B   13
#define SEG_C   3
#define SEG_D   6
#define SEG_E   5
#define SEG_F   9
#define SEG_G   2 
#define SEG_DP  7 
#define DIG_1   4
#define DIG_2   12 
#define DIG_3   11
#define DIG_4   10

/* Creates an instance of the HC7Seg library */
HC7Seg HC7Seg(COM_CATHODE_4DIG, SEG_A, SEG_B, SEG_C, SEG_D, SEG_E, SEG_F, SEG_G, SEG_DP, DIG_1, DIG_2, DIG_3, DIG_4);

/* Variables to hold timer minutes and seconds */
byte Sec = 0;
byte Min = 0;


void setup()
{
  /* Configure the pins used for the push button and buzzer. Although they are normally analogue pins we are 
     using them as digital pins */
  pinMode(BUT_MIN, INPUT_PULLUP);
  pinMode(BUT_SEC, INPUT_PULLUP);
  pinMode(BUT_START, INPUT_PULLUP);
  pinMode(BUZZER, OUTPUT);
  digitalWrite(BUZZER, HIGH);

  /* Update the display */
  Update();
}


void loop()
{
  /* Check if increment second button is pressed */
  if(Debounce(BUT_SEC))
  {
    Sec++;                        //Increment the seconds
    
    if(Sec == 60)                 //If seconds get to 60 reset it to 0
      Sec = 0;
    
    Update();                     //Update the display
    
    while(Debounce(BUT_SEC));     //Wait until button is released
  }


  /* Check if increment minute button is pressed */
  if(Debounce(BUT_MIN))
  {
    Min++;                        //Increment the minutes
    if(Min == 100)                //If seconds get to 100 reset it to 0
      Min = 0;
    
    Update();                     //Update the display
    while(Debounce(BUT_MIN));     //Wait until button is released
  }

  
  /* If start button is pressed and a time has been set then start the countdown */
  if(Debounce(BUT_START) && (Min > 0 || Sec > 0))
  {
    do
    {
      delay(1000);                //Wait a second
      if(Sec > 0)                 //If seconds isn't zero then decrement it
        Sec--;
      else                        //If it is at zero then set it to 59 and decrement the minutes
      {
        Sec = 59;
        Min--;
      }
      
      Update();                   //Update the display   
    }while(Min != 0 || Sec !=0);  //Keep counting down until we reach zero minutes and seconds


    for(byte i = 0; i < 5; i++)   //Beep the buzzer a few times
    {
      HC7Seg.clear();
      digitalWrite(BUZZER, LOW);
      delay(500);
      Update();
      digitalWrite(BUZZER, HIGH);
      delay(500);
    }
  }
}


/* Update the seven segment display with the current minutes and seconds */
void Update()
{
  HC7Seg.clear();
  
  if(Min > 9)
    HC7Seg.print7Seg(Min + ((float)Sec / 100), 4, 2);
  else
    HC7Seg.print7Seg(Min + ((float)Sec / 100), 3, 2);
}


/* Get the state of one of the buttons. When button is first pressed its switch contacts may bounce 
  causing false presses so we check it several times just to be sure.  */
boolean Debounce(byte Pin)
{
  boolean button = true;

  for(byte i = 0; i < 200; i++)
    if(digitalRead(Pin))
      button = false;

   return button;
}


