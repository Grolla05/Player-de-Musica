#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "func_musica.h"

#define SCREEN_WIDTH 128 // Adicione esta linha

const int BotaoProxima = 13;
const int BotaoAnterior = 11;
const int BotaoPlay = 9;
int indiceScroll = 0;
unsigned long tempoAnteriorScroll = 0;
const int VELOCIDADE_SCROLL = 300;
const int LARGURA_CARACTERE = 6;

void setup() {
  Serial.begin(9600);
  Wire.begin(); //Inicia a biblioteca Wire
  display.begin(); //Inicia o display OLED

  pinMode(BotaoProxima, INPUT_PULLUP);
  pinMode(BotaoAnterior, INPUT_PULLUP);
  pinMode(BotaoPlay, INPUT_PULLUP);
  pinMode(pinBuzzer, OUTPUT);
  display.clearDisplay();
  display.setTextSize(1);                 // Define o tamanho do texto
  display.setTextColor(SSD1306_WHITE);    // Define a cor do texto
  display.setCursor(0, 10);               // Define a posição do cursor (pixel X, pixel Y)
  display.println("Seja bem-vindo");
  display.setCursor(0, 25);
  display.println("ao Jukebox v1.0");
  display.display();                      // Envia o conteúdo para a tela
  delay(3000);
  desenharMenu(); // Chama a nova função para desenhar o menu inicial
}

void loop() {
  checarBotoes();
  atualizarMusica();
  atualizarTela();
}

void checarBotoes() {
  if (digitalRead(BotaoPlay) == LOW) {
    Serial.print("Botao play");
    iniciarMusica(indiceMusicaAtual);
    delay(200);
  } 
  else if (digitalRead(BotaoProxima) == LOW) {
    Serial.print("Botao Proximo");
    proximaMusica();
    delay(200);
  } 
  else if (digitalRead(BotaoAnterior) == LOW) {
    Serial.print("Botao Anterior");
    musicaAnterior();
    delay(200);
  }
}

void atualizarTela() {
  if (millis() - ultimaAtualizacaoTela > 50) { 
    if (estaTocando) {
      int totalDeNotas;
      switch (musicaSendoTocada) {
        case 0: totalDeNotas = notes_Takeonme; break;
        case 1: totalDeNotas = notes_Furelise; break;
        case 2: totalDeNotas = notes_Despacito; break;
        // Músicas a adicionar
        default: totalDeNotas = 1; break;
      }
      desenharTelaPlayer(notaAtual, totalDeNotas);
    } else {
      desenharMenu();
    }
    display.display();
    ultimaAtualizacaoTela = millis();
  }
}

void proximaMusica() {
  indiceMusicaAtual = (indiceMusicaAtual + 1) % totalDeMusicas;
  indiceScroll = 0;
  desenharMenu();
}

void musicaAnterior() {
  indiceMusicaAtual = (indiceMusicaAtual - 1 + totalDeMusicas) % totalDeMusicas;
  indiceScroll = 0;
  desenharMenu();
}


void iniciarMusica(int numeroDaMusica) {
  // Verifica se uma música já está tocando
  if (estaTocando) {
    // Se estiver, a ação é PARAR a música
    estaTocando = false;
    noTone(pinBuzzer); // Desliga o som do buzzer [cite: 4]
    
  } else {
    playerScrollX = 0;
    musicaSendoTocada = numeroDaMusica;
    estaTocando = true;
    notaAtual = 0;
    tempoProximaNota = millis();
  }
}

void desenharMenu() {
  String musicaSelecionada = musicas[indiceMusicaAtual]; 
  int larguraTexto = musicaSelecionada.length() * LARGURA_CARACTERE; 
  if (larguraTexto > SCREEN_WIDTH) { 
    if (millis() - tempoAnteriorScroll > VELOCIDADE_SCROLL) { 
      indiceScroll++;
      if (indiceScroll > larguraTexto) { 
        indiceScroll = 0; 
      }
      tempoAnteriorScroll = millis(); 
    }
  } else {
    indiceScroll = 0;
  }
  display.clearDisplay(); 
  display.setTextWrap(false);
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.println("Selecione uma musica:");
  display.drawFastHLine(0, 10, 128, SSD1306_WHITE);
  int yPos = 20; 
  for (int i = -1; i <= 1; i++) { 
    int indiceDaLista = (indiceMusicaAtual + (i+1) + totalDeMusicas) % totalDeMusicas; 
    String nomeMusica = musicas[indiceDaLista]; 
    if (i == 0) {
      display.fillRect(0, yPos - 2, 128, 12, SSD1306_INVERSE); 
      display.setTextColor(SSD1306_BLACK); 
      int xPos = (larguraTexto > SCREEN_WIDTH) ? -indiceScroll : 2; 
      display.setCursor(xPos, yPos); 
      display.print(nomeMusica);
      display.setTextColor(SSD1306_WHITE); 
    } else {
      display.setCursor(2, yPos); 
      display.print(nomeMusica);
    }
    yPos += 15; 
  }
  display.setTextWrap(true);
  display.display(); 
}
