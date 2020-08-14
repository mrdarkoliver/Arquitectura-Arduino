#include <DHT.h>
#include <iostream>

using namespace std;

int SENSOR = 2;
int temp, humedad;//Configuro las variables de temperatura y humedad del DHT11
const int nivel = 9; //Pin 9 para medir el nivel de agua
const int bomba = 13; //Pin 13 para la bomba
const int humedadsuelo = A0; //A0 para la humedad del suelo
int tiempo, humedad_planta;


DHT dht (SENSOR, DHT11);//Configuro el modelo de DHT. Es el DHT11


void setup()
{
  Serial.begin(9600);//Arrancamos el puerto serie a 9600
  dht.begin();//Arranco el sensor DHT11
  
  //Configuramos entradas y salidas
  pinMode(humedadsuelo, INPUT);//Configuro humedadsuelo como entrada
  pinMode(bomba, OUTPUT);//Configuro bomba como salida
  pinMode(nivel, INPUT);//Configuro en nivel de agua como entrada
 }

void loop()
{
  int SensorValue = analogRead(humedadsuelo);//Leo el valor de la humedad y lo meto en SensorValue
  int SensorNivel = digitalRead(nivel); //Leo lo que marca el nivel de agua
  
  //Leo y meto los valores de temperatura y humedad en las variables temp y humedad
  humedad = dht.readHumidity();
  temp = dht.readTemperature();
  
  //Imprimo por el puerto serie los valores de temperatura y humedad del DHT11
  Serial.print("Temperatura: "); Serial.print(temp);
  Serial.print("ºC Humedad: "); Serial.print(humedad); Serial.println("%");
  
  //Imprimo por el puerto serie el valor de la humedad del suelo
  Serial.print("Humedad del suelo: ");Serial.print(SensorValue); Serial.println("%");
  delay(3000);
  
if (SensorNivel==0)
  { Serial.println("Nivel bajo de Agua. Rellenar el tanque"); 
  delay(2000);}

if (SensorNivel==1) 
  {
   Serial.println("Nivel de agua correcto, se puede regar");
   if(SensorValue >= 700) // el valor que considero seco y hay que regar es de 700
  {
   Serial.println("La tierra está seca, comienza el riego");
   digitalWrite(bomba, HIGH);
   delay(2000);
   digitalWrite(bomba, LOW);
   delay(1000);
  }
   }  
  delay(1000);
}

int main(){
  cout<<"Cuanto tiempo va a regar?";cin>>tiempo;
  return 0;
}
