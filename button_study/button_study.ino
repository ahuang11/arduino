const int BUTTON_PIN = 3;
const int LED_PIN = 2;
const int HOLD_MODE_PIN = 8;
const int TOGGLE_MODE_PIN = 9;
const int BLINK_MODE_PIN = 10;

void setup() {
  Serial.begin(9600);
  pinMode(BUTTON_PIN, INPUT);
  pinMode(LED_PIN, OUTPUT);
  pinMode(HOLD_MODE_PIN, OUTPUT);
  pinMode(TOGGLE_MODE_PIN, OUTPUT);
  pinMode(BLINK_MODE_PIN, OUTPUT);
}

int button_state = 0;
int toggle_state = 0;
int mode_state = 0;
int mode_count = 0;
int blink_state = 0;

void loop() {
  button_state = digitalRead(BUTTON_PIN);
  if (button_state == HIGH and mode_state == 0) {
    digitalWrite(LED_PIN, HIGH);
  } // turn on if button is held
  else if (button_state == LOW and mode_state == 0) {
    digitalWrite(LED_PIN, LOW);
  } // turn off if button is not held
  else if (button_state == HIGH and mode_state == 1) {
    if (toggle_state == 0) {
      toggle_state = 1;
      digitalWrite(LED_PIN, HIGH);
    } // flip on if the switch was off before
    else if (toggle_state == 1) {
      toggle_state = 0;
      digitalWrite(LED_PIN, LOW);
    } // flip off if the switch was on before
    delay(200); // prevent the light from flickering
  }
  else if (button_state == HIGH and mode_state == 2 and blink_state == 0) {
    digitalWrite(LED_PIN, HIGH);
    blink_state = 1;
  } // blink on if button is held
  else if (button_state == HIGH and mode_state == 2 and blink_state == 1) {
    digitalWrite(LED_PIN, LOW);
    blink_state = 0;
  } // blink off if button is held
  else if (button_state == LOW and mode_state == 2) {
    digitalWrite(LED_PIN, LOW);
  } // turn off if no button

  // start accumulating if long pressed
  if (button_state == HIGH) {
    mode_count += 1;
  }
  else {
    mode_count = 0;
  }

  // swap the mode state if the button is pressed for 3 seconds (30 * 100 milliseconds)
  // mode == 1 only requires 10 because there's a 200 ms delay nested above
  if ((mode_count >= 30 or mode_state == 3) or (mode_count >= 10 and mode_state == 1)) {
    mode_count = 0;
    if (mode_state == 3) {
      mode_state = 0;
    }
    else {
      mode_state += 1;
    }
  }

  // activate the corresponding LED for each mode
  if (mode_state == 0) {
    digitalWrite(HOLD_MODE_PIN, HIGH);
    digitalWrite(TOGGLE_MODE_PIN, LOW);
    digitalWrite(BLINK_MODE_PIN, LOW);
  }
  else if (mode_state == 1) {
    digitalWrite(HOLD_MODE_PIN, LOW);
    digitalWrite(TOGGLE_MODE_PIN, HIGH);
    digitalWrite(BLINK_MODE_PIN, LOW);
  }
  else if (mode_state == 2) {
    digitalWrite(HOLD_MODE_PIN, LOW);
    digitalWrite(TOGGLE_MODE_PIN, LOW);
    digitalWrite(BLINK_MODE_PIN, HIGH);
  }
  else {
    digitalWrite(HOLD_MODE_PIN, LOW);
    digitalWrite(TOGGLE_MODE_PIN, LOW);
    digitalWrite(BLINK_MODE_PIN, LOW);
  }
  delay(100);
}
