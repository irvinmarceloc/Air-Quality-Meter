const int sensorPin = A0;    // seleccionar la entrada para el sensor
int sensorValue;     // variable que almacena el valor raw (0 a 1023)
const int pin = 9;

void setup()
{
  pinMode(pin, OUTPUT);  //definir pin como salida
  Serial.begin(9600);
}

void loop() 
{
  sensorValue = analogRead(sensorPin);   // realizar la lectura
  Serial.println(sensorValue);
  alarma();
  delay(1000);
}

void alarma()
{
  digitalWrite(pin, HIGH);   // poner el Pin en HIGH
  delay(5000);               // esperar 5 segundos
  digitalWrite(pin, LOW);    // poner el Pin en LOW
  delay(20000);   
}
