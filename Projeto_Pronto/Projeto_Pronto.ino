/*************************************************************

  This is a simple demo of sending and receiving some data.
  Be sure to check out other examples!
 *************************************************************/

/* Fill-in information from Blynk Device Info here */
#define BLYNK_TEMPLATE_ID           "TMPL2FNVeqWeY"
#define BLYNK_TEMPLATE_NAME         "Quickstart Template"
#define BLYNK_AUTH_TOKEN            "3k93XD8vXpsVbqJZlmq-Sd5x0VKNCeqB"
//===================================================================
#define ledA 25
#define ledpwm 26
#define pot 35
#define btn 34

/* Comment this out to disable prints and save space */
#define BLYNK_PRINT Serial


#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "WAM 2.4";
char pass[] = "manu2020";

BlynkTimer timer;

// This function is called every time the Virtual Pin 0 state changes
BLYNK_WRITE(V0)
{
  // Set incoming value from pin V0 to a variable
  int value = param.asInt();

  digitalWrite(ledA, value);
  // Update state
  Blynk.virtualWrite(V1, value);
}

// This function is called every time the device is connected to the Blynk.Cloud
BLYNK_CONNECTED()
{
  // Change Web Link Button message to "Congratulations!"
  Blynk.setProperty(V3, "offImageUrl", "https://static-image.nyc3.cdn.digitaloceanspaces.com/general/fte/congratulations.png");
  Blynk.setProperty(V3, "onImageUrl",  "https://static-image.nyc3.cdn.digitaloceanspaces.com/general/fte/congratulations_pressed.png");
  Blynk.setProperty(V3, "url", "https://docs.blynk.io/en/getting-started/what-do-i-need-to-blynk/how-quickstart-device-was-made");
}

// This function sends Arduino's uptime every second to Virtual Pin 2.
void myTimerEvent()
{
  // You can send any value at any time.
  // Please don't send more that 10 values per second.
  Blynk.virtualWrite(V2, millis() / 1000);
}

// This function sends Arduino's uptime every second to Virtual Pin 2.
void leituraAnalogica()
{
  // You can send any value at any time.
  // Please don't send more that 10 values per second.
  int potvalue = analogRead(pot);
  
  Blynk.virtualWrite(V5, potvalue);
}

void leituraBTN()
{
  int estado = digitalRead(btn);
  // You can send any value at any time.
  // Please don't send more that 10 values per second.
  Blynk.virtualWrite(V4, estado);
}

BLYNK_WRITE(V6)
{
  // Set incoming value from pin V0 to a variable
  int value = param.asInt();
  Blynk.virtualWrite(V6, value);

  value=map(value,0,100,0,255);
  ledcWrite(0, value);
}

void setup()
{
  // Debug console
  Serial.begin(115200);

  pinMode(ledA, OUTPUT);
  pinMode(ledpwm, OUTPUT);
  pinMode(btn, INPUT);
  ledcSetup(0,5000,8);
  ledcAttachPin(26,0);

  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
  // You can also specify server:
  //Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass, "blynk.cloud", 80);
  //Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass, IPAddress(192,168,1,100), 8080);

  // Setup a function to be called every second
  timer.setInterval(1000L, myTimerEvent);
  timer.setInterval(100L, leituraAnalogica);
  timer.setInterval(100L, leituraBTN);
}

void loop()
{
  Blynk.run();
  timer.run();
  // You can inject your own code or combine it with other sketches.
  // Check other examples on how to communicate with Blynk. Remember
  // to avoid delay() function!
}
