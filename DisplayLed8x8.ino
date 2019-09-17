int pinarrayrenglon[]= {30,31,32,33,34,35,36,37}; //Puerto C [PC7, PC6,..., PC0]
int pinarraycolumna[]= {13,12,11,10,50,51,52,53};//Puerto B [PB7, PB6,..., PB0]
int letra_E[]= {0X00,0XFF,0XFF,0XDB,0XDB, 0XC3,0XC3,0X00}; //Letra E Cada entrada es el binario para las columnas, es decir primera entrada son los 8 renglones para la primera columna
int letra_Z[]= {0X00,0XC7,0XCF,0XDF,0XFB,0XF3,0XE3,0X00};
int letra_H[]= {0X00,0XFF,0XFF,0X18,0X18,0XFF,0XFF,0X00};
int columnas []= {B01111111,B10111111,B11011111,B11101111,B11110111,B11111011,B11111101,B11111111};
int cont1 = 0; // variable que nos va a servir para contar las posiciones en los variables tipo array de arriba
int cont2 = 0;
int tiempo = 33; //nos va a ayudar a controlar la frecuencia
void setup() {
  // put your setup code here, to run once
 //Vamos a utilizar for para dar la instrucción para que todos los pines del puerto B y del puerto C sean de salida
for (cont1 = 0; cont1 < 7; cont1 ++) {
  pinMode (pinarrayrenglon[cont1],OUTPUT);
  pinMode (pinarraycolumna[cont1],OUTPUT);
}
}
void loop() {
  // Necesito para cada letra, mandar la señal para que encienda la columna 1 al tiempo que envío la primera entrada de letra_x al puerto c.
for(cont1=0; cont1<30;cont1++){ //Número de veces que se repite el ciclo anidado. determina el tiempo que se mantiene  la inicial en el display
  for(cont2=0; cont2<7;cont2++){ //Para cada columna, se envía el byte indicado para los renglones
  PORTB = columnas[cont2];
  PORTC = letra_E[cont2];
  delay (1);
  }
}
for(cont1=0; cont1<30;cont1++){
  for(cont2=0; cont2<7;cont2++){
  PORTB = columnas[cont2];
  PORTC = letra_Z[cont2];
  delay (1);
  }
 }
for(cont1=0; cont1<30;cont1++){
  for(cont2=0; cont2<7;cont2++){
  PORTB = columnas[cont2];
  PORTC = letra_H[cont2];
  delay (1);
  }
}
}


