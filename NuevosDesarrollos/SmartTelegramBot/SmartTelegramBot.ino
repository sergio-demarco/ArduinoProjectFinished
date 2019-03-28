#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>
#include <UniversalTelegramBot.h>
#include <Servo.h>

Servo servo; 
// Inicializamos la conexion WIFI con el Router
char ssid[] = "Fibertel WiFi541 2.4GHz";      // el nombre de tu Red
char password[] = "0140932832"; // la clave de tu Red

// Inicializar Telegram BOT
#define BOTtoken "703915656:AAE15TgS67XWDp_dXTTieEoUqGQlP5xMjBk"  // el token de tu BOT, lo obtenemos de BotFather

 
WiFiClientSecure client;
UniversalTelegramBot bot(BOTtoken, client);
 
int Bot_mtbs = 50; //Tiempo medio entre el escaneo de mensajes
long Bot_lasttime;   //exploracion de el ultimo mensaje
bool Start = false;
String chat_id2;
bool flag = false;
 
void handleNewMessages(int numNewMessages) {
  Serial.println("handleNewMessages");
  Serial.println(String(numNewMessages));
 
  for (int i = 0; i < numNewMessages; i++) {
    String chat_id = String(bot.messages[i].chat_id);
    chat_id2 = chat_id;
    String text = bot.messages[i].text;
 
    String from_name = bot.messages[i].from_name;
    if (from_name == "") from_name = "Guest";
 
    if (text == "/start") {
      String welcome = "Bienvenido a el BOT de Sergio, " + from_name + ".\n";
      welcome += "Escribe /opciones si quieres ver lo que puedo hacer.\n\n";
      bot.sendMessage(chat_id, welcome);
    }
    if (text == "Que sabes hacer?") {
      bot.sendMessage(chat_id, "/Encender_Televisor ,/Apagar_Televisor ,/Encender_Luces,/Apagar_Luces,/Sistema_de_Riego,/Alimentar_Perro,Hola,Como andas?,Donde estas?,Gracias,Chau y /opciones");
    }
    if (text == "/Encender_Televisor") {
      bot.sendMessage(chat_id, "Televisor Encendido");
    }
        if (text == "/Apagar_Televisor") {
      bot.sendMessage(chat_id, "Televisor Apagado");
    }
        if (text == "/Encender_Luces") {
      bot.sendMessage(chat_id, "Luces Encendidas");
    }
        if (text == "/Apagar_Luces") {
      bot.sendMessage(chat_id, "Luces Apagadas");
    }
        if (text == "/Sistema_de_Riego") {
      bot.sendMessage(chat_id, "El sistema de riego se ha activado por 3 Minutos");
    }
            if (text == "/Alimentar_Perro") {
      bot.sendMessage(chat_id, "Alimento Servido");
    }

              if (text == "Hola") {
      bot.sendMessage(chat_id, "Hola "+ from_name);
    }
                if (text == "hola") {
      bot.sendMessage(chat_id, "Hola "+ from_name);
    }
                    if (text == "Como andas?") {
      bot.sendMessage(chat_id, "Muy bien, y vos "+ from_name+" ?");
    }
                        if (text == "¿Como andas?") {
      bot.sendMessage(chat_id, "Muy bien, y vos "+ from_name+" ?");
    }
                        if (text == "como andas?") {
      bot.sendMessage(chat_id, "Muy bien, y vos "+ from_name+" ?");
    }
                            if (text == "¿como andas?") {
      bot.sendMessage(chat_id, "Muy bien, y vos "+ from_name+" ?");
    }
                                if (text == "¿Donde estas?") {
      bot.sendMessage(chat_id, "En la casa de Sergio conectado a la red WIFI");
    }
                                    if (text == "Donde estas?") {
      bot.sendMessage(chat_id, "En la casa de Sergio conectado a la red WIFI");
    }
                                        if (text == "Gracias") {
      bot.sendMessage(chat_id, "Denada "+ from_name);
    }
                                            if (text == "gracias") {
      bot.sendMessage(chat_id, "Denada "+ from_name);
    }
                                            if (text == "Chau") {
      bot.sendMessage(chat_id, "Chau "+ from_name);
    }
                                                if (text == "chau") {
      bot.sendMessage(chat_id, "Chau "+ from_name);
    }
    if (text == "/opciones") {
      String keyboardJson = "[[\"/Encender_Televisor\", \"/Apagar_Televisor\"],[\"/Encender_Luces\", \"/Apagar_Luces\"],[\"/Sistema_de_Riego\", \"/Alimentar_Perro\"]]";
      bot.sendMessageWithReplyKeyboard(chat_id, "Selecciona una de las siguientes opciones:", "", keyboardJson, true);
    }
  }
}
 
 
void setup() {
  Serial.begin(115200);
servo.attach(5);
servo.write(0);
delay(2000);
servo.write(90);
delay(1000);
servo.write(120);
delay(1000);
servo.write(0);
delay(1000);
  // Establecer el modo WiFi y desconectarse de un AP si fue Anteriormente conectada
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  delay(100);
 
  // Intentar conectarse a la red
  Serial.print("Conectando al Wifi: ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
 
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
 
  Serial.println("");
  Serial.println("WiFi conectada");
}
 
void loop() {
  if (millis() > Bot_lasttime + Bot_mtbs)  {
    int numNewMessages = bot.getUpdates(bot.last_message_received + 1);
 
    while (numNewMessages) {
      Serial.println("got response");
      handleNewMessages(numNewMessages);
      numNewMessages = bot.getUpdates(bot.last_message_received + 1);
    }
     
    Bot_lasttime = millis();
  }
}
