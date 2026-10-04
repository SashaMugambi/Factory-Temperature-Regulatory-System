// Arduino 1
// C++ code
//
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27,16,2);

void setup () {
  pinMode (3, OUTPUT); //RED
  pinMode (4, OUTPUT); //BLUE
  pinMode (5, OUTPUT); //GREEN
  pinMode (7, OUTPUT); //BUZZER
  pinMode (A0, INPUT); //TEMP SENSOR
  pinMode (8, INPUT); //Ultrasonic sensor
  lcd. init ();
  lcd. backlight ();
  Serial. begin(9600);
}

void loop () {

  float temp = 0;
  bool override = false;

  if (Serial. available() > 0) {
    String data = Serial.readStringUntil('\n');
    data. trim ();

    if (data == "off") {
      noTone (7);
      lcd.clear ();
      lcd. setCursor (0,0);
      lcd.print ("CMD: OFF");
      lcd. setCursor (0,1);
      lcd.print ("Buzzer Off");
      delay (500);
      return;
    }

    temp = data.toFloat ();
    if (temp > 0) {
      override = true;
    }
  }

  if (! override) {
    int t = analogRead(A0);
    float v = t * (5.0 / 1023.0);
    temp = v * 100;
  }

  lcd. clear ();
  lcd. setCursor (0,0);
  lcd.print("Temp=");
  lcd.print(temp);
  lcd. setCursor (0,1);

  if (temp <= 30) {
    digitalWrite (3, LOW);
    digitalWrite (4, LOW);
    digitalWrite (5, HIGH); //GREEN ON
    analogWrite (6, 100);
    lcd.print("Cool");
    noTone (7);
  }
  else if (temp > 30 && temp <= 50) {
    digitalWrite (3, LOW); 
    digitalWrite (4, HIGH); //BLUE ON
    digitalWrite (5, LOW);
    analogWrite (6, 180);
    lcd. print ("Warm");
    tone (7,200);
  }
  else {
    digitalWrite (3, HIGH); //RED ON
    digitalWrite (4, LOW);
    digitalWrite (5, LOW);
    analogWrite (6, 255);
    lcd. print("Hot");
    tone (7,1000);
  }
  delay (5000);
}

// Arduino 2
// C++ code
//
void setup () {
  pinMode (2, OUTPUT);
  Serial. begin(9600);
}

void loop () {
  if (Serial. available () > 0) {
    String data = Serial. readStringUntil('\n');
    data. trim ();
    Serial. println(data);

    if (data == "off") {
      noTone (2);
    }
    else if (data == "low") {
      tone (2, 500);
    }
    else if (data == "medium") {
      tone (2, 1000);
    }
    else if (data == "high") {
      tone (2, 2000);
    }
    else {
      float temp = data. toFloat ();
      if (temp <= 30) {
        tone (2, 500);
      }
      else if (temp <= 50) {
        tone (2, 1000);
      }
      else {
        tone (2, 2000);
      }
    }
  }
}
