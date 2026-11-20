#include "pitches.h"
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <avr/pgmspace.h>

//----------------------------------
//Melodia calma: trecho inicial de "Für Elise" (frequências em Hz; 0 = pausa)
int melodiaCalma[] = {
  659, 622, 659, 622, 659, 494, 587, 523, 440,
  262, 330, 440, 494,
  330, 415, 494, 523,
  330, 659, 622, 659, 622, 659, 494, 587, 523, 440,
  262, 330, 440, 494,
  330, 523, 494, 440
};

 //Duração de cada nota (quanto maior o número, mais curta a nota)
int duracaoCalma[] = {
  8, 8, 8, 8, 8, 8, 8, 8, 4,
  8, 8, 8, 4,
  8, 8, 8, 4,
  8, 8, 8, 8, 8, 8, 8, 8, 4,
  8, 8, 8, 4,
  8, 8, 8, 2
};
//----------------------------------
// Melodia alegre: tema do Super Mario (frequências em Hz; 0 = pausa)
int melodiaMario[] = {
  659, 659, 0, 659, 0, 523, 659, 0,
  784, 0, 0, 0, 392, 0, 0, 0,
  523, 0, 0, 392, 0, 0, 330, 0,
  0, 440, 0, 494, 0, 466, 440, 0,
  392, 659, 784, 880, 0, 698, 784, 0,
  659, 0, 523, 587, 494, 0, 0, 0
};

// Duração de cada nota do Mario
int duracaoMario[] = {
  8, 8, 8, 8, 8, 8, 8, 8,
  4, 8, 8, 8, 4, 8, 8, 8,
  4, 8, 8, 4, 8, 8, 4, 8,
  8, 8, 8, 8, 8, 8, 8, 8,
  6, 6, 6, 8, 8, 8, 8, 8,
  4, 8, 8, 8, 4, 8, 8, 8
};
//----------------------------------
LiquidCrystal_I2C lcd(0x27, 16, 2);

#define BUZZER_PIN 12

//Comando alegre (botao/led amarelo)
int botaoamarelo = 11;
int estadobotaoamarelo = 0;
int ledamarelo = 9;

//Comando triste (botao/led azul) /ação vai ser jogo da memoria
int botaoazul = 10;
int estadobotaoazul = 0;
int ledazul = 6;

//Comando raiva (botao/led vermelho) /ação vai ser a respiração em caixa
int botaovermelho = 2;
int estadobotaovermelho = 0;
int ledvermelho = 5;

//Comando medo (botao/led verde) /ação vai ser ouvir musica calma
int botaoverde = 8;
int estadobotaoverde = 0;
int ledverde = 3;

int leds[4] = {ledamarelo, ledazul, ledvermelho, ledverde};



void setup() {

  //LCD INICIALIZAÇÃO
  lcd.init();
  lcd.backlight();

  //Amarelo (feliz) 
  pinMode(botaoamarelo, INPUT);
  pinMode(ledamarelo, OUTPUT);

  //Azul (triste)
  pinMode(botaoazul, INPUT);
  pinMode(ledazul, OUTPUT);

  //Vermelho (raiva)
  pinMode(botaovermelho, INPUT);
  pinMode(ledvermelho, OUTPUT);

  //Verde (medo)
  pinMode(botaoverde, INPUT);
  pinMode(ledverde, OUTPUT);
}

void loop() {

  estadobotaoamarelo = digitalRead(botaoamarelo);
  estadobotaoazul = digitalRead(botaoazul);
  estadobotaovermelho = digitalRead(botaovermelho);
  estadobotaoverde = digitalRead(botaoverde);

  mostrarLCD(F("Ola, tudo bem?"), F("Como voce esta"));
  delay(1000);

  mostrarLCD(F("Feliz?"), F(""));
  digitalWrite(ledamarelo, HIGH);
  delay(2000);
  digitalWrite(ledamarelo, LOW);

  mostrarLCD(F("Triste?"), F(""));
  digitalWrite(ledazul, HIGH);
  delay(2000);
  digitalWrite(ledazul, LOW);


  mostrarLCD(F("Com Raiva?"), F(""));
  digitalWrite(ledvermelho, HIGH);
  delay(2000);
  digitalWrite(ledvermelho, LOW);


  mostrarLCD(F("Com Medo?"), F(""));
  digitalWrite(ledverde, HIGH);
  delay(2000);
  digitalWrite(ledverde, LOW);
  
  mostrarLCD(F("Feliz? Triste?"), F("Raiva? Medo?"));
  digitalWrite(ledamarelo, HIGH);
  digitalWrite(ledazul, HIGH);
  digitalWrite(ledvermelho, HIGH);
  digitalWrite(ledverde, HIGH);
 

  // Ação tomada pelo sistema com base nos sentimentos escolido pelo ususario
  if (estadobotaoamarelo == HIGH) {
    mostrarLCD(F("Voce esta feliz"), F("aeeeeeee"));
    musicaAlegre();
    void loop();

  }
  
  else if (estadobotaoazul == HIGH){
    mostrarLCD(F("Vamos jogar um"), F("jogo para animar"));
    delay(2500);
    mostrarLCD(F("Jogo da memoria"), F("Iniciado?"));
    delay(2500);
    mostrarLCD(F("Preste atenção"), F("Nos leds"));
    delay(2000);
    
    jogarMemoria();
    void loop();
  }

  else if (estadobotaovermelho == HIGH){
    mostrarLCD(F("Esta com raiva"), F("Vamos relaxar"));
    delay(2500);
    
    respiracaoCaixa();
    void loop();
  }

  else if (estadobotaoverde == HIGH){
    mostrarLCD(F("Vamos ouvir uma"), F("musica calma"));
    delay(2500);
    musicaCalma();
    void loop();
  }
}


void jogarMemoria() {
  int leds[4] = {ledamarelo, ledazul, ledvermelho, ledverde};
  int botoes[4] = {botaoamarelo, botaoazul, botaovermelho, botaoverde};
  
  int sequenciaPC[3]; // Sequencia de 3 passos para ser simples
  int sequenciaUsuario[3];

  // 1. O computador sorteia a sequência (valores de 0 a 3 correspondentes aos LEDs)
  for (int i = 0; i < 3; i++) {
    sequenciaPC[i] = random(0, 4); 
  }

  // 2. Mostra a sequência piscando os LEDs
  for (int i = 0; i < 3; i++) {
    int ledAtual = leds[sequenciaPC[i]];
    digitalWrite(ledAtual, HIGH);
    delay(800);
    digitalWrite(ledAtual, LOW);
    delay(400);
  }

  mostrarLCD(F("Sua vez! Aperte"), F("Os botões na ordem"));
  delay(2500);
  
  // 3. Lê as respostas do usuário
  int passosRegistrados = 0;
  unsigned long tempoInicio = millis();

  while (passosRegistrados < 3) {
    // Timeout de 10 segundos caso o usuário demore muito
    if (millis() - tempoInicio > 15000) {
      mostrarLCD(F("Tempo Esgotado!"), F("."));
      delay(2500);
  
      return;
    }

    for (int i = 0; i < 4; i++) {
      if (digitalRead(botoes[i]) == HIGH) {
        // Acende o LED correspondente ao botão apertado para dar feedback visual
        digitalWrite(leds[i], HIGH);
        
        sequenciaUsuario[passosRegistrados] = i;
        passosRegistrados++;
        
        delay(300); // Debounce simples
        digitalWrite(leds[i], LOW);
        
        // Espera soltar o botão
        while (digitalRead(botoes[i]) == HIGH);
      }
    }
  }

  // 4. Verifica se acertou
  bool acertou = true;
  for (int i = 0; i < 3; i++) {
    if (sequenciaPC[i] != sequenciaUsuario[i]) {
      acertou = false;
      break;
    }
  }

  if (acertou) {
    mostrarLCD(F("Parabéns! voce"), F("Acertou"));
    delay(2500);



//    mostrarLCD(F("Pode jogar"), F("Novamente"));
  //  delay(2500)
  


    // Pisca todos os LEDs de felicidade
    for(int p=0; p<3; p++){
      digitalWrite(ledamarelo, HIGH); digitalWrite(ledazul, HIGH); digitalWrite(ledvermelho, HIGH); digitalWrite(ledverde, HIGH);
      delay(200);
      digitalWrite(ledamarelo, LOW); digitalWrite(ledazul, LOW); digitalWrite(ledvermelho, LOW); digitalWrite(ledverde, LOW);
      delay(200);
    }
  } else {
    mostrarLCD(F("Errou a"), F("Sequencia"));
    delay(2500);
    
    mostrarLCD(F("Clique no botao"), F("verde"));
    delay(2500);
  }
}

void respiracaoCaixa() {
  // Passa por cada um dos 4 LEDs individualmente fazendo o ciclo de respirar
  for (int i = 0; i < 4; i++) {
    
    
    mostrarLCD(F("Respire"), F("."));
    delay(1000);
  
    for (int brilho = 0; brilho <= 255; brilho++) {
      analogWrite(leds[i], brilho);
      delay(10); 
    }

    mostrarLCD(F("Prenda a"), F("Respiracao"));
    delay(1000);

    mostrarLCD(F("Solte o ar"), F("."));
    delay(1000);
    // 2. Expirar (LED apaga devagar: do forte ao fraco)
    for (int brilho = 255; brilho >= 0; brilho--) {
      analogWrite(leds[i], brilho);
      delay(10); 
    }
    mostrarLCD(F("Segure a"), F("Respiracao"));
    delay(2500);
    mostrarLCD(F("Pode respirar"), F("Normalmente"));
    delay(2500);
  }
}

void musicaAlegre() {
  int totalNotas = sizeof(duracaoMario) / sizeof(int);

  for (int i = 0; i < totalNotas; i++) {
    int duracao = 1000 / duracaoMario[i];

    if (melodiaMario[i] > 0) {
      tone(BUZZER_PIN, melodiaMario[i], duracao);
    }

    int pausa = duracao * 1.25;
    delay(pausa);
    noTone(BUZZER_PIN);
  }
}

void musicaCalma() {
  int totalNotas = sizeof(duracaoCalma) / sizeof(int);

  for (int i = 0; i < totalNotas; i++) {
    int duracao = 1100 / duracaoCalma[i]; // Um pouco mais lento para ficar bem calmo

    if (melodiaCalma[i] > 0) {
      tone(BUZZER_PIN, melodiaCalma[i], duracao);
    }

    int pausa = duracao * 1.25;
    delay(pausa);
    noTone(BUZZER_PIN);
  }
}


void mostrarLCD(const __FlashStringHelper* linha1, const __FlashStringHelper* linha2) {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(linha1);
  lcd.setCursor(0, 1);
  lcd.print(linha2);
}