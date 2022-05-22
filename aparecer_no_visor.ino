#include <NTPClient.h> 
#include <WiFi.h> /* Biblioteca do WiFi. */
#include "heltec.h"
#include "Arduino.h"
#include <DS3231.h>     


/*-------- Configurações de Wi-fi----------- */
const char* ssid = "NET_2G2EA0F1"; /* Substitua pelo nome da rede */
const char* password = "4F2EA0F1";    /* Substitua pela senha */
/* -------- Configurações de relógio on-line----------- */
WiFiUDP udp;
NTPClient ntp(udp, "a.st1.ntp.br",  -10800, -60000);/* Cria um objeto "NTP" com as configurações.utilizada no Brasil */
String hora;            /* Variável que armazena */



//rotate only for GEOMETRY_128_64
 SSD1306Wire display(0x3c, SDA_OLED, SCL_OLED, RST_OLED);
 
void VextON(void)
{
  pinMode(Vext,OUTPUT);
  digitalWrite(Vext, LOW);
}

void VextOFF(void) //Vext default OFF
{
  pinMode(Vext,OUTPUT);
  digitalWrite(Vext, HIGH);
}

void setup() {

  Serial.begin(9600);
  WiFi.begin(ssid, password);
  delay(2000);               /* Espera a conexão. */
  ntp.begin();               /* Inicia o protocolo */
  ntp.forceUpdate();    /* Atualização */
  

  VextON();
  delay(100);

  display.init();
  display.clear();
  display.display();
  
  display.setContrast(255);
  
  display.setTextAlignment(TEXT_ALIGN_CENTER);
  display.clear();
  display.display();
  display.screenRotate(ANGLE_0_DEGREE);
  display.setFont(ArialMT_Plain_16);

}

void loop() { 

hora = ntp.getFormattedTime(); 
  Serial.println(hora);     
  delay(1000);             
  ntp.forceUpdate();    
  display.clear();
display.drawString(64, 32-16/2, hora);
display.display();
}
