#ifndef FUNC_MUSICA_H
#define FUNC_MUSICA_H

#include <Arduino.h>
#include <Adafruit_SSD1306.h>
#include "pitches.h"
#include "assets.h"

#define SCREEN_WIDTH 128

extern Adafruit_SSD1306 display;
extern const String musicas[];
extern const int totalDeMusicas;
extern int indiceMusicaAtual;
extern bool estaTocando;
extern const int pinBuzzer;
extern int musicaSendoTocada;
extern int notaAtual;
extern unsigned long tempoProximaNota;
extern unsigned long ultimaAtualizacaoTela;
extern int playerScrollX;
extern const int notes_Takeonme;
extern const int notes_Furelise;
extern const int notes_Despacito;

// --- DECLARAÇÕES DAS FUNÇÕES (PROTÓTIPOS) ---
void atualizarMusica();
void desenharTelaPlayer(int notaAtual, int totalDeNotas); // <-- MUDANÇA AQUI
void redesenharMenuPrincipal();
void desenharMenu();

#endif