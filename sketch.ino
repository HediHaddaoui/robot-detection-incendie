#include <ESP32Servo.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <DHT.h>

// ============================================================
//  1. RÉGLAGES DES VITESSES
// ============================================================
#define V_PATROUILLE  80
#define V_ROTATION    190
#define V_RECUL       90

// ============================================================
//  2. CONFIGURATION MATERIELLE
// ============================================================
#define RELAY_PUMP  17
#define SENSOR_FC   32
#define SENSOR_FL   33
#define SENSOR_FR   34
#define SENSOR_BL   35
#define SENSOR_BR   23

#define TRIG_PIN    5
#define ECHO_PIN    18
#define SERVO_PIN   19

#define FEU_DETECTE LOW
#define POMPE_ON    LOW
#define POMPE_OFF   HIGH

#define IN1 25
#define IN2 26
#define IN3 27
#define IN4 14
#define ENA 12
#define ENB 13

DHT dht(15, DHT22);
LiquidCrystal_I2C lcd(0x27, 16, 2);
Servo myservo;

int servoPos = 90;
int servoDir = 5;
unsigned long tServo = 0;

// ============================================================
//  3. SETUP
// ============================================================
void setup() {
  pinMode(RELAY_PUMP, OUTPUT);
  digitalWrite(RELAY_PUMP, POMPE_OFF);

  Serial.begin(115200);
  Serial.println("--- SYSTEME PRET ---");

  dht.begin();

  lcd.init();
  lcd.backlight();

  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);

  ESP32PWM::allocateTimer(0);
  myservo.attach(SERVO_PIN, 500, 2400);
  myservo.write(90);

  pinMode(SENSOR_FC, INPUT);
  pinMode(SENSOR_FL, INPUT);
  pinMode(SENSOR_FR, INPUT);
  pinMode(SENSOR_BL, INPUT);
  pinMode(SENSOR_BR, INPUT);

  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);

  lcd.setCursor(0, 0);
  lcd.print("Robot Pret");
}

// ============================================================
//  4. LOOP
// ============================================================
void loop() {
  bool fc = (digitalRead(SENSOR_FC) == FEU_DETECTE);
  bool fl = (digitalRead(SENSOR_FL) == FEU_DETECTE);
  bool fr = (digitalRead(SENSOR_FR) == FEU_DETECTE);
  bool bl = (digitalRead(SENSOR_BL) == FEU_DETECTE);
  bool br = (digitalRead(SENSOR_BR) == FEU_DETECTE);

  long dist = mesurer();

  // --- ACTION POMPE : feu devant + distance < 50 cm ---
  if (fc && dist < 50) {
    stopMoteurs();

    digitalWrite(RELAY_PUMP, POMPE_ON);

    lcd.setCursor(0, 0);
    lcd.print("FEU! DIST:");
    lcd.print(dist);
    lcd.print("cm ");

    // Balayage du servo
    if (millis() - tServo > 30) {
      tServo = millis();

      servoPos += servoDir;

      if (servoPos >= 120 || servoPos <= 60) {
        servoDir *= -1;
      }

      myservo.write(servoPos);
    }
  }

  else {
    digitalWrite(RELAY_PUMP, POMPE_OFF);
    myservo.write(90);

    // --- Recherche feu gauche ---
    if (fl || bl) {
      lcd.setCursor(0, 0);
      lcd.print("Cherche Gauche ");
      tournerGauche();
    }

    // --- Recherche feu droite ---
    else if (fr || br) {
      lcd.setCursor(0, 0);
      lcd.print("Cherche Droite ");
      tournerDroite();
    }

    // --- Patrouille normale ---
    else {
      if (dist < 40) {
        eviterObstacle();
      } else {
        avancer(V_PATROUILLE);

        lcd.setCursor(0, 0);
        lcd.print("Patrouille...  ");
      }
    }
  }

  // --- Affichage temperature et humidite ---
  static unsigned long lastDHT = 0;

  if (millis() - lastDHT > 2000) {
    lastDHT = millis();

    float temperature = dht.readTemperature();
    float humidity = dht.readHumidity();

    lcd.setCursor(0, 1);

    lcd.print("T:");
    lcd.print((int)temperature);
    lcd.print("C H:");
    lcd.print((int)humidity);
    lcd.print("% ");
  }
}

// ============================================================
//  5. FONCTIONS OUTILS
// ============================================================

long mesurer() {
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);

  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);

  digitalWrite(TRIG_PIN, LOW);

  long d = pulseIn(ECHO_PIN, HIGH, 25000);

  if (d == 0) {
    return 999;
  }

  return d * 0.034 / 2;
}

void eviterObstacle() {
  stopMoteurs();
  delay(150);

  reculer(V_RECUL);
  delay(600);

  tournerDroite();
  delay(800);

  stopMoteurs();
}

void tournerDroite() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  analogWrite(ENA, V_ROTATION);

  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  analogWrite(ENB, 0);
}

void tournerGauche() {
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  analogWrite(ENB, V_ROTATION);

  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  analogWrite(ENA, 0);
}

void avancer(int v) {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);

  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);

  analogWrite(ENA, v);
  analogWrite(ENB, v);
}

void reculer(int v) {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);

  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);

  analogWrite(ENA, v);
  analogWrite(ENB, v);
}

void stopMoteurs() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);

  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);

  analogWrite(ENA, 0);
  analogWrite(ENB, 0);
}