#define LDR 4

void setup() {
  Serial.begin(115200);
}

void loop() {
  int ldr = analogRead(LDR);
  Serial.println(ldr);
  delay(1000);
}



