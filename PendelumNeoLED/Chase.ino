// Theatre-style crawling lights with a spacing of 3
void theaterChase(uint32_t color, uint8_t wait) {
  for (int j=0; j<10; j++) {  //do 10 cycles of chasing
    for (int q=0; q < 4; q++) {
      for (int i=0; i < numLeds; i=i+4) {
        strip.setPixelColor(q+i, color);    //turn every third pixel on
      }
      strip.show();
      delay(wait);
      for (int i=0; i < numLeds; i=i+3) {
        strip.setPixelColor(q+i, 0);        //turn every third pixel off
      }
    }
  }
}
