/* FILE:    IR_Decoder
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

#define RECEIVER_PIN 13 //IR receiver digital input pin.

/* Hold the address and command information for a received IR code. */
byte Address, InvAddress, Command, InvCommand;

void setup() 
{
  Serial.begin(9600); //Initialise the serial port
  pinMode(RECEIVER_PIN, INPUT); //Set the receiver pin to an input
}

void loop() 
{
  /* Check if a button has been pressed */
  if(CheckStartPulse())
  {
    Address = GetData();    //Get The buttons address.
    InvAddress = GetData(); //Get the inverse of the address.
    Command = GetData();    //Get the command code.
    InvCommand = GetData();  //Get the inverse of the command code.
  

    /* Output the results to the serial port */
    Serial.print("Address: 0x");
    Serial.print(Address, HEX);
    Serial.print(" Command: 0x");
    Serial.print(Command, HEX);
    Serial.print(" ");
    if((Address + InvAddress) - (Command + InvCommand)) //Should be equal to zero !
      Serial.print("ERROR!");

    Serial.println("");
  }
}

/* Checks for a 9ms pulse followed by a 4.5ms space */
boolean CheckStartPulse(void)
{
  unsigned long StartTime, EndTime;
  
  if(digitalRead(RECEIVER_PIN) == LOW)
  {
    StartTime = millis();
    EndTime = StartTime;

    /* Check for pulses */
    while((EndTime - StartTime) <= 30 && digitalRead(RECEIVER_PIN) == LOW)
      EndTime = millis();

    /* If pulse is valid check for space */
    if((EndTime - StartTime) >= 8 && (EndTime - StartTime) <= 10)
      while((EndTime - StartTime) <= 30 && digitalRead(RECEIVER_PIN) == HIGH)
        EndTime = millis();

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

