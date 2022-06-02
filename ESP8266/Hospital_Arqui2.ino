#include <Arduino.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);
#include <SPI.h>
#include <MFRC522.h>
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <ESPAsyncWebServer.h>
#include <WebSocketsServer.h>
#include <WiFiClient.h>
const char* ssid = "LOPEZ";
const char* password = "0zymandias_1818";
const char* hostname = "Arqui2";

IPAddress local_IP(192, 168, 1, 184);
IPAddress gateway(192, 168, 1, 1);
IPAddress subnet(255, 255, 255, 0);
IPAddress primaryDNS(8, 8, 8, 8);   
IPAddress secondaryDNS(8, 8, 4, 4); 

#define RST_PIN D0
#define SS_PIN D8
#define PULSO D3
int turno_actual[5] = {0,0,0,0,0};
int personas[5] = {0,0,0,0,0};
int turno_total[5] = {0,0,0,0,0};
int aforo_maximo[5] = {25,30,35,20,15};
int area = 0;
int conteo = 0;
int reinicio = 1;
MFRC522 mfrc522(SS_PIN, RST_PIN);   // Create MFRC522 instance.
const String tarjeta = "F2B5D12C"; 
const String llavero = "DA8C6525"; 

const char* serverName = "http://arqui-hospital.herokuapp.com/nuevo_turno";
const char* serverName1 = "http://arqui-hospital.herokuapp.com/siguiente";
const char* serverName2 = "http://arqui-hospital.herokuapp.com/actualizar";
const char* serverName3 = "http://arqui-hospital.herokuapp.com/reset";
AsyncWebSocket ws("/ws");
AsyncWebServer server(80);

void InitServer()
{ 
  server.serveStatic("/", SPIFFS, "/").setDefaultFile("index.html");
  server.serveStatic("/admin", SPIFFS, "/").setDefaultFile("admin.html");
  server.on("/turno", [](AsyncWebServerRequest *request) {
    char buffer[40];//5
    sprintf(buffer, "%d-%d-%d,%d-%d-%d,%d-%d-%d,%d-%d-%d,%d-%d-%d",
    turno_actual[0],personas[0],aforo_maximo[0],turno_actual[1],personas[1],aforo_maximo[1],turno_actual[2], personas[2], aforo_maximo[2],turno_actual[3], personas[3], aforo_maximo[3],turno_actual[4], personas[4], aforo_maximo[4]);
    request->send(200, "text/plain", buffer);
  });
  server.on("/cambiarArea",HTTP_GET, [](AsyncWebServerRequest *request) {
    String inputMessage1;
    // GET input1 value on <ESP_IP>/update?output=<inputMessage1>&state=<inputMessage2>
    if (request->hasParam("area")) {
      inputMessage1 = request->getParam("area")->value();
      area = inputMessage1.toInt();
      char buffer[40];//5
      sprintf(buffer, "%d-%d-%d,%d-%d-%d,%d-%d-%d,%d-%d-%d,%d-%d-%d",
      turno_actual[0],personas[0],aforo_maximo[0],turno_actual[1],personas[1],aforo_maximo[1],turno_actual[2], personas[2], aforo_maximo[2],turno_actual[3], personas[3], aforo_maximo[3],turno_actual[4], personas[4], aforo_maximo[4]);
      request->send(200, "text/plain", buffer);
    }
  });
  server.on("/generar",HTTP_GET, [](AsyncWebServerRequest *request) {
    String inputMessage1;
    // GET input1 value on <ESP_IP>/update?output=<inputMessage1>&state=<inputMessage2>
    if (request->hasParam("area")) {
      inputMessage1 = request->getParam("area")->value();
      area = inputMessage1.toInt();
      turno_total[area]++;
      personas[area]++;
      httpPostActualizar();
      request->send(200, "text/plain", String(turno_total[area]));
    }
  });
  server.onNotFound([](AsyncWebServerRequest *request) {
    request->send(400, "text/plain", "Not found");
  });

  server.begin();
  Serial.println("HTTP server started");
}

void setup()
{
  Serial.begin(115200);
 SPIFFS.begin();
  SPI.begin();      // Initiate  SPI bus
  mfrc522.PCD_Init();   // Initiate MFRC522
  // Iniciar LCD
  lcd.begin(16, 2);
  lcd.init();
  lcd.backlight(); // Agregar brillo
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("ARQUITECTURA                  ");
  lcd.setCursor(0, 1); // Segunda fila
  lcd.print("DE COMPUTADORES  2             ");
  pinMode(PULSO,INPUT);
  
  WiFi.mode(WIFI_STA);
  if (!WiFi.config(local_IP, gateway, subnet, primaryDNS, secondaryDNS)) {
    Serial.println("STA Failed to configure");
  }
  
  WiFi.begin(ssid, password);
  Serial.println("Connecting");
  while(WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to WiFi network with IP Address: ");
  Serial.println(WiFi.localIP());
  InitWebSockets();
  InitServer();
  httpReset();
  Serial.println("Approximate your card to the reader...");
}

void loop()
{
  if (digitalRead(PULSO) == LOW && personas > 0){
      turno_actual[area]++;
      personas[area]--;
      lcd.setCursor(0, 0);
      lcd.print("TURNO ACTUAL:"+String(turno_actual[area])+"                  ");
      lcd.setCursor(0, 1); // Segunda fila
      lcd.print("AFORO ACTUAL: "+String(personas[area])+"                  ");
      httpPostActualizar();
    delay(1000);
  }
      lcd.setCursor(0, 0);
      lcd.print("TURNO ACTUAL:"+String(turno_actual[area])+"                  ");
      lcd.setCursor(0, 1); // Segunda fila
      lcd.print("AFORO ACTUAL: "+String(personas[area])+"                  ");
  codigo_rfid();
  mfrc522.PICC_HaltA();
}

void codigo_rfid(){
  if (mfrc522.PICC_IsNewCardPresent() && mfrc522.PICC_ReadCardSerial())
  {
    char str[32] = "";
    array_to_string(mfrc522.uid.uidByte, 4, str);
    if (tarjeta.equals(String(str)) || llavero.equals(String(str)))
    {
      turno_total[area]++;
      personas[area]++;
      lcd.setCursor(0, 0);
      lcd.print("TURNO ACTUAL:"+String(turno_actual[area])+"                  ");
      lcd.setCursor(0, 1); // Segunda fila
      lcd.print("TU TURNO: "+String(turno_total[area])+"                  ");
      httpPostActualizar();
      delay(1000);
    }
  }
}

void httpPostActualizar(){
  WiFiClient client;
  HTTPClient http;
  http.begin(client, serverName2);
  http.addHeader("Content-Type", "application/json");
  int httpResponseCode = http.POST("{\"area\":\""+String(area)+"\",\"t\":"+String(turno_actual[area])+",\"tt\":"+String(turno_total[area])+",\"a\":"+String(personas[area])+"}");
  Serial.print("HTTP Response code: ");
  Serial.println(httpResponseCode);      
  // Libera recursos
  http.end();
  char buffer[40];//5
  sprintf(buffer, "%d-%d-%d",
  turno_actual[area],personas[area],aforo_maximo[area]);
  ws.textAll(buffer);
}

void httpReset(){
  WiFiClient client;
  HTTPClient http;
  http.begin(client, serverName3);
  int httpResponseCode = http.GET();
  Serial.print("HTTP Response code: ");
  Serial.println(httpResponseCode);    
  http.end();
}

void array_to_string(byte array[], unsigned int len, char buffer[])
{
  for (unsigned int i = 0; i < len; i++)
  {
    byte nib1 = (array[i] >> 4) & 0x0F;
    byte nib2 = (array[i] >> 0) & 0x0F;
    buffer[i * 2 + 0] = nib1 < 0xA ? '0' + nib1 : 'A' + nib1 - 0xA;
    buffer[i * 2 + 1] = nib2 < 0xA ? '0' + nib2 : 'A' + nib2 - 0xA;
  }
  buffer[len * 2] = '\0';
}

void InitWebSockets()
{
  server.addHandler(&ws);
  Serial.println("WebSocket server started");
}
