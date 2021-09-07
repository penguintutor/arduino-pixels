

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

// turns all LEDs on based on colors in colors array
// flashes alternate between on and off
// reverse option sets colors from right to left instead of left to right
int flash(int seq_position, bool reverse, uint32_t colors[], int num_colors) {
  if (seq_position != 0) {
    for(int i=0; i<strip.numPixels(); i++) { // For each pixel in strip
      strip.setPixelColor(i, strip.Color(0,0,0));
    }
  }
  else if (reverse == false) {
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
  return 1 - seq_position;               // return 0 or 1
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


/* This is not currently used - same as chaserChangeColor if you only select one color */
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


// chaser using only a single color at a time
// show 4 LEDs on, followed by 4 LEDs off
// Note if the number of pixels is divisible by 8 then change on single block
// otherwise may change in a block of colors
int chaserChangeColor(int seq_position, bool reverse, uint32_t colors[], int num_colors) {
  int current_color = seq_position / strip.numPixels();
  for (int i=0; i<strip.numPixels(); i++) {
    if ((i%8 >= seq_position%8 && i%8 < seq_position%8 +4) || (i%8 >= seq_position%8 -7 && i%8 <= seq_position%8 -5)) {
      int pixel_color;
      if (i < seq_position - (strip.numPixels()* current_color)) {
        pixel_color = current_color +1;
        if (pixel_color >= num_colors) pixel_color = 0;
      }
      else pixel_color = current_color;
      strip.setPixelColor(i, colors[pixel_color]);

    }
    else {
      strip.setPixelColor(i, strip.Color(0,0,0));

    }
  }
  strip.show();
  if (reverse == true) {
    seq_position --;
    if (seq_position < 0) {
      seq_position = (num_colors*strip.numPixels())-1;
    }
  }
  else {
    seq_position ++;
    if (seq_position >= num_colors*strip.numPixels()) seq_position = 0;
  }
  return seq_position;
}

// chaser with black background
// If multiple colours then a single block of colours goes across the strip
// If single color selected then show 4 LEDs on, followed by 4 LEDs off
int chaserBackground(int seq_position, bool reverse, uint32_t colors[], int num_colors) {
  // create a separate array for colors if only single color selected
  // this simplifies remaining code
  uint32_t *chase_colors = colors;
  uint32_t new_colors[4] = {colors[0],colors[0],colors[0],colors[0]};
  if (num_colors < 2) {
    chase_colors = new_colors;
    num_colors = 4;
  }
  // now just use chase_colors and it will either use original colors or be 4 x colors[0]

  // pixel_color set this for this pixel
  uint32_t pixel_color = -1;
  for (int i=0; i<strip.numPixels(); i++) {
    // if seq position before this pixel
    if ((i >= seq_position && i < seq_position + num_colors )) {
      pixel_color = chase_colors[i - seq_position];
    }
    // if wrap around
    else if (i < seq_position-strip.numPixels()+num_colors) {
      pixel_color = chase_colors[strip.numPixels() - seq_position + i];
    }
    // otherwise background
    else {
      pixel_color = strip.Color(0,0,0);
    }
    strip.setPixelColor(i, pixel_color);

  }
  strip.show();
  if (reverse == true) {
    seq_position --;
    if (seq_position < 0) {
      seq_position = strip.numPixels()-1;
    }
  }
  else {
    seq_position ++;
    if (seq_position >= strip.numPixels()) seq_position = 0;
  }
  return seq_position;
}


// Single LED chaser to end and then fill up
// If multiple colours then color fills up at end - led gets it's final color
int chaserFillEnd(int seq_position, bool reverse, uint32_t colors[], int num_colors) {

  int working_seq = seq_position; // use to calculate how far in sequence
  int static_leds = 0;            // how many leds from end are static color
  int num_pixels = strip.numPixels();
  int end_pixel = num_pixels;  // current end of pixels (when calculating pixel)

  int current_color = 0;

  int moving_color = 0;   // Set an initial color, but change later
  
  // loop across all static pixels
  while (working_seq >= end_pixel) {
    working_seq -= end_pixel;
    end_pixel --;
    static_leds ++;
  }

  // now have number of leds to light at end (static)
  // and which led to light as moving up 
  // light up the static leds, turn all other LEDs off
  for (int i=0; i<num_pixels; i++) {
    if (i >= num_pixels - static_leds) {
      // if reverse then go from far end instead of nearest
      if (reverse) strip.setPixelColor(num_pixels -i -1, colors[current_color]);
      else strip.setPixelColor(i, colors[current_color]);
    }
    else {
      if (reverse) strip.setPixelColor(num_pixels -i -1, strip.Color(0,0,0));
      else strip.setPixelColor(i, strip.Color(0,0,0));
    }

    // is this the last non-static (if so use for color of moving)
    if (i == num_pixels - static_leds -1) {
      moving_color = current_color;
    }

    // Increment color
    current_color = color_inc (current_color, num_colors, reverse);
    
  }
  

  // set the moving pixel to the determined color
  if (working_seq > 0) {
    if (reverse) strip.setPixelColor(num_pixels - working_seq, colors[moving_color]); 
    else strip.setPixelColor(working_seq-1, colors[moving_color]);
  }

  strip.show();
  if (static_leds >= num_pixels) return 0;
  else return seq_position +1;
}


// From first pixel to last add LED at a time then stay lit
int colorWipeOn(int seq_position, bool reverse, uint32_t colors[], int num_colors) {
  // pixel_color set this for this pixel
  int current_color = 0;
  for (int i=0; i<strip.numPixels(); i++) {
    if ((reverse == false && i <= seq_position )||(reverse == true && i >= strip.numPixels() - seq_position -1)) {
      strip.setPixelColor(i, colors[current_color]);
    }
    // otherwise off
    else {
      strip.setPixelColor(i, strip.Color(0,0,0));
    }
    // increment color regardless so we don't break sequence
    current_color += 1;
    if (current_color >= num_colors) current_color = 0;
  }
  strip.show();


  seq_position ++;
  if (seq_position >= strip.numPixels()) seq_position = strip.numPixels()-1;

  return seq_position;
}

// From all on remove LED at a time then stay off
int colorWipeOff(int seq_position, bool reverse, uint32_t colors[], int num_colors) {

  // pixel_color set this for this pixel
  int current_color = 0;
  for (int i=0; i<strip.numPixels(); i++) {
    if ((reverse == false && i >= seq_position )||(reverse == true && i <= strip.numPixels() - seq_position -1)) {
      strip.setPixelColor(i, colors[current_color]);
    }
    // otherwise off
    else {
      strip.setPixelColor(i, strip.Color(0,0,0));
    }
    // increment color regardless so we don't break sequence
    current_color += 1;
    if (current_color >= num_colors) current_color = 0;

  }
  strip.show();

  seq_position ++;
  if (seq_position >= strip.numPixels()) seq_position = strip.numPixels();
  return seq_position;
}


// turn all on one at a time, then all off again
int colorWipeOnOff(int seq_position, bool reverse, uint32_t colors[], int num_colors) {
  // works by having seq_position 0 to 2 x number pixels
  // if < number pixels then turn on, if > then turn off
  if (seq_position < strip.numPixels()) {
    colorWipeOn (seq_position, reverse, colors, num_colors);
  }
  else {
    colorWipeOff (seq_position - strip.numPixels(), reverse, colors, num_colors);
  }
  seq_position ++;
  if (seq_position > (strip.numPixels()*2)-1) seq_position = 0;
  return seq_position;
  
}





// Helper function to increment or decrement color based on reverse = true / false
int color_inc (int current_color, int num_colors, bool reverse) {
  if (reverse == false) {
    current_color ++;
    if (current_color >= num_colors) current_color = 0;
  }
  else {
    current_color --;
    if (current_color < 0) current_color = num_colors -1;
  }
  return current_color;
}


// From outside going inwards (both ends)
// Color applies equally from both ends
// goes from sequence 0 (none on) until 
//     sequence = (num_pixels/2)+1 if even
//     sequence = (num_pixels/2)+2 if odd 
int colorWipeInOn(int seq_position, bool reverse, uint32_t colors[], int num_colors) {

  int num_pixels = strip.numPixels(); // avoid multiple function calls and simplify code
  // index of the last pixel
  int pixel_last_pair = (num_pixels/2) - 1; // If odd number of pixels then we have one more after this value
  int current_color = 0;
  // if reverse then we need color based on center
  if (reverse) {
    current_color = (num_pixels/2) % num_colors;
    // if even subtract 1
    if (num_pixels % 2 == 0) current_color --;
    if (current_color < 0) current_color = num_colors -1;
  }
  for (int i=0; i<=pixel_last_pair; i++) {
    if (i<seq_position-1) {
      strip.setPixelColor(i, colors[current_color]);
      strip.setPixelColor(num_pixels-1-i, colors[current_color]);
    }
    else {
      strip.setPixelColor(i, strip.Color(0,0,0));
      strip.setPixelColor(num_pixels-1-i, strip.Color(0,0,0));
    }
    // Increment color
    current_color = color_inc (current_color, num_colors, reverse);
  }
  // if odd number pixels then we have one more
  if (num_pixels %2 == 1) {
    if (pixel_last_pair+1 < seq_position-1) {
      strip.setPixelColor(pixel_last_pair+1, colors[current_color]);
    }
    else {
      strip.setPixelColor(pixel_last_pair+1, strip.Color(0,0,0));
    }
  }
  strip.show();
  // only increment sequence if we are not at end
  // if even
  if (num_pixels %2 == 0 && seq_position <= pixel_last_pair + 1) seq_position ++;
  // if odd
  else if (num_pixels %2 == 1 && seq_position <= pixel_last_pair + 2) seq_position ++;
  return seq_position;
}

// From inside going outwards (both ends)
// Color applies equally from both ends
// goes from sequence 0 (none on) until 
//     sequence = (num_pixels/2)+1 if even
//     sequence = (num_pixels/2)+2 if odd 
int colorWipeOutOn(int seq_position, bool reverse, uint32_t colors[], int num_colors) {
  int num_pixels = strip.numPixels(); // avoid multiple function calls and simplify code
  // index of the last pixel
  int pixel_last_pair = (num_pixels/2) - 1; // If odd number of pixels then we have one more after this value
  int current_color = 0;
  // if reverse then we need color based on center
  if (reverse) {
    current_color = (num_pixels/2) % num_colors;
    // if even subtract 1
    if (num_pixels % 2 == 0) current_color --;
    if (current_color < 0) current_color = num_colors -1;
  }
  for (int i=0; i<=pixel_last_pair; i++) {
    if (i>= pixel_last_pair - seq_position +1) {
      strip.setPixelColor(i, colors[current_color]);
      strip.setPixelColor(num_pixels-1-i, colors[current_color]);
    }
    else {
      strip.setPixelColor(i, strip.Color(0,0,0));
      strip.setPixelColor(num_pixels-1-i, strip.Color(0,0,0));
    }
    // Increment color
    current_color = color_inc (current_color, num_colors, reverse);
  }
  // if odd number pixels then we have one more
  if (num_pixels %2 == 1) {
    if (pixel_last_pair+1 >= pixel_last_pair - seq_position +1) {
      strip.setPixelColor(pixel_last_pair+1, colors[current_color]);
    }
    else {
      strip.setPixelColor(pixel_last_pair+1, strip.Color(0,0,0));
    }
  }
  strip.show();
  // only increment sequence if we are not at end
  // if even
  if (num_pixels %2 == 0 && seq_position <= pixel_last_pair + 1) seq_position ++;
  // if odd
  else if (num_pixels %2 == 1 && seq_position <= pixel_last_pair + 2) seq_position ++;
  return seq_position;
}



// From outside going inwards (both ends) turning off
// Color applies equally from both ends
// goes from sequence 0 (all on) until 
//     sequence = (num_pixels/2)+1 if even
//     sequence = (num_pixels/2)+2 if odd 
int colorWipeInOff(int seq_position, bool reverse, uint32_t colors[], int num_colors) {
  int num_pixels = strip.numPixels(); // avoid multiple function calls and simplify code
  // index of the last pixel
  int pixel_last_pair = (num_pixels/2) - 1; // If odd number of pixels then we have one more after this value
  int current_color = 0;
  // if reverse then we need color based on center
  if (reverse) {
    current_color = (num_pixels/2) % num_colors;
    // if even subtract 1
    if (num_pixels % 2 == 0) current_color --;
    if (current_color < 0) current_color = num_colors -1;
  }
  for (int i=0; i<=pixel_last_pair; i++) {
    if (i>= seq_position) {
      strip.setPixelColor(i, colors[current_color]);
      strip.setPixelColor(num_pixels-1-i, colors[current_color]);
      //Serial.print (i);
    }
    else {
      strip.setPixelColor(i, strip.Color(0,0,0));
      strip.setPixelColor(num_pixels-1-i, strip.Color(0,0,0));
      //Serial.print (".");
    }
    // Increment color
    current_color = color_inc (current_color, num_colors, reverse);
  }
  // if odd number pixels then we have one more
  if (num_pixels %2 == 1) {
    if (pixel_last_pair+1 >= seq_position) {
      strip.setPixelColor(pixel_last_pair+1, colors[current_color]);
    }
    else {
      strip.setPixelColor(pixel_last_pair+1, strip.Color(0,0,0));
    }
  }
  strip.show();
  // only increment sequence if we are not at end
  // if even
  if (num_pixels %2 == 0 && seq_position <= pixel_last_pair + 1) seq_position ++;
  // if odd
  else if (num_pixels %2 == 1 && seq_position <= pixel_last_pair + 2) seq_position ++;
  return seq_position;
}


// From inwards going outwards (both ends) turning off
// Color applies equally from both ends
// goes from sequence 0 (all on) until 
//     sequence = (num_pixels/2)+1 if even
//     sequence = (num_pixels/2)+2 if odd 
int colorWipeOutOff(int seq_position, bool reverse, uint32_t colors[], int num_colors) {
  int num_pixels = strip.numPixels(); // avoid multiple function calls and simplify code
  // index of the last pixel
  int pixel_last_pair = (num_pixels/2) - 1; // If odd number of pixels then we have one more after this value
  int current_color = 0;
  // if reverse then we need color based on center
  if (reverse) {
    current_color = (num_pixels/2) % num_colors;
    // if even subtract 1
    if (num_pixels % 2 == 0) current_color --;
    if (current_color < 0) current_color = num_colors -1;
  }
  for (int i=0; i<=pixel_last_pair; i++) {
    if (i<= pixel_last_pair - seq_position +1) {
      strip.setPixelColor(i, colors[current_color]);
      strip.setPixelColor(num_pixels-1-i, colors[current_color]);
      //Serial.print (i);
    }
    else {
      strip.setPixelColor(i, strip.Color(0,0,0));
      strip.setPixelColor(num_pixels-1-i, strip.Color(0,0,0));
      //Serial.print (".");
    }
    // Increment color
    current_color = color_inc (current_color, num_colors, reverse);
  }
  // if odd number pixels then we have one more
  if (num_pixels %2 == 1) {
    if (pixel_last_pair+1 <= pixel_last_pair - seq_position +1) {
      strip.setPixelColor(pixel_last_pair+1, colors[current_color]);
    }
    else {
      strip.setPixelColor(pixel_last_pair+1, strip.Color(0,0,0));
    }
  }
  strip.show();
  // only increment sequence if we are not at end
  // if even
  if (num_pixels %2 == 0 && seq_position <= pixel_last_pair + 1) seq_position ++;
  // if odd
  else if (num_pixels %2 == 1 && seq_position <= pixel_last_pair + 2) seq_position ++;
  return seq_position;
}



// colorWipeInOut
//Turn on in sequence going inwards, then out again. Starting at both ends.
int colorWipeInOut(int seq_position, bool reverse, uint32_t colors[], int num_colors) {
  // set seq_count to the number of steps in each sequence
  int seq_count = (strip.numPixels()/2) + 1;
  // if odd then add one more
  if (strip.numPixels() % 2 == 1) seq_count++;

  if (seq_position <= seq_count) {
    colorWipeInOn (seq_position, reverse, colors, num_colors);
  }
  else {
    colorWipeOutOff (seq_position-seq_count, reverse, colors, num_colors);
  }

  seq_position ++;
  if (seq_position > (seq_count * 2)) seq_position = 0;
  return seq_position;
}


// colorWipeOutIn
//Turn on in sequence going outwards, then in again. Starting at both ends.
int colorWipeOutIn(int seq_position, bool reverse, uint32_t colors[], int num_colors) {
  // set seq_count to the number of steps in each sequence
  int seq_count = (strip.numPixels()/2) + 1;
  // if odd then add one more
  if (strip.numPixels() % 2 == 1) seq_count++;

  if (seq_position <= seq_count) {
    colorWipeOutOn (seq_position, reverse, colors, num_colors);
  }
  else {
    colorWipeInOff (seq_position-seq_count, reverse, colors, num_colors);
  }

  seq_position ++;
  if (seq_position > (seq_count * 2)) seq_position = 0;
  return seq_position;
}
