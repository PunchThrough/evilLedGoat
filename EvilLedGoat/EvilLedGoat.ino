/*
  This sketch programs a LightBlue Bean to blink two LEDs using the iOS app LightBlue.
  
  Go to the sandbox view in the app to change the LED color/intensity.
  
  NOTE: This is not a low-power sketch.
   
  This example code is in the public domain.
*/ 

#include <SoftPWM.h>

// The pins that the LEDs are soldered to
#define redPin1 0
#define redPin2 5
#define greenPin2 1
#define greenPin1 4
#define bluePin2 2
#define bluePin1 3

// The inputs we will use from the sandbox
#define redSlider 0
#define greenSlider 2
#define blueSlider 4
#define discoSlider 6

#define redCheckbox 1
#define greenCheckbox 3
#define blueCheckbox 5
#define discoCheckbox 7

int redBrightness=0;
int blueBrightness=0;
int greenBrightness=0;
int discoIntensity=0;

bool redTurnedOn=true;
bool greenTurnedOn=true;
bool blueTurnedOn=true;
bool discoMode=true;

/*************************************************************************/
void setup() {
  SoftPWMBegin();
  for(int i = 0; i< 6; i++){
    SoftPWMSet(i, LOW);
  }
}

/*************************************************************************/
void loop(){
    char buffer[64];
    size_t length = 64;
    length = Serial.readBytes(buffer, length);   
    if ( length > 0 )
    {
      for(int i = 0; i < length - 2; i++){
        int i = length-2;
        //Check which checkbox/slider has been changed
        switch(buffer[i])
        {
           case redCheckbox: 
            redTurnedOn=buffer[i+1];
            changeLED(redPin1, redPin2, redTurnedOn*redBrightness);
            break;
          case redSlider:
            redBrightness=(float)((uint8_t)buffer[i+1])/255*100;
            changeLED(redPin1, redPin2, redTurnedOn*redBrightness);
            break;

          case blueCheckbox: 
            blueTurnedOn=buffer[i+1];
            changeLED(bluePin1, bluePin2, blueTurnedOn*blueBrightness);
            break;
          case blueSlider:
            blueBrightness=(float)((uint8_t)buffer[i+1])/255*100;
            changeLED(bluePin1, bluePin2, blueTurnedOn*blueBrightness);
            break;
            
          case greenCheckbox: 
            greenTurnedOn=buffer[i+1];
            changeLED(greenPin1, greenPin2, greenTurnedOn*greenBrightness);
            break;
          case greenSlider:
            greenBrightness=(float)((uint8_t)buffer[i+1])/255*100;
            changeLED(greenPin1, greenPin2, greenTurnedOn*greenBrightness);
            break;

          case discoCheckbox:
            discoMode=(uint8_t)buffer[i+1];
            break;
          case discoSlider:
            discoIntensity=(uint8_t)buffer[i+1];
            break;
            
          default:
            break;
    }
   }
    }
   
   if(discoMode && discoIntensity > 0){
     for(int i = 0; i < 10; i++){
       SoftPWMSetPercent(random(6), random(100)*random(2));
       delay(random(255-discoIntensity));
     }
   }
}

void changeLED(int pin1, int pin2, int percent){
  SoftPWMSetPercent(pin1, percent);
  SoftPWMSetPercent(pin2, percent);
}
