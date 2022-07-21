//velocidade ja aumenta com o tempo
//colocar mais obsctaculos com o tempo, e variar a distanci entre eles
//variar tempo de pulo
#include <Adafruit_LiquidCrystal.h>

#define BTN_LOWER 2
#define BTN_JUMP 3
#define LED_LOWER 4
#define LED_JUMP 5

#define BIRD 0
#define CACTUS 1
#define RUN 2
#define JUMP 3
#define LOWER 4
#define DELAY_MAX 1000
#define DELAY_MIN 500

Adafruit_LiquidCrystal lcd(0);
bool btn_c = 0;
byte run[8]={B01100,B01100,B00000,B01110,B11100,B01100,B11010,B10011};
byte jump[8]={B01100,B01100,B00000,B11110,B01101,B11111,B11000,B00000};
byte lower[8]={B00000,B00000,B00011,B00011,B11100,B11110,B10000,B11000};
byte bird[8]={B10001,B10001,B10001,B11011,B01010,B01010,B00100,B00100};
byte cactus[8]={B10000,B10001,B11111,B11110,B01101,B10111,B11110,B01111};
int characterx, charactery, obstaclex, obstacley;
unsigned long counting_score;
unsigned long score = 0;
String score_print = "000";
bool on = true, play = false;
int jumped = 0, lowerd = 0;
unsigned long prev_detour = 0;
unsigned long prev_obstacle = 0;
bool jumping=0, lowering=0;
int DELAY;

void wait_play();
void playing();
void set_score_print();
void int_jump(){
  play = true;
  jumped++;
}
void int_lower(){
  play = true;
  lowerd++;
}

void setup()
{
  pinMode(BTN_LOWER, INPUT_PULLUP);
  pinMode(BTN_JUMP, INPUT_PULLUP);
  pinMode(LED_LOWER, OUTPUT);
  pinMode(LED_JUMP, OUTPUT);
  lcd.begin(16, 2);
  lcd.setBacklight(HIGH);
  lcd.createChar(RUN, run);
  lcd.createChar(JUMP, jump);
  lcd.createChar(LOWER, lower);
  lcd.createChar(BIRD, bird);
  lcd.createChar(CACTUS, cactus);
  attachInterrupt(digitalPinToInterrupt(BTN_JUMP), int_jump, RISING);
  attachInterrupt(digitalPinToInterrupt(BTN_LOWER), int_lower, RISING);
  randomSeed(analogRead(0));
  Serial.begin(9600);
}

void loop()
{
  if (on && play){
    playing();
  }
  else{
    wait_play();
  }
}

void wait_play(){
  //starts playing
  if (!on && play){
    score = 0;
    jumped = lowerd = 0;
    lcd.clear();
    lcd.setCursor(13,0);
    lcd.print("000");
    lcd.setCursor(0,1);
    lcd.write(RUN);
    on = true;
    characterx = 0;
    charactery = 1;
    obstaclex = -1;
    counting_score = millis();
    jumping = lowering = 0;
    DELAY = DELAY_MAX;
  }
  //stop playing
  else if (on && !play){
    lcd.clear();
    if (score == 0){
      lcd.setCursor(2,0);
      lcd.print("PRESS START!");
    }
    else if (score == 999){
      lcd.setCursor(4,0);
      lcd.print("YOU WON!");
    }
    else{
      lcd.setCursor(4,0);
      lcd.print("YOU LOST");
    }
    lcd.setCursor(3,1);
    lcd.print("score  ");
    set_score_print();
    lcd.print(score_print);
    on = false;
    digitalWrite(LED_LOWER, LOW);
    digitalWrite(LED_JUMP, LOW);
  }
}

void playing(){
  //lower
  if (lowerd && !lowering && !jumping){
    lowering = 1;
    prev_detour = millis();
    lcd.setCursor(characterx, charactery);
    lcd.write(LOWER);
    digitalWrite(LED_LOWER, HIGH);
  }
  //jump
  if (jumped && !lowering && !jumping){
    jumping = 1;
    prev_detour = millis();
    lcd.setCursor(characterx, charactery);
    lcd.print(" ");
    charactery = 0;
    lcd.setCursor(characterx, charactery);
    lcd.write(JUMP);
    digitalWrite(LED_JUMP, HIGH);
  }
  //stop jumping or lowering
  if (millis()-prev_detour > 2*DELAY_MAX && (jumping || lowering)){
    jumped=lowerd=jumping=lowering=0;
    lcd.setCursor(characterx, charactery);
    lcd.print(" ");
    charactery = 1;
    lcd.setCursor(characterx, charactery);
    lcd.write(RUN);
    digitalWrite(LED_LOWER, LOW);
    digitalWrite(LED_JUMP, LOW);
  }
  //verify score and speed up
  if (score == 999)
    play = false;
  else
  	DELAY = map(score, 0, 999, DELAY_MAX, DELAY_MIN);
  //print score
  score = (millis()-counting_score)/100;
  set_score_print();
  lcd.setCursor(13, 0);
  lcd.print(score_print);
  //calculate obstacle
  if (obstaclex == -1){
    if (obstacley != charactery){
      lcd.setCursor(0,obstacley);
      lcd.print(" ");
    }
    obstacley = random(0,2);
    obstaclex = 15;
    prev_obstacle = millis();
  }
  else if (millis()-prev_obstacle > DELAY){
    prev_obstacle = millis();
    obstaclex--;
  }
  lcd.setCursor(obstaclex,obstacley);
  lcd.write(obstacley);
  lcd.setCursor(obstaclex,obstacley);
  lcd.print(" ");
  //verify hit
  if (obstaclex == characterx){
    if (obstacley == CACTUS && obstacley == charactery)
	  play = false;
    else if (obstacley == BIRD && !lowering){
      play = false;
    }
  }
}

void set_score_print(){
  String score_ = String(score);
    int j = score_print.length()-1;
    for (int i=score_.length()-1; i>=0; i--){
      score_print.setCharAt(j, score_[i]);
      j--;
    }
}
