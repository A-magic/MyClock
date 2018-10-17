# Biblioteca S4ALib
Biblioteca para el **S4A EDU Robotic Controller**.

## Autor
Jorge Villalobos Carvajal - Marzo.2018

## Uso
Se declara una variable con el tipo de la biblioteca y se inicializa por medio del método **begin** en el **setup** del sketch.

#### Ejemplo
```
#include <S4ALib.h>

S4ALib Robot;

void setup() {
  Robot.begin();             // Se realiza la inicialización de la placa
}  // setup

void loop() {
  robot.setSpeed(175, 175);  // Se establece una velocidad de 175 (0-255)
  robot.forward(500);        // Se avanza hacia adelante por medio segundo
  robot.left(500);           // Se gira a la izquierda por medio segundo
  robot.right(500);          // Se gira a la derecha por medio segundo
  robot.backward(500);       // Se retrocede por medio segundo
}
```

## Métodos de la biblioteca

Método | Descripción
------ | -----------
**begin()** | Inicializa los puertos del controlador (usar en el setup del sketch)
**forward()** | Se desplaza hacia adelante
**forward(int ms)** | Se desplaza hacia adelante por **_ms_** milisegundos y se detiene
**backward()** | Se desplaza hacia atrás
**backward(int ms)** | Se desplaza hacia atrás por **_ms_** milisegundos y se detiene
**left()** | Gira hacia la izquierda
**left(int ms)** | Gira hacia la izquierda por **_ms_** milisegundos y se detiene
**right()** | Gira hacia la derecha
**right(int ms)** | Gira hacia la derecha por **_ms_** milisegundos y se detiene
**stop()** | Detiene ambos motores, estableciendo su velocidad en 0.
**ledOn()** | Enciende el led incorporado
**ledOff()** | Apaga el led incorporado
**blink(int ms)** | Realiza un parpadeo del led incorporado por **_ms_** milisegundos
**setMotors(bool leftVal, bool rightVal)** | Establece la dirección de los motores (**LOW** = hacia adelante, **HIGH** = hacia atrás)
**setSpeed(int leftVal, int rightVal)** | Establece la velocidad de los motores (valores entre 0 y 255)

## Recomendaciones
- Si va a utilizar el header para comunicaciones (por ejemplo: Bluetooth HC-06), recuerde **quitar el dispositivo que tenga conectado antes de cargar el sketch**.

![Bluetooth](/images/Bluetooth.jpg)

- Una vez cargado el sketch, se debe utilizar la alimentación externa (**6V - 9V**) y mover el switch de encendido a la posición **ON**.
- Se puede utilizar la placa **Duemilanove or Diecimila, ATmega328P** o descargar en el administrador de placas

![Instalacion placa](/images/DriversPlaca.png)

## Hardware utilizado
* [S4A EDU Robotic Controller](http://www.crcibernetica.com/s4a-edu-robotic-controller/)
* [Bluetooth Module HC-06](http://www.crcibernetica.com/bluetooth-module-hc-06/)
* [Basic Chassis with gear motors and wheels](http://www.crcibernetica.com/basic-chassis-with-gear-motors-and-wheels/)

## APP utilizada
* [Bluetooth Controller](https://play.google.com/store/apps/details?id=com.lafabricadeandroides.lfdabluetoothcontroller)

Puede se alguna otra, en ese caso se utilizan los siguientes comandos:
- Comando **s** para detener el carro
- Comando **u** para ir hacia adelante
- Comando **b** para ir hacia atrás
- Comando **l** para girar a la izquierda
- Comando **r** para girar a la derecha
- Comandos del **1 al 0** corresponden a los valores del 1 al 10 para la velocidad (1 detenido y 10 la máxima velocidad).

## Licencia
Este proyecto ha sido liberado bajo la licencia: **MIT License**
