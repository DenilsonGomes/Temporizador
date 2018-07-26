/*
 * Autor: Denilson Gomes
 */

// -- Bibliotecas --
#include <TM1637Display.h> // Inclui a biblioteca do Display
#include <Keypad.h> // Inclui a biblioteca do teclado

// -- Variaveis e Constantes --
const int DIO = 9; //Define o pino 8 para o sinal digital
const int CLK = 10; //Define o pino 9 para o clock

int segundos = 0;  //Quantidade de segundos
int minutos = 0; //Quantidade de minutos
int alarme = 11; //Variavel para alarme
int botReset = 12; //Botao Reset
int botPause = 13; //Botao botPause

byte pinosLinhas[]  = {2,3,4,5};
byte pinosColunas[] = {6,7,8};
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
  uint8_t segto = 0x80; // Atribui os dois pontos a variavel
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
    
    int reset = digitalRead(botReset); //Variavel reset recebe a leitura de botReset
    if(reset){ //Se o botao for pressionado
      minutos = 0; segundos = 0; //Resetar o tempo
      display.showNumberDecEx(100*minutos + segundos, &segto); //Exibir tempo no display
    }

    // -- Acionamento do Alarme --
    while (tempint == (minutos*100 + segundos)){
      digitalWrite(alarme, HIGH); //Ativar o alarme
      display.showNumberDecEx(tempint, &segto); //Exibir tempo no display

      int reset = digitalRead(botReset); //Variavel reset recebe a leitura de botReset
      if(reset){ //Se o botao for pressionado
        minutos = 0; segundos = 0; //Resetar o tempo
        digitalWrite(alarme, LOW); //Desativar o alarme
        display.showNumberDecEx(100*minutos + segundos, &segto); //Exibir tempo no display
      }
    }
    delay(1000);  //Tempo de espera da contagem
  }
minutos++; //Acrescenta a variavel minutos
}
