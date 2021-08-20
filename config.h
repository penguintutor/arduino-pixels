#define LED_PIN 15 // Pin where NeoPixels are connected - Do not use PIN 25 (D2) - possible conflict with WiFi
#define LED_COUNT 45  // How many NeoPixels?
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

