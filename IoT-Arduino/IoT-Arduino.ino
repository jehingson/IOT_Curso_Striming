# Ifdef ARDUINO_ARCH_ESP32
# include  < WiFi.h >
# include  < WiFiMulti.h >
WiFiMulti wifiMulti;
# else
# include  < ESP8266WiFi.h >
# include  < ESP8266WiFiMulti.h >
ESP8266WiFiMulti wifiMulti;
# endif

int LedIndicador = 2;
int Led = 14;
int Boton = 0;
boolean EstadoBoton = false;

void setup() {
  Serial.begin(115200);
  delay(10);
  Serial.println("Iniciando Sistema");
  pinMode(LedIndicador, OUTPUT);
  pinMode(led, OUTPUT);
  pinMode(Boton, INPUT);
  wifiMulti.addAP("edward", "lokysan777");
  wifiMulti.addAP("edward", "Lokysan777");
  Conectado();
}
  
void loop() {
  if(wifiMulti.run() != WL_CONNECTED){
  Conectado();
  }
  ActualizarLed();
  Actualizarboton();
}
void ActualizarLed(){
   if(EstadoBoton){
    digitalWrite(Led, 1);
    }else{
      digitalWrite(Led, 0);
      }
}

void ActualizarBoton(){
  if(digitalRead(Boton) == 1){
    EstadoBoton = !EstadoBoton;
    delay(500);
    }
}

void Conectando(){
  if (wifiMulti.run() != WL_CONNECTED) {
    digitalWrite(LedIndicador, 0);
    delay(2000);
    digitalWrite(LedIndicador, 1);
    delay(2000);
  } else {
    
    Serial.println("conectado wifi");    
  }
}
