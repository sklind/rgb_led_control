#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif

#define PIN 6
#define NUM_LEDS 24



// Parameter 1 = number of pixels in strip
// Parameter 2 = Arduino pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)
//   NEO_RGBW    Pixels are wired for RGBW bitstream (NeoPixel RGBW products)
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUM_LEDS, PIN, NEO_GRB + NEO_KHZ800);


byte inData[4];
int debug_led = 12;

void setup() {
  
  
  pinMode(debug_led, OUTPUT);

  pixels.begin();
  
  Serial.begin(115200, SERIAL_8N1);
  Serial.print("Arduino is here!\n");
} 




void process_command(byte command[]) {
    int led = command[0];
    
    
//    digitalWrite(debug_led, HIGH);    
//    leds[led].r = command[1]; 
//    leds[led].g = command[2]; 
//    leds[led].b = command[3];

    pixels.setPixelColor(led, pixels.Color(command[1],command[2],command[3]));
    pixels.show();
}


int currentByte = 0;

void loop() {
  
 while (Serial.available() > 0) {
        byte recieved = Serial.read();
        
        if (recieved == 255)
        {
            process_command(inData);
            currentByte = 0;
        } else {
            inData[currentByte] = recieved;
            currentByte++;
        }
    }
 
}


