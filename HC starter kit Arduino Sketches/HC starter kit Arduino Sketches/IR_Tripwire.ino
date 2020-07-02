/* FILE:    IR_Tripwire
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

#define IR_LED_PIN 13
#define IR_SENSOR_PIN 2   
#define SPEAKER_PIN 3 
#define RED_LED_PIN 4
#define BLU_LED_PIN 5

#define ARMED_TIME 10000  //Delay time before the alarm is armed

int ArmedCounter = 0;     //Used to hold the current value for the arm timer
boolean AlarmFlag = false;  //Armed flag, high when alarm has been triggered


void setup() 
{
  /* Configure the digital pins for the speaker, LED's and sensor */
  pinMode(IR_LED_PIN, OUTPUT);           
  digitalWrite(IR_LED_PIN, HIGH);
  pinMode(IR_SENSOR_PIN, INPUT); 
  pinMode(RED_LED_PIN, OUTPUT);
  pinMode(BLU_LED_PIN, OUTPUT);
  digitalWrite(RED_LED_PIN, LOW);
  digitalWrite(BLU_LED_PIN, HIGH);

  /* Sets up an interrupt that automatically runs the alarm() function if the IR 
     sensor pin goes low (triggered) */
  attachInterrupt(digitalPinToInterrupt(IR_SENSOR_PIN), alarm, LOW);
}

void loop() 
{

  if(ArmedCounter < ARMED_TIME) //Check arm time has passed 
  {
    ArmedCounter++;
    if(ArmedCounter == ARMED_TIME) //If so then turn the red LED off
      digitalWrite(RED_LED_PIN, HIGH);
  }

  /* Send an IR pulse from the IR led to the IR receiver */
  Send32KHzPulse(10);
    delayMicroseconds(250);

  /* If alarm has been triggered (AlarmFlag = true) then repeatedly flash the LED's and sound the alarm */
  while(AlarmFlag)
  {
    digitalWrite(RED_LED_PIN, LOW);
    digitalWrite(BLU_LED_PIN, HIGH);
    tone(SPEAKER_PIN, 500);
    delay(300);
    digitalWrite(RED_LED_PIN, HIGH);
    digitalWrite(BLU_LED_PIN, LOW);
    tone(SPEAKER_PIN, 1000);
    delay(300);
  }
}


/* This function is automatically run if the IR receiver pin goes low. It simply sets the AlarmFlag to 
   trigger the if the arm time has elapsed */
void alarm()
{
  if(ArmedCounter == ARMED_TIME)
  AlarmFlag = true;
}


/* Pulses the LED at 38KHz */
void Send32KHzPulse(unsigned int pulses)
{
  while(pulses)
  {
   PORTB &= ~_BV(PB5);
   delayMicroseconds(13);
   PORTB |= _BV(PB5);
   delayMicroseconds(13);
   pulses--; 
  }
}
