#include <DHT.h>
#include <DHT_U.h>

#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>


#include "Adafruit_CCS811.h"
Adafruit_CCS811 ccs;

#define ANCHO 128
#define ALTO 64
#define OLED_RESET 4

Adafruit_SSD1306 oled(ANCHO, ALTO, &Wire, OLED_RESET);




/*Configurar DHT*/
int SENSOR = 2;
int TEMPERATURA;
int HUMEDAD;

DHT dht(SENSOR, DHT22);

/*Fin configuración*/

const int sensorPin = A0;    // seleccionar la entrada para el sensor


const int rojoPin = 7;
const int verdePin = 8;
const int altavoz = 9;


void setup()
{
  /*Inicia Pantall*/
  Serial.begin(9600);
  oled.begin(SSD1306_SWITCHCAPVCC, 0x3C); //initialize with the I2C addr 0x3C (128x64)
  delay(500);
  
  /*Inicia sensor CSS811*/
  Serial.println("CCS811 test");
 
  if (!ccs.begin()) 
  {
    Serial.println("Failed to start sensor! Please check your wiring.");
    while(1);
  }
 
  // Wait for the sensor to be ready
  while (!ccs.available());
  
  /*Inicia indicadores*/
  pinMode(verdePin, OUTPUT);  //definir pin como salida LUZ VERDE 
  pinMode(rojoPin, OUTPUT);  //definir pin como salida LUZ ROJA
  pinMode(altavoz, OUTPUT);  //definir pin como salida LUZ ROJA
  /*Inicia sensor DHT*/
  dht.begin();
  
}

void loop() 
{
    
  TEMPERATURA = dht.readTemperature();
  HUMEDAD = dht.readHumidity();
  

 
  if(ccs.available()){
    if(!ccs.readData()){
        oled.clearDisplay();
        oled.setTextColor(WHITE);
        oled.setCursor(0,0);
        oled.setTextSize(1);
        oled.print("Air Quality Meter ");
        oled.setCursor(5,30);
        oled.print("Temperatura: ");
        oled.setTextSize(1);
        oled.print(TEMPERATURA);
        oled.print(" C \n");
        oled.print(" Humedad:     ");
        oled.setTextSize(1);
        oled.print(HUMEDAD);
        oled.print(" % ");
        oled.display();
        delay(1500);
        oled.clearDisplay();
        oled.setTextColor(WHITE);
        oled.setCursor(0,0);
        oled.setTextSize(1);
        oled.print("Air Quality Meter");
        oled.setCursor(0,30);
        oled.print("CO2:      ");
        oled.setTextSize(1);
        oled.print(ccs.geteCO2());
        oled.print(" ppm\n");
        oled.print("TVOC:     ");
        oled.setTextSize(1);
        oled.print(ccs.getTVOC());
        oled.print("  ppb");
        oled.display();
        delay(1500);
        oled.clearDisplay();
        oled.setCursor(0,0);
        oled.setTextSize(1);
        oled.print("Air Quality Meter ");
        oled.setCursor(5,30);
    }else{
      Serial.println("ERROR!");
    }
  }
  //Ambiente muy bueno
  if (ccs.geteCO2()<500 && ccs.getTVOC()<200){
    digitalWrite(rojoPin, LOW);   
    digitalWrite(verdePin, LOW);   
    digitalWrite(altavoz, LOW);   
    oled.print("Ambiente muy bueno");
    oled.display();
    delay(500);
  }
  //Ambiente bueno 
  if ((ccs.geteCO2()>=500 || ccs.getTVOC()>=200) && (ccs.geteCO2()< 1000 && ccs.getTVOC()<600) ){
    digitalWrite(verdePin, HIGH);   
    digitalWrite(rojoPin, LOW);   
    digitalWrite(altavoz, LOW);   
    oled.print("Ambiente bueno");
    oled.display();
    delay(500);
  }
  //Ambiente moderadamente malo
  if ((ccs.geteCO2()>=1000 || ccs.getTVOC()>=600) && (ccs.geteCO2()< 1500 && ccs.getTVOC()<1000) ){
    digitalWrite(verdePin, HIGH);   
    digitalWrite(rojoPin, HIGH);   
    digitalWrite(altavoz, LOW);   
    oled.print("Ambiente malo");
    oled.display();
    delay(500);
  }  
  //Ambiente muy malo
  if ((ccs.geteCO2()>=1500 || ccs.getTVOC()>=1000) && (ccs.geteCO2()<2000 && ccs.getTVOC()<2000) ){
    digitalWrite(rojoPin, HIGH);   
    digitalWrite(verdePin, LOW);   
    digitalWrite(altavoz, LOW);   
    oled.print("Ambiente muy malo");
    oled.display();
    delay(500);
  }
  //Ambiente inaceptable
  if (ccs.geteCO2()>=2000 || ccs.getTVOC()>=2000){
    digitalWrite(rojoPin, HIGH);   
    digitalWrite(verdePin, LOW);   
    digitalWrite(altavoz, HIGH); 
    oled.print("ALERTA");
    oled.display();
    delay(500);      
  }
  
  //Serial.print("Temperatura: ");
  Serial.print(TEMPERATURA);
  Serial.print(",");
  //Serial.print("Humedad:  ");
  Serial.print(HUMEDAD);
  Serial.print(",");
  //Serial.print("CO2: ");
  Serial.print(ccs.geteCO2());
  Serial.print(",");
  //Serial.print("TVOC: ");
  Serial.print(ccs.getTVOC());
  Serial.println();
  //Serial.println("\n");
  delay(1500);
}
