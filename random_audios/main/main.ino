#include <DFRobotDFPlayerMini.h>
#include <SoftwareSerial.h>

#define RX 11//A4
#define TX 10//A5
#define BTN A3

bool control_btn = 0; //variável pra controlar o clique do botão
int max = 1; //quantidade de vezes que o áudio mais repetido foi tocado
int *cont; //vetor que armazena quantidade de vezes que cada áudio foi tocado
int cont_max = 0; //quantidade de áudios que foram repetido max vezes
int r; //variável que armazena o valor aleatório que é o áudio a ser tocado

SoftwareSerial SoftwareSerial(RX, TX);
DFRobotDFPlayerMini MP3;

unsigned long int cont_vol = 0;

bool readButton(const byte button, bool &control){ //função para ler o valor do botão
  if(!digitalRead(button)) 
    control = 1;
  if(digitalRead(button) && control)
  {
    control = 0;
    return true;
  } 
  return false;
}

void setup() {
  SoftwareSerial.begin(9600);
  Serial.begin(9600);
  Serial.println("Initializing DFPlayer ...");
  while (!MP3.begin(SoftwareSerial)) {
    Serial.println("Unable to begin.");
  }
  Serial.println("Initializing suceed!");
  Serial.print(MP3.readFileCounts());
  Serial.println(" audios");
  MP3.setTimeOut(500);
  MP3.volume(30);
  MP3.outputDevice(DFPLAYER_DEVICE_SD);
  MP3.EQ(0);
  cont = new int[MP3.readFileCounts()];
  for(int i=0; i<MP3.readFileCounts(); i++)
    cont[i] = 0;
  pinMode(BTN, INPUT_PULLUP);
  randomSeed(analogRead(0));
  pinMode(13, OUTPUT);
  digitalWrite(13, HIGH);
}

void loop() {
  if (MP3.readType() != DFPlayerPlayFinished && millis() - cont_vol > 500){
    cont_vol = millis();
    MP3.volume(30);
  }
  if(readButton(BTN, control_btn)){
    do{
      r = random(1,MP3.readFileCounts()+1);
    }
    while (cont[r-1] == max);
    cont[r-1]++;
    cont_max++;
    if (cont_max == MP3.readFileCounts()){
      max++;
      cont_max = 0;
    }
    Serial.println(r);
    MP3.play(r);
  }
  delay(100);
}