//////////////////////////////////////////////////////////////////////////////
//  
//
// Este programa controla el proyecto de un par de semáforos que cambian
// por la presencia de algún peatón en la proximidad de dichos semáforos,
// indicado por la señal de sendos sensores PIR. Además, se indica la 
// posibilidad de cruzar con una señal sonora durante el tiempo en que los
// semáforos están en rojo para los vehículos.
//
//
//
/////////////////////////////////////////////////////////////////////////////

// Empiezo estableciendo los pines que voy a utilizar de la placa

int rojo = 13;       // Activación de los LED rojo, digital
int amarillo = 12;    // Activación de los LED amarillo, digital
int verde = 11;     // Activación de los LED verde, digital
int p_rojo = 5;    // Activación de los LED rojo para peatones, digital
int p_verde = 6;   // Activación de los LED verde para peatones, digital
int trigger = 2; 
int echo = 3;
int Buzzer = 7;     // Activación de los buzzers, digital
long distancia;
long tiempo;


// the setup routine runs once when you press reset:
void setup() {
  // Se inicializan los pines como salida o entrada
  Serial.begin(9600);   //iniciar puerto serial
  pinMode(rojo, OUTPUT);
  pinMode(amarillo, OUTPUT);
  pinMode(verde, OUTPUT);
  pinMode(p_rojo, OUTPUT);
  pinMode(p_verde, OUTPUT);
  pinMode(Buzzer, OUTPUT);
  pinMode(echo, INPUT);
  pinMode(trigger, OUTPUT);
}

// the loop routine runs over and over again forever:
void loop() {

  int i, j;    // Variables que usar en los ciclos

digitalWrite(trigger, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigger, LOW);
  tiempo = pulseIn(echo, HIGH, 100 * 58); 
  distancia = tiempo / 58; 

  Serial.print("Distancia: ");
  Serial.print(distancia);      
  Serial.print("cm");
  Serial.println();
  delay(100);
  
  if (distancia <=10 && distancia >0){ // Se avisa de la presencia de peatones con un cambio de color del semáforo
     digitalWrite(verde,HIGH);       // Se cambian los semforos de verde
    digitalWrite(amarillo, LOW);     // a amarillo,
    digitalWrite(rojo, LOW);
    digitalWrite(p_rojo, HIGH);
    digitalWrite(p_verde, LOW);
    delay(4000);
    digitalWrite(verde, LOW);       // Se cambian los semforos de verde
    digitalWrite(amarillo, HIGH);     // a amarillo,
    digitalWrite(rojo, LOW);
    digitalWrite(p_rojo, HIGH);
    digitalWrite(p_verde, LOW);
    delay(2000);               // que se mantendr durante 20 segundos.
      // Se permite el paso de los peatones
    digitalWrite(verde, LOW); 
    digitalWrite(amarillo, LOW);    // Se cambian los semáforos de amarillo
    digitalWrite(rojo, HIGH);       // a verde.
    digitalWrite(p_rojo, LOW);
    digitalWrite(p_verde, HIGH);
        // Se inicia una señal sonora con un ritmo que indique el tiempo restante.
    for (i=1;i<11;i++) {
      for (j=1;j<5;j++) {
       digitalWrite(Buzzer, HIGH);
       delay(1000/i);
       digitalWrite(Buzzer, LOW);
       delay(1000/i);
      }  
    }
           // Se vuelve a permitir la circulación de vehículos
  digitalWrite(rojo, LOW);     // Se apaga la luz roja
  digitalWrite(amarillo, LOW);
  digitalWrite(verde, HIGH);     // y se enciende la luz verde
  digitalWrite(p_rojo, HIGH);
  digitalWrite(p_verde, LOW);
  delay(6000);               // Se espera al menos 3 minutos a volver a habilitar el paso de peatones
  }
}
