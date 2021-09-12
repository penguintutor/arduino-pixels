// Pin where NeoPixels are connected
// RP2040 using pin 17 (D5). Do not use PIN 25 (D2) - possible conflict with WiFi
// UNO WiFi use pin 5 (D5), Nano IOT use pin 5 (D5 / PA05)
#define LED_PIN 17
#define LED_COUNT 65  // How many NeoPixels?
/* Brightness of neopixels. 
Maximum is 255 - for lower brightness consider 50 */
#define BRIGHTNESS 50 

// Designed for static IP address so you can connect to Arduino
// These are lists and need to be commas instead of dots
// eg. for IP address 192.168.0.1 use 192,168,0,1 instead
#define IP_ADDR 192,168,0,44
#define IP_DNS 8,8,8,8          // Google DNS
#define IP_GW 192,168,0,1       // default gateway (router)
#define IP_SUBNET 255,255,255,0 
