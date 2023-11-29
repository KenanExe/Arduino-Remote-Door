#include <Wire.h>
#include <IRremote.h>
#include <LiquidCrystal.h>
#include <Servo.h>

int ledPinRed = 3;     // Kırmızı
int ledPinYellow = 4;  // Sarı
int ledPinGreen = 5;   // Yeşil
int irPin = 6;
int servoPin = 9;
int potPin = A0;

IRrecv irrecv(irPin);
decode_results results;
LiquidCrystal lcd(0, 1, 2, 7, 11, 12);
Servo motor;

void setup() {
  motor.attach(servoPin);
  lcd.begin(16, 2);
  lcd.print("( ͡• ͜ʖ ͡•)");
  irrecv.enableIRIn();
  pinMode(ledPinRed, OUTPUT);
  pinMode(ledPinYellow, OUTPUT);
  pinMode(ledPinGreen, OUTPUT);
}

void loop() {
  
  int reading = analogRead(potPin);
  int angle = map(reading, 0, 1023, 0, 180);

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("pos:");

  if (angle == 0) {
    lcd.setCursor(0, 1);
    lcd.print("Kilitli");
    digitalWrite(ledPinRed, HIGH);
    digitalWrite(ledPinYellow, LOW);
    digitalWrite(ledPinGreen, LOW);
  } else if (angle == 180) {
    lcd.setCursor(0, 1);
    lcd.print("Kilit acildi");
    digitalWrite(ledPinRed, LOW);
    digitalWrite(ledPinYellow, LOW);
    digitalWrite(ledPinGreen, HIGH);
  } else {
    lcd.setCursor(0, 1);
    lcd.print("Komut Bekleniyor");
    digitalWrite(ledPinRed, LOW);
    digitalWrite(ledPinYellow, HIGH);
    digitalWrite(ledPinGreen, LOW);
  }

  delay(200);
}

void unlock() {
  motor.write(180);
}

void lock() {
  motor.write(0);
}
