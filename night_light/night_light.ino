// LED turns on only when there's insufficient ambient light and when there's an object within a short distance in front.
// Utilizes a photoresistor, ultrasonic sensor, and LED.
// Could be used as a night light in the bathroom.

const int RLED_PIN = 7;  // red LED pin
const int ECHO_PIN = 8;  // ultrasonic echo pin
const int TRIG_PIN = 9;  // ultrasonic trigger pin
const int LRES_PIN = A0;  // light resistor pin

void setup() {
  Serial.begin(9600);  //configure serial to talk to computer
  pinMode(RLED_PIN, OUTPUT);  // output power to the red LED pin
  pinMode(TRIG_PIN, OUTPUT);  // output power to the trigger pin
  pinMode(ECHO_PIN, INPUT);  // receive signals from the echo pin
}

float light, duration, distance;  // initialize variables

void loop() {
  light = analogRead(LRES_PIN);  // store the ambient light
  Serial.println("light");
  Serial.println(light);

  // send ultrasonic waves
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);
  
  duration = pulseIn(ECHO_PIN, HIGH);
  // 0.343 = speed of sound in centimeters per microsecond
  // divide by two for tround trip
  distance = (duration * .0343) / 2;
  Serial.println("distance");
  Serial.println(distance);

  if (light < 8 and distance < 75) {
    digitalWrite(RLED_PIN, HIGH);
    Serial.println("It's on!");
  }
  else {
    digitalWrite(RLED_PIN, LOW);
    Serial.println("It's off!");
  }

  delay(1000);  // wait one second
}
