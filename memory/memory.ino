#define BUZZER 12
const byte PINOS_BTN[] = {2,10,8,6,4};
const byte PINOS_LED[] = {3,11,9,7,5};

#define N 5
#define MAX_BLINK 8
#define DELAY_MAX 500
#define STEP 50
#define DELAY_MIN 100

bool btn_controle[] = {0, 0, 0, 0, 0};
byte random_[MAX_BLINK];
byte answer[MAX_BLINK];
byte size_;
bool playing, prev_playing, hit;
bool on = true;
int lag;

bool readButton(const byte button, bool &control);
byte readButtons(const byte buttons[], bool controls[], byte n);
void play();
void reset();
void win();
void start_finish(){
	playing = !playing;
}

void setup()
{
  for (int i=0; i<N; i++)
  	pinMode(PINOS_BTN[i], INPUT_PULLUP);
  for (int i=0; i<N; i++)
  	pinMode(PINOS_LED[i], OUTPUT);
  pinMode(BUZZER, OUTPUT);
  attachInterrupt(digitalPinToInterrupt(PINOS_BTN[0]), start_finish, FALLING);
  randomSeed(analogRead(0));
  reset();
}

void loop()
{
  if (prev_playing != playing){
    reset();
  }
  
  if (on){
    digitalWrite(PINOS_LED[0], HIGH);
    for (; size_<MAX_BLINK && hit && playing; size_++){
      play();
    }
    for (; lag>DELAY_MIN && hit && playing; lag-=STEP){
      play();
    }
    playing = false;
    if (playing)
	  win();
  }  
}

bool readButton(const byte button, bool &control){
  if(!digitalRead(button)) 
    control = 1;
  if(digitalRead(button) && control)
  {
    control = 0;
    return true;
  } 
  return false;
}
               
byte readButtons(const byte buttons[], bool controls[], byte n){
  for (int i=1; i<n; i++){
    if (readButton(buttons[i], controls[i]))
      return i;
  }
  return 0;
}

void play(){
  delay(500);
  for (int i=0; i<size_ && playing; i++){
    random_[i] = random(1,N);
    digitalWrite(PINOS_LED[random_[i]], HIGH);
    delay(lag);
    digitalWrite(PINOS_LED[random_[i]], LOW);
    delay(lag);
  }
  for (int i=0; i<size_ && playing; i++){
    answer[i] = readButtons(PINOS_BTN, btn_controle, N);
    for (int i=1; i<N; i++){
      if (btn_controle[i])
        digitalWrite(PINOS_LED[i], HIGH);
      else
        digitalWrite(PINOS_LED[i], LOW);
    }
    if (answer[i]==0)
      i--;
    else if (answer[i] != random_[i]){
      hit = false;
      playing = false;
    }
    else
      tone(BUZZER,4978, 30);
  }
  if (!hit)
    tone(BUZZER,44, 500);
}

void reset(){
  on = !on;
  prev_playing = playing;
  size_ = 1;
  hit = true;
  lag = DELAY_MAX;
  digitalWrite(PINOS_LED[0], LOW);
}

void win(){
  int length_ = 10;
  char notes[] = "fefeca a#a ";
  int beats[] = { 4, 1, 1, 1, 1, 1, 1, 2, };
  int tempo = 300;
  
  for (int i = 0; i < length_; i++) {
    if (notes[i] == ' ') {
      delay(beats[i] * tempo);
    }
    else {
      char names[] = { 'c', 'd', 'd#', 'e', 'f', 'g', 'g#', 'a', 'a#' };
      int tones[] = { 1915, 1700, 1608, 1519, 1432, 1275, 1205, 1136, 1073 };
      for (int i = 0; i < 8; i++) {
        if (names[i] == notes[i]) {
          for (long i = 0; i < beats[i] * tempo * 1000L; i += tones[i] * 2) {
            digitalWrite(BUZZER, HIGH);
            delayMicroseconds(tones[i]);
            digitalWrite(BUZZER, LOW);
            delayMicroseconds(tones[i]);
          }
        }
      }
    }
    delay(tempo / 2); 
  }
}
