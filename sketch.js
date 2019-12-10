
let BotonActivar;
let BotonApagar;
let EstadoFondo = false;



let BrokerMQTT = 'broker.shiftr.io';
let PuertoMQTT = 80;
let ClienteIDMQTT = "MQTT-P5";
let UsuarioMQTT = "d09f357f";
let ContrasenaMQTT = "2bbb49cb0c48832c";

client = new Paho.MQTT.Client(BrokerMQTT, PuertoMQTT, ClienteIDMQTT);

client.onConnectionLost = MQTTPerder;
client.onMessageArrived = MQTTMensaje;

client.connect({
  onSuccess: CuandoConectadoMQTT,
  userName: UsuarioMQTT,
  password: ContrasenaMQTT
});

function MQTTPerder(responseObject) {
  if (responseObject.errorCode !== 0) {
    console.log("MQTT Perdio coneccion Error:" + responseObject.errorMessage);
  }
}
function MQTTMensaje(message) {
  console.log("Mensaje recibido:" + message.payloadString);
  let Mensaje = message.payloadString;
  if((Mensaje == '1') == true ){
  	EstadoFondo = true;
  	console.log("Encendiendo Fondo")
  }else{
    EstadoFondo = false;
}
}


function CuandoConectadoMQTT() {
  console.log("MQTT Conectado");
  client.subscribe("/Jehingson/Boton");
}


function setup() {
  createCanvas(200, 200);
  createP();
  
  BotonActivar = createButton('Activar Led');
  BotonApagar = createButton('Apagar Led');
  BotonActivar.mousePressed(ApagarLed);
  BotonApagar.mousePressed(ActivarLed);
  
}

function ApagarLed(){
	console.log("Apagar Led");
	
    message = new Paho.MQTT.Message("0");
    message.destinationName = "/Jehingson/Led";
    client.send(message);
}
function ActivarLed(){
	console.log("Activar Led");

	message = new Paho.MQTT.Message("1");
    message.destinationName = "/Arduino-IOT/Led";
    client.send(message);
}

function draw() {
   if (EstadoFondo) {
    background(0);

  } else {
    background(255);
  
}
 }


