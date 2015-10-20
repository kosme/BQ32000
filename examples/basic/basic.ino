#include <BQ32000.h>

Bq32000 RTC;
BYTE *time;
int i;

void setup()
{
  Serial.begin(9600);
  if(RTC.detect())
  {
    Serial.println("Successful detection");
    time=RTC.getTime();
    Serial.println("Time");
    Serial.print(time[0]);
    for(i=1;i<3;i++)
    {
      Serial.print(":");
      Serial.print(time[i]);
    }
    Serial.println("");
    Serial.print(time[3]);
    for(i=4;i<6;i++)
    {
      Serial.print(" ");
      Serial.print(time[i]);
    }
  }
  else
  {
    Serial.println("ERROR");
    Serial.println("BQ32000 could not be detected.");
    Serial.println("Check wiring.");
    while(true);
  }
}

void loop()
{
}



