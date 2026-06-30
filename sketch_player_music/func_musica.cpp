#include "func_musica.h"
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "assets.h"

Adafruit_SSD1306 display;

const String musicas[] = {
  "Take on Me - A-HA",
  "Fur Elise - BEETHOVEN",
  "Despacito - LUIS FONSE",
};
const int totalDeMusicas = sizeof(musicas) / sizeof(String);

extern const int pinBuzzer = 2;
int indiceMusicaAtual = 0;
bool estaTocando = false;
int musicaSendoTocada = 0;
int notaAtual = 0;
unsigned long tempoProximaNota = 0;
unsigned long ultimaAtualizacaoTela = 0;

const int melody_Takeonme[] PROGMEM = {
  NOTE_FS5,8, NOTE_FS5,8,NOTE_D5,8, NOTE_B4,8, REST,8, NOTE_B4,8, REST,8, NOTE_E5,8, 
  REST,8, NOTE_E5,8, REST,8, NOTE_E5,8, NOTE_GS5,8, NOTE_GS5,8, NOTE_A5,8, NOTE_B5,8,
  NOTE_A5,8, NOTE_A5,8, NOTE_A5,8, NOTE_E5,8, REST,8, NOTE_D5,8, REST,8, NOTE_FS5,8, 
  REST,8, NOTE_FS5,8, REST,8, NOTE_FS5,8, NOTE_E5,8, NOTE_E5,8, NOTE_FS5,8, NOTE_E5,8,
  NOTE_FS5,8, NOTE_FS5,8,NOTE_D5,8, NOTE_B4,8, REST,8, NOTE_B4,8, REST,8, NOTE_E5,8, 
  
  REST,8, NOTE_E5,8, REST,8, NOTE_E5,8, NOTE_GS5,8, NOTE_GS5,8, NOTE_A5,8, NOTE_B5,8,
  NOTE_A5,8, NOTE_A5,8, NOTE_A5,8, NOTE_E5,8, REST,8, NOTE_D5,8, REST,8, NOTE_FS5,8, 
  REST,8, NOTE_FS5,8, REST,8, NOTE_FS5,8, NOTE_E5,8, NOTE_E5,8, NOTE_FS5,8, NOTE_E5,8,
  NOTE_FS5,8, NOTE_FS5,8,NOTE_D5,8, NOTE_B4,8, REST,8, NOTE_B4,8, REST,8, NOTE_E5,8, 
  REST,8, NOTE_E5,8, REST,8, NOTE_E5,8, NOTE_GS5,8, NOTE_GS5,8, NOTE_A5,8, NOTE_B5,8,
  
  NOTE_A5,8, NOTE_A5,8, NOTE_A5,8, NOTE_E5,8, REST,8, NOTE_D5,8, REST,8, NOTE_FS5,8, 
  REST,8, NOTE_FS5,8, REST,8, NOTE_FS5,8, NOTE_E5,8, NOTE_E5,8, NOTE_FS5,8, NOTE_E5,8,
};
const int notes_Takeonme = sizeof(melody_Takeonme) / sizeof(melody_Takeonme[0]) / 2;
const int tempo_Takeonme = 140;
const int wholenote_Takeonme = (60000 * 4) / tempo_Takeonme;

const int melody_Furelise[] PROGMEM = {
  NOTE_E5, 16, NOTE_DS5, 16,
  NOTE_E5, 16, NOTE_DS5, 16, NOTE_E5, 16, NOTE_B4, 16, NOTE_D5, 16, NOTE_C5, 16,
  NOTE_A4, -8, NOTE_C4, 16, NOTE_E4, 16, NOTE_A4, 16,
  NOTE_B4, -8, NOTE_E4, 16, NOTE_GS4, 16, NOTE_B4, 16,
  NOTE_C5, 8,  REST, 16, NOTE_E4, 16, NOTE_E5, 16,  NOTE_DS5, 16,
  NOTE_E5, 16, NOTE_DS5, 16, NOTE_E5, 16, NOTE_B4, 16, NOTE_D5, 16, NOTE_C5, 16,
  NOTE_A4, -8, NOTE_C4, 16, NOTE_E4, 16, NOTE_A4, 16, 
  NOTE_B4, -8, NOTE_E4, 16, NOTE_C5, 16, NOTE_B4, 16, 
  NOTE_A4 , 4, REST, 8,
  NOTE_E5, 16, NOTE_DS5, 16,
  NOTE_E5, 16, NOTE_DS5, 16, NOTE_E5, 16, NOTE_B4, 16, NOTE_D5, 16, NOTE_C5, 16,
  NOTE_A4, -8, NOTE_C4, 16, NOTE_E4, 16, NOTE_A4, 16,
  NOTE_B4, -8, NOTE_E4, 16, NOTE_GS4, 16, NOTE_B4, 16,
  NOTE_C5, 8,  REST, 16, NOTE_E4, 16, NOTE_E5, 16,  NOTE_DS5, 16,
  NOTE_E5, 16, NOTE_DS5, 16, NOTE_E5, 16, NOTE_B4, 16, NOTE_D5, 16, NOTE_C5, 16,
  NOTE_A4, -8, NOTE_C4, 16, NOTE_E4, 16, NOTE_A4, 16, 
  NOTE_B4, -8, NOTE_E4, 16, NOTE_C5, 16, NOTE_B4, 16, 
  NOTE_A4, 8, REST, 16, NOTE_B4, 16, NOTE_C5, 16, NOTE_D5, 16,
  NOTE_E5, -8, NOTE_G4, 16, NOTE_F5, 16, NOTE_E5, 16, 
  NOTE_D5, -8, NOTE_F4, 16, NOTE_E5, 16, NOTE_D5, 16,
  NOTE_C5, -8, NOTE_E4, 16, NOTE_D5, 16, NOTE_C5, 16,
  NOTE_B4, 8, REST, 16, NOTE_E4, 16, NOTE_E5, 16, REST, 16,
  REST, 16, NOTE_E5, 16, NOTE_E6, 16, REST, 16, REST, 16, NOTE_DS5, 16,
  NOTE_E5, 16, REST, 16, REST, 16, NOTE_DS5, 16, NOTE_E5, 16, NOTE_DS5, 16,
  NOTE_E5, 16, NOTE_DS5, 16, NOTE_E5, 16, NOTE_B4, 16, NOTE_D5, 16, NOTE_C5, 16,
  NOTE_A4, 8, REST, 16, NOTE_C4, 16, NOTE_E4, 16, NOTE_A4, 16,
  NOTE_B4, 8, REST, 16, NOTE_E4, 16, NOTE_GS4, 16, NOTE_B4, 16,
  NOTE_C5, 8, REST, 16, NOTE_E4, 16, NOTE_E5, 16,  NOTE_DS5, 16,
  NOTE_E5, 16, NOTE_DS5, 16, NOTE_E5, 16, NOTE_B4, 16, NOTE_D5, 16, NOTE_C5, 16,
  NOTE_A4, 8, REST, 16, NOTE_C4, 16, NOTE_E4, 16, NOTE_A4, 16,
  NOTE_B4, 8, REST, 16, NOTE_E4, 16, NOTE_C5, 16, NOTE_B4, 16,
  NOTE_A4, 8, REST, 16, NOTE_B4, 16, NOTE_C5, 16, NOTE_D5, 16,
  NOTE_E5, -8, NOTE_G4, 16, NOTE_F5, 16, NOTE_E5, 16, 
  NOTE_D5, -8, NOTE_F4, 16, NOTE_E5, 16, NOTE_D5, 16,
  NOTE_C5, -8, NOTE_E4, 16, NOTE_D5, 16, NOTE_C5, 16,
  NOTE_B4, 8, REST, 16, NOTE_E4, 16, NOTE_E5, 16, REST, 16,
  REST, 16, NOTE_E5, 16, NOTE_E6, 16, REST, 16, REST, 16, NOTE_DS5, 16,
  NOTE_E5, 16, REST, 16, REST, 16, NOTE_DS5, 16, NOTE_E5, 16, NOTE_DS5, 16,
  NOTE_E5, 16, NOTE_DS5, 16, NOTE_E5, 16, NOTE_B4, 16, NOTE_D5, 16, NOTE_C5, 16,
  NOTE_A4, 8, REST, 16, NOTE_C4, 16, NOTE_E4, 16, NOTE_A4, 16,
  NOTE_B4, 8, REST, 16, NOTE_E4, 16, NOTE_GS4, 16, NOTE_B4, 16,
  NOTE_C5, 8, REST, 16, NOTE_E4, 16, NOTE_E5, 16,  NOTE_DS5, 16,
  NOTE_E5, 16, NOTE_DS5, 16, NOTE_E5, 16, NOTE_B4, 16, NOTE_D5, 16, NOTE_C5, 16,
  NOTE_A4, 8, REST, 16, NOTE_C4, 16, NOTE_E4, 16, NOTE_A4, 16,
  NOTE_B4, 8, REST, 16, NOTE_E4, 16, NOTE_C5, 16, NOTE_B4, 16,
  NOTE_A4, 8, REST, 16, NOTE_C5, 16, NOTE_C5, 16, NOTE_C5, 16,
  NOTE_C5 , 4, NOTE_F5, -16, NOTE_E5, 32,
  NOTE_E5, 8, NOTE_D5, 8, NOTE_AS5, -16, NOTE_A5, 32,
  NOTE_A5, 16, NOTE_G5, 16, NOTE_F5, 16, NOTE_E5, 16, NOTE_D5, 16, NOTE_C5, 16,
  NOTE_AS4, 8, NOTE_A4, 8, NOTE_A4, 32, NOTE_G4, 32, NOTE_A4, 32, NOTE_B4, 32,
  NOTE_C5 , 4, NOTE_D5, 16, NOTE_DS5, 16,
  NOTE_E5, -8, NOTE_E5, 16, NOTE_F5, 16, NOTE_A4, 16,
  NOTE_C5 , 4,  NOTE_D5, -16, NOTE_B4, 32,
  NOTE_C5, 32, NOTE_G5, 32, NOTE_G4, 32, NOTE_G5, 32, NOTE_A4, 32, NOTE_G5, 32, NOTE_B4, 32, NOTE_G5, 32, NOTE_C5, 32, NOTE_G5, 32, NOTE_D5, 32, NOTE_G5, 32, //33
  NOTE_E5, 32, NOTE_G5, 32, NOTE_C6, 32, NOTE_B5, 32, NOTE_A5, 32, NOTE_G5, 32, NOTE_F5, 32, NOTE_E5, 32, NOTE_D5, 32, NOTE_G5, 32, NOTE_F5, 32, NOTE_D5, 32,
  NOTE_C5, 32, NOTE_G5, 32, NOTE_G4, 32, NOTE_G5, 32, NOTE_A4, 32, NOTE_G5, 32, NOTE_B4, 32, NOTE_G5, 32, NOTE_C5, 32, NOTE_G5, 32, NOTE_D5, 32, NOTE_G5, 32,
  NOTE_E5, 32, NOTE_G5, 32, NOTE_C6, 32, NOTE_B5, 32, NOTE_A5, 32, NOTE_G5, 32, NOTE_F5, 32, NOTE_E5, 32, NOTE_D5, 32, NOTE_G5, 32, NOTE_F5, 32, NOTE_D5, 32, //36
  NOTE_E5, 32, NOTE_F5, 32, NOTE_E5, 32, NOTE_DS5, 32, NOTE_E5, 32, NOTE_B4, 32, NOTE_E5, 32, NOTE_DS5, 32, NOTE_E5, 32, NOTE_B4, 32, NOTE_E5, 32, NOTE_DS5, 32,
  NOTE_E5, -8, NOTE_B4, 16, NOTE_E5, 16, NOTE_DS5, 16,
  NOTE_E5, -8, NOTE_B4, 16, NOTE_E5, 16, REST, 16,
  REST, 16, NOTE_DS5, 16, NOTE_E5, 16, REST, 16, REST, 16, NOTE_DS5, 16,
  NOTE_E5, 16, NOTE_DS5, 16, NOTE_E5, 16, NOTE_B4, 16, NOTE_D5, 16, NOTE_C5, 16,
  NOTE_A4, 8, REST, 16, NOTE_C4, 16, NOTE_E4, 16, NOTE_A4, 16,
  NOTE_B4, 8, REST, 16, NOTE_E4, 16, NOTE_GS4, 16, NOTE_B4, 16,
  NOTE_C5, 8, REST, 16, NOTE_E4, 16, NOTE_E5, 16, NOTE_DS5, 16,
  NOTE_E5, 16, NOTE_DS5, 16, NOTE_E5, 16, NOTE_B4, 16, NOTE_D5, 16, NOTE_C5, 16,
  NOTE_A4, 8, REST, 16, NOTE_C4, 16, NOTE_E4, 16, NOTE_A4, 16,
  NOTE_B4, 8, REST, 16, NOTE_E4, 16, NOTE_C5, 16, NOTE_B4, 16,
  NOTE_A4, 8, REST, 16, NOTE_B4, 16, NOTE_C5, 16, NOTE_D5, 16,
  NOTE_E5, -8, NOTE_G4, 16, NOTE_F5, 16, NOTE_E5, 16,
  NOTE_D5, -8, NOTE_F4, 16, NOTE_E5, 16, NOTE_D5, 16,
  NOTE_C5, -8, NOTE_E4, 16, NOTE_D5, 16, NOTE_C5, 16,
  NOTE_B4, 8, REST, 16, NOTE_E4, 16, NOTE_E5, 16, REST, 16,
  REST, 16, NOTE_E5, 16, NOTE_E6, 16, REST, 16, REST, 16, NOTE_DS5, 16,
  NOTE_E5, 16, REST, 16, REST, 16, NOTE_DS5, 16, NOTE_E5, 16, NOTE_D5, 16,
  NOTE_E5, 16, NOTE_DS5, 16, NOTE_E5, 16, NOTE_B4, 16, NOTE_D5, 16, NOTE_C5, 16,
  NOTE_A4, 8, REST, 16, NOTE_C4, 16, NOTE_E4, 16, NOTE_A4, 16,
  NOTE_B4, 8, REST, 16, NOTE_E4, 16, NOTE_GS4, 16, NOTE_B4, 16,
  NOTE_C5, 8, REST, 16, NOTE_E4, 16, NOTE_E5, 16, NOTE_DS5, 16,
  NOTE_E5, 16, NOTE_DS5, 16, NOTE_E5, 16, NOTE_B4, 16, NOTE_D5, 16, NOTE_C5, 16,
  NOTE_A4, 8, REST, 16, NOTE_C4, 16, NOTE_E4, 16, NOTE_A4, 16,
  NOTE_B4, 8, REST, 16, NOTE_E4, 16, NOTE_C5, 16, NOTE_B4, 16,
  NOTE_A4, 8, REST, 16, REST, 16, REST, 8, 
  NOTE_CS5 , -4, 
  NOTE_D5 , 4, NOTE_E5, 16, NOTE_F5, 16,
  NOTE_F5 , 4, NOTE_F5, 8, 
  NOTE_E5 , -4,
  NOTE_D5 , 4, NOTE_C5, 16, NOTE_B4, 16,
  NOTE_A4 , 4, NOTE_A4, 8,
  NOTE_A4, 8, NOTE_C5, 8, NOTE_B4, 8,
  NOTE_A4 , -4,
  NOTE_CS5 , -4,
  NOTE_D5 , 4, NOTE_E5, 16, NOTE_F5, 16,
  NOTE_F5 , 4, NOTE_F5, 8,
  NOTE_F5 , -4,
  NOTE_DS5 , 4, NOTE_D5, 16, NOTE_C5, 16,
  NOTE_AS4 , 4, NOTE_A4, 8,
  NOTE_GS4 , 4, NOTE_G4, 8,
  NOTE_A4 , -4,
  NOTE_B4 , 4, REST, 8,
  NOTE_A3, -32, NOTE_C4, -32, NOTE_E4, -32, NOTE_A4, -32, NOTE_C5, -32, NOTE_E5, -32, NOTE_D5, -32, NOTE_C5, -32, NOTE_B4, -32,
  NOTE_A4, -32, NOTE_C5, -32, NOTE_E5, -32, NOTE_A5, -32, NOTE_C6, -32, NOTE_E6, -32, NOTE_D6, -32, NOTE_C6, -32, NOTE_B5, -32,
  NOTE_A4, -32, NOTE_C5, -32, NOTE_E5, -32, NOTE_A5, -32, NOTE_C6, -32, NOTE_E6, -32, NOTE_D6, -32, NOTE_C6, -32, NOTE_B5, -32,
  NOTE_AS5, -32, NOTE_A5, -32, NOTE_GS5, -32, NOTE_G5, -32, NOTE_FS5, -32, NOTE_F5, -32, NOTE_E5, -32, NOTE_DS5, -32, NOTE_D5, -32,
  NOTE_CS5, -32, NOTE_C5, -32, NOTE_B4, -32, NOTE_AS4, -32, NOTE_A4, -32, NOTE_GS4, -32, NOTE_G4, -32, NOTE_FS4, -32, NOTE_F4, -32,
  NOTE_E4, 16, NOTE_DS5, 16, NOTE_E5, 16, NOTE_B4, 16, NOTE_D5, 16, NOTE_C5, 16,
  NOTE_A4, -8, NOTE_C4, 16, NOTE_E4, 16, NOTE_A4, 16,
  NOTE_B4, -8, NOTE_E4, 16, NOTE_GS4, 16, NOTE_B4, 16,
  NOTE_C5, 8, REST, 16, NOTE_E4, 16, NOTE_E5, 16, NOTE_DS5, 16,
  NOTE_E5, 16, NOTE_DS5, 16, NOTE_E5, 16, NOTE_B4, 16, NOTE_D5, 16, NOTE_C5, 16, 
  NOTE_A4, -8, NOTE_C4, 16, NOTE_E4, 16, NOTE_A4, 16, 
  NOTE_B4, -8, NOTE_E4, 16, NOTE_C5, 16, NOTE_B4, 16, 
  NOTE_A4, -8, REST, -8,
  REST, -8, NOTE_G4, 16, NOTE_F5, 16, NOTE_E5, 16,
  NOTE_D5 , 4, REST, 8,
  REST, -8, NOTE_E4, 16, NOTE_D5, 16, NOTE_C5, 16,
  NOTE_B4, -8, NOTE_E4, 16, NOTE_E5, 8,
  NOTE_E5, 8, NOTE_E6, -8, NOTE_DS5, 16,
  NOTE_E5, 16, REST, 16, REST, 16, NOTE_DS5, 16, NOTE_E5, 16, NOTE_DS5, 16,
  NOTE_E5, 16, NOTE_DS5, 16, NOTE_E5, 16, NOTE_B4, 16, NOTE_D5, 16, NOTE_C5, 16,
  NOTE_A4, -8, NOTE_C4, 16, NOTE_E4, 16, NOTE_A4, 16,
  NOTE_B4, -8, NOTE_E4, 16, NOTE_GS4, 16, NOTE_B4, 16,
  NOTE_C5, 8, REST, 16, NOTE_E4, 16, NOTE_E5, 16, NOTE_DS5, 16, //102
  NOTE_E5, 16, NOTE_DS5, 16, NOTE_E5, 16, NOTE_B4, 16, NOTE_D5, 16, NOTE_C5, 16,
  NOTE_A4, -8, NOTE_C4, 16, NOTE_E4, 16, NOTE_A4, 16,
  NOTE_B4, -8, NOTE_E4, 16, NOTE_C5, 16, NOTE_B4, 16,
  NOTE_A4 , -4,
};
const int notes_Furelise = sizeof(melody_Furelise) / sizeof(melody_Furelise[0]) / 2;
const int tempo_Furelise = 80;
const int wholenote_Furelise = (60000 * 4) / tempo_Furelise;

const int melody_Despacito[] PROGMEM = {
  NOTE_D5, 4, NOTE_CS5, 4, NOTE_B4, 10, NOTE_G4, 10, NOTE_G4, 20, NOTE_G4, 20, NOTE_G4, 20, NOTE_G4, 20,
  NOTE_G4, 20, NOTE_B4, 20, NOTE_B4, 20, NOTE_B4, 20, NOTE_B4, 10, NOTE_A4, 20, NOTE_B4, 10, NOTE_GS4, 7,
  NOTE_GS4, 20, NOTE_GS4, 20, NOTE_GS4, 20, NOTE_GS4, 20, NOTE_GS4, 20, NOTE_B4, 20, NOTE_B4, 20, NOTE_B4, 20,
  NOTE_B4, 10, NOTE_CS5, 20, NOTE_D5, 10, NOTE_A4, 7, NOTE_A4, 20, NOTE_A4, 20, NOTE_A4, 20, NOTE_A4, 64,
  NOTE_A4, 72, NOTE_A4, 20, NOTE_D5, 20, NOTE_D5, 20, NOTE_D5, 58, NOTE_D5, 58, NOTE_D5, 10, NOTE_E5, 20,
  NOTE_E5, 10, NOTE_CS5, 4, NOTE_D5, 5, NOTE_CS5, 5, NOTE_B4, 10, NOTE_G4, 10, NOTE_G4, 20,
  NOTE_G4, 20, NOTE_G4, 20, NOTE_G4, 20, NOTE_G4, 20, NOTE_B4, 58, NOTE_B4, 58, NOTE_B4, 20, NOTE_B4, 20,
  NOTE_B4, 10, NOTE_A4, 20, NOTE_B4, 10, NOTE_GS4, 10, NOTE_GS4, 20, NOTE_GS4, 64, NOTE_GS4, 72,
  NOTE_GS4, 20, NOTE_GS4, 20, NOTE_GS4, 20, NOTE_B4, 20, NOTE_B4, 20, NOTE_B4, 20, NOTE_B4, 10, NOTE_CS5, 20,
  NOTE_D5, 10, NOTE_A4, 7, NOTE_A4, 20, NOTE_A4, 42, NOTE_A4, 42, NOTE_A4, 20, NOTE_A4, 20,
  NOTE_A4, 20, NOTE_D5, 20, NOTE_D5, 20, NOTE_D5, 52, NOTE_D5, 52, NOTE_D5, 10, NOTE_E5, 10,
  NOTE_E5, 10, NOTE_CS5, 20, NOTE_A5, 20, NOTE_A5, 20, NOTE_A5, 20, NOTE_A5, 20, NOTE_A5, 20, NOTE_A5, 20,
  NOTE_A5, 20, NOTE_A5, 20, NOTE_A5, 20, NOTE_A5, 20, NOTE_A5, 7, NOTE_FS5, 20, NOTE_E5, 20, NOTE_FS5, 20,
  NOTE_E5, 20, NOTE_FS5, 10, NOTE_E5, 20, NOTE_FS5, 10, NOTE_E5, 20, NOTE_FS5, 20, NOTE_E5, 20, NOTE_FS5, 10,
  NOTE_G5, 20, NOTE_G5, 10, NOTE_D5, 7, NOTE_G5, 10, NOTE_G5, 20, NOTE_G5, 20, NOTE_G5, 20, NOTE_G5, 20,
  NOTE_G5, 22, NOTE_G5, 581, NOTE_A5, 21, NOTE_A5, 10, NOTE_FS5, 24, NOTE_A5, 14, NOTE_FS5, 14,
  NOTE_A5, 10, NOTE_FS5, 20, NOTE_A5, 10, NOTE_FS5, 20, NOTE_A5, 10, NOTE_FS5, 20, NOTE_A5, 10, NOTE_G5, 20,
  NOTE_G5, 10, NOTE_D5, 7, NOTE_G5, 10, NOTE_G5, 20, NOTE_G5, 20, NOTE_G5, 20, NOTE_G5, 20, NOTE_G5, 23,
  NOTE_G5, 581, NOTE_A5, 21, NOTE_A5, 10, NOTE_FS5, 12, NOTE_FS5, 20, NOTE_FS5, 20, NOTE_FS5, 20,
  NOTE_FS5, 20, NOTE_A5, 10, NOTE_G5, 20, NOTE_FS5, 10, NOTE_E5, 10, NOTE_E5, 20, NOTE_E5, 20,
  NOTE_E5, 20, NOTE_E5, 20, NOTE_E5, 20, NOTE_E5, 20, NOTE_E5, 20, NOTE_E5, 20, NOTE_D5, 10,
  NOTE_D5, 10, NOTE_FS5, 20, NOTE_E5, 20, NOTE_FS5, 20, NOTE_E5, 20, NOTE_FS5, 20, NOTE_E5, 20, NOTE_FS5, 10,
  NOTE_E5, 15, NOTE_FS5, 13, NOTE_E5, 18, NOTE_FS5, 14, NOTE_G5, 20, NOTE_G5, 10, NOTE_D5, 7,
  NOTE_G5, 10, NOTE_G5, 20, NOTE_G5, 20, NOTE_G5, 20, NOTE_G5, 20, NOTE_G5, 20, NOTE_G5, 21,
  NOTE_A5, 20, NOTE_A5, 10, NOTE_FS5, 12, NOTE_FS5, 20, NOTE_FS5, 20, NOTE_FS5, 20, NOTE_FS5, 20,
  NOTE_FS5, 19, NOTE_A5, 10, NOTE_G5, 20, NOTE_FS5, 10, NOTE_E5, 10, NOTE_E5, 20, NOTE_E5, 20,
  NOTE_E5, 20, NOTE_E5, 20, NOTE_E5, 20, NOTE_E5, 20, NOTE_E5, 20, NOTE_D5, 10, NOTE_D5, 10,
  NOTE_D5, 10, NOTE_CS5, 10, NOTE_D5, 10, NOTE_CS5, 10, NOTE_D5, 10, NOTE_D5, 10, NOTE_D5, 10,
  NOTE_D5, 10, NOTE_D5, 10, NOTE_D5, 10, NOTE_D5, 10, NOTE_B4, 20, NOTE_E5, 10, NOTE_D5, 13,
  NOTE_D5, 13, NOTE_D5, 20, NOTE_D5, 20, NOTE_D5, 20, NOTE_D5, 20, NOTE_D5, 20, NOTE_B4, 20,
  NOTE_B4, 20, NOTE_B4, 20, NOTE_E5, 10, NOTE_CS5, 20, NOTE_D5, 10, NOTE_B4, 7, NOTE_B4, 20,
  NOTE_B4, 44, NOTE_B4, 48, NOTE_B4, 20, NOTE_B4, 20, NOTE_B4, 20, NOTE_D5, 20, NOTE_D5, 20,
  NOTE_D5, 52, NOTE_D5, 52, NOTE_D5, 10, NOTE_E5, 10, NOTE_E5, 10, NOTE_CS5, 20, NOTE_B4, 20,
  NOTE_D5, 10, NOTE_B4, 52, NOTE_B4, 52, NOTE_B4, 20, NOTE_B4, 20, NOTE_E5, 20, NOTE_B4, 10,
  NOTE_CS5, 10, NOTE_CS5, 20, NOTE_CS5, 20, NOTE_CS5, 20, NOTE_CS5, 20, NOTE_B4, 10, NOTE_B4, 10,
  NOTE_B4, 10, NOTE_B4, 10, NOTE_B4, 10, NOTE_B4, 10, NOTE_B4, 10, NOTE_B4, 20, NOTE_D5, 10,
  NOTE_CS5, 20, NOTE_D5, 44, NOTE_D5, 44, NOTE_D5, 20, NOTE_D5, 20, NOTE_D5, 20, NOTE_D5, 20,
  NOTE_D5, 20, NOTE_D5, 20, NOTE_D5, 20, NOTE_B4, 20, NOTE_E5, 10, NOTE_D5, 20, NOTE_D5, 44,
  NOTE_D5, 44, NOTE_D5, 20, NOTE_D5, 20, NOTE_D5, 20, NOTE_D5, 20, NOTE_E5, 10, NOTE_E5, 10,
  NOTE_D5, 13, NOTE_D5, 14, NOTE_D5, 13, NOTE_D5, 14, NOTE_D5, 20, NOTE_CS5, 20, NOTE_D5, 20,
  NOTE_B4, 52, NOTE_B4, 52, NOTE_B4, 20, NOTE_D5, 20, NOTE_B4, 10, NOTE_B4, 10, NOTE_B4, 10,
  NOTE_B4, 52, NOTE_B4, 52, NOTE_B4, 20, NOTE_B4, 20, NOTE_E5, 10, NOTE_CS5, 10, NOTE_E5, 10,
  NOTE_CS5, 10, NOTE_CS5, 10, NOTE_CS5, 10, NOTE_CS5, 20, NOTE_B4, 20, NOTE_E5, 10, NOTE_D5, 10,
  NOTE_D5, 10, NOTE_D5, 10, NOTE_D5, 10, NOTE_D5, 10, NOTE_D5, 10, NOTE_D5, 10, NOTE_D5, 10,
  NOTE_D5, 10, NOTE_D5, 10, NOTE_D5, 10, NOTE_D5, 10, NOTE_B4, 20, NOTE_E5, 10, NOTE_D5, 44,
  NOTE_D5, 44, NOTE_D5, 20, NOTE_D5, 20, NOTE_D5, 20, NOTE_D5, 20, NOTE_E5, 20, NOTE_E5, 20,
  NOTE_E5, 20, NOTE_E5, 20, NOTE_E5, 20, NOTE_A5, 20, NOTE_A5, 20, NOTE_D5, 20, NOTE_D5, 20,
  NOTE_D5, 10, NOTE_D5, 20, NOTE_E5, 20, NOTE_E5, 20, NOTE_E5, 20, NOTE_E5, 20, NOTE_E5, 16,
  NOTE_E5, 18, NOTE_E5, 19, NOTE_D5, 18, NOTE_D5, 20, NOTE_CS5, 13, NOTE_D5, 10, NOTE_D5, 10
};
const int notes_Despacito = sizeof(melody_Despacito) / sizeof(melody_Despacito[0]) / 2;
const int tempo_Despacito = 89; // Ajuste o tempo da música
const int wholenote_Despacito = (60000 * 4) / tempo_Despacito;

const int INTERVALO_TELA_MS = 500;

int playerScrollX = 0;
unsigned long tempoAnteriorPlayerScroll = 0;
const int VELOCIDADE_PLAYER_SCROLL = 200; // Ajuste a velocidade aqui

void atualizarMusica() {
  if (!estaTocando) {
    return;
  }
  if (millis() >= tempoProximaNota) {
    const int* melodiaAtual;
    int totalDeNotas;
    int wholenote;
    switch (musicaSendoTocada) {
      case 0: // Take on Me
        melodiaAtual = melody_Takeonme;
        totalDeNotas = notes_Takeonme;
        wholenote = wholenote_Takeonme;
        break;
      case 1: // Fur Elise
        melodiaAtual = melody_Furelise;
        totalDeNotas = notes_Furelise;
        wholenote = wholenote_Furelise;
        break;
      case 2: // Despacito
        melodiaAtual = melody_Despacito;
        totalDeNotas = notes_Despacito;
        wholenote = wholenote_Despacito;
        break;
      default:
        estaTocando = false;
        return;
    }
    if (notaAtual >= totalDeNotas * 2) {
      estaTocando = false;
      noTone(pinBuzzer);
      desenharMenu();
      return;
    }
    int note = pgm_read_word_near(melodiaAtual + notaAtual);
    int divider = pgm_read_word_near(melodiaAtual + notaAtual + 1);
    int noteDuration = 0;
    if (divider > 0) {
      noteDuration = wholenote / divider;
    } else if (divider < 0) {
      noteDuration = (wholenote / abs(divider)) * 1.5;
    }
    if (note > 0) {
      tone(pinBuzzer, note, noteDuration * 0.9);
    }
    tempoProximaNota = millis() + noteDuration;
    notaAtual += 2;
  }
}

void desenharTelaPlayer(int notaAtual, int totalDeNotas) {
  display.clearDisplay();
  for (int i = 0; i < 4; i++) {
    int alturaBarra = random(2, 16); 
    display.drawRect(i * 4, 16 - alturaBarra, 3, alturaBarra, SSD1306_WHITE);
  }
  display.setTextSize(2);
  display.setTextColor(SSD1306_WHITE);
  String nomeMusica = musicas[musicaSendoTocada];
  int larguraTexto = nomeMusica.length() * 12;
  if (larguraTexto > SCREEN_WIDTH - 20) {
    if (millis() - tempoAnteriorPlayerScroll > VELOCIDADE_PLAYER_SCROLL) {
      playerScrollX--;
      if (playerScrollX < -larguraTexto) {
        playerScrollX = 5;
      }
      tempoAnteriorPlayerScroll = millis();
    }
    display.setCursor(20 + playerScrollX, 2);
  } else {
    display.setCursor((SCREEN_WIDTH - 20 - larguraTexto) / 2 + 20, 2);
  }
  display.setTextWrap(false);
  display.println(nomeMusica);
  display.setTextWrap(true);
  int barraPosY = 35;
  int barraWidth = 128;
  int barraHeight = 10;
  int progressoWidth = map(notaAtual, 0, totalDeNotas * 2, 0, barraWidth);
  
  display.drawRect(0, barraPosY, barraWidth, barraHeight, SSD1306_WHITE);
  for (int x = 2; x < progressoWidth - 2; x += 3) {
      display.drawFastVLine(x, barraPosY + 2, barraHeight - 4, SSD1306_WHITE);
  }
  display.drawBitmap(25, 48, icon_prev, 16, 16, SSD1306_WHITE);
  if (estaTocando) {
      display.drawBitmap(56, 48, icon_pause, 16, 16, SSD1306_WHITE);
  } else {
      display.drawBitmap(56, 48, icon_play, 16, 16, SSD1306_WHITE);
  }
  display.drawBitmap(87, 48, icon_next, 16, 16, SSD1306_WHITE);
}
