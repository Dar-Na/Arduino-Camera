#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED display width,  in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
Adafruit_SSD1306 oled(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

int servoPinX = 9, servoPinY = 10;
int val, count;
int width = 640, height = 480;
int posx = 0, posy = 0, bzzz = 0;
int duration = 100;
bool isX = false, isY = false;

void setup()
{
  pinMode(servoPinX, OUTPUT);
  pinMode(servoPinY, OUTPUT);
  Serial.begin(9600);
  Serial.println("Servo is ready");
  count = 0;
  isX = false;
  isY = false;
  if (!oled.begin(SSD1306_SWITCHCAPVCC, 0x3C)) 
  {
    Serial.println(F("SSD1306 allocation failed"));
    while (true);
  }
  
  oled.clearDisplay(); // clear display

  oled.setTextSize(2);          // text size
  oled.setTextColor(WHITE);     // text color
  oled.setCursor(0, 10);        // position to display
  oled.println("wykryto");
  oled.print("osob: ");
  oled.println(count);
  oled.display();               // show on OLED  
}

void loop()
{
    int x_mid, y_mid;
    if (Serial.read() == 'x') {
      x_mid = Serial.parseInt();
      isX = false;
    }
    if (Serial.read() == 'y') {
      y_mid = Serial.parseInt();
      isY = false;
    }
    if (Serial.read() == 't') {
      bzzz = Serial.parseInt();
    }
    if (Serial.read() == 'f') {
      count = Serial.parseInt();
    }

    reDrawCount();

    // rotation OX
    if (isX == false) 
    {
      if (x_mid > width / 2 + width / 4) 
      {
        Serial.println("X: > ");
        servoPulse(servoPinX, 1580);
        posx += 3;
        isX = true;
      } 
      if (x_mid < width / 2 - width / 4) 
      {
        Serial.println("X: < ");
        servoPulse(servoPinX, 1420);
        posx -= 3;
        isX = true;
      } 
    }

    // rotation OY
    if (isY == false) 
    {
      if ((y_mid > height / 2 + height / 10) && posy < 3) 
      {
        Serial.println("Y: > ");
        servoPulse(servoPinY, 1420);
        posy += 3;
        isY = true;
      } 
      //*
      if ((y_mid < height / 2 + height / 10) && posy > -3) 
      {
        Serial.println("Y: < ");
        servoPulse(servoPinY, 1580);
        posy -= 3;
        isY = true;
      } 
      //*/
    }

    //return camera back
    /*
    if (posx <= -12) 
    {
      for (int i = 0; i < 4; i++) 
      {
        servoPulse(servoPinX, 1580);
      } 
      posx = 0;
    }
    if (posx >= 12) 
    {
      for (int i = 0; i < 4; i++) 
      {
        servoPulse(servoPinX, 1420);
      } 
      posx = 0;
    }
    
    if (posy <= -9) 
    {
      for (int i = 0; i < 3; i++) 
      {
        servoPulse(servoPinY, 1580);
      } 
      posy = 0;
    }
    
    if (posy >= 9) 
    {
      for (int i = 0; i < 3; i++) 
      {
        servoPulse(servoPinY, 1420);
      } 
      posy = 0;
    }
    */
  if(bzzz == 1){
    bzz();
  }  
}

// define a servo pulse function
void servoPulse(int pin, int pulseWidth)
{
  // convert angle to 500-2480 pulse width
  digitalWrite(pin, HIGH); // set the level of servo pin as high
  delayMicroseconds(pulseWidth); // delay microsecond of pulse width
  digitalWrite(pin, LOW); // set the level of servo pin as low
  delay(20 - pulseWidth / 1000);
  Serial.println(pulseWidth);
}


void bzz()
{
  tone(8, 2000, duration);
  delay(duration / 2);
  // stop the tone
  noTone(8);
}

void reDrawCount() 
{
  oled.clearDisplay(); // clear display
  oled.setTextSize(2);          // text size
  oled.setTextColor(WHITE);     // text color
  oled.setCursor(0, 10);        // position to display
  oled.println("wykryto");
  oled.print("osob: ");
  oled.println(count);
  oled.display();               // show on OLED  
}
