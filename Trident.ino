#include "FastLED.h"


#define NUM_LEDS_BOTTOM 59
#define NUM_LEDS_TOP 29
#define NUM_LEDS_PRONGS 18
#define NUM_LEDS (NUM_LEDS_BOTTOM + NUM_LEDS_TOP)
#define BUFFER_END 8
#define ARRAY_SIZE (BUFFER_END + NUM_LEDS + BUFFER_END)

// For led chips like Neopixels, which have a data line, ground, and power, you just
// need to define DATA_PIN.  For led chipsets that are SPI based (four wires - data, clock,
// ground, and power), like the LPD8806 define both DATA_PIN and CLOCK_PIN
#define DATA_PIN A3

// Define the array of leds
CRGB leds[ARRAY_SIZE];

CRGB wheel(byte WheelPos) {
	CRGB colour;
	
	if(WheelPos < 85) {
		colour = CRGB(255 - WheelPos * 3, WheelPos * 3, 0);
	} else if(WheelPos < 170) {
		WheelPos -= 85;
		colour = CRGB(0, 255 - WheelPos * 3, WheelPos * 3);
	} else {
		WheelPos -= 170;
		colour = CRGB(WheelPos * 3, 0, 255 - WheelPos * 3);
	}
	
	return colour;
}

void setup() { 
  FastLED.addLeds<NEOPIXEL, DATA_PIN>(&leds[BUFFER_END], NUM_LEDS);
  pinMode(A1, INPUT_PULLUP);
}

void FalshAll(bool changeColour) {
  byte colourVal = random(255);

  byte iterations = random(20, 30);
  for(int i = 0; i < iterations; i++) {
    CRGB colour = wheel(colourVal).fadeToBlackBy(253);
    for(int j = BUFFER_END; j < BUFFER_END + NUM_LEDS; j++) {
      leds[j] = colour;
    } 
    FastLED.show();
    delay(random(10, 200));

    for(int j = BUFFER_END; j < BUFFER_END + NUM_LEDS; j++) {
      leds[j] = CRGB::Black;
    } 
    FastLED.show();
    delay(random(10, 200));
    
    if (changeColour) colourVal = random(255);
  }
}

void FalshProngs(bool changeColour) {
  byte colourVal = random(255);

  for(int j = 0; j < ARRAY_SIZE; j++) {
    leds[j] = CRGB::Black;
  }

  byte iterations = random(20, 30);
  for(int i = 0; i < iterations; i++) {
    CRGB colour = wheel(colourVal).fadeToBlackBy(200);
    for(int j = BUFFER_END + NUM_LEDS - NUM_LEDS_PRONGS; j < BUFFER_END + NUM_LEDS; j++) {
      leds[j] = colour;
    } 
    FastLED.show();
    delay(random(10, 200));

    for(int j = BUFFER_END + NUM_LEDS - NUM_LEDS_PRONGS; j < BUFFER_END + NUM_LEDS; j++) {
      leds[j] = CRGB::Black;
    } 
    FastLED.show();
    delay(random(10, 200));
    
    if (changeColour) colourVal = random(255);
  }
}

byte topToBottom(bool changeColour, int speed, byte colourVal=random(255)) {
  for(int i = BUFFER_END + NUM_LEDS - 1; i >= 0; i--) {
    for(int j=0; j < BUFFER_END + NUM_LEDS; j++) {
      leds[j] = CRGB::Black;
    }

    CRGB colour = wheel(colourVal);
    leds[i] = CRGB(colour).fadeToBlackBy(240);
    leds[i+1] = CRGB(colour).fadeToBlackBy(224);
    leds[i+2] = CRGB(colour).fadeToBlackBy(180);
    leds[i+3] = CRGB(colour).fadeToBlackBy(128);
    leds[i+4] = colour;
    leds[i+5] = CRGB(colour).fadeToBlackBy(128);
    leds[i+6] = CRGB(colour).fadeToBlackBy(180);
    leds[i+7] = CRGB(colour).fadeToBlackBy(224);
    leds[i+8] = CRGB(colour).fadeToBlackBy(240);
    FastLED.show();
    
    delay(2);
    
    if (changeColour) colourVal++;
  }
  return colourVal;
}

byte bottomToTop(bool changeColour, int speed, byte colourVal=random(255)) {
  for(int i = 0; i < BUFFER_END + NUM_LEDS; i++) {
    for(int j=0; j < BUFFER_END + NUM_LEDS; j++) {
      leds[j] = CRGB::Black;
    }

    CRGB colour = wheel(colourVal);
    leds[i] = CRGB(colour).fadeToBlackBy(240);
    leds[i+1] = CRGB(colour).fadeToBlackBy(224);
    leds[i+2] = CRGB(colour).fadeToBlackBy(180);
    leds[i+3] = CRGB(colour).fadeToBlackBy(128);
    leds[i+4] = colour;
    leds[i+5] = CRGB(colour).fadeToBlackBy(128);
    leds[i+6] = CRGB(colour).fadeToBlackBy(180);
    leds[i+7] = CRGB(colour).fadeToBlackBy(224);
    leds[i+8] = CRGB(colour).fadeToBlackBy(240);
    FastLED.show();
    
    delay(2);
    
    if (changeColour) colourVal++;
  }
  return colourVal;
}

void setBottom(byte idx, CRGB& colour) {
  if (idx < BUFFER_END + NUM_LEDS_BOTTOM) {
    leds[idx] = colour;
  }
}

void setTop(byte idx, CRGB& colour) {
  if (idx >= BUFFER_END + NUM_LEDS_BOTTOM && idx < ARRAY_SIZE) {
    leds[idx] = colour;
  }
}

byte middleToOut(bool changeColour, int speed, byte colourVal=random(255)) {
  for(int i = 0; i < BUFFER_END + NUM_LEDS_BOTTOM; i++) {
    for(int j=0; j < BUFFER_END + NUM_LEDS; j++) {
      leds[j] = CRGB::Black;
    }

    CRGB colour = wheel(colourVal);
    byte bottomIdx = BUFFER_END + NUM_LEDS_BOTTOM - i - 1;
    setBottom(bottomIdx, colour);
    setBottom(bottomIdx+1, CRGB(colour).fadeToBlackBy(180));
    setBottom(bottomIdx+2, CRGB(colour).fadeToBlackBy(200));
    setBottom(bottomIdx+3, CRGB(colour).fadeToBlackBy(220));
    setBottom(bottomIdx+4, CRGB(colour).fadeToBlackBy(240));
    setBottom(bottomIdx+5, CRGB(colour).fadeToBlackBy(245));
    setBottom(bottomIdx+6, CRGB(colour).fadeToBlackBy(250));

    byte topIdx = BUFFER_END + NUM_LEDS_BOTTOM + i;
    setTop(topIdx, colour);
    setTop(topIdx-1, CRGB(colour).fadeToBlackBy(180));
    setTop(topIdx-2, CRGB(colour).fadeToBlackBy(200));
    setTop(topIdx-3, CRGB(colour).fadeToBlackBy(220));
    setTop(topIdx-4, CRGB(colour).fadeToBlackBy(240));
    setTop(topIdx-5, CRGB(colour).fadeToBlackBy(245));
    setTop(topIdx-6, CRGB(colour).fadeToBlackBy(250));
    FastLED.show();
    
    delay(10);
    
    if (changeColour) colourVal++;
  }
  return colourVal;
}

byte outToMiddle(bool changeColour, int speed, byte colourVal=random(255)) {
  for(int i = BUFFER_END + NUM_LEDS_BOTTOM - 1; i >= 0; i--) {
    for(int j=0; j < BUFFER_END + NUM_LEDS; j++) {
      leds[j] = CRGB::Black;
    }

    CRGB colour = wheel(colourVal);
    byte bottomIdx = BUFFER_END + NUM_LEDS_BOTTOM - i - 1;
    setBottom(bottomIdx+6, colour);
    setBottom(bottomIdx+5, CRGB(colour).fadeToBlackBy(180));
    setBottom(bottomIdx+4, CRGB(colour).fadeToBlackBy(200));
    setBottom(bottomIdx+3, CRGB(colour).fadeToBlackBy(220));
    setBottom(bottomIdx+2, CRGB(colour).fadeToBlackBy(240));
    setBottom(bottomIdx+1, CRGB(colour).fadeToBlackBy(245));
    setBottom(bottomIdx, CRGB(colour).fadeToBlackBy(250));

    byte topIdx = BUFFER_END + NUM_LEDS_BOTTOM + i;
    setTop(topIdx-6, colour);
    setTop(topIdx-5, CRGB(colour).fadeToBlackBy(180));
    setTop(topIdx-4, CRGB(colour).fadeToBlackBy(200));
    setTop(topIdx-3, CRGB(colour).fadeToBlackBy(220));
    setTop(topIdx-2, CRGB(colour).fadeToBlackBy(240));
    setTop(topIdx-1, CRGB(colour).fadeToBlackBy(245));
    setTop(topIdx, CRGB(colour).fadeToBlackBy(250));
    FastLED.show();
    
    delay(10);
    
    if (changeColour) colourVal++;
  }
  return colourVal;
}

void loop() {
  if (digitalRead(A1) == LOW) {
    int speed = random(0, 10);
    bool changeColour = random(4) == 0;
    byte colourVal;
    switch(random(10)) {
      case 0:
        FalshProngs(changeColour);
        break;
      case 1:
        FalshAll(changeColour);
        break;
      case 2:
        bottomToTop(changeColour, speed);
        break;
      case 3:
        topToBottom(changeColour, speed);
        break;
      case 4:
        middleToOut(changeColour, speed);
        break;
      case 5:
        outToMiddle(changeColour, speed);
        break;
      case 6:
        colourVal = topToBottom(changeColour, speed);
        bottomToTop(changeColour, speed, colourVal);
        break;
      case 7:
        colourVal = topToBottom(changeColour, speed);
        bottomToTop(changeColour, speed, colourVal);
        break;
      case 8:
        colourVal = middleToOut(changeColour, speed);
        outToMiddle(changeColour, speed, colourVal);
        break;
      case 9:
        colourVal = outToMiddle(changeColour, speed);
        middleToOut(changeColour, speed, colourVal);
        break;
    }
  }

  for(int j=0; j < BUFFER_END + NUM_LEDS; j++) {
    leds[j] = CRGB::Black;
  }
  FastLED.show();
}
