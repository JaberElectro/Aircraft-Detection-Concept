/*
 * Aircraft Detection Concept: Virtual Database Classification
 * -----------------------------------------------------------
 * Demonstrates the "virtual database" stage of the concept.
 * Type a simulated target ID into the Serial Monitor (9600 baud,
 * newline ending) and the system classifies it.
 *
 * Original experimental platform: Arduino Nano.
 *
 * The ID is supplied by the user. That is exactly the point: the physical
 * motion sensor cannot provide one (see README, "What the hardware can
 * actually do").
 */

const int BUZZER_PIN = 9;

// Simulated list of known / friendly IDs.
const char* const FRIENDLY_IDS[] = {
  "SIM-101",
  "SIM-204",
  "SIM-317"
};
const int FRIENDLY_COUNT = sizeof(FRIENDLY_IDS) / sizeof(FRIENDLY_IDS[0]);

bool isFriendly(const String& id) {
  for (int i = 0; i < FRIENDLY_COUNT; i++) {
    if (id.equalsIgnoreCase(FRIENDLY_IDS[i])) return true;
  }
  return false;
}

void setup() {
  Serial.begin(9600);
  pinMode(BUZZER_PIN, OUTPUT);
  Serial.println(F("Virtual database classification. Enter a target ID:"));
}

void loop() {
  if (!Serial.available()) return;

  String id = Serial.readStringUntil('\n');
  id.trim();
  if (id.length() == 0) return;

  Serial.print(F("Target "));
  Serial.print(id);

  if (isFriendly(id)) {
    Serial.println(F(" -> FRIENDLY (logged)"));
  } else {
    Serial.println(F(" -> UNKNOWN (simulated alert)"));
    tone(BUZZER_PIN, 1200, 300);
  }
}
