/*Este código es para probar los encoder y estimar más o menos cuantas lecutras tiene por revolución, etc. Muy importante probar esto primero*/


/*Estos son los pines que va a utilizar el encoder, es importante notar que a la hora de leer los datos para este ejercicio no vamos a utilizar el típico Digital Read, 
si no que utilizaremos un método para leer todo el puerto que en este caso va a ser un método con números binarios, de estados anteriores y posteriores. */

const int    C1 = 3; // Entrada de la señal A del encoder.
const int    C2 = 2; // Entrada de la señal B del encoder.


/* Estas variables son para generar una variable n que va a ser el número de lecturas qu haga el encoder y las lecturas de los puertos A y B del encoder*/
volatile int  n    = 0;
volatile byte ant  = 0;
volatile byte act  = 0;

unsigned long lastTime = 0;  // Tiempo anterior
unsigned long sampleTime = 100;  // Tiempo de muestreo

void setup()
{
  Serial.begin(9600);

  pinMode(C1, INPUT);
  pinMode(C2, INPUT);



/* Estos métodos que los pines del encoder se puedan */
  attachInterrupt(digitalPinToInterrupt(C1), encoder, CHANGE);
  attachInterrupt(digitalPinToInterrupt(C2), encoder, CHANGE);
  
  Serial.println("Numero de conteos");

}

void loop() {
  if (millis() - lastTime >= sampleTime)
  {  // Se actualiza cada sampleTime (milisegundos)
      lastTime = millis();
      Serial.print("Cuentas: ");Serial.println(n);
   }
}

// Encoder precisión cuádruple.
void encoder(void)
{

/* Esta es la parte interesante de este código, aqui se realiza la función de las lecturas del puerto PIND y se transforman los valore anteriores y actuales
en binario para que el encoder pueda dar una lectura y determine qué sentido y a qué velocidad se movió el motor  */


/* Cuando la lecutra de puertos sea: 

0 0 0 0 1 1 0 0 ------> 12
7 6 5 4 3 2 1 0              */

/* Cuando la lecutra de puertos sea: 

0 0 0 0 1 0 0 0 ------> 8
7 6 5 4 3 2 1 0              */

/* Cuando la lecutra de puertos sea: 

0 0 0 0 0 1 0 0 ------> 4
7 6 5 4 3 2 1 0              */

/* Cuando la lecutra de puertos sea: 

0 0 0 0 0 0 0 0 ------> 0
7 6 5 4 3 2 1 0              */

    ant=act;                           
    act=PIND & 12;         
                           
    if(ant==0  && act== 4)  n++;
    if(ant==4  && act==12)  n++;
    if(ant==8  && act== 0)  n++;
    if(ant==12 && act== 8)  n++;
    
    if(ant==0  && act==8)  n--; 
    if(ant==4  && act==0)  n--;
    if(ant==8  && act==12) n--;
    if(ant==12 && act==4) n--;
    

}
