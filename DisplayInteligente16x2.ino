int pinarraydatos[]= {13,12,11,10,50,51,52,53}; //Puerto B [PB7, PB6,..., PB0] Irán conectados a los pins para datos  del display de la siguiente manera PB7-D0, PB6-D1...
int pinarraycontrol[]= {30,31,32,33,34,35,36,37};//Puerto C [PC2, PC1, PC0]Irán conectados con los pins de control del display de la siguiente manera PC2-E, PC1-RW, PC0-RS
int configuracioninicial[] = {0x01,0x02,0x06,0x0F,0x38}; //Este arreglo contiene los valores de entrada para configurar el display al inicio
int hola[] = {0x048,0x6F,0x6C,0x61};//Este arreglo el que escriba la palabra Hola
int mundo[] = {0x4D,0x75,0x6E,0x64,0x6F};//Este arreglo el que escriba la palabra Mundo.
int cont1 = 0 ;

void setup() {
  // put your setup code here, to run once
  //Vamos a utilizar for para dar la instrucción para que todos los pines del puerto B y del puerto C sean de salida
//Configuración Arduino
for (cont1 = 0; cont1 <= 7; cont1 ++) {
  pinMode (pinarraydatos[cont1],OUTPUT);
  pinMode (pinarraycontrol[cont1],OUTPUT);
}
for (cont1 = 0; cont1 <= 4; cont1 ++) { 
  PORTB = configuracioninicial[cont1];
  PORTC = 0x04;
  delay(10);
  PORTC = 0x00;
  delay (10);
}
PORTC = 0x01; 
for (cont1 = 0; cont1 <= 3; cont1 ++) {
  PORTB = hola[cont1];
  PORTC = 0x05;
  delay(10);
  PORTC = 0x01;
  delay (10);
}
PORTC = 0x00;
PORTB = 0xC0;
delay (10);
PORTC = 0x04;
delay(10);
PORTC =0x00;

PORTC = 0x01;
for (cont1 = 0; cont1 <= 4; cont1 ++) { 
  PORTB = mundo[cont1];
  PORTC = 0x05;
  delay(10);
  PORTC = 0x01;
  delay (10);
}
}
void loop() {
//Configuración Display

}



