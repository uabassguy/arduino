int greenpin = 11; //select the pin for the red LED
int redpin =10;// select the pin for the green LED
int bluepin =9; // select the pin for the  blue LED

int oldRed, oldGreen, oldBlue;

int val;
void setup() { 
  pinMode(redpin, OUTPUT); pinMode(bluepin, OUTPUT); pinMode(greenpin, OUTPUT); Serial.begin(9600);
}
void loop()
{
  //cycle('r');
  //cycle('g');
  //cycle('b');
  //randomize(3000);
  smoothRandomize(3000);
}

void smoothRandomize(int waitAfter)
{
  int newRed = rand() % 255;
  int newGreen = rand() % 255;
  int newBlue = rand() % 255;
  smoothColor('r', oldRed, newRed, 3);
  smoothColor('g', oldGreen, newGreen, 3);
  smoothColor('b', oldBlue, newBlue, 3);
  oldRed = newRed;
  oldGreen = newGreen;
  oldBlue = newBlue;
  delay(waitAfter);
}

void randomize(int increment)
{
  writeRed(rand() % 255);
  writeGreen(rand() % 255);
  writeBlue(rand() % 255);
  delay(increment);
}

void smoothColor(char color, int oldVal, int newVal, int spd)
{
  for (val = oldVal; val != newVal; (oldVal > newVal ? val-- : val++) )
  {
    switch (color){
      case 'r':
        writeRed(val);
        break;
      case 'g':
        writeGreen(val);
        break;
      case 'b':
        writeBlue(val);
        break;
      }
    delay(spd);
  }
}

void cycle(char color)
{
  for (val = 0; val < 255; val++)
  {
    switch (color){
      case 'r':
        writeRed(val);
        break;
      case 'g':
        writeGreen(val);
        break;
      case 'b':
        writeBlue(val);
        break;
      }
    delay(10);
  }
  for (val = 255; val > 0; val--)
  {
    switch (color){
      case 'r':
        writeRed(val);
        break;
      case 'g':
        writeGreen(val);
        break;
      case 'b':
        writeBlue(val);
        break;
      }
    delay(10);
  }
}

void writeRed(int val)
{
  analogWrite(redpin, val);
}
void writeGreen(int val)
{
  analogWrite(greenpin, val);
}
void writeBlue(int val)
{
  analogWrite(bluepin, val);
}

