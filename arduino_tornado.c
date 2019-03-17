#include <LiquidCrystal_I2C.h>

int wait = 200;
int resetPin = A1;
int rightButton = A0;
int leftButton = A2;
int leftPlayerPoints = 0;
int rightPlayerPoints = 0;
int maxPoints = 5;
int valR_previous = 0;
int valL_previous = 0;

/*
*  LCM1602 & Arduino Uno
*  VCC - > 5 V
*  GND - GND
*  SCL -> A5
*  SDA -> A4
*/
LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);  // Ustawienie adresu ukladu na 0x27

void setup() {
  pinMode(0, OUTPUT);
  pinMode(1, OUTPUT);
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(13, OUTPUT);
  pinMode(leftButton, INPUT);
  pinMode(rightButton, INPUT);

  lcd.begin(16, 2);  // Inicjalizacja LCD 2x16
  lcd.backlight(); // zalaczenie podwietlenia
  lcd.setCursor(0, 0); // Ustawienie kursora w pozycji 0,0 (pierwszy wiersz, pierwsza kolumna)
  lcd.print("Hello!");
  delay(500);
  lcd.setCursor(0, 1); //Ustawienie kursora w pozycji 0,0 (drugi wiersz, pierwsza kolumna)
  lcd.print("Let's play!");
  delay(500);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Blue: ");
  lcd.print(leftPlayerPoints);
  lcd.setCursor(0, 1);
  lcd.print("Red: ");
  lcd.print(rightPlayerPoints);

  BlinkAll(13, maxPoints, wait);
}

void loop() 
{
  for (int i = 1; i <= 13; i++) {
    Blink(i, wait);
  }
  for (int i = 12; i >= 0; i--) {
    Blink(i, wait);
  }
  if (wait > 20) {
    wait -= 10;
  }
}

void Blink(int pin, int wait) {
  digitalWrite(pin, HIGH);
  CheckButtons(leftButton, rightButton, pin);
  delay(wait);
  digitalWrite(pin, LOW);
}

void BlinkAll(int leds, int times, int wait) {
  for (int i = 0; i < times; i++) {
    for (int j = 0; j <= leds; j++) {
      digitalWrite(j, HIGH);
    }
    delay(wait);

    for (int j = 0; j <= leds; j++) {
      digitalWrite(j, LOW);
    }
    delay(wait);
  }
}

void GameOver(int led, int resetPin) {
  for (int i = 0; i < 5; i++) {
    Blink(led, 100);
  }

  delay(100);
  analogWrite(resetPin, 255);
}

void CheckButtons(int l, int r, int i)
{
  int valL = analogRead(l);
  int valR = analogRead(r);

  if (valL > 300 && valL_previous == 0)
  {
    if (i == 0)
    {
      leftPlayerPoints++;
      UpdatePoints(leftPlayerPoints, rightPlayerPoints);
      BlinkAll(13, 2, wait);
    }
  }

  if (valR > 300 && valR_previous == 0)
  {
    if (i == 13)
    {
      rightPlayerPoints++;
      UpdatePoints(leftPlayerPoints, rightPlayerPoints);
      BlinkAll(13, 2, wait);
    }
  }

    valR_previous = valL;
    valL_previous = valL;
}

void UpdatePoints(int leftP, int rightP){
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Blue: ");
  lcd.print(leftP);
  lcd.setCursor(0, 1);
  lcd.print("Red: ");
  lcd.print(rightP);
}