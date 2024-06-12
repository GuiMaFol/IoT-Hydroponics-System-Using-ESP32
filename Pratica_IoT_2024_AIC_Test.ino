//------------ Bibliotecas -------------------
#include <WiFi.h>
#include <PubSubClient.h> 
#include <OneWire.h>
#include <DallasTemperature.h>

//------------ Conexão WiFi -----------------
#define SSID "5BOLA-FUNDO"
#define PASSWORD "5bola2008_"


//------------ Conexão MQTT -----------------
#define MQTT_ID "182270416_IoT-SEMB2"
#define MQTT_BROKER "broker.hivemq.com"
#define MQTT_PORT 1883
#define MQTT_LED_TOPIC "182270416_IoT-SEMB2_Tanque3"
#define MQTT_DIST_TOPIC "182270416_IoT-SEMB2_Tanque"
#define MQTT_TEMP_TOPIC "182270416_IoT-SEMB2_Tanque2"
#define MQTT_LEDB_TOPIC "182270416_IoT-SEMB2_Tanque4"

//------------ Declaração dos pinos ---------
#define LED_B 2
#define LED_R 22
#define LED_I 34
#define AC_TERM 19
//#define AC_BOMB 35



int estadoLB = 0;
int estadoLR = 0;

//----- hc
const int trigPin = 5;
const int echoPin = 18;

#define SOUND_SPEED 0.034

long duration;
float distanceCm;

//----- ds
const int oneWireBus = 4;
OneWire oneWire(oneWireBus);
DallasTemperature sensors(&oneWire);

//------------ Definindo Clientes -----------
WiFiClient espClient; 
PubSubClient MQTT(espClient);

unsigned long lastMsg = 0;
#define MSG_BUFFER_SIZE1  (50)
#define MSG_BUFFER_SIZE2  (50)
#define MSG_BUFFER_SIZE3  (50)
#define MSG_BUFFER_SIZE4  (50)
char msg1[MSG_BUFFER_SIZE1];
char msg2[MSG_BUFFER_SIZE2];
char msg3[MSG_BUFFER_SIZE3];
char msg4[MSG_BUFFER_SIZE4];
float value1;
float value2;
float value3;
float value4;

// ----------  Função WiFi ------------------
void setupWIFI()
{
  if(WiFi.status() == WL_CONNECTED)
  {
    return;
  } 
  else 
  {
    
// Conexão WiFi
    Serial.println();
    Serial.print("Aguarde - Conectando a rede ");
    Serial.println(SSID);

    WiFi.begin(SSID, PASSWORD);

// Garantir Conexão WiFi
    while (WiFi.status() != WL_CONNECTED)
    {
        delay(500);
        Serial.print(".");
    }

// Monitor Serial / Display
    Serial.println("");
    Serial.println("Concluido - Conectado a rede WiFi");
    Serial.println("IP:");
    Serial.println(WiFi.localIP());
  }
}

// ------------- Conexão broker MQTT ---------------
void setupMQTT()
{
    MQTT.setServer(MQTT_BROKER, MQTT_PORT);
    MQTT.setCallback(mqtt_callback); 

// Conclusão Conexão MQTT
    while (!MQTT.connected())
    {
        Serial.print("Aguarde - Tentando se conectar ao Broker MQTT: ");
        Serial.println(MQTT_BROKER);
        Serial.print(".\n");
        
        if(MQTT.connect(MQTT_ID))
        {
            Serial.println("Concluido - Conectado ao broker com sucesso");
             MQTT.subscribe(MQTT_DIST_TOPIC);
        } 
        else 
        {
            Serial.println("Falha ao se conectar com o broker, em 5 segundos: tente novamente");
            delay(5000);
        }
    }
}


void setup(void)
{
    Serial.begin(115200);
    pinMode(LED_B, OUTPUT);
    pinMode(LED_R, OUTPUT);
  

    pinMode(trigPin, OUTPUT);
    pinMode(echoPin, INPUT);
    
// -------------- Execução das Funções WiFi e MQTT -----------
    setupWIFI();
    setupMQTT();
    sensors.begin();
}


void loop(void)
{
    
    setupWIFI();
    setupMQTT();
    MQTT.loop();

// -------------- Sensor Temperatura - ds18B20 -----------------
    sensors.requestTemperatures(); 
    float temperatureC = sensors.getTempCByIndex(0);
    //Serial.print("Temperatura do Sistema: ");
    //Serial.print(temperatureC);
    //Serial.println("ºC");

// ------------- Sensor Distancia - hc sr04 ---------------------
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);
  
    duration = pulseIn(echoPin, HIGH);
    distanceCm = duration * SOUND_SPEED/2;
  
    //Serial.print("Distancia (cm): ");
    //Serial.println(distanceCm);

// ------------- _________________________ ---------------------
    unsigned long now = millis();
  if (now - lastMsg > 3000) 
  { //Envio periódico de msg MQTT (Distancia, Temperatura)
    lastMsg = now;
    value1 = temperatureC;
    snprintf (msg1, MSG_BUFFER_SIZE1, "%lf", value1);
    Serial.println(msg1);
    value2 = distanceCm;
    snprintf (msg2, MSG_BUFFER_SIZE2, "%lf", value2);
    Serial.println(msg2);
    MQTT.publish("182270416_IoT-SEMB2_Tanque", msg1);
    MQTT.publish("182270416_IoT-SEMB2_Tanque2", msg2);
  }

  delay(3000);
    
  estadoLR = digitalRead(LED_R);
  if(estadoLR == HIGH)
  {
     snprintf (msg3, MSG_BUFFER_SIZE3, "1");
     Serial.println(msg3);
     MQTT.publish("182270416_IoT-SEMB2_Tanque3", msg3);
  }
  if(estadoLR == LOW)
  {
     snprintf (msg3, MSG_BUFFER_SIZE3, "0");
     Serial.println(msg3);
     MQTT.publish("182270416_IoT-SEMB2_Tanque3", msg3);
  }
    estadoLB = digitalRead(LED_B);
  if(estadoLB == HIGH)
  {
     snprintf (msg4, MSG_BUFFER_SIZE4, "1");
     Serial.println(msg4);
     MQTT.publish("182270416_IoT-SEMB2_Tanque4", msg4);
  }
  if(estadoLB == LOW)
  {
     snprintf (msg4, MSG_BUFFER_SIZE4, "0");
     Serial.println(msg4);
     MQTT.publish("182270416_IoT-SEMB2_Tanque4", msg4);
  }

  if(temperatureC < 27)
  {
     digitalWrite(LED_R, HIGH);
     digitalWrite(AC_TERM, HIGH);
  }
  if(temperatureC >= 27)
  {
     digitalWrite(LED_R, LOW);
     digitalWrite(AC_TERM, LOW);
  }
    if(distanceCm <= 10)
  {
     digitalWrite(LED_B, HIGH);
    // digitalWrite(AC_BOMB, LOW);
  }
  if(distanceCm > 10)
  {
     digitalWrite(LED_B, LOW);
    // digitalWrite(AC_BOMB, HIGH);
  }
}


// -------------- Callback - Função Acionamento ----------
void mqtt_callback(char* topic, byte* payload, unsigned int length)
{
  String MM1;
  for (int i = 0; i < length; i++)
  {
    char c1 = (char)payload[i];
    MM1 += c1;
  }
    String MM2;
  for (int i = 0; i < length; i++)
  {
    char c2 = (char)payload[i];
    MM2 += c2;
  }
}

//-------- Controlando LED AZUL ------------
/*  if (MM1.equals("1R1"))
  {
    digitalWrite(LED_B, HIGH);
    Serial.println("\n Bomba - Acionado \n");
  } 
  else if (MM1.equals("1R0"))
  {
    digitalWrite(LED_B, LOW);
    Serial.println("\n Bomba - Desligado \n");
  }

//-------- Controlando LED AMARELO -------- 
  if (MM2.equals("2R1"))
  {
    digitalWrite(LED_R, HIGH);
    Serial.println("\n Aquecimento - Acionado \n");
  } 
  else if (MM2.equals("2R0"))
  {
    digitalWrite(LED_R, LOW);
    Serial.println("\n Aquecimento - Desligado \n");
  }
  
}
//-------- Função Altura da Coluna d'agua - Sensor HC-sr04 --------




//-------- Função Temperatura da agua - Sensor ds18B20 ------------*/
