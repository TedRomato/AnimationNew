#include<Adafruit_NeoPixel.h>
#include<Animation.h>


class FireFly: public Animation 
{
  public:
    // Variable to hold which color should be displayed
    int counter = 0;
    uint8_t tailLen = 15;

    
    FireFly(Adafruit_NeoPixel strip, uint16_t numPixels ,uint16_t groupSize, uint16_t animationInterval): Animation (strip, numPixels, groupSize, animationInterval) {};
    
    void animationLogic() override
    {
      
      uint16_t index = 0;
      for (int i = 0; i < tailLen; i++) 
      {
          index = (counter % getStripSize()/getGroupSize()) + tailLen - i;
          if(index > getStripSize()/getGroupSize() - 1) index = index - getStripSize()/getGroupSize();
          setGroupColor(index, fadeTailColor(i,Color(0,255,0),1.5));        
      }      
      setGroupColor((counter % getStripSize()/getGroupSize()), Color(0,0,0));
      counter += 1; 
    } 
};

uint8_t PIN = 6;
uint16_t NUM_LEDS = 160;
Adafruit_NeoPixel strip(NUM_LEDS, PIN, NEO_GRB + NEO_KHZ800);
FireFly fireFly(strip, NUM_LEDS, 1, 35);



void setup() {
  strip.begin();

}

void loop() {
   fireFly.tick();
}
