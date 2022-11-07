#include "pitches.h"

#define ledBranco 8
#define ledAzul 15
#define ledVerde 6
#define ledAmarelo 4

int ldr = 1;//Atribui 1 a variável ldr
int valorldr = 0;//Declara a variável valorldr como inteiro
int buzzer = 38; //Atribui 38 a variável buzzer
int botao1 = 9; //Atribui 9 a variável botão1
int botao2 = 10; //Atribui 10 a variável botão2
int botao1Estado = 0; //Representa Estado do botão1
int botao2Estado = 0; //Representa Estado do botão2

int contador = 0; 
int armazenaVetor[4]; //Vetor de armazenamento do valor em binário 

void setup() {
  pinMode(ldr, INPUT);//Define ldr (pino analógico 1) como saída
  pinMode(buzzer, OUTPUT); //Define buzzer (pino 38) como saída
  pinMode(ledBranco, OUTPUT); //Define led como saída
  pinMode(ledAzul, OUTPUT);
  pinMode(ledVerde, OUTPUT);
  pinMode(ledAmarelo, OUTPUT);
  pinMode(botao1, INPUT_PULLUP); //Define botão como input_pullup
  pinMode(botao2, INPUT_PULLUP);
  Serial.begin(9600);//Inicialização da comunicação serial, com taxa de transferência em bits por segundo de 9600
}

void loop() {

  //Faz a leitura do valor do ldr de 0 a 4095 e após isso, converte para os valores de 0 a 15. Os quais serão usados na conversão para valores binários em string.
  valorldr = analogRead(ldr);
  int valorldrmapeado = map(valorldr, 0, 4095, 0, 15);

  delay (1000);

  //Salva valores do LDR convertidos para o formato de caratér, que serão utilizados posteriormente na conversão para valores binários em string.
  Serial.println(valorldrmapeado);

  botao1Estado = digitalRead(botao1);
  botao2Estado = digitalRead(botao2);

//Configuração do botão 1 para realização do armazamento dos valores do LDR, indicando se os botões foram apertados ou não.
  if (botao1Estado == HIGH && contador <= 3) {
    Serial.println("Button1 Apertado");

//Função para armazenar valores mapeados pelo LDR e convertidos em binário, e contagem de +1 valor na leitura dos 4 valores dos leds e buzzer
//que forem adicionados a cada clique no botão.

    Serial.println(contador);
    armazenaVetor[contador] = valorldrmapeado; 
    contador += 1;

  } else if (botao1Estado == LOW){
    Serial.println("Button1 Não Apertado");
  }

//Indica o armazenamento de valores, que deverão ser menores ou igual a 3.
  for (int i = 0; i <= 3; i++){
    Serial.print(armazenaVetor[i]);
    Serial.print(" ");
  }

//Configuração do botão 2 para realização da reprodução dos valores armazenados.
if (botao2Estado == HIGH) {

//Coordena como será realizada a reprodução dos valores armazenados.
    for (int i = 0; i <= 3; i++){
      Serial.print("Reproduzindo: ");
      Serial.println(armazenaVetor[i]);
      ldr2b(armazenaVetor[i]); //reproduz o código criado para conversão dos números binários em formato de string, onde também está contido a ativação dos leds e buzzer.
    }

//Realiza o resete dos valores que estão contidos no vetor, após a reprodução feita pelo botão 2, retornando todas as respectivas posições dos vetores para 0.
    for (int i = 0; i <= 3; i++){
      armazenaVetor[0] = 0;
      armazenaVetor[1] = 0;
     armazenaVetor[2] = 0;
      armazenaVetor[3] = 0;
    }
    Serial.println("Button2 Apertado");

  } else if (botao1Estado == LOW){
    Serial.println("Button2 Não Apertado");
  }

}

//Função char* ldr2b que realiza a conversão dos valores lidos pelo LDR de 0 a 15 para retornar valor binários em string.

//Leds: Ativados pelo digitalWrite, variando em sequência de 0 a 15
//Buzer: Variando de tons para cada número binário de 0 a 15
//Serial.printin("Entrou...") = utilizado no serial monitor para verificação dos valores que estão sendo retornados de 0 a 15 para cada string binário

char* ldr2b (int valorldrmapeado2){ 

   if (valorldrmapeado2 == 0) {
    Serial.println("Entrou 0");
    digitalWrite(ledBranco, HIGH);
    digitalWrite(ledAzul, LOW);
    digitalWrite(ledVerde, LOW);
    digitalWrite(ledAmarelo, LOW);
    tone (buzzer, NOTE_C4);
    return "0000";
  }

  if (valorldrmapeado2 == 1) {
    Serial.println("Entrou 1");
    digitalWrite(ledBranco, LOW);
    digitalWrite(ledAzul, HIGH);
    digitalWrite(ledVerde, LOW);
    digitalWrite(ledAmarelo, LOW);
    tone (buzzer, NOTE_G3);
    return "0001";
  }

  if (valorldrmapeado2 == 2) { 
    Serial.println("Entrou 2");
    digitalWrite(ledBranco, LOW);
    digitalWrite(ledAzul, LOW);
    digitalWrite(ledVerde, HIGH);
    digitalWrite(ledAmarelo, LOW); 
    tone (buzzer, NOTE_A3);
    return "0010";
  }

  if (valorldrmapeado2 == 3) {   
    Serial.println("Entrou 3");
    digitalWrite(ledBranco, LOW);
    digitalWrite(ledAzul, LOW);
    digitalWrite(ledVerde, LOW);
    digitalWrite(ledAmarelo, HIGH); 
    tone (buzzer, NOTE_B3);
    return "0011"; 
  }

  if (valorldrmapeado2 == 4) { 
    Serial.println("Entrou 4");
    digitalWrite(ledBranco, HIGH);
    digitalWrite(ledAzul, LOW);
    digitalWrite(ledVerde, LOW);
    digitalWrite(ledAmarelo, LOW);
    tone (buzzer, NOTE_A5);
    return "0100";
  }

  if (valorldrmapeado2 == 5) { 
    Serial.println("Entrou 5");
    digitalWrite(ledBranco, LOW);
    digitalWrite(ledAzul, HIGH);
    digitalWrite(ledVerde, LOW);
    digitalWrite(ledAmarelo, LOW); 
    tone (buzzer, NOTE_B5);
    return "0101";
  }

  if (valorldrmapeado2 == 6) { 
    Serial.println("Entrou 6");
    digitalWrite(ledBranco, LOW);
    digitalWrite(ledAzul, LOW);
    digitalWrite(ledVerde, HIGH);
    digitalWrite(ledAmarelo, LOW); 
    tone (buzzer, NOTE_C6);
    return "0110";
  }

  if (valorldrmapeado2 == 7) { 
    Serial.println("Entrou 7");
    digitalWrite(ledBranco, LOW);
    digitalWrite(ledAzul, LOW);
    digitalWrite(ledVerde, LOW);
    digitalWrite(ledAmarelo, HIGH); 
    tone (buzzer, NOTE_G5);
    return "0111";
  }

  if (valorldrmapeado2 == 8) { 
    Serial.println("Entrou 8");
    digitalWrite(ledBranco, HIGH);
    digitalWrite(ledAzul, LOW);
    digitalWrite(ledVerde, LOW);
    digitalWrite(ledAmarelo, LOW); 
    tone (buzzer, NOTE_C7);
    return "1000"; 
  }

  if (valorldrmapeado2 == 9) { 
    Serial.println("Entrou 9");
    digitalWrite(ledBranco, LOW);
    digitalWrite(ledAzul, HIGH);
    digitalWrite(ledVerde, LOW);
    digitalWrite(ledAmarelo, LOW);  
    tone (buzzer, NOTE_G7);
    return "1001";
  }

  if (valorldrmapeado2 == 10) {
    Serial.println("Entrou 10");
    digitalWrite(ledBranco, LOW);
    digitalWrite(ledAzul, LOW);
    digitalWrite(ledVerde, HIGH);
    digitalWrite(ledAmarelo, LOW);   
    tone (buzzer, NOTE_A7);
    return "1010";  
  }

  if (valorldrmapeado2 == 11) {
    Serial.println("Entrou 11");
    digitalWrite(ledBranco, LOW);
    digitalWrite(ledAzul, LOW);
    digitalWrite(ledVerde, LOW);
    digitalWrite(ledAmarelo, HIGH); 
    tone (buzzer, NOTE_C8);
    return "1011";  
  }

  if (valorldrmapeado2 == 12) { 
    Serial.println("Entrou 12");
    digitalWrite(ledBranco, HIGH);
    digitalWrite(ledAzul, LOW);
    digitalWrite(ledVerde, LOW);
    digitalWrite(ledAmarelo, LOW);
    tone (buzzer, NOTE_C4);
    return "1100";  
  }

  if (valorldrmapeado2 == 13) { 
    Serial.println("Entrou 13");
    digitalWrite(ledBranco, LOW);
    digitalWrite(ledAzul, HIGH);
    digitalWrite(ledVerde, LOW);
    digitalWrite(ledAmarelo, LOW); 
    tone (buzzer, NOTE_G3);
    return "1101";
  }

  if (valorldrmapeado2 == 14) {
    Serial.println("Entrou 14");
    digitalWrite(ledBranco, LOW);
    digitalWrite(ledAzul, LOW);
    digitalWrite(ledVerde, HIGH);
    digitalWrite(ledAmarelo, LOW);
    tone (buzzer,NOTE_A3);
    return "1110"; 
  }

  if (valorldrmapeado2 == 15) {
    Serial.println("Entrou 15");
    digitalWrite(ledBranco, HIGH);
    digitalWrite(ledAzul, HIGH);
    digitalWrite(ledVerde, HIGH);
    digitalWrite(ledAmarelo, HIGH); 
    tone (buzzer, NOTE_C4);
    return "1111"; 
  }

  delay (100);
}