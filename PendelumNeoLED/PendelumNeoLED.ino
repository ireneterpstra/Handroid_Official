#include <Adafruit_NeoPixel.h>

#define PIN 6
const int numLeds = 8;
const int delayTime = 100;

#define NUMBER_OF_FLAMES 5 // depends on number of neopixel triplets. 5 for 16 NeoPixel ring. 4 for 12 NeoPixel ring
#define FLAME_WIDTH 3      // How wide are the flames (in LEDs)
#define FLICKER_CHANCE 3 


// Parameter 1 = number of pixels in strip
// Parameter 2 = pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)
Adafruit_NeoPixel strip = Adafruit_NeoPixel(8, PIN, NEO_GRB + NEO_KHZ800);
    

void setup() {
  strip.begin();
  strip.setBrightness(80); // 1/3 brightness

  strip.show(); // Initialize all pixels to 'off'

}

void loop() {
  
//  rainbow(30);
//    
//  delay(10);
//  strip.setPixelColor(249, 45, 9);
//  strip.setPixelColor(249, 133, 9);
//  strip.setPixelColor(249, 229, 9);
//  strip.setPixelColor(3, 249, 9, 109);
//  strip.setPixelColor(4, 249, 9, 109);
//  strip.setPixelColor(5, 249, 9, 109);
//  strip.setPixelColor(6, 249, 9, 109);
//  strip.setPixelColor(7, 249, 9, 109);
//  strip.show();
//  theaterChase(strip.Color(127, 0, 0), delayTime); // red
//  theaterChase(strip.Color(127, 127, 127), delayTime); // white
//  theaterChase(strip.Color(0, 0, 127), delayTime); // blue
  theaterChaseRainbow(20);
  //Fire(55,120,15);

}
