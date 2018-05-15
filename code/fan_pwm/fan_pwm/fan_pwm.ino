#include <DallasTemperature.h>
#include <OneWire.h>

#define ONE_WIRE_BUS 2
// Setup a oneWire instance to communicate with any OneWire devices (not just Maxim/Dallas temperature ICs)
OneWire oneWire(ONE_WIRE_BUS);
// Pass our oneWire reference to Dallas Temperature.
DallasTemperature sensors(&oneWire);

int fan = 11;    
int val;
float fanInitTemp = 81.7;
float fanCutoffTemp = 81.6;
int loopWait = 10000;

void setup()
{
 Serial.begin(9600);
 pinMode(fan, OUTPUT);
 sensors.begin();
}

void loop(){
  sensors.requestTemperatures();
  float currentTemp = sensors.getTempFByIndex(0);
  if (currentTemp < fanInitTemp){
    Serial.print("Temp less than threshold ");
    Serial.print(fanInitTemp);
    Serial.print(", nothing to do.\n");
    Serial.print("Current temp ");
    Serial.print(currentTemp);
    Serial.print("\n");
    delay(loopWait);
    return;
  }

  Serial.print("Temp exceeds threshold ");
  Serial.print(fanInitTemp);
  Serial.print(", initializing fan\n");
  
  // kick the fan on with a high value before stepping up pwm
  analogWrite(fan, 255);
  for (val = 50; val < 255; val++)
  {
    analogWrite(fan, val);
  }

  Serial.print("Waiting for cooldown.");
  //Serial.print(sensors.getTempFByIndex(0));
  float newTemp;
  do {
    sensors.requestTemperatures();
    newTemp = sensors.getTempFByIndex(0);
    if (newTemp <= fanCutoffTemp)
    {
      Serial.println("Temp reached low threshold.");
      break;
    }
    //Serial.print(newTemp);
    Serial.print(".");
    delay(10000);
  } while( newTemp > fanCutoffTemp );
  
  Serial.println("Ramping down");
  // ramp down
  for (val = 255; val > 100; val--)
  {
    analogWrite(fan, val);
    delay(100);
  }
  analogWrite(fan, 0);
  delay(loopWait);
}
