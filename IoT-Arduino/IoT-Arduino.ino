# ifdef ARDUINO_ARCH_ESP32
#include <WiFi.h>
#include <WiFiMulti.h>
WiFiMulti wifiMulti;
# else
#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>

ESP8266WiFiMulti wifiMulti;

# endif

#include <MQTT.h>

WiFiClient net;
MQTTClient client;

long TiempoPasado = 0;
int LedIndicador = D4;
int Led = 12;
int Boton = 0;
boolean EstadoBoton = false;
boolean EstadoLed = false;

void setup() {
  Serial.begin(115200);
  delay(10);
  Serial.println("Iniciando Sistema");
  pinMode(LedIndicador, OUTPUT);
  pinMode(Led, OUTPUT);
  pinMode(Boton, INPUT_PULLUP);
  wifiMulti.addAP("edward","lokysan777");

  client.begin("broker.shiftr.io", net);
  client.onMessage(RecibirMensaje);
  
  Conectando();
}
  
void loop() {
  client.loop();
  delay(10);
  
  if (!client.connected()){
  Conectando();
  }
  ActualizarLed();
  ActualizarBoton();
  MandarData();

}
void MandarData(){
if(millis() > TiempoPasado + 500){
   String Mensaje = String(EstadoBoton);
   client.publish("/Jehingson/Boton", Mensaje);
   TiempoPasado = millis();
}
}
void ActualizarLed(){
   if(EstadoLed){
    digitalWrite(Led, 1);
    }
    else{
      digitalWrite(Led, 0);
  }
}

void ActualizarBoton(){
  if(digitalRead(Boton) == 0){
    EstadoBoton = !EstadoBoton;
    Serial.println("Se presiono el boton");
    delay(10);
    }
}

void Conectando(){
  while (wifiMulti.run() != WL_CONNECTED){
    digitalWrite(LedIndicador, 0);
    delay(2000);
    digitalWrite(LedIndicador, 1);
    delay(2000);
    Serial.println(".");
  }
   while(!client.connect("esp8266", "d09f357f", "2bbb49cb0c48832c")){
   digitalWrite(LedIndicador, 0);
    delay(500);
    digitalWrite(LedIndicador, 1);
    delay(500);
    Serial.println("*");
  }
  Serial.println("Conectado MQTT");
  client.subscribe("/Jehingson/Led");  
   
}
  

void RecibirMensaje(String &topic, String &payload){
  Serial.println("incoming: " + topic + " - " + payload);
  if(payload == "1"){
    EstadoLed = true;
}else if(payload == "0"){
    EstadoLed = false;
}
} 
