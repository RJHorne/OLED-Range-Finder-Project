/* FILE:    Door_Access_System
   DATE:    16/10/17
   VERSION: 0.1
   AUTHOR:  Andrew Davies

16/10/17 version 0.1: Original version

THIS SOFTWARE IS PROVIDED "AS IS". HOBBY COMPONENTS MAKES NO WARRANTIES, WHETHER
EXPRESS, IMPLIED OR STATUTORY, INCLUDING, BUT NOT LIMITED TO, IMPLIED WARRANTIES OF
MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE, ACCURACY OR LACK OF NEGLIGENCE.
HOBBY COMPONENTS SHALL NOT, IN ANY CIRCUMSTANCES, BE LIABLE FOR ANY DAMAGES,
INCLUDING, BUT NOT LIMITED TO, SPECIAL, INCIDENTAL OR CONSEQUENTIAL DAMAGES FOR ANY
REASON WHATSOEVER.
*/

/* Default pin code (1234) */
#define PIN1    KEY_1
#define PIN2    KEY_2
#define PIN3    KEY_3
#define PIN4    KEY_4

/* Time in ms to keep the door unlocked after a correct code has been entered */
#define DOOR_OPEN_TIME 5000

/* Digital pins to control buzzer and door lock (LED) */
#define BUZZER    10
#define DOORLOCK  11

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
#define KEY_*     30
#define KEY_0     31
#define KEY_#     32
#define KEY_D     33
#define KEY_NONE  255


const byte Rows[] = {9, 8, 7, 6}; //Holds the pin numbers for the 4 keypad rows.
const byte Cols[] = {5, 4, 3, 2}; //Holds the pin numbers for the 4 keypad columns.
byte Access_Code[4] = {PIN1, PIN2, PIN3, PIN4}, Keypad_Code[4], KeyIndex;
unsigned int Timeout;


void setup() 
{
  /* Set all keypad row pins to output */
  for(byte i = 0; i < 4; i++)
  {
    pinMode(Rows[i], OUTPUT);
    digitalWrite(Rows[i], HIGH);
  }

  /* Set all keypad column pins to inputs */
  for(byte i = 0; i < 4; i++)
    pinMode(Cols[i], INPUT_PULLUP);

  /* Set the door lock and buzzer pins to outputs */
  pinMode(BUZZER, OUTPUT);
  digitalWrite(BUZZER, LOW);
  pinMode(DOORLOCK, OUTPUT);
  digitalWrite(DOORLOCK, LOW);

  /* Clear the buffer that holds the pin code last entered into the keypad*/
  ClearKeypadCode();
}



void loop() 
{
  /* Check to see if a key on the keypad has been pressed */
  if(KeyPressed())
  {
    /* If so then get the key and save it into the buffer */
    Keypad_Code[KeyIndex] = GetKey();

    /* Let the user know the key has been entered with a short beep from the buzzer */
    Buzzer(100);
    KeyIndex++;

    /* Have 4 keys been pressed yet? */
    if(KeyIndex == 4)
    {
      /*If so then check to see if the entered pin code is correct */
      if(CheckCode())
         {
            /* Pin code is correct so open the door */
            delay(100);
            Buzzer(100);

            digitalWrite(DOORLOCK, HIGH);
            delay(DOOR_OPEN_TIME);
            digitalWrite(DOORLOCK, LOW);
         }else
         {
            /* Pin code is incorrect so warn the user with a long beep from the buzzer */
            Buzzer(1000);
         }

      /* Remove the pin code from the buffer */
      ClearKeypadCode();
    }

    /* Don't continue until the currently pressed button is released */
    while(KeyPressed());
  }


  /* If a partial code has been entered wait for 5 seconds and then clear the buffer (timeout) */
  if(KeyIndex > 0)
  {
      Timeout++;
      if(Timeout > 5000)
      {
        Buzzer(1000);
        ClearKeypadCode();
        Timeout = 0;
      }
      delay(1);
  }else
    Timeout = 0;
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


/* Check to see if the currently entered pin code is correct */
boolean CheckCode()
{
  if(Keypad_Code[0] == Access_Code[0] &&
     Keypad_Code[1] == Access_Code[1] &&
     Keypad_Code[2] == Access_Code[2] &&
     Keypad_Code[3] == Access_Code[3])
    return true;
  else
    return false;
}

/* Clears the buffer holding the last entered pin code */
void ClearKeypadCode()
{
  KeyIndex = 0;
  
  for(byte i = 0; i < 4; i++)
     Keypad_Code[i] = KEY_NONE;
}

/* Beeps the buzzer for the specified time in ms */
void Buzzer(int Time)
{
  digitalWrite(BUZZER, HIGH);
  delay(Time);
  digitalWrite(BUZZER, LOW);
}

