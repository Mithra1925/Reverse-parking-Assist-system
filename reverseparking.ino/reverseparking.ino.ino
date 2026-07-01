#include <LiquidCrystal.h>

LiquidCrystal lcd(7, 6, 5, 4, 3, 2);

const int trigPin = 9;
const int echoPin = 10;

const int buzzer = 11;
const int led = 12;

long duration;
int distance;

void setup()
{
  lcd.begin(16,2);

  pinMode(trigPin,OUTPUT);
  pinMode(echoPin,INPUT);

  pinMode(buzzer,OUTPUT);
  pinMode(led,OUTPUT);

  lcd.print("Reverse Assist");
  delay(2000);
  lcd.clear();
}

void loop()
{
  digitalWrite(trigPin,LOW);
  delayMicroseconds(2);

  digitalWrite(trigPin,HIGH);
  delayMicroseconds(10);

  digitalWrite(trigPin,LOW);

  duration = pulseIn(echoPin,HIGH);

  distance = duration * 0.034 / 2;

  lcd.setCursor(0,0);
  lcd.print("Dist:");
  lcd.print(distance);
  lcd.print(" cm   ");

  if(distance > 100)
  {
    lcd.setCursor(0,1);
    lcd.print("SAFE         ");

    digitalWrite(led,LOW);
    noTone(buzzer);
  }

  else if(distance > 50)
  {
    lcd.setCursor(0,1);
    lcd.print("CAUTION      ");

    digitalWrite(led,LOW);

    tone(buzzer,1000);
    delay(300);
    noTone(buzzer);
    delay(300);
  }

  else if(distance > 20)
  {
    lcd.setCursor(0,1);
    lcd.print("SLOW DOWN    ");

    digitalWrite(led,HIGH);

    tone(buzzer,1000);
    delay(150);
    noTone(buzzer);
    delay(150);
  }

  else
  {
    lcd.setCursor(0,1);
    lcd.print("STOP !!      ");

    digitalWrite(led,HIGH);

    tone(buzzer,1200);
  }

  delay(50);
}
