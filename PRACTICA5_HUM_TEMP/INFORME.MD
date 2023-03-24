### PRACTICA 5 : Buses de comunicación I (introducción y I2c) 


# Practica 5.A ESCÀNER I2C
## **Introducción**
El objetivo de esta práctica es comprender el funcionamiento de los buses/sistemas de comunicación entre periféricos, estos elementos pueden ser internos o externos al procesador.
## **Hardware**
* ESP32-Wroom-32.
* Sensor I2C BMP280.
* Protoboard (opcional).
* AHT10 Sensor de Temperatura y Humedad I2C.
  

## **Funcionamiento**
En este ejercicio, comprobaremos la humedad y la temperatura del laboratorio, con un dispositivo externo llamado AHT10, un sensor de temperatura y humedad, y se reproducirá el resultado en nuestro dispositivo I2C.
#### **INFORMACIÓN AHT10**
AHT10 es un sensor que permite obtener lecturas de temperatura y humedad, es de bajo costo y excelente rendimiento. Utiliza este sensor en aplicaciones de control automático de temperatura, aire acondicionado, estaciones meteorológicas, aplicaciones en el hogar, regulador de humedad y temperatura.

Este sensor es muy pequeño para facilitar su utilización, ya viene integrado en un módulo que incorpora regulador de voltaje de 3.3V, cambio de nivel lógico que consta de una matriz de resistencias SMD de 10Kx4 (103) y un chip MOSFET de canal N dual de 6 pines y otros componentes SMD para complementar su funcionamiento, también este módulo tiene 4 pines, 2 para su alimentación y 2 para establecer comunicación I2C (Dirección 0x38 predeterminada) con tarjetas de desarrollo como Arduino, NodeMCU, ESP32 y otros microcontroladores.

![](AHT10.jpg)


## **Software y su funcionamiento**
### **Cabecera del Código**
Incluimos las librerías "Wire.h" y "AHT10.h" para poder establecer la comunicación con el I2C y para poder usar el el sensor AHT10.
```cpp

//Se declaran las librerías 
#include <Wire.h> // Librería para establecer comunicación I2C
#include <AHT10.h> // Librería para utilizar el sensor AHT10

AHT10 myAHT10(0x38);
```
### **Estructura del Setup**
La estructura del set up empiza inicializando la libreria de "Wire", juntamente tambien se inicializa la comunicación serial.
Se imprime el nombre del sensor (AHT10).
Por último con un "if", si la comunicación con el sensor falla, se imprime un mensaje de error.

```cpp

void setup() {
Wire.begin(); // Función que inicializa la librería Wire
Serial.begin(9600); //comunicación serial 
Serial.println("AHT10"); //imprime nombre sensor
if (!myAHT10.begin()) { //mensaje de error si falla
Serial.println("Error no se el sensor!");
while (1);
}
}
```
### **Estructura del Loop**
En la estructura del Loop se lee la temperatura y se asigna =="tem"== y también lee la humedad se le asigna =="hum"==.
Posteriormente se imprime el valor de la temperatura y 
con esta función "Serial.print("tt");" se imprimen dos pestañas para acomodar los valores de temperatura y humedad. Por último se imprime el valor de humedad y finaliza el loop.

```cpp
void loop() {
float temp = myAHT10.readTemperature(); //Se lee la temperatura y se asigna "tem"
float hum = myAHT10.readHumidity(); //Se lee humedad y se asigna "hum" 
Serial.print("Temp: "); Serial.print(temp); Serial.print(" °C"); // el valor de tempertura 
Serial.print("tt"); // Imprime dos pestañas para acomodar los valores de temperatura y humedad
Serial.print("Humidity: "); Serial.print(hum); Serial.println(" %"); // el valor de humedad
delay(1000);
}
```

## **Código completo**
```cpp
//Se declaran las librerías 
#include <Wire.h> // Librería para establecer comunicación I2C
#include <AHT10.h> // Librería para utilizar el sensor AHT10

AHT10 myAHT10(0x38);

void setup() {
Wire.begin(); // Función que inicializa la librería Wire
Serial.begin(9600); //Se inicia la comunicación serial 
Serial.println("AHT10"); // Se imprime el nombre de sensor
if (!myAHT10.begin()) { // Si la comunicación con el sensor falla se imprime el un mensaje de error 
Serial.println("Error no se el sensor!");
while (1);
}
}

void loop() {
float temp = myAHT10.readTemperature(); //Se lee la temperatura y se asigna "tem"
float hum = myAHT10.readHumidity(); //Se lee humedad y se asigna "hum" 
Serial.print("Temp: "); Serial.print(temp); Serial.print(" °C"); //Se imprime el valor de tempertura 
Serial.print("tt"); // Imprime dos pestañas para acomodar los valores de temperatura y humedad
Serial.print("Humidity: "); Serial.print(hum); Serial.println(" %"); //Se imprime el valor de humedad
delay(1000);
}
```