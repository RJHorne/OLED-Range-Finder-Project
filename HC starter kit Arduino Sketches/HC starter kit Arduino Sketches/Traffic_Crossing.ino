/* FILE:    Traffic_Crossing
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


/* Digital pins for red, amber, & green traffic LED's */
#define TRAFFIC_RED_LED 5    
#define TRAFFIC_AMB_LED 6    
#define TRAFFIC_GRN_LED 7     

/* Digital pins for pedestrian red (wait) and green (cross) LED's */
#define PEDESTRIAN_RED_LED 8 
#define PEDESTRIAN_GRN_LED 9

/* Digital pin for optional pedestrian button wait LED. This gives a visual acknowledgment that 
   the crossing button has been pressed and a new crossing sequence will start soon */
#define PEDESTRIAN_WAIT_LED 12

/* Digital input pin for crossing button */
#define BTN 13  

/* Digital output pin for buzzer */
#define BUZZER 10

/* Used to specify the state of the LED's/button. Not necessary but makes the code more readable */
#define OFF HIGH       
#define ON LOW
#define BTN_PRESSED LOW


/* Used to store the time left to the next sequence in milliseconds */
unsigned int Timer = 33000;

/* Indicates that the crossing button has been pressed */
boolean Pressed_Flag = false;


void setup() 
{
  /* Set all the LED pins to outputs */
  pinMode(TRAFFIC_RED_LED, OUTPUT);
  pinMode(TRAFFIC_AMB_LED, OUTPUT);
  pinMode(TRAFFIC_GRN_LED, OUTPUT);
  pinMode(PEDESTRIAN_RED_LED, OUTPUT);
  pinMode(PEDESTRIAN_GRN_LED, OUTPUT);
  pinMode(PEDESTRIAN_WAIT_LED, OUTPUT);

  /* Set the crossing button pin to an input */
  pinMode(BTN, INPUT_PULLUP);

  /* Set the buzzer pin to an output */
  pinMode(BUZZER, OUTPUT);

  /* Set the default state of the LED's */ 
  digitalWrite(TRAFFIC_RED_LED, OFF);
  digitalWrite(TRAFFIC_AMB_LED, OFF);
  digitalWrite(TRAFFIC_GRN_LED, ON);
  digitalWrite(PEDESTRIAN_RED_LED, ON);
  digitalWrite(PEDESTRIAN_GRN_LED, OFF);
  digitalWrite(PEDESTRIAN_WAIT_LED, OFF);

  /* Make sure the buzzer is turned off! */
  digitalWrite(BUZZER, OFF);
}


void loop() 
{
  /* Check to see if the crossing button has been pressed but only 
     if a crossing sequence isn't currently in progress */
  if(digitalRead(BTN) == BTN_PRESSED && Timer > 21000)
  {
    /* We may be currently executing a sequence so don't start a new 
       sequence yet, just make a note that the button has been pressed. */
    Pressed_Flag = true;
    digitalWrite(PEDESTRIAN_WAIT_LED, ON);
  }


  /* Check if the crossing button has been pressed and we are not currently 
     executing a sequence */
  if(Pressed_Flag == true && Timer == 33000)
  {
    /* If so then first clear the button pressed flag and reset the timer 
       to start a new sequence */
    Pressed_Flag = false;
    
    Timer = 0;
  }

  /* Update all the LED's depending on the timer */
  Update_LEDs();

  /* Wait 1ms before stepping though the loop again */
  delay(1);
}



void Update_LEDs(void)
{
  /* Used to toggle the flash state every 300ms (used to flash LED's */
  boolean Flash = Timer % 600 > 300;

  /* Used to toggle the buzzer state every 100ms */
  boolean Buzzer = Timer % 200 > 100;

  /* If we are at zero seconds then change traffic light to amber 
     to give stop warning to traffic */
  if(Timer == 0)
  {
    digitalWrite(TRAFFIC_AMB_LED, ON);
    digitalWrite(TRAFFIC_GRN_LED, OFF);
  }

  /* After 3 seconds change traffic light to red to clear traffic */
  if(Timer == 3000)
  {
    digitalWrite(TRAFFIC_RED_LED, ON);
    digitalWrite(TRAFFIC_AMB_LED, OFF);
  }

  /* After 3 seconds pedestrians can cross */
  if(Timer > 6000 && Timer < 13000)
  {
    digitalWrite(PEDESTRIAN_RED_LED, OFF);
    digitalWrite(PEDESTRIAN_GRN_LED, ON);
    digitalWrite(PEDESTRIAN_WAIT_LED, OFF);
    digitalWrite(BUZZER, Buzzer);
  }

  /* After 7 seconds give pedestrians a warning to finish crossing */
  if(Timer > 13000 && Timer < 15000)
  {
    digitalWrite(TRAFFIC_RED_LED, OFF);
    digitalWrite(TRAFFIC_AMB_LED, ON);
    digitalWrite(PEDESTRIAN_GRN_LED, Flash);
    digitalWrite(BUZZER, OFF);
  }

  /* After 2 seconds signal traffic can go if clear */
  if(Timer > 15000 && Timer < 21000)
  {
    digitalWrite(TRAFFIC_AMB_LED, Flash);
    digitalWrite(PEDESTRIAN_GRN_LED, Flash);
  }

  /* After 6 seconds give pedestrians additional time before traffic can start */
  if(Timer > 21000 && Timer < 23000)
  {
    digitalWrite(TRAFFIC_AMB_LED, Flash);
    digitalWrite(PEDESTRIAN_RED_LED, ON);
    digitalWrite(PEDESTRIAN_GRN_LED, OFF);
  }

  /* After 2 seconds traffic may go */
  if(Timer > 23000 && Timer < 33000)
  {
    digitalWrite(TRAFFIC_AMB_LED, OFF);
    digitalWrite(TRAFFIC_GRN_LED, ON);
  }

  /* Increase the timer count by 1. Each tick is 1ms */
  if(Timer < 33000)
    Timer++; 
}



