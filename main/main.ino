#include <DHT.h>
#include <DHT_U.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

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

int ALTAVOZ;     // variable que almacena el valor raw (0 a 1023)
int sensorValue;
const int altavozPin = 9;
const int rojoPin = 7;
const int verdePin = 8;


void setup()
{
  /*Inicia pantalla oled*/
  Wire.begin();
  oled.begin(SSD1306_SWITCHCAPVCC, 0X3C);
  /*Inicia indicadores*/
  pinMode(altavozPin, OUTPUT);  //definir pin como salida ALTAVOZ
  pinMode(verdePin, OUTPUT);  //definir pin como salida LUZ VERDE 
  pinMode(rojoPin, OUTPUT);  //definir pin como salida LUZ ROJA
  /*Inicia sensor DHT*/
  dht.begin();
  /*Inicia sensor CSS811*/
  Serial.println("CCS811 test");
  if(!ccs.begin()){
    Serial.println("Failed to start sensor! Please check your wiring.");
    while(1);
  }
  // Wait for the sensor to be ready
  while(!ccs.available());
  //
  Serial.begin(9600);
}

void loop() 
{
    
  sensorValue = analogRead(sensorPin);   // realizar la lectura
  TEMPERATURA = dht.readTemperature();
  HUMEDAD = dht.readHumidity();
  
  if (TEMPERATURA>23){
    digitalWrite(rojoPin, HIGH);   
    digitalWrite(verdePin, LOW);   
  } else {
    digitalWrite(verdePin, HIGH);     
    digitalWrite(rojoPin, LOW);   
    alarma();
  } 
  

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

  if(ccs.available()){
    if(!ccs.readData()){
     Serial.println(ccs.calculateTemperature(););
     Serial.print("ºC, CO2: ");
      Serial.print(ccs.geteCO2());
      Serial.print("ppm, TVOC: ");
      Serial.println(ccs.getTVOC());
   }   
    else{
      Serial.println("ERROR!");
      while(1);
    }
  }
  
  
  Serial.println("Temperatura: ");
  Serial.println(TEMPERATURA);
  Serial.println(" Humedad:  ");
  Serial.println(HUMEDAD);
  Serial.println();
  delay(3000);
}

void alarma()
{
  digitalWrite(altavozPin, HIGH);   
}
