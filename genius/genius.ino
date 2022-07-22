#define BUZZER 11
#define BTN_CONTROL 2

const byte LED_CONTROL[] = {A5, A4, A3};
const byte BTNS[] = {9, 7, 5, 3};
const byte LEDS[] = {10, 8, 6, 4};

#define MAX_BLINK 31
#define DELAY 500
#define OFF 0
#define FOLLOW_SEQUENCE 1
#define MADE_SEQUENCE 2
#define CHOOSE_COLLOR 3
#define WAIT 5000

bool btns_c[] = {0, 0, 0, 0};
byte random_[MAX_BLINK];
byte size_;
byte mode = OFF;

void lights();
void spark();
void off();
void follow_sequence();
void made_sequence();
void choose_collor();//n da pra testar no computador
bool in(int elem, int vet[], int n);
bool readButton(const byte button, bool &control);
int readButtons(const byte buttons[], bool controls[], byte n);
void change_mode(){
  mode++;
  lights();
}

void setup()
{
  for (int i=0; i<3; i++)
  	pinMode(LED_CONTROL[i], OUTPUT);
  for (int i=0; i<4; i++)
  	pinMode(BTNS[i], INPUT_PULLUP);
  for (int i=0; i<4; i++)
  	pinMode(LEDS[i], OUTPUT);
  pinMode(BTN_CONTROL, INPUT_PULLUP);
  pinMode(BUZZER, OUTPUT);
  attachInterrupt(digitalPinToInterrupt(BTN_CONTROL), change_mode, FALLING);
  randomSeed(analogRead(0));
  spark();
}

void loop()
{
  switch (mode){
    case OFF:
      off();
      break;
  	case FOLLOW_SEQUENCE:
      follow_sequence();
      break;
   	case MADE_SEQUENCE:
      made_sequence();
      break;
    case CHOOSE_COLLOR:
      choose_collor();
      break;
    default:
      mode = OFF;
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
               
int readButtons(const byte buttons[], bool controls[], byte n){
  for (int i=0; i<n; i++){
    if (readButton(buttons[i], controls[i]))
      return i;
  }
  return -1;
}

void lights(){
  for (int i=0; i<mode; i++){
    digitalWrite(LED_CONTROL[i], HIGH);
  }
  for (int i=mode; i<3; i++){
    digitalWrite(LED_CONTROL[i], LOW);
  }
}

void spark(){
  for (int i=0; i<4; i++){
    digitalWrite(LEDS[i], HIGH);
    delay(200);
    digitalWrite(LEDS[i], LOW);
    delay(200);
  }
  for (int i=0; i<4; i++)
    digitalWrite(LEDS[i], HIGH);
  delay(200);
  for (int i=0; i<4; i++)
    digitalWrite(LEDS[i], LOW);
  delay(200);
  for (int i=3; i>=0; i--){
    digitalWrite(LEDS[i], HIGH);
    delay(200);
    digitalWrite(LEDS[i], LOW);
    delay(200);
  }
  for (int i=0; i<4; i++)
    digitalWrite(LEDS[i], HIGH);
  delay(200);
  for (int i=0; i<4; i++)
    digitalWrite(LEDS[i], LOW);
  delay(200);
}

void off(){
  lights();
}

void follow_sequence(){
  int index, prev_i;
  unsigned long count;
  for (size_= 1; size_<=MAX_BLINK && mode == FOLLOW_SEQUENCE; size_++){
    delay(DELAY);
    random_[size_-1] = random(0,4);
    if (size_>1){
      while(random_[size_-1]==random_[size_-2])
        random_[size_-1] = random(0,4);
    }
    for (int i=0; i<size_ && mode == FOLLOW_SEQUENCE; i++){
      digitalWrite(LEDS[random_[i]], HIGH);
      delay(DELAY);
      digitalWrite(LEDS[random_[i]], LOW);
    }
    prev_i = -1;
    for (int i=0; i<size_ && mode == FOLLOW_SEQUENCE; i++){
      if (prev_i != i){
        prev_i = i;
        count = millis();
      }
      index = readButtons(BTNS, btns_c, 4);
      for (int j=0; j<4; j++){
        if (btns_c[j])
          digitalWrite(LEDS[j], HIGH);
        else
          digitalWrite(LEDS[j], LOW);
      }
      if (index == -1 && millis()-count < WAIT)
        i--;
      else if (index != random_[i] || millis()-count > WAIT)
        mode = OFF;
      else
        tone(BUZZER,4978, 30);
    }
  }
  if (mode == OFF){
    tone(BUZZER,44, DELAY);
    for (int i=0; i<4; i++)
      digitalWrite(LEDS[i], HIGH);
    delay(DELAY);
    for (int i=0; i<4; i++)
      digitalWrite(LEDS[i], LOW);
  }
  if (size_==MAX_BLINK+1){
    spark();
    mode = OFF;
  }
}
void made_sequence(){
  int prev_i, index;
  unsigned long count;
  size_ = 1;
  random_[size_-1] = random(0,4);
  digitalWrite(LEDS[random_[size_-1]], HIGH);
  delay(DELAY);
  digitalWrite(LEDS[random_[size_-1]], LOW);
  while(size_<=MAX_BLINK && mode == MADE_SEQUENCE){
    prev_i = -1;
    for (int i=0; i<size_ && mode == MADE_SEQUENCE; i++){
	  if (prev_i != i){
        prev_i = i;
        count = millis();
      }
      index = readButtons(BTNS, btns_c, 4);
      for (int j=0; j<4; j++){
        if (btns_c[j])
          digitalWrite(LEDS[j], HIGH);
        else
          digitalWrite(LEDS[j], LOW);
      }
      if (index == -1 && millis()-count < WAIT)
        i--;
      else if (index != random_[i] || millis()-count > WAIT)
        mode = OFF;
      else
        tone(BUZZER,4978, 30);
    }
    size_++;
    index = -1;
    while (index == -1 && mode == MADE_SEQUENCE){
      index = readButtons(BTNS, btns_c, 4);
      for (int j=0; j<4; j++){
        if (btns_c[j])
          digitalWrite(LEDS[j], HIGH);
        else
          digitalWrite(LEDS[j], LOW);
      }
    }
    random_[size_-1] = index;
    for (int i=0; i<4; i++)
      digitalWrite(LEDS[i], HIGH);
    delay(100);
    for (int i=0; i<4; i++)
      digitalWrite(LEDS[i], LOW);
  }
  if (mode == OFF){
    tone(BUZZER,44, DELAY);
    for (int i=0; i<4; i++)
      digitalWrite(LEDS[i], HIGH);
    delay(DELAY);
    for (int i=0; i<4; i++)
      digitalWrite(LEDS[i], LOW);
  }
  if (size_==MAX_BLINK+1){
    spark();
    mode = OFF;
  }
}
void choose_collor(){
  int choices[4];
  int cont = 0;
  while (mode == CHOOSE_COLLOR){
  	for (int j=0; j<4; j++){
      if (!digitalRead(BTNS[j]))
        digitalWrite(LEDS[j], HIGH);
      else
        digitalWrite(LEDS[j], LOW);
    }
  }
  mode = CHOOSE_COLLOR;
  for (int j=0; j<4; j++){
    choices[j] = !digitalRead(BTNS[j])? j:-1;
    digitalWrite(LEDS[j], LOW);
  }
  int index, prev_i;
  unsigned long count;
  for (size_= 1; size_<=MAX_BLINK && mode == CHOOSE_COLLOR; size_++){
    delay(DELAY);
    random_[size_-1] = random(0,4);
    while(!in(random_[size_-1], choices, 4))
      random_[size_-1] = random(0,4);
	for (int i=0; i<size_ && mode == CHOOSE_COLLOR; i++){
      digitalWrite(LEDS[random_[i]], HIGH);
      delay(DELAY);
      digitalWrite(LEDS[random_[i]], LOW);
    }
    prev_i = -1;
    for (int i=0; i<size_ && mode == CHOOSE_COLLOR; i++){
      if (prev_i != i){
        prev_i = i;
        count = millis();
      }
      index = readButtons(BTNS, btns_c, 4);
      for (int j=0; j<4; j++){
        if (btns_c[j] && in(j, choices, 4))
          digitalWrite(LEDS[j], HIGH);
        else
          digitalWrite(LEDS[j], LOW);
      }
      if ((index == -1 || !in(index, choices, 4)) && millis()-count < WAIT)
        i--;
      else if (index != random_[i] || millis()-count > WAIT)
        mode = OFF;
      else
        tone(BUZZER,4978, 30);
    }
  }
  if (mode == OFF){
    tone(BUZZER,44, DELAY);
    for (int i=0; i<4; i++)
      digitalWrite(LEDS[i], HIGH);
    delay(DELAY);
    for (int i=0; i<4; i++)
      digitalWrite(LEDS[i], LOW);
  }
  if (size_==MAX_BLINK+1){
    spark();
    mode = OFF;
  }
  
}
  
bool in(int elem, int vet[], int n){
  for (int i=0; i<n; i++){
    if (vet[i] == elem)
    	return 1;
  }
  return 0;
}
