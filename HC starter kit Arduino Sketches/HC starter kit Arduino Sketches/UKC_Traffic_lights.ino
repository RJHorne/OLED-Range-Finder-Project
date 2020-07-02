/* FILE:    UKC_traffic_lights
   DATE:    03/06/20
   VERSION: 0.1
   AUTHOR:  Andrew Brookman

03/06/20 version 0.1: Original version

THIS SOFTWARE IS PROVIDED "AS IS", and is provided for educational purposes only

This is to be used in conjunction with the Hobby Components starter kit
Thius sketch shoul dbe used with the Traffic Lights hardware on page 19
of the printed manual
3 Leds are used each with a 220 ohm series resistor pins used are 5,6,7
the positive LED pin (Longest one) is connected to the resistor, the negative
pin is connected to the Arduino pin. There are 4 sections to this code:

1. This bit which is purely human readable comments
2. The definitions section from lines 24 to 29
3. The setup routine that sets pins as In or Out etc. and runs just once at the start
4. The main loop from lines 54 to 71 that runs the main code, loping continously
*/


#define RED_LED 5
#define AMB_LED 6  //This assigns a text label (e.g. RED_LED) to pin 5
#define GRN_LED 7
#define LED_OFF HIGH //This assigns a text label (e.g. LED_ON) to the constant definition HIGH which means the pin will be ON
#define LED_ON LOW   // As above but pin OFF

void setup()    // this setup routine applies to the code from here until line 27, this code is run once at startup

{               // or if the reset button is pressed

  pinMode(RED_LED, OUTPUT);
  pinMode(AMB_LED, OUTPUT);   //define these 3 pins as outputs
  pinMode(GRN_LED, OUTPUT);

  digitalWrite(RED_LED, LED_OFF);
  digitalWrite(AMB_LED, LED_OFF);  //turn all 3 pins we are using OFF
  digitalWrite(GRN_LED, LED_OFF);
delay(200); 
  digitalWrite(RED_LED, LED_ON);
  digitalWrite(AMB_LED, LED_ON);  //turn all 3 pins we are using ON
  digitalWrite(GRN_LED, LED_ON);
  delay(200);                     //use a built in function to wait of 200 ms (0.2 second)
  digitalWrite(RED_LED, LED_OFF);
  digitalWrite(AMB_LED, LED_OFF);  //turn all 3 pins we are using OFF again
  digitalWrite(GRN_LED, LED_OFF);
  delay(500);                      //wait 500ms

}

void loop()                       //this routine runs all the code sequentialy until it reaches line 69 when it starts again

{                                 //from line 56. This will run for ever until the reset button is pressed

  digitalWrite(RED_LED, LED_ON);
  delay(1000);
  digitalWrite(RED_LED, LED_OFF);   //flash the RED Led on for 1 second
  delay(1000);

  digitalWrite(AMB_LED, LED_ON);
  delay(1000);
  digitalWrite(AMB_LED, LED_OFF);  //flash the AMBER Led on for 1 second
  delay(1000);

  digitalWrite(GRN_LED, LED_ON);
  delay(1000);
  
  digitalWrite(GRN_LED, LED_OFF);  //flash the GREEN Led on for 1 second
  delay(1000);
}
