/*
 * Autor: Denilson Gomes Vaz da Silva
 * Graduando em Engenharia da Computação - UFC
 * Temporizador com Arduino
 */
 
// Interrupt.0 encontra-se no pino digital 2 
// Interrupt.1 encontra-se no pino digital 3

/*  Criamos a variável do tipo <em>volatile</em> 
  para assegurar que a variável estará acessível a partir
  do fluxo normal do programa e a partir da interrupção.
*/

// -- Bibliotecas --
#include <Keypad.h> // Inclui a biblioteca do Teclado
#include <TM1637Display.h> // Inclui a biblioteca do Display

// -- Variaveis e Constantes --
int botPause = 2; //Botao botPause
int botReset = 3; //Botao Reset
int alarme = 4; //Variavel para alarme

const int DIO = 5; //Define o pino 8 para o sinal digital
const int CLK = 6; //Define o pino 9 para o clock

byte pinosColunas[] = {9,8,7}; //Pinos das colunas
byte pinosLinhas[]  = {13,12,11,10}; //Pinos das linhas

volatile int pause;
volatile int minutos=0;
volatile int segundos=0;

char teclas[4][3] = {{'1','2','3'},
                     {'4','5','6'},
                     {'7','8','9'},
                     {'*','0','#'}};

char tempo[3]; // Variavel para tempo
int tempint = 100000;
char tecla_pressionada;

// -- Instancia de objetos --
TM1637Display display(CLK, DIO);  //Inicializa objeto displays com CLK e DIO
Keypad teclado1 = Keypad( makeKeymap(teclas), pinosLinhas, pinosColunas, 4, 3); //Inicializa o teclado1

void setup() {

  Serial.begin(9600);
  
  display.setBrightness(0x0a);  //Determina o brilho dos leds do minino (0x00) ate o maximo (0xff)
  pinMode(alarme, OUTPUT); //Define alarme como saida
  pinMode(botReset, INPUT); //Define botReset como entrada
  pinMode(botPause, INPUT); //Define botPause como entrada
  
  // Sintaxe das interrupções:
  // attachInterrupt(numero_interrupt,funcao_a_executar,modo);
  // Modos LOW,CHANGE,RISING,FALLING
  
  attachInterrupt(0, pausa, RISING);
  attachInterrupt(1, reseta, RISING);
}

void pausa() {
  pause=!pause;
}

void reseta() {
  minutos = 0; segundos = 0; //Resetar o tempo
  uint8_t segto = 0x80; // Atribui os dois pontos a variavel
  display.showNumberDecEx(100*minutos + segundos, &segto); //Exibe o tempo com os dois pontos
}

void loop() {
  uint8_t segto = 0x80; // Atribui os dois pontos a variavel

  if(!pause){
    //-- Contagem --
  for(segundos = 0; segundos < 60; segundos++)  //Conta os segundos de 0 a 59
  {  
   
    // -- Acionamento do Alarme --
    while(tempint == (minutos*100 + segundos)){
      digitalWrite(alarme, HIGH); //Ativar o alarme
      display.showNumberDecEx(tempint, &segto); //Exibir tempo no display
    }
    digitalWrite(alarme, LOW); //Desativar o alarme
    
    while(pause){ //Enquanto botPause estiver pressionado
      
      display.showNumberDecEx(100*minutos + segundos, &segto); //Exibe o tempo com os dois pontos
      
      if (teclado1.getKey() == '*'){ //Se o asterisco for pressionado
        tecla_pressionada = teclado1.getKey(); //Lê o teclado
        while(!tecla_pressionada){ //Enquanto nenhuma tecla for apertada
          tecla_pressionada = teclado1.getKey(); //Lê o teclado
        }
        tempo[0] = tecla_pressionada; //tempo[0] recebe a tecla pressionada
        Serial.println(tecla_pressionada); //printa a tecla na serial
        
        tecla_pressionada = teclado1.getKey(); //Lê o teclado
        while(!tecla_pressionada){ //Enquanto nenhuma tecla for apertada
          tecla_pressionada = teclado1.getKey(); //Lê o teclado
        }
        tempo[1]= tecla_pressionada; //tempo[1] recebe a tecla pressionada
        Serial.println(tecla_pressionada); //printa a tecla na serial
                
        tecla_pressionada = teclado1.getKey(); //Lê o teclado
        while(!tecla_pressionada){ //Enquanto nenhuma tecla for apertada
          tecla_pressionada = teclado1.getKey(); //Lê o teclado
        }
        tempo[2] = tecla_pressionada; //tempo[2] recebe a tecla pressionada
        Serial.println(tecla_pressionada); //printa a tecla na serial
                
        tecla_pressionada = teclado1.getKey(); //Lê o teclado
        while(!tecla_pressionada){ //Enquanto nenhuma tecla for apertada
          tecla_pressionada = teclado1.getKey(); //Lê o teclado
        }
        tempo[3] = tecla_pressionada; //tempo[3] recebe a tecla pressionada
        Serial.println(tempo); //printa o tempo na serial
        tempint = atoi(tempo); //converte o tempo (char) para (int)
        Serial.println(tempint); //printa o tempo na serial
        display.showNumberDecEx(tempint, &segto); //Exibe o tempo com os dois pontos
        delay(3000); //Espera 3 segundos
      }
    }
    
    display.showNumberDecEx(100*minutos + segundos, &segto); //Exibe o tempo com os dois pontos
    
    delay(1000);  //Tempo de espera da contagem
  }
  minutos++; //Acrescenta a variavel minutos 
  } 
}
