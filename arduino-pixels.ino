
#include <WiFiNINA.h>
#include <Adafruit_NeoPixel.h>
#include "arduino_secrets.h"
#include "sequences.h"
#include "index.html.h"
#include "pixels.css.h"
#include "pixels.js.h"


// Sensitive information in arduino_secrets.h
char ssid[] = SECRET_SSID;        // network SSID (name)
char pass[] = SECRET_PASS;        // network password (use for WPA, or use as key for WEP)
int keyIndex = 0;                 // network key index number (needed only for WEP)

#define LED_PIN 15 // Pin where NeoPixels are connected - Do not use PIN 25 (D2) - possible conflict with WiFi
#define LED_COUNT 45  // How many NeoPixels?

// what level of debug from serial console
// higher number the more debug messages
// recommend level 1 (includes occassional messages)
#define DEBUG 1

int status = WL_IDLE_STATUS;
WiFiServer server(80);

Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);


#define URL_DEFAULT 0
#define URL_HTML 0
#define URL_SEQUENCE 1
#define URL_CSS 2
#define URL_JS 3
#define URL_JSON 4


void setup() {
  Serial.begin(9600);      // initialize serial communication

  WiFi.config({192,168,0,44}, {8,8,8,8}, {192,168,0,1}, {255,255,255,0});

  // check for the WiFi module:
  if (WiFi.status() == WL_NO_MODULE) {
    Serial.println("Communication with WiFi module failed!");
    // don't continue
    while (true);

  }

  /*Unable to update wifi on RP2040 so commented out
   * String fv = WiFi.firmwareVersion();
  if (fv < WIFI_FIRMWARE_LATEST_VERSION) {
    Serial.println("Please upgrade the firmware");

  }*/
  // attempt to connect to WiFi network:
  while (status != WL_CONNECTED) {
    if (DEBUG > 0) Serial.print("Attempting to connect to Network named: ");
    if (DEBUG > 0) Serial.println(ssid);                   // print the network name (SSID);

    // Connect to WPA/WPA2 network. Change this line if using open or WEP network:
    status = WiFi.begin(ssid, pass);
    // wait 10 seconds for connection:
    delay(10000);
  }

  server.begin();                           // start the web server on port 80
  if (DEBUG > 0) printWifiStatus();                        // you're connected now, so print out the status

  // Now setup NeoPixels
  strip.begin();           // INITIALIZE NeoPixel strip object (REQUIRED)
  strip.show();            // Turn OFF all pixels ASAP
  strip.setBrightness(50); // Set BRIGHTNESS to about 1/5 (max = 255)
}

void loop() {

  // What action to perform
  // position in sequences array for selected sequence
  static int action = 0;
  // delay (speed) in ms (default 1 second)
  static int delay_value = 1000;
  // Whether direction reversed
  static bool reverse = false;
  // Number of colour options cannot exceed number of LEDs
  // One more included in array to allow terminating null
  // Must always have at last one color in position 0
  static uint32_t colors[LED_COUNT+1] = {strip.Color(255,255,255)};
  // should always be 1 color
  static int num_colors = 1;

  // Message to send from sequence request
  static String status_msg = "Ready";

  // What page to reply with (it's only after action handled that we return page)
  static int web_req = URL_DEFAULT;


  WiFiClient client = server.available();   // listen for incoming clients

  if (client) {                             // if you get a client,
    if (DEBUG > 1) Serial.println("new client");           // print a message out the serial port
    String currentLine = "";                // make a String to hold incoming data from the client
    while (client.connected()) {            // loop while the client's connected
      if (client.available()) {             // if there's bytes to read from the client,
        char c = client.read();             // read a byte, then
        if (DEBUG > 1) Serial.write(c);                    // print it out the serial monitor
        if (c == '\n') {                    // if the byte is a newline character

          // if the current line is blank, you got two newline characters in a row.
          // that's the end of the client HTTP request, so send a response:
          if (currentLine.length() == 0) {
            if (web_req == URL_SEQUENCE) {
              showStatus(client, status_msg);
              web_req = URL_DEFAULT;
            }
            else if (web_req == URL_CSS) {
              showCSS(client);
              // reset web request
              web_req = URL_DEFAULT;
            }
            else if (web_req == URL_JS) {
              showJS(client);
              web_req = URL_DEFAULT;
            }
            else if (web_req == URL_JSON) {
              showJSON(client);
              web_req = URL_DEFAULT;
            }
            // default return web page
            else {
              showWebPage(client);
            }
            // break out of the while loop:
            break;
          } else {    // if you got a newline, then clear currentLine:
              currentLine = "";
          }
        } else if (c != '\r') {  // if you got anything else but a carriage return character,
          currentLine += c;      // add it to the end of the currentLine
        }

        // temp variables for assessing arguments
        String url_arguments;
        String arg_name;
        String arg_value;

        // Only check for URL if it's a GET <url options> HTTP/ (ignore the http version number)
        if (currentLine.startsWith("GET") && currentLine.endsWith("HTTP/")) {
          String url_string = currentLine.substring(4, currentLine.indexOf(" HTTP/"));
          if (url_string.startsWith("/pixels.css")) {
            if (DEBUG == 1) Serial.println ("Request: /pixels.css");
            web_req = URL_CSS;
          }
          else if (url_string.startsWith("/pixels.js")) {
            if (DEBUG == 1) Serial.println ("Request: /pixels.js");
            web_req = URL_JS;
          }
          else if (url_string.startsWith("/sequences.json")) {
            if (DEBUG == 1) Serial.println ("Request: /sequences.json");
            web_req = URL_JSON;
          }
          // Sequence request
          else if (url_string.startsWith("/set")) {
            if (DEBUG == 1) {
              Serial.print ("Request: ");
              Serial.println (url_string);
            }
            url_arguments = url_string.substring(5);
            // take off each argument 
            while (url_arguments.length() > 0) {
              // get to = 
              // if no = then no more arguments
              if (url_arguments.indexOf("=") < 1) break;
              // strip to = (the name of the argument)
              arg_name = url_arguments.substring(0, url_arguments.indexOf("="));
              url_arguments = url_arguments.substring(url_arguments.indexOf("=")+1);
              // strip to & (if there is another)
              if (url_arguments.indexOf("&") < 1) {
                arg_value = url_arguments;
                //break;
              }
              else {
                arg_value = url_arguments.substring(0, url_arguments.indexOf("&"));
                url_arguments = url_arguments.substring(url_arguments.indexOf("&")+1);}
                // Validate argument
                if (arg_name == "seq") {
                  int seq_value = get_sequence (arg_value);
                  // update action if it's a valid entry (not -1)
                  if (seq_value >=0) action = seq_value;
                }
                else if (arg_name == "delay") {
                    // toInt returns 0 if error so test for that separately
                    if (arg_value == "0") delay_value = 0;
                    else {
                    int delay_val = arg_value.toInt();
                    // check delay_val is valid
                    if (delay_val > 0) delay_value = delay_val;
                    } 
                }
                else if (arg_name == "reverse") {
                  if (arg_value == "0") reverse = false;
                  else if (arg_value == "1") reverse = true;
                }
                else if (arg_name == "colors") {
                   num_colors = read_colors (arg_value, colors);
                   // If no colors then set to default (1 white)
                   // shouldn't get this except on malformed request
                   if (num_colors == 0) {
                    num_colors = read_colors ("ffffff", colors);
                   }
                }
                // Otherwise invalid argument so ignore
                else if (DEBUG > 0) {
                  Serial.print ("Request invalid:");
                  Serial.println (url_string);
                }
            }
            web_req = URL_SEQUENCE;

          }
          else {
            web_req = URL_HTML;
          }
        }

      }
    }
    // close the connection:
    client.stop();
    if (DEBUG > 1) Serial.println("client disconnected");
  }
  updatePixels (action, delay_value, reverse, colors, num_colors);
}

void updatePixels (int new_sequence, int delay_value, bool reverse, uint32_t colors[], int num_colors) {
  static int sequence = new_sequence;
  // seq_position is used by sequence function to determine what it will next do
  // sequence function can manage how it works (eg. count up / count down)
  // will always be reset to 0 when the sequence changes otherwise it's under control of sequence function
  static int seq_position = 0;
  static unsigned long start_time = 0;

  // if change in sequence then reset seq_position
  // sequence is responsible for incrementing seq_position
  if (sequence != new_sequence) {
    seq_position = 0;
    sequence = new_sequence;
    // if change sequence also restart delay timer
    start_time = 0;
  }

  // if delay not reached then return
  // first check is for overflow - just reset start_time (will result in one partial skipped delay every 50 days)
  unsigned long current_time = millis();
  if (current_time > start_time && current_time < start_time + delay_value) return;
  else start_time = current_time;

  // run appropriate sequence based on ptr in sequence structure
  seq_position = sequences[sequence].seqFunction (seq_position, reverse, colors, num_colors);
}

// get sequence from sequences (based on seq_name)
// return index in array
// or -1 if not valid
int get_sequence (String arg_value){
  for (int i=0; i < (sizeof(sequences)/sizeof(sequence)); i++){
    if (sequences[i].seq_name == arg_value) return i;
  }
  // if not found in array search return -1 for not found
  return -1;
}

// reads a string of colors 
// updates the color array passed to it and then returns number of colors 
// any colors beyond num_colors will be set to black (this is important for certain sequences)
int read_colors (String color_string, uint32_t colors[]){
  int num_colors = 0;
  String this_color_string = color_string;
  // reset array to all zeros
  for (int i=0; i<LED_COUNT; i++) {
    colors[i] = strip.Color(0,0,0);
  }
  // work through colors
  for (int i=0; i<LED_COUNT; i++) {
    // not enough characters for a string so return
    if (this_color_string.length()<6) return num_colors;
    // Convert each pair to a rgb value
    int r = h2int (this_color_string[0], this_color_string[1]);
    int g = h2int (this_color_string[2], this_color_string[3]);
    int b = h2int (this_color_string[4], this_color_string[5]);
    // if any are invalid then return
    if (r < 0 || g < 0 || b < 0) return num_colors;
    // store this as a color
    colors[i] = strip.Color(r,g,b);
    num_colors ++;
    // if not enough characters for another color then end
    if (this_color_string.length() < 13) {
      return num_colors;
    }
    // check if there is a comma in which case strip current color and comma and repeat
    if (this_color_string[6] == ',') {
      this_color_string = this_color_string.substring(7);
    }
    
  }
}


int h2int (char high_nibble, char low_nibble) {
  int value=0;
  // if 0 to 9
  if (high_nibble >= 48 && high_nibble <= 57) {
    value += (high_nibble - 48) * 16;
  }
  // if a to f
  else if (high_nibble >= 97 && high_nibble <= 102) {
    value += (high_nibble - 97) * 16;
  }
  else return -1;

  // if 0 to 9
  if (low_nibble >= 48 && low_nibble <= 57) {
    value += (low_nibble - 48) * 16;
  }
  // if a to f
  else if (low_nibble >= 97 && low_nibble <= 102) {
    value += (low_nibble - 97) * 16;
  }
  else return -1;

  return value;
}

void printWifiStatus() {
  // print the SSID of the network you're attached to:
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());

  // print your board's IP address:
  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);

  // print the received signal strength:
  long rssi = WiFi.RSSI();
  Serial.print("signal strength (RSSI):");
  Serial.print(rssi);
  Serial.println(" dBm");
  // print where to go in a browser:
  Serial.print("To see this page in action, open a browser to http://");
  Serial.println(ip);
}
