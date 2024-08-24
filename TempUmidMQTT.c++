#include <WiFi.h>
#include <MQTT.h>
#include <vector>
///////////////////
#include "DHT.h"
#define DHTPIN 18
#define DHTTYPE DHT11

#define vermelha 21
#define verde 5
#define amarela 19
///////////////////
//////rede////////////////
const char ssid[] = "JFN";
const char pass[] = "";
////////broker//////////////////
const char clienteID_broker[] = "";//ID de preferência que irá aparecer no broker
const char username_broker[] = "";// Username do Broker
const char host_broker[] = "";// Url do Broker
const char pass_broker[] = "";// Token do Broker

const char topico1[] = "senai/umidade";
const char topico2[] = "senai/temperatura";
const char topico3[] = "senai/motor";
const char topico4[] = "senai/botao";

//Media da temperatura e umidade
const char topico5[] = "senai/temperatura/media";
const char topico6[] = "senai/umidade/media";

//O número de dados enviados
const char topico7[] = "senai/dados";

//Temperatura mínima e máxima
const char topico8[] = "senai/temperatura/minima";
const char topico9[] = "senai/temperatura/maxima";

//Umidade mínima e máxima
const char topico10[] = "senai/umidade/minima";
const char topico11[] = "senai/umidade/maxima";


int cont = 0;
float temperaturaMedia = 0.0;
float umidadeMedia = 0.0;
float tMedia = 0.0;
float uMedia = 0.0;
float soma = 0.0;
float somaUmid = 0.0;


std::vector<int> Novosvalores;
std::vector<int> NovosvaloresUmid;

//Parte da temperatura minima e máxima
float tempMin = 1000;
float tempMax = -2;

//Parte da umidade minima e máxima
float umidMin = 1000;
float umidMax = -2;

WiFiClient net;
MQTTClient client;
//////////////////////////////
DHT dht(DHTPIN, DHTTYPE);
/////////////////////////////
unsigned long lastMillis = 0;
//float cont=0;
//char numero[10];
///////////////////////////////
char temperatura[10],umidade[10];
///////////////////////////////
void connect() {
  Serial.print("checking wifi...");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(1000);
    //depois colocar função para resetar o esp
  }

  Serial.print("\nconnecting...");
  while (!client.connect(clienteID_broker, username_broker, pass_broker)) {
    Serial.print(".");
    delay(1000);
  }

  Serial.println("\nconnected!");

  client.subscribe("senai/#");

    Serial.println("WiFi connected");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());
    Serial.println("Conectando ...");
    digitalWrite(verde,1);
    Serial.println ("Conexão realizada com sucesso");
}

void messageReceived(String &topic, String &payload) {
    Serial.println(topic + ": " + payload);
    digitalWrite(vermelha, HIGH);
    delay(1000);
    digitalWrite(vermelha, LOW);
}

void setup() {
  Serial.begin(115200);
  pinMode (vermelha, OUTPUT);
  pinMode (amarela, OUTPUT);
  pinMode (verde, OUTPUT);
  // start wifi and mqtt
  WiFi.begin(ssid, pass);
  client.begin(host_broker, net);
  client.onMessage(messageReceived);
  //client.onMessage(messageReceived);

  connect();
  //////////////
  dht.begin();
  ////////////////
}

void loop() {
  client.loop();
  delay(10);

  // check if connected
  if (!client.connected()) {
    connect();
  }

  /////////////////////////////////
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  if (isnan(h) || isnan(t)) {
    Serial.println(F("Falha no sensor!"));
    return;
  }
  // publish a message roughly every second.
  if (millis() - lastMillis > 3000) {
    lastMillis = millis();
    dtostrf(h, 2, 2, umidade);
    dtostrf(t, 2, 2, temperatura);
    tMedia = atof(temperatura); // Converte a string temperatura para float
    uMedia = atof(umidade); // Converte a string umidade para float
    //client.publish(topico2, temperatura);
    if (client.publish(topico2, temperatura) && client.publish(topico1, umidade)) {
      //Temperatura minima e maxima
      if (tMedia < tempMin){
        tempMin = tMedia;
      };
      if (tMedia > tempMax){
        tempMax = tMedia;
      };
      digitalWrite(amarela,1);
      delay(1000);
      digitalWrite(amarela,0);

      //Umidade minima e maxima
      if (uMedia < umidMin){
        umidMin = uMedia;
      };
      if (uMedia > umidMax){
        umidMax = uMedia;
      };
      
      cont = cont + 1; // Incrementa o contador

      //Temperatura media
      Novosvalores.push_back(tMedia);
      int soma = 0;
      for(int i = 0; i < Novosvalores.size(); i++) {
        soma += Novosvalores[i];
        //temperaturaMedia = (temperaturaMedia + soma / cont);
      }
      temperaturaMedia = ((temperaturaMedia + soma) / cont);

      //Umidade média
      NovosvaloresUmid.push_back(uMedia);
      int somaUmid = 0;
      for(int i = 0; i < NovosvaloresUmid.size(); i++) {
        somaUmid += NovosvaloresUmid[i];
        //temperaturaMedia = (temperaturaMedia + soma / cont);
      }
      umidadeMedia = ((umidadeMedia + somaUmid) / cont);
    }
    // Converte a temperatura para uma string
    String temperaturaMinima = String(tempMin);
    String temperaturaMaxima = String(tempMax);

    // Converte a umidade para uma string
    String umidadeMinima = String(umidMin);
    String umidadeMaxima = String(umidMax);

    // Converte o cont para uma string
    String contStr = String(cont);
    
    //Transforma a temperatura e umidade em string
    String tt  = String(temperaturaMedia);
    String uu  = String(umidadeMedia);

    //Pública a contagem de quantos vezes a temperatura chegou no broker
    client.publish(topico7, contStr.c_str());
    
    //Pública a temperatura e umidade
    client.publish(topico5,tt.c_str());
    client.publish(topico6, uu.c_str());

    //Pública a temperatura minima e temperatura máxima
    client.publish(topico8,temperaturaMinima.c_str());
    client.publish(topico9, temperaturaMaxima.c_str());
    
    //Pública a umidade minima e umidade máxima
    client.publish(topico10,umidadeMinima.c_str());
    client.publish(topico11, umidadeMaxima.c_str());
  }
}