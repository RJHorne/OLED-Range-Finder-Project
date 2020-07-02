/* FILE:    Scrolling_Message_Display
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


#include "HCDotMatrix.h"

//Create an instance of the HCDotMatrix library
HCDotMatrix HCDotMatrix(ROW1,ROW2,ROW3,ROW4,ROW5,ROW6,ROW7,ROW8,  
                        COL1,COL2,COL3,COL4,COL5,COL6,COL7,COL8);



void setup() 
{
  //Initialise the HCDotMatrix library. 
  HCDotMatrix.init(COMMON_CATHODE);
}


void loop() 
{
  //Scroll a message. Replace the text below with your own message.
  //Lower the scroll speed from 50 to make the message scroll faster or 
  //increase it to make it scroll slower.
  
  ScrollMessage("Hello World ! ! !", 50);
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
