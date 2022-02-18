#include<Adafruit_NeoPixel.h>
#include "Arduino.h"
#include "Animation.h"


Color::Color(uint8_t r, uint8_t g, uint8_t b) 
{
    red = r;
    green = g;
    blue = b;
}
Color::Color(uint32_t color) 
{
    red = color >> 16;
    green = color >> 8;
    blue = color >> 0;
}
Color::Color() 
{

}

typedef struct Color Color;


Animation::Animation(Adafruit_NeoPixel strip, uint16_t numPixels, uint16_t groupSize, uint16_t animationInterval)
{
   _strip = strip;
  _numPixels = numPixels;
  _groupSize = groupSize;
  _animationInterval = animationInterval;
}

void Animation::tick()
{
  
  if(millis() - _lastUpdate >= _animationInterval) 
  {
    animationLogic(); 
    _lastUpdate = millis();
   show();
  } 
}

void Animation::setGroupSize(uint16_t groupSize)
{
  _groupSize = groupSize;
}

uint16_t Animation::getGroupSize()
{
  return _groupSize;
}

void Animation::setInterval(uint16_t interval)
{
  _animationInterval = interval;
}

uint16_t Animation::getInterval()
{
  return _animationInterval;
}

void Animation::setGroupColor(uint16_t index, uint8_t r, uint8_t g, uint8_t b)
{
  for(uint16_t i = 0; i < getGroupSize(); ++i)
  {
    _strip.setPixelColor(index*getGroupSize() + i,r,g,b);
  }
}

void Animation::setGroupColor(uint16_t index, Color color)
{
  for(uint16_t i = 0; i < getGroupSize(); ++i)
  {
    _strip.setPixelColor(index*getGroupSize() + i,color.red,color.green,color.blue);
  }
}

Color Animation::getGroupColor(uint16_t index)
{
  uint32_t color = _strip.getPixelColor(index*getGroupSize());

  return Color(color);
}

uint16_t Animation::getStripSize()
{
  return _numPixels;
}

void Animation::show()
{
  _strip.show();
}