// Inicialización de las librerias
#include <ESP8266WiFi.h>
#include <OneWire.h>
#include <DallasTemperature.h>

// Ingresar la contraseña de API desde ThingSpeak
String apiKey = "Q2K6JYS9W5JRDK57"; 
 
// Ingresar datos de la red wifi a utilizar 
const char *ssid = "Redmi Note 13 Pro 5G"; 
const char *pass = "1234567890";
const char* server = "api.thingspeak.com";
 
#define ONE_WIRE_BUS 2 
 
OneWire oneWire(ONE_WIRE_BUS); 
 
DallasTemperature sensors(&oneWire); 
 
WiFiClient client;
// Inicio del programa principal 
void setup()
{
Serial.begin(115200);
delay(10);
 
// Conexión a la red wifi
WiFi.begin(ssid, pass);
 
while (WiFi.status() != WL_CONNECTED)
{
delay(500);
}

}
// Lazos de repetición

void loop()
{
sensors.requestTemperatures();
float tempC = sensors.getTempCByIndex(0);

if (client.connect(server,80)) 
{
String postStr = apiKey;
postStr +="&field1=";
postStr += String(tempC);

postStr += "\r\n\r\n";
 
client.print("POST /update HTTP/1.1\n");
client.print("Host: api.thingspeak.com\n");
client.print("Connection: close\n");
client.print("X-THINGSPEAKAPIKEY: "+apiKey+"\n");
client.print("Content-Type: application/x-www-form-urlencoded\n");
client.print("Content-Length: ");
client.print(postStr.length());
client.print("\n\n");
client.print(postStr);

}
client.stop();

delay(15000);
}