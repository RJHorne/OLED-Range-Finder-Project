/* FILE:    Bricks
   DATE:    15/09/17
   VERSION: 0.1
   AUTHOR:  Andrew Davies

15/09/17 version 0.1: Original version

THIS SOFTWARE IS PROVIDED "AS IS". HOBBY COMPONENTS MAKES NO WARRANTIES, WHETHER
EXPRESS, IMPLIED OR STATUTORY, INCLUDING, BUT NOT LIMITED TO, IMPLIED WARRANTIES OF
MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE, ACCURACY OR LACK OF NEGLIGENCE.
HOBBY COMPONENTS SHALL NOT, IN ANY CIRCUMSTANCES, BE LIABLE FOR ANY DAMAGES,
INCLUDING, BUT NOT LIMITED TO, SPECIAL, INCIDENTAL OR CONSEQUENTIAL DAMAGES FOR ANY
REASON WHATSOEVER.
*/

// DIO pins used to drive module. Change the pin numbers to match your connections
#define ROW1  2    
#define ROW2  9    
#define ROW3  17    
#define ROW4  3   
#define ROW5  10 
#define ROW6  16
#define ROW7  11 
#define ROW8  12

#define COL1  6
#define COL2  13
#define COL3  14
#define COL4  4 
#define COL5  15
#define COL6  5
#define COL7  7
#define COL8  8

#define POT   5             //Analog pin number for potentiometer
#define BUTTON 18           //Digital pin number for switch

#define POT_MIN 256         //Pot minimum value 
#define POT_MAX 768         //Pot maximum value


enum GameStates             //State machine states for different stages of the game
{
  STATE_INIT,               //Initiliases a new game
  STATE_NEWLEVEL,           //Sets up next level
  STATE_START,              //Start of a new game, allows for positioning of bat
  STATE_PLAY,               //Game is in progress
  STATE_NEXT_LEVEL,         //Last level completed, sets up next level
  STATE_LOSE,               //Game lost
  STATE_END,                //All levels completed
};


#include "HCDotMatrix.h"

//Create an instance of the HCDotMatrix library
HCDotMatrix HCDotMatrix(ROW1,ROW2,ROW3,ROW4,ROW5,ROW6,ROW7,ROW8,  
                        COL1,COL2,COL3,COL4,COL5,COL6,COL7,COL8);

//Various variables required for the game
int8_t GameState = STATE_INIT, BatPos, BallX, BallY, DirX = 0, DirY = -1, Level = 1;
byte GameSpeed = 200;




void setup() 
{
  //Initialise the HCDotMatrix library. 
  HCDotMatrix.init(COMMON_CATHODE);

  //Configure the start button pin as an input
  pinMode(BUTTON, INPUT_PULLUP);
}



void loop() 
{
  //Game state machine
  switch(GameState)
  {
    case(STATE_INIT):
      Level = 1;                    //Set level to the first level
      GameSpeed = 200;              //Set game speed (delay in ms) to the slowest speed
      GameState = STATE_NEWLEVEL;   //Go to game new level state
      break;
    
    //Setup a new game 
    case(STATE_NEWLEVEL):
      HCDotMatrix.clear();          //Clear the display
      DrawBricks();                 //Draw the 3 rows of bricks
      GameState = STATE_START;      //Go to game start state
      break;

    //Wait for game start button to be pressed
    case(STATE_START): 
      GetBatX();                    //Update the bats X coordinate by reading the pot         
      DrawBat();                    //Draw the bat
      DrawBall();                   //Draw ball based on current position of pot
      if(digitalRead(BUTTON)==LOW)  //Check if start button is pressed (pin low)
        GameState = STATE_PLAY;     //If so then switch to play state
      break;

    //Game in progress state
    case(STATE_PLAY):               
      GetBatX();                    //Update the bats X coordinate by reading the pot 
      DrawBat();                    //Draw the bat
      DrawBall();                   //Draw ball based on current position of pot
      if(CheckBricks())             //Check to see if there are anymore bricks left
        GameState = STATE_NEXT_LEVEL; //If so then go to next level state
      delay(GameSpeed);        
      break;


    //Level is complete so move to next level
    case(STATE_NEXT_LEVEL):
      Level++;                      //Set level counter to next level

      if(Level == 10)               //Check if last level has been reached
        GameState = STATE_END;      //If so then go to end game state
      else                          
      {
        ScrollMessage("Level", 50); //If not then scroll next level message
        HCDotMatrix.print(Level, 8, 0);

        delay(2000);

        GameSpeed -= 10;            //Increase game speed to make next level harder
        GameState = STATE_NEWLEVEL; //Setup next level
      }
      break;


    //Game lost state (ball missed bat) 
    case(STATE_LOSE):
      for(byte i = 0; i < 40; i++)  //Flash the display
      {
        HCDotMatrix.invert();
        delay(50);
      }

      ScrollMessage("GAME OVER!", 50); //Scroll game over message
      
      delay(2000);
      GameState = STATE_INIT;       //Setup a new game  
      break;


    //All levels complete - game has been won!
    case(STATE_END):
      ScrollMessage("Congratulations...you WIN!", 50); //Scroll you win message

      delay(2000);
      GameState = STATE_INIT;       //Setup a new game 
      break;
  }  
}


//Scrolls a string of text across the display from right to left
void ScrollMessage(char Message[], byte Speed)
{
  for(int X = 0; X <= (strlen(Message)* 8) + 8; X++)
  {
    HCDotMatrix.print(Message, X);
    delay(Speed);
  } 
}


//Draws 3 rows of bricks across the top of the display
void DrawBricks()
{
  for(byte Y = 0; Y <= 2; Y++)
    for(byte X = 0; X < 8; X++)
       HCDotMatrix.setLED(X, Y); 
}


//Draws the ball at its current position
void DrawBall()
{

  if(GameState == STATE_START)                    //If game hasn't started yet then just draw the ball in the middle of the bat
  {
    for(byte X = 0; X < 8; X++)                   //Erase the ball
      HCDotMatrix.clearLED(X,6);

    BallX = BatPos;                               //Set the balls X position to wherever the bat is
    BallY = 6;                                    //Set the balls Y position to just above the bat
    HCDotMatrix.setLED(BatPos, 6);                //Draw the ball
  
  }else                                           //If game has started then draw the ball at the next X,Y coordinate
  {
    HCDotMatrix.clearLED(BallX, BallY);           //Erase the ball
    
    if(BallY == 0)                                //Has ball hit top of screen?
        DirY = 1;                                 //If so then change its Y direction
    
    else if(HCDotMatrix.getLED(BallX, BallY - 1)) //Has ball hit brick directly above it?
    {
      HCDotMatrix.clearLED(BallX, BallY - 1);     //If so then remove the brick...
      DirY = 1;                                   //...and change the balls Y direction                  
    
    }else if(BallY == 7)                          //Has ball hit bottom of screen?
      GameState = STATE_LOSE;                     //If so then ball missed the bat so end the game
  
    else if(BallY == 6 && (BallX >= BatPos - 2 && BallX <= BatPos + 2)) //Has ball hit bat?
      DirY = -1;                                  //If so then change the balls Y direction
  

    
    if(BallX == 0)                                //Has ball hit left wall?
      DirX = 1;                                   //If so then change X direction
    
    else if(BallX == 7)                           //Has ball hit right wall?
      DirX = -1;                                  //If so then change X direction

    else if(BallY == 6)                           //Has ball hit the bat?
    {
      if(BallX == BatPos - 1 || BallX == BatPos - 2)  //Has ball hit left side of bat?
        DirX = -1;                                    //If so then change its X direction
      else if(BallX == BatPos + 1 || BallX == BatPos + 2) //Has ball hit right side of bat?
        DirX = 1;                                     //If so then change its X direction
    }


    BallX += DirX;                              //Move the ball
    BallY += DirY;
    
    HCDotMatrix.setLED(BallX, BallY);           //Draw the ball in its new location
  }
}



// Check to see if there are no more bricks
boolean CheckBricks()
{
  boolean Flag = true;

  for(byte Y = 0; Y <= 2; Y++)                  //Scan top 3 rows of display for bricks
    for(byte X = 0; X < 8; X++)
      if(HCDotMatrix.getLED(X, Y))
        Flag = false;

  return Flag;                                  //Return true if there are no more bricks
}


//Draw the bat with its centre at the specified X location
void DrawBat()
{
  for(byte X = 0; X < 8; X++)                   //Erase the bat
    HCDotMatrix.clearLED(X,7);
    
  HCDotMatrix.setLED(BatPos - 1, 7);            //Redraw the bat on row 7 at the specified X location
  HCDotMatrix.setLED(BatPos, 7);
  HCDotMatrix.setLED(BatPos + 1, 7);
}



//Updates the bats location by reading the current position of the pot
//and converting it to a X coordinate.
void GetBatX()
{
  int Value = analogRead(POT);

  if(Value < POT_MIN)
    BatPos = 1;
  else if (Value > POT_MAX)
    BatPos = 6;
  else
    BatPos = Value / (1024 / 8);
}

