/* FILE:    Simon_Says
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

#define LEVELS 10  //Sets the number of levels

/* Digital pins for the 4 LED's and buttons */
#define RED_LED 12
#define YEL_LED 10
#define GRN_LED 8
#define BLU_LED 6

#define RED_BTN 13
#define YEL_BTN 11
#define GRN_BTN 9
#define BLU_BTN 7

#define SPEAKER 5

#define OFF HIGH //LED OFF state.
#define ON LOW   //LED ON state.

/* A very simple tune to play if the player completes the game */
unsigned int melody[] = {262, 196, 196, 220, 196, 0, 247, 262};

byte Pattern[LEVELS]; // Stores the random pattern of colours


void setup()
{
  /* Set all LED pins to outputs */
  pinMode(RED_LED, OUTPUT);
  pinMode(YEL_LED, OUTPUT);
  pinMode(GRN_LED, OUTPUT);
  pinMode(BLU_LED, OUTPUT);
  All_LEDs(OFF);

  /* Set all button pins to inputs with pullup resistor */
  pinMode(RED_BTN, INPUT_PULLUP);
  pinMode(YEL_BTN, INPUT_PULLUP);
  pinMode(GRN_BTN, INPUT_PULLUP);
  pinMode(BLU_BTN, INPUT_PULLUP);
}


void loop()
{
  int Level = 0;

  /* Wait for the player to press a button to start a new game */
  StartNewGame();

  /* Create a new random pattern of colours */
  GeneratePattern();

  do // Loop for each completed level
  {
    delay(1000);

    Level++; // Move to the next level

    PlayPattern(Level); // Play the pattern for the current level
  }while(GetPlayerPattern(Level) && Level < LEVELS); // If player keyed the correct sequence and it's not the last level then loop back


  /* Game has now ended so check if player got to the last level */
  if(Level == LEVELS)
    PlayWinMelody();
  else
    PlayLoseMelody();
}


/* Waits for the player to press a button */
void StartNewGame(void)
{
  while(WaitForButton() == 0);
  while(GetButton(RED_BTN) || GetButton(YEL_BTN) || GetButton(GRN_BTN) || GetButton(BLU_BTN));
  tone(SPEAKER, 1500, 1000);
  All_LEDs(ON);
  delay(1000);
  All_LEDs(OFF);
}


/* Fills the pattern array with a new set of random LED colours */
void GeneratePattern(void)
{
  for(int i = 0; i < LEVELS; i++)
  {
    byte Colour = random(0, 4);

    switch(Colour)
    {
      case(0):
        Pattern[i] = RED_LED;
        break;

      case(1):
        Pattern[i] = YEL_LED;
        break;

      case(2):
        Pattern[i] = GRN_LED;
        break;

      case(3):
        Pattern[i] = BLU_LED;
        break;
    }
  }
}


/* Plays the LED pattern stored in the pattern array up to the specified level */
void PlayPattern(byte Level)
{
    for(int i = 0; i < Level; i++)
    {
    PlayLEDTone(Pattern[i]);

    digitalWrite(Pattern[i], ON);
    delay(500);
    digitalWrite(Pattern[i], OFF);
    delay(100);
    }
}


/* Reads the player inputs and checks them against the stored pattern. 
 * If it is correct then it will return true, if not false */
boolean GetPlayerPattern(byte Level)
{
  byte i = 0;
  byte Button;
  do
  {
    Button = WaitForButton();
    PlayLEDTone(Button);
    digitalWrite(Button, ON);
    delay(500);
    digitalWrite(Button, OFF);
    while(GetButton(RED_BTN) || GetButton(YEL_BTN) || GetButton(GRN_BTN) || GetButton(BLU_BTN));
    i++;
  }while(i < Level && Pattern[i-1] == Button);

  if(i == Level && Pattern[i-1] == Button)
    return true;

  return false;
}


/* Gets the current state of a button. If pressed it will read it several times to check for button bounce 
 * Returns true if the button is pressed */
boolean GetButton(byte Button)
{
  boolean State = true;

  for(byte i = 0; i < 254; i++)
    if(digitalRead(Button))
      State = false;

  return State;
}


/* Waits for any of the 4 buttons to be pressed. Times out after 5 seconds otherwise returns the button that was pressed */
byte WaitForButton()
{
  unsigned int Timeout = 500;
  while(Timeout > 0)
  {
    if(GetButton(RED_BTN))
      return RED_LED;
    if(GetButton(YEL_BTN))
      return YEL_LED;
    if(GetButton(GRN_BTN))
      return GRN_LED;
    if(GetButton(BLU_BTN))
      return BLU_LED;

    delay(10);
    Timeout--;
  }
  return 0;
}


/* Plays a single tone. The frequency of which is dependent on the specified LED */
void PlayLEDTone(byte Led)
{
  switch(Led)
    {
      case(RED_LED):
        tone(SPEAKER, 500, 500);
        break;
      case(YEL_LED):
        tone(SPEAKER, 1000, 500);
        break;
      case(GRN_LED):
        tone(SPEAKER, 1500, 500);
        break;
      case(BLU_LED):
        tone(SPEAKER, 2000, 500);
        break;
    }
}


/* Sets all 4 LED's to either on or off */
void All_LEDs(boolean State)
{
  digitalWrite(RED_LED, State);
  digitalWrite(YEL_LED, State);
  digitalWrite(GRN_LED, State);
  digitalWrite(BLU_LED, State);
}


/* Plays the game won melody */
void PlayWinMelody(void)
{
  for(byte i = 0; i < 8; i++)
  {
    tone(SPEAKER, melody[i], 200);
      All_LEDs(i % 2);
      delay(200);
  }
}

/* Plays the game lost melody */
void PlayLoseMelody(void)
{
  delay(500);
  tone(SPEAKER, 500, 500);
  delay(500);
  tone(SPEAKER, 250, 500);
  delay(500);
}

