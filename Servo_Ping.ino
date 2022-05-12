/*
===================================================================================
    Barrera de seguridad - Por Diego Aravena, para el profesor Marcos Terreros

  Dependiendo de un sensor de distancia, abre o baja una barrera automaticamente.
===================================================================================
*/
#define PULSE 7
#define PING 8
#include <Servo.h>

int i = 0;
bool enRango = false;

Servo miServo;

void setup() {
  // Configuramos el servo y modulo ping
  miServo.attach(PULSE);
  pinMode(PING, INPUT);
}

void loop() {
  long duration, cm;

  // Configuramos el modulo PING
  pinMode(PING, OUTPUT);
  digitalWrite(PING, LOW);
  delayMicroseconds(2);
  digitalWrite(PING, HIGH);
  delayMicroseconds(5);
  digitalWrite(PING, LOW);

  pinMode(PING, INPUT);
  duration = pulseIn(PING, HIGH);

  // Convienrte la duracion del ping a microsegundos
  cm = microsegundosACentimetros(duration);


  // Si hay una distancia de 150cm, el objeto esta en el rango.
  if (cm <= 150) {
    enRango = true;
  } else if (cm > 200) {
  // Si la distancia es superior a 200cm, el objeto salió del rango.
    enRango = false;
  }

  // Si hay un objeto en el rango, sube la barrera.
  if (enRango) {
    for (i; i < 90; i++){
      miServo.write(i);
      delay(5);
    }
  } else {
  // Si no hay un objeto en el rango, baja la barrera.
    for (i; i > 0; i--){
      miServo.write(i);
      delay(5);
    }
  }

  delay(100);
 
}
long microsegundosACentimetros(long microsegundos) {
  // Calculamos la distancia utilizando la duracion del ping, dividido en la velocidad del sonido, divido en 2 
  return microsegundos / 29 / 2;
}
