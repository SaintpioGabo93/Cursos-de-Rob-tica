
/* Con este bombón vamos a sabér la posición angular de la rueda en grados */

/* Para Calcular la posición de la rueda se usa la ecuación que está en el PDF y 
de ahí obtenemos la resolución */


const int    C1 = 3;                  // Entrada de la señal A del encoder.
const int    C2 = 2;                  // Entrada de la señal B del encoder.


volatile int  n = 0;
volatile byte ant  = 0;
volatile byte act  = 0;

/* Esta es la variable para la posición, la vamos a obtener de la función que está
declarada más adelante del código */

double P = 0.0;

unsigned long lastTime = 0;  // Tiempo anterior
unsigned long sampleTime = 100;  // Tiempo de muestreo

const int R = 201; // Resolucion del encoder R = mH*s*r

void setup()
{
  Serial.begin(9600);

  pinMode(C1, INPUT);
  pinMode(C2, INPUT);

  attachInterrupt(digitalPinToInterrupt(C1), encoder, CHANGE);
  attachInterrupt(digitalPinToInterrupt(C2), encoder, CHANGE);
  
  Serial.println("Posicion en grados");

}

void loop() {
  if (millis() - lastTime >= sampleTime)
  {  // Se actualiza cada sampleTime (milisegundos)
    lastTime = millis();
    computePos();
    Serial.print("Posicion: ");Serial.println(P);
  }
}


/* */
void computePos(void)
{
  P = (n*360.0)/R;
}
 
// Encoder precisión cuádruple.
void encoder(void)
{

    ant=act;                           
    act=PIND & 12;         
                           
    if(ant==0  && act== 4)  n++;
    if(ant==4  && act==12)  n++;
    if(ant==8  && act== 0)  n++;
    if(ant==12 && act== 8)  n++;
    
    if(ant==0 && act==8)  n--; 
    if(ant==4 && act==0)  n--;
    if(ant==8 && act==12) n--;
    if(ant==12 && act==4) n--;

}
