#include <OneWire.h>
#include <DallasTemperature.h>
#include <math.h>

// Data wire is plugged into digital pin 2 on the Arduino
#define ONE_WIRE_BUS 4

// Setup a oneWire instance to communicate with any OneWire device
OneWire oneWire(ONE_WIRE_BUS);  

// Pass oneWire reference to DallasTemperature library
DallasTemperature sensors(&oneWire);
double e = 2.71828182845904;
double N = 0.6687451584;
float k = 6.112;
float td, tw ;
float k1 = 17.502 * td;
float k2 = 240.97 + td;
float k3 = 17.502 * tw;
float k4 = 240.97 + tw;
double ed = k*pow(e,(k1/k2));
double ew = k*pow(e,(k3/k4));
double RH = ((ew-(N*(1+(0.00115*tw))*(td-tw))*100)/ed);
int deviceCount = 0;
float tempC ;


void setup(void)
{
  sensors.begin();  // Start up the library
  Serial.begin(9600);
  
  // locate devices on the bus
  Serial.print("Locating devices...");
  Serial.print("Found ");
  deviceCount = sensors.getDeviceCount();
  Serial.print(deviceCount, DEC);
  Serial.println(" devices.");
  Serial.println("");
}

void loop(void)
{ 
  
  // Send command to all the sensors for temperature conversion
  sensors.requestTemperatures(); 
  
  // Display temperature from each sensor
  for (int i = 0;  i < deviceCount;  i++)
  {
   Serial.print(deviceCount, DEC);  
    Serial.print("Sensor ");
    Serial.print(i+1);
    Serial.print(" : ");
    if ( i=0)
      {
      td = tempC;
      }
     else 
     {
      tw = tempC;
     }
     
    tempC = sensors.getTempCByIndex(i);
    Serial.print(tempC);
   
    Serial.print("C  |  ");
    Serial.print(DallasTemperature::toFahrenheit(tempC));
    
    Serial.println("F");
    
    delay(10000);
  }
  //Serial.print(RH);
  Serial.println("");
  //delay(10000);
}
