#include <Button2.h>
#include <Servo.h>

#define PIN_PULS 12

Button2 puls{PIN_PULS, INPUT_PULLUP, false};

Servo sv_ri;
Servo sv_pi;
Servo sv_pd;
Servo sv_rd;

int vel = 0;

void setup() {
  sv_ri.attach(10);
  sv_pi.attach(9);
  sv_rd.attach(6);
  sv_pd.attach(5);
  // Servos en parada
  sv_pi.write(90);
  sv_ri.write(90);
  sv_rd.write(90);
  sv_pd.write(90);

  // puls.setChangedHandler(changed);
  // puls.setPressedHandler(pressed);
  puls.setReleasedHandler(onReleaseDelay); // Retrasa la entrada del programa, para que de tiempo de haberlo soltado

  // puls.setTapHandler(tap);
  puls.setClickHandler(piesPuntillas);
  // puls.setLongClickDetectedHandler(longClickDetected);
  puls.setLongClickHandler(caminamiento);
  
  puls.setDoubleClickHandler(vueltaDerecha);
  // puls.setTripleClickHandler(tripleClick);
}

void loop() {
  // put your main code here, to run repeatedly:
  puls.loop();
}

void onReleaseDelay() {
  delay(500);
}

void servoSetSpeed(Servo sv, int speed) {
  sv.write(speed + 90);
}

void caminamiento() {
  // Apoyarse sobre pie izq
  servoSetSpeed(sv_pi, 40);
  servoSetSpeed(sv_pd, 40);
  delay(100);
  servoSetSpeed(sv_pi, 0);
  servoSetSpeed(sv_pd, 0);
  delay(250);

  // Girar cadera izq
  servoSetSpeed(sv_ri, 40);
  servoSetSpeed(sv_rd, 40);
  delay(100);
  servoSetSpeed(sv_ri, 0);
  servoSetSpeed(sv_rd, 0);
  delay(250);  // Fin del primer medio-paso

  // Apoyarse sobre pie der
  servoSetSpeed(sv_pd, -20);
  servoSetSpeed(sv_pi, -20);
  delay(2*100);
  servoSetSpeed(sv_pd, 0);
  servoSetSpeed(sv_pi, 0);
  delay(250);

  // Girar cadera der
  servoSetSpeed(sv_rd, -40);
  servoSetSpeed(sv_ri, -40);
  delay(2*100);
  servoSetSpeed(sv_rd, 0);
  servoSetSpeed(sv_ri, 0);
  delay(250);

  // Apoyarse sobre pie izq
  /*servoSetSpeed(sv_pd, 20);
  servoSetSpeed(sv_pi, 20);
  delay(2*150);
  servoSetSpeed(sv_pd, 0);
  servoSetSpeed(sv_pi, 0);
  delay(1000);*/

  // Girar cadera izq
  servoSetSpeed(sv_ri, 40);
  servoSetSpeed(sv_rd, 40);
  delay(150);
  servoSetSpeed(sv_ri, 0);
  servoSetSpeed(sv_rd, 0);
  delay(1000);
}

void piesPuntillas() {
  // pies puntillas
  // Subiendo
  servoSetSpeed(sv_pi, 30);
  servoSetSpeed(sv_pd, -30);
  delay(400);
  // Para una vez arriba
  servoSetSpeed(sv_pi, 0);
  servoSetSpeed(sv_pd, 0);
  delay(2000);
  // Bajando
  servoSetSpeed(sv_pi, -30);
  servoSetSpeed(sv_pd, 30);
  delay(400);
  // Para una vez abajo
  servoSetSpeed(sv_pi, 0);
  servoSetSpeed(sv_pd, 0);
}

void vueltaDerecha() {
// rodillas paradas
  vel = 90;
  sv_ri.write(vel);
  sv_rd.write(vel);
  delay(500);

// rodillas giran a izquierdas (hast ala mitad por ejemplo)
  vel = 110;
  sv_ri.write(vel);
  sv_rd.write(vel);
  delay(600);

// rodillas paran
  vel = 90;
  sv_ri.write(vel);
  sv_rd.write(vel);
  delay(500);

// rodillas vuelven al sitio anterior
  vel = 70;
  sv_ri.write(vel);
  sv_rd.write(vel);
  delay(600);

// rodillas paran
  vel = 90;
  sv_ri.write(vel);
  sv_rd.write(vel);
  delay(500);
}
