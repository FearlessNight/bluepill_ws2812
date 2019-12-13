//--------------------------------------------------------------
// Blue Pill STM32F103C8 WS2812 Neopixel driver example
// Color Wheel display
// Connect WS2812 LED string to pin PC13 (use level up-shifter)

#include "bluepill_ws2812.h"
bluepill_neopixel PIX;       // a string of pixels
#define NUM_PIXELS 16     //   number of pixels in the string
pixel string[NUM_PIXELS]; //   rgb data buffer
#define string_port GPIOC //   pin string is connected to
#define string_pin  13

// RGB color wheel
void wheel( pixel *p, uint8_t w )
{
  if(w < 85)
  { p->rgb.r = 255 - w * 3;
    p->rgb.g = 0;
    p->rgb.b = w * 3;
  }
  else if(w < 170)
  { w -= 85;
    p->rgb.r = 0;
    p->rgb.g = w * 3;
    p->rgb.b = 255 - w * 3;
  }
  else
  { w -= 170;
    p->rgb.r = w * 3;
    p->rgb.g = 255 - w * 3;
    p->rgb.b = 0;
  }
}

// dim pixel down
void attenuate( pixel *p, uint8_t factor )
{
  p->rgb.r /= factor;
  p->rgb.g /= factor;
  p->rgb.b /= factor;
}

void setup() 
{
  PIX.begin(string_port, string_pin); // set pin to output
}

void loop()
{
  static uint8_t wheel_index = 0; // color wheel

  // fill pixel buffer
  for (uint8_t i=0; i < NUM_PIXELS; i++)
  { wheel( &string[i], wheel_index + i*(256/NUM_PIXELS) );  
    attenuate( &string[i], 8 );
  } 
  
  // output pixel buffer to string  
  PIX.paint( string[0].bytes, NUM_PIXELS, string_port, string_pin );

  // loop
  wheel_index++;
  delay(50);
}


