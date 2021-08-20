

// turns all LEDs on based on colors in colors array
// reverse option sets colors from right to left instead of left to right
int allOn(int seq_position, bool reverse, uint32_t colors[], int num_colors) {
  if (reverse == false) {
    int color_pos = 0;
    for(int i=0; i<strip.numPixels(); i++) { // For each pixel in strip
      // do we have a new color? if not then reset to position 0 and start again
      if (color_pos >= num_colors) {
        color_pos = 0;
      }
      strip.setPixelColor(i, colors[color_pos]);
      color_pos ++;
    }
  }
  else {
    int color_pos = num_colors-1;
    for(int i=0; i<strip.numPixels(); i++) { // For each pixel in strip
      // do we have a new color? if not then reset to position 0 and start again
      if (color_pos < 0) {
        color_pos = num_colors-1;
      }
      strip.setPixelColor(i, colors[color_pos]);
      color_pos --;
    }
  }
  strip.show();                          //  Update strip
  return seq_position;                   //  Seq position not relevant for this so return current
}

int allOff(int seq_position, bool reverse, uint32_t colors[], int num_colors) {
  for(int i=0; i<strip.numPixels(); i++) { // For each pixel in strip...
    // colors array is ignored - set to black
    strip.setPixelColor(i, strip.Color(0,0,0));
    strip.show();                          //  Update strip
  }
  return seq_position;                   //  Seq position not relevant for this so return current
}

// Chaser - moves LEDs to left or right
// Only uses colours specified unless only one color in which case use second as black
// Colors in order passed to it (starting from first pixel)
// forward direction is moving away from first pixel
// reverse direction moves towards first pixel
int chaser(int seq_position, bool reverse, uint32_t colors[], int num_colors) {
  // special case if only one color then pretend we have two (next color will always be black)
  if (num_colors == 1){
    num_colors = 2;
  }

  // seq_position indicates where to start in colors array
  int current_color = seq_position;
  for (int i=0; i<strip.numPixels(); i++) {
    // if past last color then reset to 0
    if (current_color >= num_colors) current_color = 0;
    strip.setPixelColor(i, colors[current_color]);
    current_color++;
  }
  strip.show();                          //  Update strip
  // set seq_position based on whether reverse direction or forward
  if (reverse == false) {
    seq_position --;
    if (seq_position < 0) {
      seq_position = num_colors-1;
    }
  }
  else {
    seq_position ++;
    if (seq_position >= num_colors) seq_position = 0;
  }
  return seq_position;
}


// chaser using only a single color
// show 4 LEDs on, followed by 4 LEDs off
int chaserSingleColor(int seq_position, bool reverse, uint32_t colors[], int num_colors) {
  for (int i=0; i<strip.numPixels(); i++) {
    if ((i%8 >= seq_position && i%8 < seq_position +4) || (i%8 >= seq_position -7 && i%8 <= seq_position -5)) {
      strip.setPixelColor(i, colors[0]);
    }
    else {
      strip.setPixelColor(i, strip.Color(0,0,0));
    }
  }
  strip.show();
  if (reverse == true) {
    seq_position --;
    if (seq_position < 0) {
      seq_position = 7;
    }
  }
  else {
    seq_position ++;
    if (seq_position >= 8) seq_position = 0;
  }
  return seq_position;
}
