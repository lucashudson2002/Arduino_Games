#include <DFRobotDFPlayerMini.h>
#include <SoftwareSerial.h>

#define RX A4
#define TX A5
#define BTN A3

bool control_btn = 0; //variável pra controlar o clique do botão
int max = 1; //quantidade de vezes que o áudio mais repetido foi tocado
int *cont; //vetor que armazena quantidade de vezes que cada áudio foi tocado
int cont_max = 0; //quantidade de áudios que foram repetido max vezes
int r; //variável que armazena o valor aleatório que é o áudio a ser tocado

SoftwareSerial SoftwareSerial(RX, TX);
DFRobotDFPlayerMini MP3;

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

void(* resetFunc) (void) = 0; //função para reiniciar o arduino

void setup() {
  SoftwareSerial.begin(9600);
  Serial.begin(9600);
  Serial.println("Initializing DFPlayer ...");
  if (!MP3.begin(SoftwareSerial)) {
    Serial.println("Unable to begin.");
    delay(100);
    resetFunc();
  }
  Serial.println("Initializing suceed!");
  Serial.print(MP3.readFileCounts());
  Serial.println(" audios");
  MP3.volume(30);
  cont = new int[MP3.readFileCounts()];
  for(int i=0; i<MP3.readFileCounts(); i++)
    cont[i] = 0;
  pinMode(BTN, INPUT_PULLUP);
  randomSeed(analogRead(0));
}

void loop() {
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
}
