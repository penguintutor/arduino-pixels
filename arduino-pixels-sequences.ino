

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
//  Serial.println("");
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


// From outside going inwards (both ends)
// Color applies equally from both ends
// reverse - reverses color order
int colorWipeInOn(int seq_position, bool reverse, uint32_t colors[], int num_colors) {
  // pixel_color set this for this pixel
  int current_color = 0;
  int num_pixels = strip.numPixels();           // reduce function calls by saving value in variable
  if (reverse) current_color = num_colors-1;
  int i;
  for (i=0; i<num_pixels/2; i++) {
    if (i <= seq_position ) {
      strip.setPixelColor(i, colors[current_color]);
      strip.setPixelColor(num_pixels-1-i, colors[current_color]);
    }
    // otherwise off
    else {
      strip.setPixelColor(i, strip.Color(0,0,0));
      strip.setPixelColor(num_pixels-1-i, strip.Color(0,0,0));
    }
    // increment color
    if (reverse == false){
      current_color ++;
      if (current_color >= num_colors) current_color = 0;
    }
    else {
      current_color --; 
      if (current_color < 0) current_color = num_colors -1;
    }
  }

  // if we have an odd number of pixels then handle odd one afterwards
  if (strip.numPixels() % 2 == 1) {
    if (i <= seq_position ) {
      strip.setPixelColor(i, colors[current_color]);
    }
  }
  
  strip.show();
  
  seq_position ++;
  // stop when reach end
  if (seq_position >= num_pixels/2 + 1) seq_position = num_pixels/2 + 1;

  return seq_position;
}


// From outside going inwards (both ends) turning off
// Color applies equally from both ends
// reverse - reverses color order
int colorWipeInOff(int seq_position, bool reverse, uint32_t colors[], int num_colors) {
  // pixel_color set this for this pixel
  int current_color = 0;
  int num_pixels = strip.numPixels();           // reduce function calls by saving value in variable
  if (reverse) current_color = num_colors-1;
  for (int i=0; i<num_pixels/2; i++) {
    if (i >= seq_position ) {
      strip.setPixelColor(i, colors[current_color]);
      strip.setPixelColor(num_pixels-1-i, colors[current_color]);
    }
    // otherwise off
    else {
      strip.setPixelColor(i, strip.Color(0,0,0));
      strip.setPixelColor(num_pixels-1-i, strip.Color(0,0,0));
    }
    // increment color
    if (reverse == false){
      current_color ++;
      if (current_color >= num_colors) current_color = 0;
    }
    else {
      current_color --; 
      if (current_color < 0) current_color = num_colors -1;
    }
  }
  strip.show();
  
  seq_position ++;
  // stop when reach end
  if (seq_position >= num_pixels/2) seq_position = num_pixels/2;

  return seq_position;
}


// From inside going outwards (both ends)
// Color applies equally from both ends
// reverse - reverses color order
int colorWipeOutOn(int seq_position, bool reverse, uint32_t colors[], int num_colors) {
  // pixel_color set this for this pixel
  // use modulo against center of strip
  int current_color = (strip.numPixels()/2) % num_colors;
  if (reverse) current_color = num_colors-1-((strip.numPixels()/2) % num_colors);
  // if it's an odd number of pixels then 0 is only one pixel
  if (strip.numPixels() % 2 == 1) {
    // Todo 
  }
  for (int i=0; i<=strip.numPixels()/2; i++) {
    if (i <= seq_position ) {
      strip.setPixelColor(strip.numPixels()/2 - i, colors[current_color]);
      strip.setPixelColor(strip.numPixels()/2  -1 + i, colors[current_color]);
    }
    // otherwise off
    else {
      strip.setPixelColor(strip.numPixels()/2 - i, strip.Color(0,0,0));
      strip.setPixelColor(strip.numPixels()/2 -1 + i, strip.Color(0,0,0));
    }
    // increment color (opposite to in as we go in out)
    if (reverse == true){
      current_color ++;
      if (current_color >= num_colors) current_color = 0;
    }
    else {
      current_color --; 
      if (current_color < 0) current_color = num_colors -1;
    }
  }
   
  strip.show();


  seq_position ++;
  // stop when reach end
  if (seq_position > (strip.numPixels()/2)+1) seq_position = strip.numPixels()/2 + 1;

  return seq_position;
}


// From inside going outwards (both ends)
// Color applies equally from both ends
// reverse - reverses color order
int colorWipeOutOff(int seq_position, bool reverse, uint32_t colors[], int num_colors) {
  // pixel_color set this for this pixel
  // use modulo against center of strip
  int current_color = (strip.numPixels()/2) % num_colors;
  // if odd number of pixels then don't subtract one
  int sub_one = -1;
  if (strip.numPixels() % 2 == 1) sub_one = 0;
  if (reverse) current_color = num_colors-1-((strip.numPixels()/2) % num_colors);
  for (int i=0; i<=strip.numPixels()/2; i++) {
    if (i >= seq_position ) {
      strip.setPixelColor(strip.numPixels()/2 - i, colors[current_color]);
      strip.setPixelColor(strip.numPixels()/2  + sub_one + i, colors[current_color]);
    }
    // otherwise off
    else {
      strip.setPixelColor(strip.numPixels()/2 - i, strip.Color(0,0,0));
      strip.setPixelColor(strip.numPixels()/2 + sub_one + i, strip.Color(0,0,0));
    }
    // increment color (opposite to in as we go in out)
    if (reverse == true){
      current_color ++;
      if (current_color >= num_colors) current_color = 0;
    }
    else {
      current_color --; 
      if (current_color < 0) current_color = num_colors -1;
    }
  }
  strip.show();


  seq_position ++;
  // stop when reach end
  if (seq_position > (strip.numPixels()/2)+1) seq_position = strip.numPixels()/2 + 1;

  return seq_position;
}

// colorWipeInOut
//Turn on in sequence going inwards, then out again. Starting at both ends.
int colorWipeInOut(int seq_position, bool reverse, uint32_t colors[], int num_colors) {
  // works by having seq_position 0 to number pixels
  // if < number pixels/2 then wipe in, if > then wipe out
  if (seq_position <= strip.numPixels()/2) {
    colorWipeInOn (seq_position, reverse, colors, num_colors);
  }
  else {
    colorWipeOutOff (seq_position-(strip.numPixels()/2), reverse, colors, num_colors);
  }

  seq_position ++;
  if (seq_position > (strip.numPixels() + 2)) seq_position = 0;
  return seq_position;
  
}


// colorWipeOutIn
//Turn on in sequence going outwards, then in again. Starting at both ends.
int colorWipeOutIn(int seq_position, bool reverse, uint32_t colors[], int num_colors) {
  // works by having seq_position 0 to number pixels
  // if < number pixels/2 then wipe in, if > then wipe out
  if (seq_position <= strip.numPixels()/2) {
    colorWipeOutOn (seq_position, reverse, colors, num_colors);
  }
  else {
    colorWipeInOff (seq_position-(strip.numPixels()/2), reverse, colors, num_colors);
  }

  seq_position ++;
  if (seq_position > (strip.numPixels() + 2)) seq_position = 0;
  return seq_position;
  
}
