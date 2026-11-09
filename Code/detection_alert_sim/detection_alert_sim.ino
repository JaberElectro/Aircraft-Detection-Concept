/*
 * Aircraft Detection Concept: Detection & Alert Simulation
 * ---------------------------------------------------------
 * Motion sensor -> servo sweep -> piezo warning tone.
 * The potentiometer sets the alert frequency (500-2000 Hz).
 *
 * Original experimental platform: Arduino Nano.
 *
 * SIMULATION ONLY: this produces a local audible alert. It does not
 * identify aircraft or interact with any communication system.
 *
 * Wiring:
 *   Motion sensor OUT -> D2
 *   Potentiometer wiper -> A0
 *   Piezo buzzer -> D9
 *   Servo signal -> D6
 */

#include <Servo.h>

Servo scanServo;

const int MOTION_PIN = 2;
const int POT_PIN    = A0;
const int BUZZER_PIN = 9;
const int SERVO_PIN  = 6;

void setup() {
  Serial.begin(9600);

  pinMode(MOTION_PIN, INPUT);
  pinMode(BUZZER_PIN, OUTPUT);

  scanServo.attach(SERVO_PIN);
  scanServo.write(90);                     // centre / idle position

  Serial.println(F("Detection Simulation Started"));
}

void loop() {
  int motionDetected = digitalRead(MOTION_PIN);
  int sensitivity    = analogRead(POT_PIN);

  int warningFrequency = map(sensitivity, 0, 1023, 500, 2000);

  if (motionDetected == HIGH) {
    Serial.println(F("Motion Detected"));
    Serial.println(F("Unknown Target - Simulated Alert"));

    scanServo.write(45);                   // sweep left
    tone(BUZZER_PIN, warningFrequency, 300);
    delay(400);

    scanServo.write(135);                  // sweep right
    delay(400);
  } else {
    noTone(BUZZER_PIN);
    scanServo.write(90);
  }

  delay(50);
}
