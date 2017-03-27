
//screaming chickens led code simple
#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
#include <avr/power.h>
#endif

#define PIN 4
#define NUM_LEDS 19
#define BRIGHTNESS 100
int in_1 = 7;
int in_2 = 9;
int in_3 = 11;
int in_4 = 13;

int count = 1;

Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUM_LEDS, PIN, NEO_GRB + NEO_KHZ800);

void setup() {
  Serial.begin(9600);
  pinMode(in_1, INPUT);
  pinMode(in_2, INPUT);
  pinMode(in_3, INPUT);
  pinMode(in_4, INPUT);

  strip.setBrightness(BRIGHTNESS);
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'
}

void loop() {
  Serial.println(digitalRead(in_1));
  Serial.println(digitalRead(in_2));
  Serial.println(digitalRead(in_3));
  Serial.println(digitalRead(in_4));
  if (EnabledRoutine()) {
    Serial.println("Enabled Routine");
    rainbowCycle(1);
  } else if (ShoutRoutine()) {
    //gold
    
    theaterChase(strip.Color(255, 215, 0), 45); // Red



    Serial.println("ShoutRoutine");
    //delay(10);
  } else if (PIDWorking()) {
    //purple
    Serial.println("PID Working");

    color(238, 130, 238);
  } else if (PIDLockedOn()) {

    Serial.println("Locked on");

    green();
  } else if (PIDFail()) {
    Serial.println("PID Fail");
    red();
  } else if (GearIntake()) {
    //orange
    Serial.println("Gear Intake");

    color(255, 40, 0);
  } else if (Climbing()) {
    Serial.println("Climbing");
    chase(strip.Color(255, 0, 0)); // Red
    chase(strip.Color(0, 255, 0)); // Green
    chase(strip.Color(0, 0, 255)); // Blue
  } else if (DisabledRoutine()) {
    Serial.println("Disabled Routine");

    theaterChase(strip.Color(255, 0, 0), 45); // Red
  } else {
    Serial.println("Default");

    theaterChase(strip.Color(255, 0, 0), 45); // Red
  }
}

// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
uint32_t Wheel(byte WheelPos) {
  WheelPos = 255 - WheelPos;
  if (WheelPos < 85) {
    return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  }
  if (WheelPos < 170) {
    WheelPos -= 85;
    return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
  WheelPos -= 170;
  return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
}

void rainbowCycle(uint8_t wait) {
  uint16_t i, j;

  for (j = 0; j < 256; j++) { // 5 cycles of all colors on wheel
    for (i = 0; i < strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel(((i * 256 / strip.numPixels()) + j) & 255));
    }
    strip.show();
    delay(wait);
  }
}


//Theatre-style crawling lights.
void theaterChase(uint32_t c, uint8_t wait) {
  for (int j = 0; j < 5; j++) { //do 10 cycles of chasing
    for (int q = 0; q < 3; q++) {
      for (uint16_t i = 0; i < strip.numPixels(); i = i + 3) {
        strip.setPixelColor(i + q, c);  //turn every third pixel on
      }
      strip.show();

      delay(wait);

      for (uint16_t i = 0; i < strip.numPixels(); i = i + 3) {
        strip.setPixelColor(i + q, 0);      //turn every third pixel off
      }
    }
  }
}
void color (int red, int green, int blue) {
  for (int i = 0; i < NUM_LEDS; i++) {
    strip.setPixelColor(i, strip.Color(red, green, blue));
    strip.show();
    //delay(100);
  }
}

void blue () {
  for (int i = 0; i < NUM_LEDS; i++) {
    strip.setPixelColor(i, strip.Color(0, 0, 255));
    strip.show();
    //delay(100);
  }
}
void red () {
  for (int i = 0; i < NUM_LEDS; i++) {
    strip.setPixelColor(i, strip.Color(255, 0, 0));
    strip.show();
    //delay(100);
  }
}

void green () {
  for (int i = 0; i < NUM_LEDS; i++) {
    strip.setPixelColor(i, strip.Color(0, 255, 0));
    strip.show();
    //delay(100);
  }
}
bool DisabledRoutine() {
  return ((digitalRead(in_1) == LOW) && (digitalRead(in_2) == LOW) && (digitalRead(in_3) == LOW) && (digitalRead(in_4) == LOW));

}

bool EnabledRoutine() {
  return ((digitalRead(in_1) == HIGH) && (digitalRead(in_2) == LOW) && (digitalRead(in_3) == LOW) && (digitalRead(in_4) == LOW));

}

bool ShoutRoutine() {
  return ((digitalRead(in_1) == HIGH) && (digitalRead(in_2) == HIGH) && (digitalRead(in_3) == LOW) && (digitalRead(in_4) == HIGH));

}

bool PIDFail() {
  return ((digitalRead(in_1) == HIGH) && (digitalRead(in_2) == LOW) && (digitalRead(in_3) == HIGH) && (digitalRead(in_4) == LOW));

}
bool PIDWorking() {
  return ((digitalRead(in_1) == HIGH) && (digitalRead(in_2) == LOW) && (digitalRead(in_3) == LOW) && (digitalRead(in_4) == HIGH));

}
bool PIDLockedOn() {
  return ((digitalRead(in_1) == HIGH) && (digitalRead(in_2) == LOW) && (digitalRead(in_3) == HIGH) && (digitalRead(in_4) == HIGH));

}
bool GearIntake() {
  return ((digitalRead(in_1) == LOW) && (digitalRead(in_2) == HIGH) && (digitalRead(in_3) == HIGH) && (digitalRead(in_4) == LOW));

}
bool Climbing() {
  return ((digitalRead(in_1) == LOW) && (digitalRead(in_2) == HIGH) && (digitalRead(in_3) == HIGH) && (digitalRead(in_4) == HIGH));

}

static void chase(uint32_t c) {
  for (uint16_t i = 0; i < strip.numPixels() + 4; i++) {
    strip.setPixelColor(i  , c); // Draw new pixel
    strip.setPixelColor(i - 4, 0); // Erase pixel a few steps back
    strip.show();
    delay(10);
  }
}



