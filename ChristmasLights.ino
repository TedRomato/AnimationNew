#include<Adafruit_NeoPixel.h>
#include<Animation.h>


uint8_t themeSize = 3;
Color theme[3] = {Color(3,22,0),Color(2,23,00),Color(0,25,0)};


class ChristmasLights: public Animation 
{
  public:
    // Variable to hold which color should be displayed
    int counter = 0;
    
    ChristmasLights(Adafruit_NeoPixel strip, uint16_t numPixels ,uint16_t groupSize, uint16_t animationInterval): Animation (strip, numPixels, groupSize, animationInterval) {};
    
    void animationLogic() override
    {

      for(int i = 0; i < getStripSize()/getGroupSize(); ++i)
      { 
        setGroupColor(i, theme[(counter + i)%themeSize]);
      }     
      counter += 1; 
    } 
};


uint8_t PIN = 6;
uint16_t NUM_LEDS = 160;
Adafruit_NeoPixel strip(NUM_LEDS, PIN, NEO_GRB + NEO_KHZ800);
ChristmasLights christmasLights(strip,NUM_LEDS,1,500);

void setup() {
   strip.begin();
}

void loop() {
   tide.tick();
}
