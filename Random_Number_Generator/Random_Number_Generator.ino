
#include "ThingSpeak.h"
#include <ESP8266WiFi.h>
float value = 0;
int x = 0;

char ssid[] = "Name";   
char pass[] = "password";   


unsigned long Channel_ID ="Channel ID" ; 
const int Field_number = 1; 
const char * WriteAPIKey = "API key"; 


WiFiClient  client;

void setup()
{
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  ThingSpeak.begin(client);
}

void loop()
{
  internet();
  get_value();
  upload();
}

void upload()
{
  internet();
  x = ThingSpeak.writeField(Channel_ID, Field_number, value, WriteAPIKey);
  if (x == 200)Serial.println("Data Updated.");
  if (x != 200)
  {
    Serial.println("Data upload failed, retrying....");
    delay(15000);
    upload();
  }
}

void internet()
{
  if (WiFi.status() != WL_CONNECTED)
  {
    Serial.print("Attempting to connect to SSID: ");
    Serial.println(ssid);
    while (WiFi.status() != WL_CONNECTED)
    {
      WiFi.begin(ssid, pass);
      Serial.print(".");
      delay(5000);
    }
    Serial.println("\nConnected.");
  }
}

void get_value()
{
 value = random(0, 100);
 Serial.println("---------------------");
 Serial.print("Next Value:");
 Serial.println(value);
 delay(15000);
}