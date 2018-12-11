#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>
#include <UniversalTelegramBot.h>
 #include "DHT.h"
// Inicializamos la conexion WIFI con el Router
char ssid[] = "Fibertel WiFi541 2.4GHz";      // el nombre de tu Red
char password[] = "0140932832"; // la clave de tu Red
 
// Inicializar Telegram BOT
#define BOTtoken "703915656:AAE15TgS67XWDp_dXTTieEoUqGQlP5xMjBk"  // el token de tu BOT, lo obtenemos de BotFather
 #define DHTPIN D2
 
// tipo de sensor DHT
#define DHTTYPE DHT11   // DHT 11 
 
// Inicializa el sensor
DHT dht(DHTPIN, DHTTYPE);
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
      String welcome = "Bienvenido a el BOT de Arduino Center, " + from_name + ".\n";
      welcome += "Escribe /opciones si quieres ver lo que puedo hacer.\n\n";
      //welcome += "/send_test_action : to send test chat action message\n";
      bot.sendMessage(chat_id, welcome);
    }
    
    if (text == "/temperatura") {
    int t = dht.readTemperature(); // Obtiene la Temperatura en Celsius
    delay (2000);
Serial.println(String(t));
    bot.sendMessage(chat_id, String(t) + "ºC");
    }
   if (text == "/humedad") {
    int h = dht.readHumidity(); // Obtiene la Humedad
    delay (2000);
Serial.println(String(h));
    bot.sendMessage(chat_id, String(h) + "%");
    }
  
    if (text == "/opciones") {
      String keyboardJson = "[[\"/ledOn\", \"/ledOff\"],[\"/sensor\"]]";
      bot.sendMessageWithReplyKeyboard(chat_id, "Selecciona una de las siguientes opciones:", "", keyboardJson, true);
    }
 
    if (text == "/ledOn") {
      digitalWrite(13, HIGH);
      bot.sendMessage(chat_id, "Led Encendido!");
    }
 
    if (text == "/ledOff") {
      digitalWrite(13, LOW);
      bot.sendMessage(chat_id, "Led Apagado!");
    }
 
    if (text == "/sensor") {
      if (digitalRead(4) == 0) {
        bot.sendMessage(chat_id, "Sensor en Reposo!");
      } else {
        bot.sendMessage(chat_id, "Sensor Activado!!");
      }
    }
  }
}
 
 
void setup() {
  Serial.begin(115200);
 
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
  pinMode(13, OUTPUT);
  pinMode(4, INPUT_PULLUP);
}
 
void loop() {
  if (millis() > Bot_lasttime + Bot_mtbs)  {
    int numNewMessages = bot.getUpdates(bot.last_message_received + 1);
 
    while (numNewMessages) {
      Serial.println("got response");
      handleNewMessages(numNewMessages);
      numNewMessages = bot.getUpdates(bot.last_message_received + 1);
    }
 
    if (digitalRead(4) == 1) {
      if (flag == false) {
        bot.sendMessage(chat_id2, "Se Activo el Sensor!!!");
        flag = true;
      }
    } else {
      flag = false;
    }
 
 
    Bot_lasttime = millis();
  }
}
