#ifndef Animation_h
#define Animation_h
#include "Arduino.h"

struct Color
{ 

  Color();
  Color(uint32_t color); 
  Color(uint8_t r, uint8_t g, uint8_t b);  

  uint8_t red = 0;
  uint8_t green = 0;
  uint8_t blue = 0;

};


class Animation 
{

  public:
    
    Animation (Adafruit_NeoPixel strip, uint16_t numPixels ,uint16_t groupSize, uint16_t animationInterval);
    
    void tick(); 
    
    void setGroupSize(uint16_t groupSize);
    uint16_t getGroupSize();

    void setInterval(uint16_t interval);
    uint16_t getInterval();

    void setGroupColor(uint16_t index, uint8_t r, uint8_t g, uint8_t b);
    void setGroupColor(uint16_t index, Color color);
    Color getGroupColor(uint16_t index);

    uint16_t getStripSize();

    void show();

  protected:
    virtual void animationLogic() = 0;
    
  
  private:
    Adafruit_NeoPixel _strip = NULL;
    
    uint16_t _animationInterval = 500; 
    unsigned long _lastUpdate = 0;
   
    uint16_t _groupSize = 1; 
    uint16_t _numPixels;
};




#endif