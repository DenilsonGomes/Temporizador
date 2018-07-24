/*
 * Autor: Denilson Gomes
 */

// -- Bibliotecas --
#include <TM1637Display.h> // Inclui a biblioteca do Display

// -- Variaveis e Constantes --
const int CLK = 8; //Define o pino 9 para o clock
const int DIO = 9; //Define o pino 8 para o sinal digital

int segundos = 0;  //Quantidade de segundos
int minutos = 0; //Quantidade de minutos
int alarme = 10; //Variavel para alarme no pino 10
int botReset = 11; //Botao Reset no pino 11
int botPause = 12; //Botao botPause no pino 12

// -- Instancia de objetos --
TM1637Display display(CLK, DIO);  //Inicializa objeto displays com CLK e DIO

void setup()
{
  display.setBrightness(0x0a);  //Determina o brilho dos leds do minino (0x00) ate o maximo (0xff)
  Serial.begin(9600); //Inicia comunicação serial
  pinMode(alarme, OUTPUT); //Define alarme como saida
  pinMode(botReset, INPUT); //Define botReset como entrada
  pinMode(botPause, INPUT); //Define botPause como entrada
}
    
void loop()
{
  
  uint8_t segto; // Define variavel para segmentos
  segto = 0x80; // Atribui os dois pontos a variavel
 
  Serial.println(minutos); //Exibe a quantidade de minutos para monitoramento

  //-- Contagem --
  for(segundos = 0; segundos < 60; segundos++)  //Conta os segundos de 0 a 59
  {  
   
    int pause = digitalRead(botPause); //Variavel pause recebe o estado de botPause
    while(pause){ //Enquanto botPause estiver pressionado
      
      display.showNumberDecEx(100*minutos + segundos, &segto); //Exibe o tempo com os dois pontos
      pause = digitalRead(botPause); //Variavel pause recebe o estado de botPause

      int reset = digitalRead(botReset); //Variavel reset recebe a leitura de botReset
      if(reset){ //Se o botao for pressionado
        minutos = 0; segundos = 0; //Resetar o tempo
      }
    }
    
    display.showNumberDecEx(100*minutos + segundos, &segto); //Exibe o tempo com os dois pontos
    delay(1000);  //Tempo de espera da contagem

    int reset = digitalRead(botReset); //Variavel reset recebe a leitura de botReset
    if(reset){ //Se o botao for pressionado
      minutos = 0; segundos = 0; //Resetar o tempo
    }
  }
minutos++; //Acrescenta a variavel minutos


  // -- Acionamento do Alarme --
  while (minutos==30){
    
    digitalWrite(alarme, HIGH); //Ativar o alarme
    display.showNumberDecEx(100*minutos, &segto); //Exibir i-minutos no display

    int reset = digitalRead(botReset); //Variavel reset recebe a leitura de botReset
    if(reset){ //Se o botao for pressionado
      minutos = 0; segundos = 0; //Resetar o tempo
      digitalWrite(alarme, LOW); //Desativar o alarme
    }
  }
}
