#include<Adafruit_NeoPixel.h>
#include<Animation.h>


uint8_t themeSize = 3;
Color theme[3] = {Color(3,22,0),Color(2,23,00),Color(0,25,0)};


class Tide: public Animation 
{
  public:
    // Variable to hold which color should be displayed
    int counter = 0;
    uint8_t currentColorIndex = 0;
    
    Tide(Adafruit_NeoPixel strip, uint16_t numPixels ,uint16_t groupSize, uint16_t animationInterval): Animation (strip, numPixels, groupSize, animationInterval) {};
    
    void animationLogic() override
    {

      if(counter < getStripSize()) 
      {
        setGroupColor(counter%getStripSize()/getGroupSize(), theme[currentColorIndex ]);
      } else 
      {
        setGroupColor(counter%getStripSize()/getGroupSize(), Color(0,0,0));
        if(counter == getStripSize()*2 - 1) 
        {
          counter = -1;
          currentColorIndex += 1;
          if(currentColorIndex == themeSize) currentColorIndex = 0;
        }
      }
      counter += 1; 
    } 
};



uint8_t PIN = 6;
uint16_t NUM_LEDS = 160;
Adafruit_NeoPixel strip(NUM_LEDS, PIN, NEO_GRB + NEO_KHZ800);
Tide tide(strip,NUM_LEDS,1,50);

void setup() {
   strip.begin();
}

void loop() {
   tide.tick();
}
