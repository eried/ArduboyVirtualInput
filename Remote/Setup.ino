void setup() 
{ 
  arduboy.begin();
  //arduboy.boot();
  arduboy.setFrameRate(30);
  arduboy.setTextSize(1);

  //Serial.begin(9600);
  Mouse.begin();
  Keyboard.begin();
}
