const int LDR_TOP_LEFT = A0;
const int LDR_TOP_RIGHT = A1;
const int LDR_BOTTOM_LEFT = A2;
const int LDR_BOTTOM_RIGHT = A3;

unsigned long previousMillis = 0;
const unsigned long interval = 100;

void setup() {
  Serial.begin(9600);
}

void loop() {
  unsigned long currentMillis = millis();

  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;

    int topLeft = analogRead(LDR_TOP_LEFT);
    int topRight = analogRead(LDR_TOP_RIGHT);
    int bottomLeft = analogRead(LDR_BOTTOM_LEFT);
    int bottomRight = analogRead(LDR_BOTTOM_RIGHT);

    Serial.print(topLeft);
    Serial.print(",");
    Serial.print(topRight);
    Serial.print(",");
    Serial.print(bottomLeft);
    Serial.print(",");
    Serial.println(bottomRight);
  }
}
