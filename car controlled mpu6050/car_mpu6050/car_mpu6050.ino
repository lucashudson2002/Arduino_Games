#include <esp_now.h>
#include <WiFi.h>

#define PWMA 4
#define AIN2 16
#define AIN1 17
#define STBY 5
#define BIN1 18
#define BIN2 19
#define PWMB 21

#define ANGLE 20

const uint8_t ADDRESS[] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};

typedef struct message {
  short int roll;
  short int pitch;
} message;

message data{0,0};

int pwma=0, pwmb=0;

void OnDataRecv(const uint8_t * mac_addr, const uint8_t *incomingData, int len) {
  memcpy(&data, incomingData, sizeof(data));
}

void setup() {
  Serial.begin(115200);

  pinMode(PWMA, OUTPUT);
  pinMode(AIN1, OUTPUT);
  pinMode(AIN2, OUTPUT);
  pinMode(STBY, OUTPUT);
  pinMode(BIN1, OUTPUT);
  pinMode(BIN2, OUTPUT);
  pinMode(PWMB, OUTPUT);

  digitalWrite(STBY, HIGH);

  ledcAttachPin(PWMA, 0);
  ledcSetup(0, 20000, 12);
  ledcAttachPin(PWMB, 1);
  ledcSetup(1, 20000, 12);

  WiFi.mode(WIFI_STA);
  if (esp_now_init() != ESP_OK) {
    Serial.println("There was an error initializing ESP-NOW");
    return;
  }
  esp_now_peer_info_t peerInfo;
  peerInfo.channel = 0;
  memcpy(peerInfo.peer_addr, ADDRESS, 6);
  if (esp_now_add_peer(&peerInfo) != ESP_OK){
    Serial.println("Failed to add peer");
    return;
  }
  esp_now_register_recv_cb(OnDataRecv);
}

void loop() {
  data.pitch = constrain(data.pitch, -90, 90);
  data.roll = constrain(data.roll, -90, 90);

  if(data.pitch>ANGLE && abs(data.roll)<ANGLE){
    digitalWrite(AIN1, HIGH);
    digitalWrite(AIN2, LOW);
    digitalWrite(BIN1, HIGH);
    digitalWrite(BIN2, LOW);
    pwma = pwmb = map(abs(data.pitch), ANGLE, 90, 983, 4095);
    Serial.print("FRENTE - ");
    Serial.println(pwma);
  }
  else if(data.pitch<-ANGLE && abs(data.roll)<ANGLE){
    digitalWrite(AIN1, LOW);
    digitalWrite(AIN2, HIGH);
    digitalWrite(BIN1, LOW);
    digitalWrite(BIN2, HIGH);
    pwma = pwmb = map(abs(data.pitch), ANGLE, 90, 983, 4095);
    Serial.print("TRAS - ");
    Serial.println(pwma);
  }
  else if(data.roll<-ANGLE && abs(data.pitch)<ANGLE){
    digitalWrite(AIN1, HIGH);
    digitalWrite(AIN2, LOW);
    digitalWrite(BIN1, LOW);
    digitalWrite(BIN2, HIGH);
    pwma = pwmb = map(abs(data.roll), ANGLE, 90, 983, 4095);
    Serial.print("FULL DIREITA - ");
    Serial.println(pwma);
  }
  else if(data.roll>ANGLE && abs(data.pitch)<ANGLE){
    digitalWrite(AIN1, LOW);
    digitalWrite(AIN2, HIGH);
    digitalWrite(BIN1, HIGH);
    digitalWrite(BIN2, LOW);
    pwma = pwmb = map(abs(data.roll), ANGLE, 90, 983, 4095);
    Serial.print("FULL ESQUERDA - ");
    Serial.println(pwma);
  }
  else if(data.roll<=-ANGLE && data.pitch>=ANGLE){
    digitalWrite(AIN1, HIGH);
    digitalWrite(AIN2, LOW);
    digitalWrite(BIN1, HIGH);
    digitalWrite(BIN2, LOW);
    float radius = sqrt(pow((data.pitch-ANGLE), 2) + pow((data.roll+ANGLE), 2));
    pwma = map(radius, 0, 80, 983, 4095);
    float angle = atan2(data.pitch-ANGLE, abs(data.roll+ANGLE))*180/PI;
    float percentage = map(angle, 0, 90, 0, 100);
    pwmb = pwma*percentage/100.0;
    Serial.print("FRENTE DIREITA - ");
    Serial.print(pwma);
    Serial.print(" ");
    Serial.println(pwmb);
  }
  else if(data.roll>=ANGLE && data.pitch>=ANGLE){
    digitalWrite(AIN1, HIGH);
    digitalWrite(AIN2, LOW);
    digitalWrite(BIN1, HIGH);
    digitalWrite(BIN2, LOW);
    float radius = sqrt(pow((data.pitch-ANGLE), 2) + pow((data.roll-ANGLE), 2));
    pwmb = map(radius, 0, 80, 983, 4095);
    float angle = atan2(data.pitch-ANGLE, data.roll-ANGLE)*180/PI;
    float percentage = map(angle, 0, 90, 0, 100);
    pwma = pwmb*percentage/100.0;
    Serial.print("FRENTE ESQUERDA - ");
    Serial.print(pwma);
    Serial.print(" ");
    Serial.println(pwmb);
  }
  else if(data.roll>=ANGLE && data.pitch<=-ANGLE){
    digitalWrite(AIN1, LOW);
    digitalWrite(AIN2, HIGH);
    digitalWrite(BIN1, LOW);
    digitalWrite(BIN2, HIGH);
    float radius = sqrt(pow((data.pitch+ANGLE), 2) + pow((data.roll-ANGLE), 2));
    pwmb = map(radius, 0, 80, 983, 4095);
    float angle = atan2(abs(data.pitch+ANGLE), data.roll-ANGLE)*180/PI;
    float percentage = map(angle, 0, 90, 0, 100);
    pwma = pwmb*percentage/100.0;
    Serial.print("TRAS ESQUERDA - ");
    Serial.print(pwma);
    Serial.print(" ");
    Serial.println(pwmb);
  }
  else if(data.roll<=-ANGLE && data.pitch<=-ANGLE){
    digitalWrite(AIN1, LOW);
    digitalWrite(AIN2, HIGH);
    digitalWrite(BIN1, LOW);
    digitalWrite(BIN2, HIGH);
    float radius = sqrt(pow((data.pitch+ANGLE), 2) + pow((data.roll+ANGLE), 2));
    pwma = map(radius, 0, 80, 983, 4095);
    float angle = atan2(abs(data.pitch+ANGLE), abs(data.roll+ANGLE))*180/PI;
    float percentage = map(angle, 0, 90, 0, 100);
    pwmb = pwma*percentage/100.0;
    Serial.print("TRAS DIREITA - ");
    Serial.print(pwma);
    Serial.print(" ");
    Serial.println(pwmb);
  }
  else{
    digitalWrite(AIN1, HIGH);
    digitalWrite(AIN2, HIGH);
    digitalWrite(BIN1, HIGH);
    digitalWrite(BIN2, HIGH);
    Serial.println("PARADO");
    pwma = pwmb = 0;
  }

  ledcWrite(0, pwma);
  ledcWrite(1, pwmb);
  
  delay(10);
}
