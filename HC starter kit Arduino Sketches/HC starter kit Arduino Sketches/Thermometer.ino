#include "HC7Seg.h"

/* Analogue pin for LM35 temperature sensor */
#define LM35 A0

/* Digital pins used to drive each digit and digit segment of your display. */
#define SEG_A   8
#define SEG_B   13
#define SEG_C   3
#define SEG_D   6
#define SEG_E   5
#define SEG_F   9
#define SEG_G   2 
#define SEG_DP  7 
#define DIG_1   4
#define DIG_2   12 
#define DIG_3   11
#define DIG_4   10

/* Creates an instance of the HC7Seg library */
HC7Seg HC7Seg(COM_CATHODE_4DIG, SEG_A, SEG_B, SEG_C, SEG_D, SEG_E, SEG_F, SEG_G, SEG_DP, DIG_1, DIG_2, DIG_3, DIG_4);


void setup() 
{
  /* Set the analogue reference used by the ADC inputs to the internal 1.1V reference */
  analogReference(INTERNAL);
}

void loop() 
{
  /* Read the current temperature from the temperature sensor */
  float Temperature = analogRead(LM35) / 9.31;

  /* Output this temperature to the seven segment display */
  HC7Seg.clear();
  HC7Seg.print7Seg(Temperature, 3, 1);
  
  delay(1000);
}
