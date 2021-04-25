#include <DHT.h>
#include <DHT_U.h>
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
  pinMode(altavozPin, OUTPUT);  //definir pin como salida
  pinMode(verdePin, OUTPUT);  //definir pin como salida
  pinMode(rojoPin, OUTPUT);  //definir pin como salida
  dht.begin();
  Serial.begin(9600);
}

void loop() 
{
  sensorValue = analogRead(sensorPin);   // realizar la lectura
  TEMPERATURA = dht.readTemperature();
  HUMEDAD = dht.readHumidity();
  
  if (TEMPERATURA>30){
    digitalWrite(rojoPin, HIGH);   
    digitalWrite(verdePin, LOW);   
  } else {
    digitalWrite(verdePin, HIGH);     
    digitalWrite(rojoPin, LOW);   
    alarma();
  } 
  
  

  Serial.println("Temperatura: ");
  Serial.println(TEMPERATURA);
  Serial.println(" Humedad:  ");
  Serial.println(HUMEDAD);
  Serial.println();
  delay(1000);
}

void alarma()
{
  digitalWrite(altavozPin, HIGH);   
}
