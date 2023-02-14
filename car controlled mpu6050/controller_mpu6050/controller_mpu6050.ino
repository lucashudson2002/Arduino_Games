#include <Wire.h>
#include <esp_now.h>
#include <WiFi.h>

#define MPU6050_ACCEL_XOUT_H 0x3B
#define MPU6050_GYRO_XOUT_H 0x43
#define MPU6050_PWR_MGMT_1 0x6B
#define MPU6050_ADDRESS 0x68

const uint8_t ADDRESS[] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};

typedef struct message {
  short int roll;
  short int pitch;
} message;

message data{0,0};

void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status) {
  status == ESP_NOW_SEND_SUCCESS ? digitalWrite(2, HIGH) : digitalWrite(2, LOW);
}

void setup() {
  Serial.begin(115200);

  pinMode(2, OUTPUT);

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
  esp_now_register_send_cb(OnDataSent);

  Wire.begin();
  Wire.beginTransmission(MPU6050_ADDRESS);
  Wire.write(MPU6050_PWR_MGMT_1);
  Wire.write(0);
  Wire.endTransmission(true);
}

void loop() {
  Wire.beginTransmission(MPU6050_ADDRESS);
  Wire.write(MPU6050_ACCEL_XOUT_H);
  Wire.endTransmission(false);
  Wire.requestFrom(MPU6050_ADDRESS, 14, true);

  int16_t AcX = Wire.read() << 8 | Wire.read();
  int16_t AcY = Wire.read() << 8 | Wire.read();
  int16_t AcZ = Wire.read() << 8 | Wire.read();
  int16_t Tmp = Wire.read() << 8 | Wire.read();
  int16_t GyX = Wire.read() << 8 | Wire.read();
  int16_t GyY = Wire.read() << 8 | Wire.read();
  int16_t GyZ = Wire.read() << 8 | Wire.read();

  data.roll = atan(AcY/sqrt(AcX * AcX + AcZ * AcZ)) * RAD_TO_DEG;
  data.pitch = atan(AcX/sqrt(AcY * AcY + AcZ * AcZ)) * RAD_TO_DEG;

  Serial.print(data.roll);
  Serial.print("\t");
  Serial.println(data.pitch);

  esp_now_send(ADDRESS, (uint8_t *)&data, sizeof(data));

  delay(10);
}
