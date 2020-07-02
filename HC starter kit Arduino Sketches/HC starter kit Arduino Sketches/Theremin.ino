#define FREQ_MIN 100  // minimum frequency value
#define FREQ_MAX 4000  // maximum frequency value
#define SPEAKER 13   // pin the speaker is connected to
#define LDR A0    // pin the light sensor is connected to
int Cal_Level;

void setup() //runs once at startup
{
Cal_Level = analogRead(LDR);  // read the sensor and put the result into CAL_Level

}

void loop() // runs for ever
{
int Note = analogRead(LDR);

if (Note - Cal_Level > 10)
  {
  Note = map(Note, Cal_Level, FREQ_MIN, FREQ_MAX,0);
  tone (SPEAKER, Note, 15);    // play a tone on the speaker
  }
  delay(10);   // add a small delay
}
