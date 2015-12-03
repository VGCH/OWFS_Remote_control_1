//V.G.C. https://twitter.com/generator_cher
//remote control for OWFS 
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <WiFiServer.h>
#include <WiFiUdp.h>
//Настройки Wi-Fi
const char* ssid = "SSID you network";//Name wireless network
const char* password = "you network password";//Password
const char* host = "you ip owfs server"; //OWFS adress
//Светодиодик
const int led = 13;
//GPIO12 -button ON
//GPIO14 -button OFF

void setup() {
  Serial.begin(115200);
  pinMode(led, OUTPUT);
  digitalWrite(led, 0);
  //Подключаемся к сети
  WiFi.mode(WIFI_STA); //Режим Wi-Fi клиент
  WiFi.begin(ssid, password);
  //Ждем подключение
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("Client mode");// Говорим что мы в режиме клиент
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
  }
  
void swich() {
  if (digitalRead(12)==1)
  {
 
  }
  else
  {
    //Мигаем светодиодом, говоря что кнопка нажата
    digitalWrite(led, 1);
    delay(200);
    digitalWrite(led, 0);
    delay(200);
    digitalWrite(led, 1);
    delay(200);
    //Формируем GET запрос к серверу для включения света
  Serial.print("connecting to ");
  Serial.println(host);
  // Use WiFiClient class to create TCP connections
  WiFiClient client;
  const int httpPort = 3001;//port owfs 
  if (!client.connect(host, httpPort)) {
    Serial.println("connection failed");
    return;
  }
    // We now create a URI for the request
  String url = "/you_one_wire_device_id";
  url += "?PIO.A=";
  url += "on";
  Serial.print("Requesting URL: ");
  Serial.println(url);
  digitalWrite(led, 1);
  // This will send the request to the server
  client.print(String("GET ") + url + " HTTP/1.1\r\n" +
               "Host: " + host + "\r\n" + 
               "Connection: close\r\n\r\n");
  // Read all the lines of the reply from server and print them to Serial
  while(client.available()){
    String line = client.readStringUntil('\r');
    Serial.print(line);
  }
  Serial.println();
  Serial.println("closing connection");
 digitalWrite(led, 0); 
 delay(2000);
  };
  if (digitalRead(14)==1)
  {
  }
  else
  {
    digitalWrite(led, 1);
    delay(200);
    digitalWrite(led, 0);
    delay(200);
    digitalWrite(led, 1);
    delay(200);
   //Формируем GET запрос к серверу для выключения света
  Serial.print("connecting to ");
  Serial.println(host);
  // Use WiFiClient class to create TCP connections
  WiFiClient client;
  const int httpPort = 3001;
  if (!client.connect(host, httpPort)) {
    Serial.println("connection failed");
    return;
  }
    // We now create a URI for the request
  String url = "/you_one_wire_device_id";
  url += "?PIO.A=";
  url += "off";
  Serial.print("Requesting URL: ");
  Serial.println(url);
  digitalWrite(led, 1);
  // This will send the request to the server
  client.print(String("GET ") + url + " HTTP/1.1\r\n" +
               "Host: " + host + "\r\n" + 
               "Connection: close\r\n\r\n");
  // Read all the lines of the reply from server and print them to Serial
  while(client.available()){
    String line = client.readStringUntil('\r');
    Serial.print(line);
  }
  Serial.println();
  Serial.println("closing connection");
 digitalWrite(led, 0); 
 delay(2000); 
    }; 
}
void loop() {
  // 
swich();
}
