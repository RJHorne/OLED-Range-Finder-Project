/* Include the 7 segment display library */
#include "HC7Seg.h"

/* Pins used for push button and buzzer */
#define BUZZER_PIN A0
#define BUTTON_PIN A1

#define BUZZER_ON LOW
#define BUZZER_OFF HIGH

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

void setup() 
{
  /* Configure the pins used for the push button and buzzer. Although they are normally analogue pins we are 
     using them as digital pins */
  pinMode(BUZZER_PIN, OUTPUT);
  digitalWrite(BUZZER_PIN, BUZZER_OFF);
  pinMode(BUTTON_PIN, INPUT_PULLUP);
}


void loop() 
{
  unsigned int ReactionStartTime, ReactionTime; 
  
  /* Generate a random wait time between 1 and 10 seconds */
  unsigned int WaitTime = random(1000, 10000);
  
  /* Scroll the get ready message */
  GetReadyMessage();

  /* Wait for a random amount of time */
  delay(WaitTime);

  /* Turn the buzzer on and record the start time */
  digitalWrite(BUZZER_PIN, BUZZER_ON);
  ReactionStartTime = millis();

  /* loop until either the button is pressed or we run out of time */
  do
  {
    /* each time through the loop calculate the amount of time that has passed and display it */
    ReactionTime = millis() - ReactionStartTime;
    HC7Seg.print7Seg((float)ReactionTime / 1000, 4, 3, true);
  }while(digitalRead(BUTTON_PIN) && ReactionTime < 9999);

  /* Button has been pressed or time has run out so turn off the buzzer */
  digitalWrite(BUZZER_PIN, BUZZER_OFF);

  delay(1000);
  
  /* Wait for button to be pressed again before starting a new game */


  while(!digitalRead(BUTTON_PIN));
  while(digitalRead(BUTTON_PIN));
}


/* Scroll a get ready message across the display */
void GetReadyMessage()
{
  for(byte i = 0; i < 20; i++)
  {
    HC7Seg.clear();  
    HC7Seg.print7Seg("GET READY....", i);
    delay(150);
  }
}

