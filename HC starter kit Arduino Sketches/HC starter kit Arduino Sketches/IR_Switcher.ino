/* FILE:    IR_Switcher
   DATE:    27/09/16
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

#define BUT1_LED 8  //Digital pin for the LED controlled by RC button 1
#define BUT2_LED 9  //Digital pin for the LED controlled by RC button 2
#define BUT3_LED 10 //Digital pin for the LED controlled by RC button 3
#define BUT4_LED 11 //Digital pin for the LED controlled by RC button 4

#define RECEIVER_PIN 2 //IR receiver digital input pin.

/* Hold the address and command information for a received IR code. */
byte Address, InvAddress, Command, InvCommand;

void setup() 
{
  pinMode(RECEIVER_PIN, INPUT); //Set the receiver pin to an input

  /* Set all the LED pins to outputs and high (off) */
  pinMode(BUT1_LED, OUTPUT);
  pinMode(BUT2_LED, OUTPUT);
  pinMode(BUT3_LED, OUTPUT);
  pinMode(BUT4_LED, OUTPUT);
  digitalWrite(BUT1_LED, HIGH);
  digitalWrite(BUT2_LED, HIGH);
  digitalWrite(BUT3_LED, HIGH);
  digitalWrite(BUT4_LED, HIGH);
}


void loop() 
{
  /* Check if a button has been pressed */
  byte Code = CheckForCode();
  
  if(Code) //If code is not zero then a valid IR code has been received 
  {
    switch(Code)
    {
      case(0x16): //Code for remote control numeric button 1
        digitalWrite(BUT1_LED, !digitalRead(BUT1_LED));
        break;

      case(0x18): //Code for remote control numeric button 2
        digitalWrite(BUT2_LED, !digitalRead(BUT2_LED));
        break;

      case(0x5E): //Code for remote control numeric button 3
        digitalWrite(BUT3_LED, !digitalRead(BUT3_LED));
        break;

      case(0x08): //Code for remote control numeric button 4
        digitalWrite(BUT4_LED, !digitalRead(BUT4_LED));
        break;       
    }
  }
}


/* Check for a valid code. Return 0 if no code is received */
byte CheckForCode(void)
{
  if(CheckStartPulse())
  {
    Address = GetData();    //Get The buttons address.
    InvAddress = GetData(); //Get the inverse of the address.
    Command = GetData();    //Get the command code.
    InvCommand = GetData();  //Get the inverse of the command code
    if(((Address + InvAddress) - (Command + InvCommand)) == 0)
     return Command;
  }
  return 0;
}



/* Checks for start of an IR transmission - 9ms pulse followed by a 4.5ms space */
boolean CheckStartPulse(void)
{
  unsigned long StartTime, EndTime;
  if(digitalRead(RECEIVER_PIN) == LOW)
  {
    StartTime = millis();
    EndTime = StartTime;

    /* Check for pulses */
    while((EndTime - StartTime) <= 30 && digitalRead(RECEIVER_PIN) == LOW)
    {
      EndTime = millis();
    }
    
    /* If pulse is valid check for space */
    if((EndTime - StartTime) >= 8 && (EndTime - StartTime) <= 10)
    {
      while((EndTime - StartTime) <= 30 && digitalRead(RECEIVER_PIN) == HIGH)
      {
        EndTime = millis();
      }
    }
    if((EndTime - StartTime) >= 13 && (EndTime - StartTime) <= 16)
      return true;
  }

  return false;
}


/* Get one bit of data */
byte GetBit(void)
{
  unsigned long StartTime, EndTime;
  while(digitalRead(RECEIVER_PIN) == LOW);

  StartTime = micros();

  while(digitalRead(RECEIVER_PIN) == HIGH);

  EndTime = micros();

  if(EndTime - StartTime > 700)
    return 1;

  return 0;
}

/* Get one byte (8 bits) of data */
byte GetData(void)
{
  byte Data = 0;
  for(byte i = 0; i < 8; i++)
  {
    Data |= (GetBit() << i);
  }
  return Data;
}

