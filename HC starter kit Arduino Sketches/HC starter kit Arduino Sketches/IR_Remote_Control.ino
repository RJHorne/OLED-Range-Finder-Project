/* FILE:    Remote_Control
   DATE:    08/11/17
   VERSION: 0.1
   AUTHOR:  Andrew Davies

08/11/17 version 0.1: Original version

THIS SOFTWARE IS PROVIDED "AS IS". HOBBY COMPONENTS MAKES NO WARRANTIES, WHETHER
EXPRESS, IMPLIED OR STATUTORY, INCLUDING, BUT NOT LIMITED TO, IMPLIED WARRANTIES OF
MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE, ACCURACY OR LACK OF NEGLIGENCE.
HOBBY COMPONENTS SHALL NOT, IN ANY CIRCUMSTANCES, BE LIABLE FOR ANY DAMAGES,
INCLUDING, BUT NOT LIMITED TO, SPECIAL, INCIDENTAL OR CONSEQUENTIAL DAMAGES FOR ANY
REASON WHATSOEVER.
*/


/******************************* KEYPAD ASSIGNMENTS *******************************

 Use the IR_Remote_Decoder to capture the IR adress and command codes for the 
 remote control you wish to emulate. Note that the remote must be compatible with 
 the NEC IR protocol like the one found in your kit. You can then assign the 
 captured codes to the keypdad buttons below:
*/

/* Address of the keypad. Note that this will be the same for all codes on your 
   remote */
#define IR_ADDRESS 0x00

/*      KEYPAD BUTTON      IR CODE */    
#define KEY_1_IR_CODE      0x30     //1
#define KEY_2_IR_CODE      0x18     //2
#define KEY_3_IR_CODE      0x7A     //3
#define KEY_A_IR_CODE      0xE2     //CH+
#define KEY_4_IR_CODE      0x10     //4
#define KEY_5_IR_CODE      0x38     //5
#define KEY_6_IR_CODE      0x5A     //6
#define KEY_B_IR_CODE      0xA2     //CH-
#define KEY_7_IR_CODE      0x42     //7
#define KEY_8_IR_CODE      0x4A     //8
#define KEY_9_IR_CODE      0x52     //9
#define KEY_C_IR_CODE      0xA8     //Vol+
#define KEY_STAR_IR_CODE   0x22     //Prev
#define KEY_0_IR_CODE      0x68     //0
#define KEY_HASH_IR_CODE   0x02     //Next
#define KEY_D_IR_CODE      0xE0     //Vol-

/*********************************************************************************/


/* Row/column values for each key (returned by the GetKey() function) */
#define KEY_1     00
#define KEY_2     01
#define KEY_3     02
#define KEY_A     03
#define KEY_4     10
#define KEY_5     11
#define KEY_6     12
#define KEY_B     13
#define KEY_7     20
#define KEY_8     21
#define KEY_9     22
#define KEY_C     23
#define KEY_STAR  30
#define KEY_0     31
#define KEY_HASH  32
#define KEY_D     33
#define KEY_NONE  255

const byte Rows[] = {9, 8, 7, 6}; //Holds the pin numbers for the 4 keypad rows.
const byte Cols[] = {5, 4, 3, 2}; //Holds the pin numbers for the 4 keypad columns.



void setup() 
{
  Serial.begin(9600);

  pinMode(13, OUTPUT);            //Set the IR LED pin to an output
  digitalWrite(13, HIGH);         //And make sure the LED is off

  Init_Keypad();                  //Setup the pins connected to the keypad
}



void loop() 
{
  /* Check to see if a key on the keypad has been pressed */
  if(KeyPressed())
  {
    /* If so then get the key and send the IR code assigned to that key*/
    switch(GetKey())
    {
      case(KEY_1):
        SendCode(IR_ADDRESS, KEY_1_IR_CODE);
        break;

      case(KEY_2):
        SendCode(IR_ADDRESS, KEY_2_IR_CODE);
        break;

      case(KEY_3):
        SendCode(IR_ADDRESS, KEY_3_IR_CODE);
        break;

      case(KEY_A):
        SendCode(IR_ADDRESS, KEY_A_IR_CODE);
        break;

      case(KEY_4):
        SendCode(IR_ADDRESS, KEY_4_IR_CODE);
        break;

      case(KEY_5):
        SendCode(IR_ADDRESS, KEY_5_IR_CODE);
        break;

      case(KEY_6):
        SendCode(IR_ADDRESS, KEY_6_IR_CODE);
        break;

      case(KEY_B):
        SendCode(IR_ADDRESS, KEY_B_IR_CODE);
        break;

      case(KEY_7):
        SendCode(IR_ADDRESS, KEY_7_IR_CODE);
        break;

      case(KEY_8):
        SendCode(IR_ADDRESS, KEY_8_IR_CODE);
        break;

      case(KEY_9):
        SendCode(IR_ADDRESS, KEY_9_IR_CODE);
        break;

      case(KEY_C):
        SendCode(IR_ADDRESS, KEY_C_IR_CODE);
        break;

      case(KEY_STAR):
        SendCode(IR_ADDRESS, KEY_STAR_IR_CODE);
        break;

      case(KEY_0):
        SendCode(IR_ADDRESS, KEY_0_IR_CODE);
        break;

      case(KEY_HASH):
        SendCode(IR_ADDRESS, KEY_HASH_IR_CODE);
        break;

      case(KEY_D):
        SendCode(IR_ADDRESS, KEY_D_IR_CODE);
        break;
    }

    delay(100); //Wait a little before checking the keypad again
  }
}


/* Initiliases the pins connected to the keypad */
void Init_Keypad()
{
  /* Set all keypad row pins to outputs */
  for(byte i = 0; i < 4; i++)
  {
    pinMode(Rows[i], OUTPUT);
    digitalWrite(Rows[i], HIGH);
  }

  /* Set all keypad column pins to inputs */
  for(byte i = 0; i < 4; i++)
    pinMode(Cols[i], INPUT_PULLUP);
}


/* Function checks to see if a key on the keypad is currently pressed. */
boolean KeyPressed()
{
  boolean State = false;
  byte Debounce = 0;

  /* We only need to know if a button has been pressed, it doesn't matter which one so
   * we can check all the buttons at the same time by pulling all the rows low and looking
   * for one of the column pins being low */
  for(byte i = 0; i < 4; i++)
    digitalWrite(Rows[i], LOW);

  /* Check to see if any of the column pins are low. Do this 50 times to remove any false triggers
   * caused by a key switch contact bouncing when it is first pressed */
  do
  {
    for(byte i = 0; i < 4; i++)
      if(!digitalRead(Cols[i]))
        State = true;

    Debounce++;
  }while(State == true && Debounce < 50);   

  /* Return the row pins back to the high state */  
  for(byte i = 0; i < 4; i++)
    digitalWrite(Rows[i], HIGH);
    
  if(Debounce == 50)
    return true;  //A key is currently pressed so return true
  else
    return false; //A key is not currently pressed so return false
}


/* Gets the currently pressed key and returns a 2 digital value. 
 * The first digit represents the keypad row number (0 to 3)
 * The second digit represents the keypad column number (0 to 3) */
byte GetKey()
{
  byte Key = KEY_NONE;

  for(byte RowIndex = 0; RowIndex < 4; RowIndex++)
  {
    digitalWrite(Rows[RowIndex], LOW);
    
    for(byte ColIndex = 0; ColIndex < 4; ColIndex++)
      if(!digitalRead(Cols[ColIndex]))
        Key = ColIndex + (RowIndex * 10);

    digitalWrite(Rows[RowIndex], HIGH);
  }
  return Key;
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

/* Used by the SendCode() and SendByte() functions above to sned one bit of data */
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
