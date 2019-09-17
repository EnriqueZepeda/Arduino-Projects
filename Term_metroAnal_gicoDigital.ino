/*
 * Nombre: Enrique Zepeda Herrera
 * Fecha: 16/03/2018
 * Materia: Microcontroladores
 * Título: Termómetro Digital
 * Descripción: Se creará un termómetro utilizando un sensor LM35, un microcontrolador ATMEGA2560 y un display LM016L 16x2.
 * El display tendrá que mostrar la palabra temperatura centrada y en el primer renglón. Al tiempo que muestra en el
 * segundo renglón la temperatura en las unidades que el usuario prefiera. Para ello habrán dos switch:
 * 00 - °C, 01 - °F, 10 = K, 11 = R. 
 * Además el dispositivo deberá ser capaz de almacenar datos en la memoria. Para ello contará con un Push Botton, él
 * cual al ser presionado guardará los datos. */

  int pinarrayDatos[]={13,12,11,10,50,51,52,53}; //Pin of the PORTB datos display
  int pinarrayControl[]={30,31,32,33,34,35,36,37};              //Pin of the PORTC control display
  int arrayConfiguracion[]={0x01,0x02,0x06,0x0F,0x38,0x83};    //Contiene los valores de entrada para configurar el display
  int wordTemperatura[]={0x54,0x65,0x6D,0x70,0x65,0x72,0x61,0x74,0x75,0x72,0x61}; //Valores de entrada para escribir temperatura
  int symbolCelsius[]={0xA0,0xDF,0x43};
  int symbolFarenheit[]={0xA0,0xDF,0x46};
  int symbolKelvin[]={0xA0,0x4B,0xA0};
  int symbolRankine[]={0xA0,0x52,0xA0};
  int cont1 = 0;                                //Contador
  int dato = 0;        //variable que guardara el valor que envía el sensor 0-1023
  int centenas = 0;
  int decenas = 0;
  int unidades = 0;
  int c = 0;
  /* 
   *  Recibir el dato del sensor 
   *  Interpretar el dato
   *  Convertir a la escala adecuada
   *  Escribir el resultado en el display
   */
void configuracion() { //Subrutina para encender el display
  PORTC = 0x00;
  for(cont1 = 0; cont1 <= 5; cont1 ++) {
    PORTB = arrayConfiguracion[cont1];
    enableInstrucciones();
  }
}
void temperatura()  { //Subrutina para escribir la palabra Temperatura
  PORTC = 0x01;
  for(cont1 = 0; cont1 <= 10; cont1 ++) {
    PORTB = wordTemperatura[cont1];
    enableDatos();
  }
}

void enableInstrucciones(){ //Subrutina Enable para las intrucciones RS = 0 
  PORTC = 0x04;
  delay (1);
  PORTC = 0x00;
  delay (10);
}

void enableDatos() { // Subrutina Enable para datos RS = 1
  PORTC = 0x05;
  delay (1);
  PORTC = 0x01;
  delay(1);
}

float lectura(){ // Lee el valor analógico del sensor de temperatura
  float a;
  //dato=analogRead(temperaturaPin);
  a = (1.5 * dato)/10.23;
  return(a);
}

void celsius(float a){
  c = a;
  unidades = c%10;
  decenas = ((c-unidades)%100)/10;
  centenas = ((c-decenas)%1000)/100;
  PORTB = centenas+48;
  enableDatos();
  PORTB = decenas+48;
  enableDatos();
  PORTB = unidades+48;
  enableDatos();
  PORTC = 0x01;
  for(cont1 = 0; cont1 <= 2; cont1 ++) {
    PORTB = symbolCelsius[cont1];
    enableDatos();
  }
  //Escribir el simbolo de grados centigrados
}
void farenheit(float a)  {
  float f;
  f = a*1.8 + 32;
  c = f;
  unidades = c%10;
  decenas = ((c-unidades)%100)/10;
  centenas = ((c-decenas)%1000)/100;
  PORTB = centenas+48;
  enableDatos();
  PORTB = decenas+48;
  enableDatos();
  PORTB = unidades+48;
  enableDatos();
  for(cont1 = 0; cont1 <= 2; cont1 ++) {
    PORTB = symbolFarenheit[cont1];
    enableDatos();
  }
  //Escribir el simbolo de grados farenheit
}

void kelvin(float a)  {
  float k;
  k=a+273.15;
  c = k;
  unidades = c%10;
  decenas = ((c-unidades)%100)/10;
  centenas = ((c-decenas)%1000)/100;
  PORTB = centenas+48;
  enableDatos();
  PORTB = decenas+48;
  enableDatos();
  PORTB = unidades+48;
  enableDatos();
  for(cont1 = 0; cont1 <= 2; cont1 ++) {
    PORTB = symbolKelvin[cont1];
    enableDatos();
  }
  //Escribir el simbolo de kelvin
}

void rankine(float a)  {
  float r;
  r=(a+273.15)*1.8;
  c = r;
 unidades = c%10;
  decenas = ((c-unidades)%100)/10;
  centenas = ((c-decenas)%1000)/100;
  PORTB = centenas+48;
  enableDatos();
  PORTB = decenas+48;
  enableDatos();
  PORTB = unidades+48;
  enableDatos();
  for(cont1 = 0; cont1 <= 2; cont1 ++) {
    PORTB = symbolRankine[cont1];
    enableDatos();
  }
  //Escribir el simbolo de Rankine
}



void setup() {
 for(cont1 = 0; cont1 <= 7; cont1++) {
  pinMode(pinarrayDatos[cont1],OUTPUT);
  pinMode(pinarrayControl[cont1],OUTPUT);
 }
  pinMode(19, OUTPUT);
  pinMode(20, OUTPUT);
  pinMode(21, OUTPUT);
  //digitalWrite (19,HIGH);
  pinMode (20,INPUT_PULLUP);
  pinMode (21,INPUT_PULLUP);
  configuracion();
  temperatura();
}

void loop() {
  PORTC = 0x00;
  PORTB = 0xC5;
  enableInstrucciones();
  analogReference(EXTERNAL);
  dato = analogRead(A0);
  lectura();
  switch (PIND) {
    case 0:    // Centigrados
     celsius(lectura());
      break;
    case 1:    // Farenheit
     farenheit(lectura());
      break;
    case 2:    // Kelvin
      kelvin(lectura());
      break;
    case 3:    // Rankine
      rankine(lectura());
      break;
  }
  delay(1);        // delay in between reads for stability
}


