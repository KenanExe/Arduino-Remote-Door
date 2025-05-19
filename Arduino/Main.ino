#include <Wire.h>
#include <IRremote.h>
#include <LiquidCrystal.h>
#include <Servo.h>


int ledPinRed = 3;     // Red
int ledPinYellow = 4;  // Yellow 
int ledPinGreen = 5;   // Green
int irPin = 6;
int servoPin = 9;
int potPin = A0;
int x = 0;
IRrecv irrecv(irPin);
decode_results results;
LiquidCrystal lcd(0, 1, 2, 7, 11, 12);
Servo motor;

void setup() {

  pinMode(13, OUTPUT); //arduino uno LED
  //pinmode(2, OUTPUT); //esp LED

  motor.attach(servoPin);
  lcd.begin(16, 2);
  lcd.print(":D");
  irrecv.enableIRIn();
  pinMode(ledPinRed, OUTPUT);
  pinMode(ledPinYellow, OUTPUT);
  pinMode(ledPinGreen, OUTPUT);
}

void loop() {
  digitalWrite(13, HIGH); //uno LED
  //digitalWrite(2, HIGH); //esp LED

  int reading = analogRead(potPin);
  int angle = map(reading, 0, 1023, 0, 180);

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("pos:");

  if (angle == 0) {
    lcd.setCursor(0, 1);
    lcd.print("Lock");
    digitalWrite(ledPinRed, HIGH);
    digitalWrite(ledPinYellow, LOW);
    digitalWrite(ledPinGreen, LOW);
  } else if (angle == 180) {
    lcd.setCursor(0, 1);
    lcd.print("Unlock");
    digitalWrite(ledPinRed, LOW);
    digitalWrite(ledPinYellow, LOW);
    digitalWrite(ledPinGreen, HIGH);
  } else {
    lcd.setCursor(0, 1);
    lcd.print("Waiting code...");
    digitalWrite(ledPinRed, LOW);
    digitalWrite(ledPinYellow, HIGH);
    digitalWrite(ledPinGreen, LOW);
  }

  digitalWrite(13, LOW); //uno LED
  //digitalWrite(2, LOW); //esp LED
  delay(220); //I think it's very optimize delay
//  if u using esp, u can reboot system for it. (some times it's stuck)
//   if (x >= 100) {
//    x = 0;
//    ESP.restart();
//  }

}

void unlock() {
  motor.write(180);
}

void lock() {
  motor.write(0);
}
