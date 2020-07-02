/* IR Codes. Use the IR_Decoder sketch with a remote control to get codes you wish to send */
#define IR_ADDRESS 0xFF
#define IR_CODE1 0x10
#define IR_CODE2 0x20
#define IR_CODE3 0x30
#define IR_CODE4 0x40

#define BUT1 2  //Digital pin for buton 1
#define BUT2 3  //Digital pin for buton 2
#define BUT3 4  //Digital pin for buton 3
#define BUT4 5  //Digital pin for buton 4


void setup() 
{
  pinMode(13, OUTPUT);            //Set the IR LED pin to an output
  digitalWrite(13, HIGH);         //And make sure the LED is off
  pinMode(BUT1, INPUT_PULLUP);    //Configure button 1 digital pin to an input
  pinMode(BUT2, INPUT_PULLUP);    //Configure button 2 digital pin to an input
  pinMode(BUT3, INPUT_PULLUP);    //Configure button 3 digital pin to an input
  pinMode(BUT4, INPUT_PULLUP);    //Configure button 4 digital pin to an input
}


void loop() 
{
  if(!digitalRead(BUT1)) //If button 1 is pressed then send the first IR code
    SendCode(IR_ADDRESS, IR_CODE1);
  if(!digitalRead(BUT2)) //If button 2 is pressed then send the second IR code
    SendCode(IR_ADDRESS, IR_CODE2); 
  if(!digitalRead(BUT3)) //If button 3 is pressed then send the third IR code
    SendCode(IR_ADDRESS, IR_CODE3); 
  if(!digitalRead(BUT4)) //If button 4 is pressed then send the forth IR code
    SendCode(IR_ADDRESS, IR_CODE4);
}


/* Sends a full IR remote code */
void SendCode(byte address, byte command)
{
  Start();            //Send the start pulse
  SendByte(address);  //Send the address 
  SendByte(~address); //Send the inverse of the address for error checking
  SendByte(command);  //Send the command 
  SendByte(~command); //Send the inverse of the command for error checking
  SendBit(true);      //Send one final bit to signify the end of the code
}

/* Used by the SendCode() function above to send one byte (8 bits) of data */
void SendByte(byte data)
{
  for(int i = 0; i < 8; i++)
    SendBit((data >> i) & 1);
}

/* Used by the SendCode() and SendByte() functions above to send one bit of data */
void SendBit(boolean state)
{
  Send32KHzPulse(21);
  if(state)
    delayMicroseconds(1610);
  else
    delayMicroseconds(530);
}

/* Tells the receiver that we are about to send a code by sending a start pulse */
void Start(void)
{
  Send32KHzPulse(338);
  delayMicroseconds(4500);
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

