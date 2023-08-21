/*************************************************************

  This is a simple demo of sending and receiving some data.
  Be sure to check out other examples!
 *************************************************************/

/* Fill-in information from Blynk Device Info here */
#define BLYNK_TEMPLATE_ID           "TMPL2FNVeqWeY"
#define BLYNK_TEMPLATE_NAME         "Quickstart Template"
#define BLYNK_AUTH_TOKEN            "1fzxx8RNgskI5zKVgO76uLTOAx9xaTO5"

/* Comment this out to disable prints and save space */
#define BLYNK_PRINT Serial

//=======Configurando as Portas
#define led 26
#define pot 35
#define btn 34


#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "WAM 2.4";
char pass[] = "manu2020";

BlynkTimer timer;

// This function is called every time the Virtual Pin 0 state changes
// Da Plataforma Blynk para o ESP32
BLYNK_WRITE(V0)
{
  // Set incoming value from pin V0 to a variable
  int value = param.asInt();

  digitalWrite(led,value);
  // Update state
  Blynk.virtualWrite(V1, value);
}

BLYNK_WRITE(V3)
{
  // Set incoming value from pin V0 to a variable
  int pwm = param.asInt();
  Blynk.virtualWrite(V3, pwm);
  
  pwm = map(pwm, 0, 100, 0, 255);
  ledcWrite(0,pwm);
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
// Do ESP32 para a Plataforma Blynk
void myTimerEvent()
{
  // You can send any value at any time.
  // Please don't send more that 10 values per second.
  Blynk.virtualWrite(V2, millis() / 1000);
}

void LeituraAnalogica()
{
  // You can send any value at any time.
  // Please don't send more that 10 values per second.
  int ad = analogRead(pot);

  Blynk.virtualWrite(V8, ad);
}

void LeituraBTN()
{
  int estado = digitalRead(btn);
  // You can send any value at any time.
  // Please don't send more that 10 values per second.
  Blynk.virtualWrite(V9, estado);
}

void setup()
{
  // Debug console
  Serial.begin(115200);
  // Setup das Portas
  pinMode(led, OUTPUT);
  pinMode(btn, INPUT);
  //======= PWM =========
  ledcSetup(0, 5000, 8);
  ledcAttachPin(25, 0);

  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
  // You can also specify server:
  //Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass, "blynk.cloud", 80);
  //Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass, IPAddress(192,168,1,100), 8080);

  // Setup a function to be called every second
  // Chamada das funções que são executadas no ESP32 para a PLataorma Blink
  timer.setInterval(1000L, myTimerEvent);   // Executa a cada 1 segundo
  //=========== Chamada da Funções Criadas ==================================
  timer.setInterval(100L, LeituraAnalogica); 
  timer.setInterval(100L, LeituraBTN); 
}

void loop()
{
  Blynk.run();
  timer.run();
  // You can inject your own code or combine it with other sketches.
  // Check other examples on how to communicate with Blynk. Remember
  // to avoid delay() function!
}
