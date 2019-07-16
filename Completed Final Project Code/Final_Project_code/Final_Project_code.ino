/* 
 *  Krish Patel
 * 
 * Friday January 17th 2019- Due Date
 * 
 * "Vitals Detecting Device"
 * 
 * This project has the function of detecting both the body temperature(Celcius) and heart rate(BPM) of a user and Display it on an LCD 
 * 
 * Code will detect a sufficient heart beat out of many vibrations and will calculate BPM
 * Code will also check the temperature using a formula to convert inputted data to Celcius values
 * 
 */


#include "LiquidCrystal.h"
#define USE_ARDUINO_INTERRUPTS true    // Set-up low-level interrupts for most acurate BPM math.
#include <PulseSensorPlayground.h>     // Allows connection to pulsesensor library  

const int rs = 13, en = 12, d4 = 6, d5 = 5, d6 = 4, d7 = 3;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
int tmp36SensorPin = A0;  //Pin A0 will read the sensor output
int sensorInput;    //Where we will store the TMP36 input
double temp;        //Temperature variable 
const int PulseSensorWire = A1;       // The pulsesensor is connected to analog pin 1
const int LED = 2;          // The red LED is assigned to pin 2
int Threshold = 550;           // The minimum value which determines if the value is a heartbeat
 
PulseSensorPlayground pulseSensor;  // Creates an instance of the PulseSensorPlayground object called "pulseSensor"***************

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600); //Initialize connection to serial monitor
  pulseSensor.analogInput(PulseSensorWire);   //Initialize that the input comes from the PulseSensorWire/A1
  pulseSensor.blinkOnPulse(LED);      //Blink LED if heart beat is detected
  pulseSensor.setThreshold(Threshold);  //Set the threshold to be 550
 

      if (pulseSensor.begin()) {
    Serial.println("We created a pulseSensor Object !");  //This prints one time at Arduino power-up,  or on Arduino reset.  
  }

}
void loop() {
  // put your main code here, to run repeatedly: 
 int BPM = pulseSensor.getBeatsPerMinute();  // Turns BPM as an "int". //myBPM is the value set to hold the heartbeats 
                                                

if (pulseSensor.sawStartOfBeat()) {            // Continuously checks if there is a beat 
 Serial.println("Your Heart Beated! "); // If test is "true", print a message "a heartbeat happened".
 Serial.print("BPM: ");                        // Set up the presentation of "BPM:"
 Serial.println(BPM);                        // Print the value of myBPM
}
  sensorInput = analogRead(A0);    //Store TMP36 value
  temp = (double)sensorInput / 1024;       //Calculate percentage of input
  temp = temp * 5;                 //multiply by 5 to get voltage
  temp = temp - 0.5;               //Subtract the offset 
  temp = temp * 100;               //Convert to degrees 


  lcd.begin(16, 2);     //Chooses where messege should be set on LCD
  lcd.print("Temp: ");  //Set up presentation on LCD
  lcd.print(temp);      //Input value on LCD
  lcd.print(" C");
  
  lcd.setCursor(0,1);           //Choose second row for the messege to be printed on 
  lcd.print("Heart Rate:");     //Set up presentation on LCD
  lcd.print(BPM);             //Input BPM value on LCD
  lcd.print(" BPM"); 

  lcd.noDisplay();            
  delay(500);       //Set delay for 0.5 seconds
  lcd.display();
  delay(1500);      //Set delay for 1.5 seconds


  delay(20);        //Set delay for 0.02 seconds
}
