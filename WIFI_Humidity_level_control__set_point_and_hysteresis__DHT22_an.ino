#include <DHT.h>
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <SimpleTimer.h>
#include <WidgetLED.h>
#define BLYNK_PRINT Serial
char auth[] = "XXX`indent preformatted text by 4 spaces`"; 
SimpleTimer timer;
#define DHTPIN 2
#define DHTTYPE DHT22
const int relay1 =  5;
int humLowTrigger = 40;
DHT dht(DHTPIN, DHTTYPE);
void Readdata()
{
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  Blynk.virtualWrite(10, h);
  Blynk.virtualWrite(11, h);
  Blynk.virtualWrite(20, t);
  Blynk.virtualWrite(21, t);
  Blynk.virtualWrite(15, relay1);
  Blynk.virtualWrite(25, humLowTrigger);
  if(h < humLowTrigger) {
      digitalWrite(relay1, LOW); 
      Blynk.virtualWrite(V26, 0);
  } else {
      digitalWrite(relay1, HIGH);
      Blynk.virtualWrite(V26, 255);
  }
}
BLYNK_WRITE(V7)
{
  Blynk.virtualWrite(V7, humLowTrigger);
}
void setup()
{
  Serial.begin(9600);
  Blynk.begin(auth, "X", "Y");
  timer.setInterval(1000, Readdata);
  dht.begin();
  pinMode(relay1, OUTPUT);
  digitalWrite(relay1, LOW);
}
void loop()
{   
  Blynk.run();
  timer.run();
}
