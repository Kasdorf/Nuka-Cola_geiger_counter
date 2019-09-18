/*
Gabe 8/8/2019

I frankensteined this sketch from existing examples,
except for the loop near the end that controls the clicking of the 'geiger counter'.

 */

#include <math.h>
#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
 #include <avr/power.h> // Required for 16 MHz Adafruit Trinket
#endif

#define LED_PIN     0
#define LED_COUNT  16
// #define BRIGHTNESS 255

int proxBrightness = 100; // Initial brightness

int trigPin = 11;    // Trigger
int echoPin = 12;    // Echo
long duration, cm, inches;
// Declares NeoPixel strip object:
Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_GRBW + NEO_KHZ800);
 
void setup() {
  //Serial Port begin
//  Serial.begin (9600);
  //Define inputs and outputs
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(9, OUTPUT);        // from piezo buzzer sketch

  strip.begin();           // INITIALIZE NeoPixel strip object (REQUIRED)
  strip.show();            // Turn OFF all pixels ASAP
  strip.setBrightness(proxBrightness); // Set BRIGHTNESS to about 1/5 (max = 255)
  colorWipe(strip.Color(13,   98,   100)     , 50); 
  
}


void colorWipe(uint32_t color, int wait) {
  for(int i=0; i<strip.numPixels(); i++) { // For each pixel in strip...
    strip.setPixelColor(i, color);         //  Set pixel's color (in RAM)
    strip.show();                          //  Update strip to match
    delay(wait);                           //  Pause for a moment
  }
}

bool personClose = false;
void loop() {
  // The sensor is triggered by a HIGH pulse of 10 or more microseconds.
  // Give a short LOW pulse beforehand to ensure a clean HIGH pulse:
  digitalWrite(trigPin, LOW);
  delayMicroseconds(5);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
 
  // Read the signal from the sensor: a HIGH pulse whose
  // duration is the time (in microseconds) from the sending
  // of the ping to the reception of its echo off of an object.
  pinMode(echoPin, INPUT);
  duration = pulseIn(echoPin, HIGH);
 
  // Convert the time into a distance
  cm = (duration/2) / 29.1;     // Divide by 29.1 or multiply by 0.0343
//  inches = (duration/2) / 74;   // Divide by 74 or multiply by 0.0135
  
//  Serial.print(inches);
//  Serial.print("in, ");
//  Serial.print(cm);
//  Serial.print("cm");
//  Serial.println();

// Change brightness of LEDs:
//  int brightness = (100 + (255 - cm));
//  if (brightness > 255) {
//    brightness = 255;
//  }
//  strip.setBrightness(brightness);
//  strip.show();


  if (cm < 60 && cm > 0) {
    int delayAmount = ((cm + random(20, 70))/1.2);
    digitalWrite(9, HIGH);
//    strip.setBrightness(255);
//    strip.show();
    delay(1);
    digitalWrite(9, LOW);
//    strip.setBrightness(100);
//    strip.show();
    delay(delayAmount);
  } else {
    delay(250);
  }


}


  
  
