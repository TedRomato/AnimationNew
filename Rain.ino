#include<Adafruit_NeoPixel.h>
#include<Animation.h>



class Rain: public Animation 
{
  public:
    // Variable to hold which color should be displayed
    Color color = Color(0,255,30);    
    uint8_t mostSignificantColor = max(max(color.red, color.green),color.blue);
    
    float rToHighestRatio = (float)color.red / (float)mostSignificantColor;  
    float gToHighestRatio = (float)color.green / (float)mostSignificantColor; 
    float bToHighestRatio = (float)color.blue / (float)mostSignificantColor; 
    
    uint8_t subtract = 5;
    uint8_t subtractsToTurnOff = mostSignificantColor / subtract;

    uint16_t spawnPropability = 100; // max 10 000
    
    Rain(Adafruit_NeoPixel strip, uint16_t numPixels ,uint16_t groupSize, uint16_t animationInterval): Animation (strip, numPixels, groupSize, animationInterval) {};



    // fast overlaping animation

    void animationLogic() override
    {

      for(int i = 0; i < getStripSize()/getGroupSize(); i++) 
      {
        Color c = getGroupColor(i);
        
         
        uint16_t radnint = random(0,10000);
        
        if(radnint < spawnPropability) 
        {
          setGroupColor(i, color);  
        } 
        else if (c.red || c.green || c.blue) 
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


uint8_t PIN = 6;
uint16_t NUM_LEDS = 160;
Adafruit_NeoPixel strip(NUM_LEDS, PIN, NEO_GRB + NEO_KHZ800);
Rain rain(strip, NUM_LEDS,1,20);

void setup() {
   strip.begin();
}

void loop() {
   rain.tick();
}

