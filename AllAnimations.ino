#include <Adafruit_NeoPixel.h>
#include <Animation.h>
#include <AnalogReader.h>


class Rain : public Animation {
public:
  // Variable to hold which color should be displayed
  Color color = Color(127, 0, 255);
  uint8_t mostSignificantColor = max(max(color.red, color.green), color.blue);

  float rToHighestRatio = (float)color.red / (float)mostSignificantColor;
  float gToHighestRatio = (float)color.green / (float)mostSignificantColor;
  float bToHighestRatio = (float)color.blue / (float)mostSignificantColor;

  uint8_t subtract = 5;
  uint8_t subtractsToTurnOff = mostSignificantColor / subtract;

  uint16_t spawnPropability = 100;  // max 10 000

  Rain(Adafruit_NeoPixel strip, uint16_t numPixels, uint16_t groupSize, uint16_t animationInterval)
    : Animation(strip, numPixels, groupSize, animationInterval){};



  // fast overlaping animation

  void animationLogic() override {

    for (int i = 0; i < getStripSize() / getGroupSize(); i++) {
      Color c = getGroupColor(i);


      uint16_t radnint = random(0, 10000);

      if (radnint < spawnPropability) {
        setGroupColor(i, color);
      } else if (c.red || c.green || c.blue) {
        uint8_t subtractsTakenPlace;
        if (color.red > color.green && color.red > color.blue) {
          subtractsTakenPlace = (color.red - c.red) / subtract;
        } else if (color.green > color.blue) {
          subtractsTakenPlace = (color.green - c.green) / subtract;

        } else {
          subtractsTakenPlace = (color.blue - c.blue) / subtract;
        }


        if (subtractsTakenPlace >= subtractsToTurnOff - 1) {
          setGroupColor(i, Color(0, 0, 0));
        } else {
          c.red = max(color.red - (uint8_t)(((float)subtractsTakenPlace + 1) * (float)subtract * rToHighestRatio), 0);
          c.green = max(color.green - (uint8_t)(((float)subtractsTakenPlace + 1) * (float)subtract * gToHighestRatio), 0);
          c.blue = max(color.blue - (uint8_t)(((float)subtractsTakenPlace + 1) * (float)subtract * bToHighestRatio), 0);

          setGroupColor(i, c);
        }
      }
    }
  }

  // slow noninterupted rain
  /*
    void animationLogic() override
    {

      for(int i = 0; i < getStripSize()/getGroupSize(); i++) 
      {
        Color c = getGroupColor(i);
        
         
        uint16_t radnint = random(0,10000);
        if (c.red || c.green || c.blue) 
        {
          uint8_t subtractsTakenPlace;
          if(color.red > color.green && color.red > color.blue) 
          {
            subtractsTakenPlace = (color.red - c.red)/subtract;
          }
          else if(color.green > color.blue)
          {
            subtractsTakenPlace = (color.green - c.green)/subtract;

          }
          else 
          {
            subtractsTakenPlace = (color.blue - c.blue)/subtract;
          }


          if(subtractsTakenPlace >= subtractsToTurnOff - 1)
          {
            setGroupColor(i, Color(0,0,0));  
          }
          else
          {
            c.red = max(color.red - (uint8_t) (((float)subtractsTakenPlace + 1)*(float)subtract*rToHighestRatio), 0);
            c.green = max(color.green - (uint8_t) (((float)subtractsTakenPlace + 1)*(float)subtract*gToHighestRatio), 0);
            c.blue = max(color.blue - (uint8_t) (((float)subtractsTakenPlace + 1)*(float)subtract*bToHighestRatio), 0);
            
            setGroupColor(i, c);  
          }
        }
        else if(radnint < spawnPropability) 
        {
          setGroupColor(i, color);  
        } 
        
        
      }
    } 
    */
};

uint8_t themeSize = 3;
Color theme[3] = { Color(255, 0, 0), Color(0, 255, 0), Color(0, 0, 255) };


class ChristmasLights : public Animation {
public:
  // Variable to hold which color should be displayed
  int counter = 0;

  ChristmasLights(Adafruit_NeoPixel strip, uint16_t numPixels, uint16_t groupSize, uint16_t animationInterval)
    : Animation(strip, numPixels, groupSize, animationInterval){};

  void animationLogic() override {

    for (int i = 0; i < getStripSize() / getGroupSize(); ++i) {
      setGroupColor(i, theme[(counter + i) % themeSize]);
    }
    counter += 1;
  }
};


class Tide : public Animation {
public:
  // Variable to hold which color should be displayed
  int counter = 0;
  uint8_t currentColorIndex = 0;

  Tide(Adafruit_NeoPixel strip, uint16_t numPixels, uint16_t groupSize, uint16_t animationInterval)
    : Animation(strip, numPixels, groupSize, animationInterval){};

  void animationLogic() override {

    if (counter < getStripSize()) {
      setGroupColor(counter % getStripSize() / getGroupSize(), theme[currentColorIndex]);
    } else {
      setGroupColor(counter % getStripSize() / getGroupSize(), Color(0, 0, 0));
      if (counter == getStripSize() * 2 - 1) {
        counter = -1;
        currentColorIndex += 1;
        if (currentColorIndex == themeSize) currentColorIndex = 0;
      }
    }
    counter += 1;
  }
};


uint8_t getPercentil(uint8_t num, float percentil) {
  return (uint8_t)((float)num * percentil / 100);
}

Color fadeTailColor(int index, Color color, float stepChange) {
  float change = stepChange * index;
  float newPercentil = 100 - change;
  return Color(getPercentil(color.red, newPercentil), getPercentil(color.green, newPercentil), getPercentil(color.blue, newPercentil));
}


class FireFly : public Animation {
public:
  // Variable to hold which color should be displayed
  int counter = 0;
  uint8_t tailLen = 15;


  FireFly(Adafruit_NeoPixel strip, uint16_t numPixels, uint16_t groupSize, uint16_t animationInterval)
    : Animation(strip, numPixels, groupSize, animationInterval){};

  void animationLogic() override {

    uint16_t index = 0;
    for (int i = 0; i < tailLen; i++) {
      index = (counter % getStripSize() / getGroupSize()) + tailLen - i;
      if (index > getStripSize() / getGroupSize() - 1) index = index - getStripSize() / getGroupSize();
      setGroupColor(index, fadeTailColor(i, Color(0, 255, 0), 7));
    }
    setGroupColor((counter % getStripSize() / getGroupSize()), Color(0, 0, 0));
    counter += 1;
  }
};

uint8_t PIN = 6;
uint16_t NUM_LEDS = 80;
Adafruit_NeoPixel strip(NUM_LEDS, PIN, NEO_GRB + NEO_KHZ800);
Rain rain(strip, NUM_LEDS, 1, 20);
ChristmasLights christmasLights(strip, NUM_LEDS, 1, 500);
Tide tide(strip, NUM_LEDS, 1, 50);
FireFly fireFly(strip, NUM_LEDS, 1, 43);

uint8_t currentAnimation = 0;
uint16_t availableAnimations = 4;
Animation* animations[] = { &christmasLights, &rain, &tide, &fireFly };
AnalogReader analogReader(0, availableAnimations - 1, 10, A0, 75, 950);

void setup() {
  strip.begin();
}

void loop() {

  if (analogReader.update()) {
    currentAnimation = analogReader.getCurrentValue();
    strip.clear();
  }    
  (*animations[currentAnimation]).tick();
}
