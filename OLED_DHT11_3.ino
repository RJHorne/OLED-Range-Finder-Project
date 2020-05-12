// start of code to copy and paste
//
// June 2019 - J.Morris
// May 2020 Andy Brookman
// Code modified heavily to convert for a Thermomenter & Humidity meter woith a DHT11 sensor.


#include <Adafruit_GFX.h>         // include the Adafruit graphics library - find it in the library manager
#include <Adafruit_SSD1306.h>     // include the Adafruit OLED display library - find it in the library manager
#include <SimpleDHT.h>            // include the DHT11 sensor library

int pinDHT11 = 2;                 //define the sensor pin number
int DHTpower = 3;                 //define the sensor power pin
SimpleDHT11 dht11(pinDHT11);      //initialise the DHT11 library

int Status_LED = 5;               // LED connected to the Nano pin


#define OLED_RESET 6              //not presently used, but needed to make the code compile without errors.
Adafruit_SSD1306 display(OLED_RESET);

#include "UKCLOGO.h"               // Include the logo file that is displayed at startup.

void setup()                       //run this part of the code only once at power on or reste to setup
{
Serial.begin(9600);               // start the serial port so we can se serial data
Serial.println("=================================");
Serial.println(" DHT11 Temp and Humidity project ");
Serial.println("=================================");    //just a startup message
Serial.println("");

pinMode(DHTpower,OUTPUT);         // set pinmode for the DHT Power pin
pinMode(Status_LED,OUTPUT);       // set pinmode for the LED
pinMode(4,OUTPUT);                // define the pin for the buzzer as an output
digitalWrite(Status_LED, LOW);    // Force the LED to be off when the Nano starts up.
digitalWrite(DHTpower, HIGH);     // Switch the DHTpower pin ON when the Nano starts up.

display.begin(SSD1306_SWITCHCAPVCC, 0x3C);  // initialize with the I2C addr 0x3D (for the 128x64)  
display.clearDisplay();                     // Clear the display of any junk at startup

// --------------- display.drawBitmap(topLeftX, topLeftY, imageData, width, height, color)

display.drawBitmap(-30,0,UKCLOGO,256,128,WHITE, BLACK); // Draw the bitmap logo on the display at a certain position
display.display();                                      // Display the contents on the display
delay(5000);                                            // wait for 5 seconds
display.clearDisplay();                                 // clear display
}
    //setup completed
    //onto the main part of code that loops continuously

void loop()                                 
{

  digitalWrite(Status_LED, HIGH);                 // turn the LED on when we start the measurement loop.
  // read without samples.
  byte temperature = 0;                           //setup some memory locations to store the values measued by the sensor
  byte humidity = 0;
  int err = SimpleDHTErrSuccess;
  if ((err = dht11.read(&temperature, &humidity, NULL)) != SimpleDHTErrSuccess) {
    Serial.print("Read DHT11 failed, err="); Serial.println(err);delay(1000);
    return;                                        // This part of the code prints an error if the sensor is missing or not working
  }

  Serial.println("=================================");
  Serial.print(" DHT11 Temp ... = ");
  Serial.print((int)temperature);                                // serial port print the temperature to terminal monitor
  Serial.println(" Degrees C");
  
  Serial.print(" DHT11 Humidity ... = ");
  Serial.print((int)humidity);                                  // serial port print the humidity to terminal monitor
  Serial.println(" %");
  
  display.setTextSize(1);             // Text size 1, 2, 3 etc
  display.setTextColor(WHITE);        // set colour
  display.setCursor(27,0);            // position of text x,y coords 27,0
  display.println("Temperature");     // display text "Temperature"

  display.setTextSize(1);             
  display.setTextColor(WHITE);
  display.setCursor(96,0);  
  display.println("Deg C");  

  display.setTextSize(1);   
  display.setTextColor(WHITE);
  display.setCursor(35,18); 
  display.println("Humidity");  

  display.setTextSize(1);   
  display.setTextColor(WHITE);
  display.setCursor(90,18);  
  display.println("%");  

  display.setTextSize(2); 
  display.setTextColor(WHITE);    
  display.setCursor(1,0); 
  display.println((int)temperature);  // Print the Temperature value from sensor to the display

  display.setTextSize(2);   
  display.setTextColor(WHITE);   
  display.setCursor(1,18); 
  display.println((int)humidity);     // Print the humidity value from sensor to the display

  display.display();
  display.clearDisplay();

  digitalWrite(Status_LED, LOW);      // turn the LED  off  after the readings are taken & displayed
  
  delay(1000);                        // add a delay 1 second before we go back to the start of the loop to take another reading
}

// End of code to copy and paste
