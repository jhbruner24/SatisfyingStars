#include <Servo.h>
#include "IRremote.h"
#include <FastLED.h>

#define NUM_LEDS 28
#define LED_PIN A5       // WS2812B LED Strip to Arduino Analog Pin 5
#define RECEIVER 5      // Signal Pin of IR RECEIVER to Arduino Digital Pin 5
#define GROUND_PIN 6
#define HIGH_PIN 7

// Continuous servo instance
Servo continuousMotor;

// Array containing light RGB values
CRGB leds[NUM_LEDS];

// This is variable and can change by pressing VOL+ or Vol- on the remote
int motorSpeed = 95;

IRrecv irrecv(RECEIVER);     // create instance of 'irrecv'
decode_results results;      // create instance of 'decode_results'

void setup() {
  // Software Solution to limit wire mess
  pinMode(GROUND_PIN, OUTPUT);     
  pinMode(HIGH_PIN, OUTPUT); 
  digitalWrite(GROUND_PIN, LOW);
  digitalWrite(HIGH_PIN, HIGH);

  // Setup serial monitor for test purposes
  Serial.begin(9600);
  Serial.println("IR RECEIVER Button Decode"); 

  // Start the RECEIVER
  irrecv.enableIRIn();          

  // Attaches the servo on pin 9 
  continuousMotor.attach(9); 

  // Enables lights and turns them on to White
  FastLED.addLeds<WS2812, LED_PIN, GRB>(leds, NUM_LEDS);
  lightsWhite();
}

void loop() {
  runRemote();
  turnMotor();
}

// Everything below are helper functions
void turnMotor() {
   // May add different remote controlled speeds in the future
   continuousMotor.write(motorSpeed); //rotate counterclockwise at slow speed
}

/*----( REMOTE FUNCTIONS )----*/
void runRemote() {
  if (irrecv.decode(&results))   // have we received an IR signal?
  {
    translateIR();                 // Do not get immediate repeat
    irrecv.resume();            // receive the next value
  }  
}

void translateIR() {          // takes action based on IR code received
// describing Remote IR codes 
Serial.println(results.value, HEX);
  switch(results.value){
    case 0xFFA25D:  lightsOff(); Serial.println("POWER"); break;
    case 0xFFE21D:  Serial.println("FUNC/STOP"); break;
    case 0xFF629D:  increaseMotorSpeed(); Serial.println("VOL+"); break;
    case 0xFF22DD:  Serial.println("FAST BACK");  break;
    case 0xFF02FD:  Serial.println("PAUSE"); break;
    case 0xFFC23D:  Serial.println("FAST FORWARD"); break;
    case 0xFFE01F:  Serial.println("DOWN"); break;
    case 0xFFA857:  decreaseMotorSpeed(); Serial.println("VOL-"); break;  
    case 0xFF906F:  Serial.println("UP"); break; 
    case 0xFF9867:  Serial.println("EQ"); break;    
    case 0xFFB04F:  Serial.println("ST/REPT"); break;     
    case 0xFF6897:  lightsWhite(); Serial.println("0"); break; 
    case 0xFF30CF:  lightsRed(); Serial.println("1"); break; 
    case 0xFF18E7:  lightsGreen(); Serial.println("2"); break; 
    case 0xFF7A85:  lightsBlue(); Serial.println("3"); break;
    case 0xFF10EF:  lightsGoBears(); Serial.println("4"); break; 
    case 0xFF38C7:  lightsYouthfulAndWise(); Serial.println("5");  break;   
    case 0xFF5AA5:  lightsWinnie(); Serial.println("6"); break; 
    case 0xFF42BD:  lightsIreland(); Serial.println("7"); break; 
    case 0xFF4AB5:  lightsRainbow(); Serial.println("8"); break;    
    case 0xFF52AD:  lightsCycle(); Serial.println("9"); break; 
    case 0xFFFFFFFF:  Serial.println(" REPEAT"); break;

  default: 
    break;
     Serial.print(" other button   ");
     Serial.println(results.value);

  }
} //END translateIR


/*----( MOTOR SETTINGS )----*/

void increaseMotorSpeed() {
  if (motorSpeed < 150) {
    motorSpeed += 5;
  }
  Serial.println(motorSpeed);
}

void decreaseMotorSpeed() {
  if (motorSpeed > 4) {
    motorSpeed -= 5;
  }
  Serial.println(motorSpeed);
}

/*----( LIGHTS SETTINGS )----*/

void lightsOff() {
  for (int i = 0; i < NUM_LEDS; i++) {
        leds[i] = CRGB(0, 0, 0);
     }
     FastLED.show();
}

void lightsWhite() {
  for (int i = 0; i < NUM_LEDS; i++) {
      leds[i] = CRGB(100, 255, 255);
   }
   FastLED.show();
}

void lightsRed() {
  for (int i = 0; i < NUM_LEDS; i++) {
      leds[i] = CRGB(255,0,0);
   }
   FastLED.show();
}

void lightsGreen() {
  for (int i = 0; i < NUM_LEDS; i++) {
      leds[i] = CRGB(0,255,0);
   }
   FastLED.show();
}

void lightsBlue() {
  for (int i = 0; i < NUM_LEDS; i++) {
      leds[i] = CRGB(0,0,255);
   }
   FastLED.show();
}

void lightsGoBears() {
  const int numLightsBeforeChange = 1;
  int count = 0;
  bool blue = true;
  for (int i = 0; i < NUM_LEDS; i++) {
      if (blue) {
        leds[i] = CRGB(0,0,150);
      } else {
        leds[i] = CRGB(50, 50,1);
      }
      count += 1; 
      if (count == numLightsBeforeChange) {
        count = 0;
        blue = !blue;
      }
   }
   FastLED.show();
}

void lightsYouthfulAndWise() {
  const int numLightsBeforeChange = 1;
  const int numColors = 3;
  int count = 0;
  int color = 0;
  for (int i = 0; i < NUM_LEDS; i++) {
    if (color == 0) {
      leds[i] = CRGB(50, 50, 0);
    }
    if (color == 1) {
      leds[i] = CRGB(0, 60, 0);
    }
    if (color == 2) {
      leds[i] = CRGB(0, 0, 155);
    }
     count += 1;
    if (count == numLightsBeforeChange) {
      count = 0;
      color += 1;
      if (color == numColors) {
        color = 0;
      }
    }
  }
  FastLED.show();
}

void lightsWinnie() {
  const int numLightsBeforeChange = 1;
  int count = 0;
  bool fuschia = true;
  for (int i = 0; i < NUM_LEDS; i++) {
    if (fuschia) {
      leds[i] = CRGB(50,10,80);
    }
    else {
      leds[i] = CRGB(0,0,200);
    }
    // Can't make LED black so commenting out
//    if (color == 2) {
//      leds[i] = CRGB(0, 0, 0);
//    }
  count += 1;
  if (count == numLightsBeforeChange) {
      count = 0;
      fuschia = !fuschia;
    }
  }
  FastLED.show();
}

void lightsIreland() {
  const int numLightsBeforeChange = 1;
  const int numColors = 3;
  int count = 0;
  int color = 0;
  for (int i = 0; i < NUM_LEDS; i++) {
    if (color == 0) {
      leds[i] = CRGB(50, 30, 0);
    }
    if (color == 1) {
      leds[i] = CRGB(100, 100, 100);
    }
    if (color == 2) {
      leds[i] = CRGB(0, 100, 0);
    }
     count += 1;
    if (count == numLightsBeforeChange) {
      count = 0;
      color += 1;
      if (color == numColors) {
        color = 0;
      }
    }
  }
  FastLED.show();
}

void lightsRainbow() {
  for (int i = 0; i < NUM_LEDS; i++) {
    for (int r = 0; r < 64; r += 63) {
      if (i == NUM_LEDS) {
            break;
          }
      for (int g = 0; g < 255; g += 63) {
        if (i == NUM_LEDS) {
            break;
          }
        for (int b = 0; b < 255; b += 63) {
          if (i == NUM_LEDS) {
            break;
          }
          leds[i] = CRGB(r,g,b);
          i += 1;
        }
      }
    }
  }
  FastLED.show();
}

// Remote signals will not be received and ran while the light cycle is in progress
void lightsCycle() {
  for (int i = 0; i < NUM_LEDS; i++) {
    leds[i] = CRGB(155, 50, 70);
  }
  FastLED.show();
  delay(500);
  for (int i = 0; i < NUM_LEDS; i++) {
    leds[i] = CRGB(0, 0, 0);
    for (int j = 0; j < i; j++) {
      leds[j].b++;
    }
    FastLED.show();
    delay(50);
  }
  for (int i = NUM_LEDS - 1; i >= 0; i--) {
    leds[i] = CRGB(0, 255, 0);
    for (int j = 0; j < NUM_LEDS-i; j++) {
      leds[j].b--;
      leds[j].r++;
    }
    FastLED.show();
    delay(50);
  }
  for (int i = 0; i < NUM_LEDS; i++) {
    leds[i] = CRGB(155, 50, 70);
  }
  FastLED.show();
  delay(500);
  for (int i = 0; i < NUM_LEDS; i++) {
    leds[i] = CRGB(0, 0, 0);
  }
  FastLED.show();
  delay(500);
  for (int i = 0; i < NUM_LEDS; i++) {
    leds[i] = CRGB(155, 50, 70);
  }
  FastLED.show();
}
