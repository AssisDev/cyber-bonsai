#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include "sensor.h"

void EnviaRequest(String API){
  
  if(WiFi.status()== WL_CONNECTED){
    
    HTTPClient http;    //Declarar o objeto da classe HTTPClient
    FazLeituraUmidade();
    DHT.read11(pinoDHT11); //LÊ AS INFORMAÇÕES DO SENSOR
    http.begin(API);      //Especifique o destino do request
    http.addHeader("Content-Type", "application/json");  //Especifica o tipo de conteúdo de header
  
    int httpCode = http.POST("{\"umidade_ar\":\"" + (String)DHT.humidity + "\",\"temperatura\":\"" + (String)DHT.temperature + "\",\"umidade_solo\":\"" + (String)UmidadePercentual + "\",\"planta\":\"" + 1 + "\"}");   //Envie o request
    Serial.println("\n[Leitura ADC]" + (String)ValorADC + "\nUmidade do ar: " + (String)DHT.humidity + "%" + " / Temperatura: " + (String)DHT.temperature + "*C" + " / Umidade do solo: "+(String)UmidadePercentual + "%\n" ); //Imprime o texto no terminal
    String payload = http.getString();                  //Get the response payload
  
    Serial.println(httpCode);   //Print HTTP return code
    Serial.println(payload);    //Print request response payload
  
    http.end();  //Fechar conexão
  
    delay(1000);        
    }       
  }