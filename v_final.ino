#include <SPI.h>
#include <SD.h>
#include "TMRpcm.h"

TMRpcm audio;

int limiar = 300;  // Limiar para detecção de batida

int minVolume = 1;      // Volume mínimo
int maxVolume = 6;      // Volume máximo

int atraso = 100;//tempo de delay entre sons
unsigned long lastTriggerTime = 0;

const int numeroDeSensores = 4;//Seta o numero de sensores utilizados
int pad[numeroDeSensores];

void setup() {
  Serial.begin(9600);

  if (!SD.begin()) {
    Serial.println("Houve um erro ao iniciar o módulo do cartão SD!");
    while (true); // Fica parado aqui.
  }
  Serial.println("Módulo SD iniciado com sucesso!");
  
  printDirectory(SD.open("/"), 0);

  audio.speakerPin = 9;
  audio.setVolume(5);   // Volume inicial
  audio.quality(1);
}

void loop() {
  pad[0] = analogRead(0);///salva o valor maximo obtido pelo piezo no vetor pad
  pad[1] = analogRead(1);
  pad[2] = analogRead(2);
  pad[3] = analogRead(3);
  
  if ((pad[0] > limiar) && (millis() - lastTriggerTime > atraso)) {
    int volume = map(pad[0], limiar, 1023, minVolume, maxVolume);
    audio.setVolume(volume);
    audio.play("CRASH.wav");
    Serial.print("Tocando CRASH.wav com volume: ");
    Serial.println(volume);
    lastTriggerTime = millis();
    delay(atraso);
  } else if ((pad[1] > limiar) && (millis() - lastTriggerTime > atraso)) {
    int volume = map(pad[1], limiar, 1023, minVolume, maxVolume);
    audio.setVolume(volume);
    audio.play("CRASH.wav");
    Serial.print("Tocando CRASH.wav com volume: ");
    Serial.println(volume);
    lastTriggerTime = millis();
    delay(atraso);
  } else if ((pad[2] > limiar) && (millis() - lastTriggerTime > atraso)) {
    int volume = map(pad[2], limiar, 1023, minVolume, maxVolume);
    audio.setVolume(volume);
    audio.play("SNARE.wav");
    Serial.print("Tocando SNARE.wav com volume: ");
    Serial.println(volume);
    lastTriggerTime = millis();
    delay(atraso);
  } else if ((pad[3] > limiar) && (millis() - lastTriggerTime > atraso)) {
    int volume = map(pad[3], limiar, 1023, minVolume, maxVolume);
    audio.setVolume(volume);
    audio.play("SNARE.wav");
    Serial.print("Tocando SNARE.wav com volume: ");
    Serial.println(volume);
    lastTriggerTime = millis();
    delay(atraso);
  }
}
 
void printDirectory(File dir, int numTabs) {
  while (true) {
 
    File entry =  dir.openNextFile();
    if (! entry) {
      // no more files
      break;
    }
    for (uint8_t i = 0; i < numTabs; i++) {
      Serial.print('\t');
    }
    Serial.print(entry.name());
    if (entry.isDirectory()) {
      Serial.println("/");
      printDirectory(entry, numTabs + 1);
    } else {
      // files have sizes, directories do not
      Serial.print("\t\t");
      Serial.println(entry.size(), DEC);
    }
    entry.close();
  }
}