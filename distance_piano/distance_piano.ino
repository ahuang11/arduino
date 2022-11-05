// include library for sensor-specific functions
 
// set pins for ultrasonic sensors
#define LED_PIN_1 22
#define LED_PIN_2 33
#define ECHO_PIN 13
#define TRIG_PIN 12
#define BUZZ_PIN 11

float duration_us, distance_cm;
int led_count;

void setup() {
  Serial.begin(9600);     // initialize serial monitor at 9,600 baud

  for (int i = LED_PIN_1; i <= LED_PIN_2; i++) {
    pinMode(i, OUTPUT);
  }

  pinMode(ECHO_PIN, INPUT);
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(BUZZ_PIN, OUTPUT);

  delay(500);
}

void loop() {
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  duration_us = pulseIn(ECHO_PIN, HIGH);

  // calculate the distance
  distance_cm = 0.017 * duration_us;
  led_count = (distance_cm);
  if (led_count > 12) {
    led_count = 12;
  }

  for (int i = LED_PIN_1; i <= LED_PIN_2; i++) {
    if (i < LED_PIN_1 + led_count) {
      digitalWrite(i, HIGH);
      tone(BUZZ_PIN, 150 * led_count);
    }
    else {
      digitalWrite(i, LOW);
      noTone(BUZZ_PIN);
    }
    delay(25);
  }

  // print the value to Serial Monitor
  Serial.print("number of LEDs on: ");
  Serial.println(led_count);
  Serial.print("distance from obstacle: ");
  Serial.print(distance_cm);
  Serial.println(" cm");
}