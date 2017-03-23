
//screaming chickens led code simple
#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif

#define PIN 4
#define NUM_LEDS 19
#define BRIGHTNESS 100
int in_1 = 6;
int in_2 = 7;
int in_3 = 8;
int in_4 = 9;

int count = 1;

Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUM_LEDS, PIN, NEO_GRB + NEO_KHZ800);

void setup() {
  Serial.begin(115200);
  pinMode(in_1,INPUT);
  pinMode(in_2,INPUT);
  pinMode(in_3,INPUT);
  pinMode(in_4,INPUT);
  strip.setBrightness(BRIGHTNESS);
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'
}

void loop() {
  Serial.println(digitalRead(in_2));
  if(EnabledRoutine()){
    blue();
  }else if(ShoutRoutine()){
    theaterChase(strip.Color(255, 0, 0), 45); // Red
    //delay(10);
  } else if(PIDWorking()) {
    //purple
    color(238,130,238);
  } else if(PIDLockedOn){
    green();
  } else if(PIDFail()) {
    red();  
  } else if(GearIntake()) {
    //orange
    color(255,127,80);
  } else if(Climbing()) {
    //gold
    color(255,215,0);  
  } else if(DisabledRoutine()) {
    rainbowCycle(1);  
  } else {
    rainbowCycle(1);
  }
}

// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
uint32_t Wheel(byte WheelPos) {
  WheelPos = 255 - WheelPos;
  if(WheelPos < 85) {
    return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  }
  if(WheelPos < 170) {
    WheelPos -= 85;
    return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
  WheelPos -= 170;
  return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
}

void rainbowCycle(uint8_t wait) {
  uint16_t i, j;

  for(j=0; j<256; j++) { // 5 cycles of all colors on wheel
    for(i=0; i< strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel(((i * 256 / strip.numPixels()) + j) & 255));
    }
    strip.show();
    delay(wait);
  }
}


//Theatre-style crawling lights.
void theaterChase(uint32_t c, uint8_t wait) {
  for (int j=0; j<5; j++) {  //do 10 cycles of chasing
    for (int q=0; q < 3; q++) {
      for (uint16_t i=0; i < strip.numPixels(); i=i+3) {
        strip.setPixelColor(i+q, c);    //turn every third pixel on
      }
      strip.show();

      delay(wait);

      for (uint16_t i=0; i < strip.numPixels(); i=i+3) {
        strip.setPixelColor(i+q, 0);        //turn every third pixel off
      }
    }
  }
}
void color (int red, int green, int blue){
  for(int i = 0; i < NUM_LEDS; i++){
     strip.setPixelColor(i, strip.Color(red,green,blue)); 
     strip.show();
     //delay(100);
  }
}

void blue (){
  for(int i = 0; i < NUM_LEDS; i++){
     strip.setPixelColor(i, strip.Color(0,0,255)); 
     strip.show();
     //delay(100);
  }
}
void red (){
  for(int i = 0; i < NUM_LEDS; i++){
     strip.setPixelColor(i, strip.Color(255,0,0)); 
     strip.show();
     //delay(100);
  }
}

void green (){
  for(int i = 0; i < NUM_LEDS; i++){
     strip.setPixelColor(i, strip.Color(0,255,0)); 
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
  return ((digitalRead(in_1) == HIGH) && (digitalRead(in_2) == HIGH) && (digitalRead(in_3) == HIGH) && (digitalRead(in_4) == HIGH));
     
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



