#include <LiquidCrystal_I2C.h>
#include <Servo.h>

LiquidCrystal_I2C lcd (0x27, 16, 2);
Servo myServoMotor;

// initialize pins here
int myServoPin = 2;
int myPushButtonPin = 3;
int myGreenLED = 4;
int myRedLED = 5;
int myTrigPin = 6;
int myEchoPin = 7;

// initialize variables here
long duration, cm;
int threshold = 10;
int buttonState = 0;

void setup() {
  // put your setup code here, to run once:
  lcd.init();
  lcd.begin(16, 2);
  lcd.backlight();
  
  Serial.begin(9600);

  pinMode(myTrigPin, OUTPUT);
  pinMode(myEchoPin, INPUT);

  digitalWrite(myRedLED, LOW);
  digitalWrite(myGreenLED, LOW);

  pinMode(3, INPUT);

  myServoMotor.attach(2);
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(myTrigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(myTrigPin, LOW);

  buttonState = digitalRead(3);

  duration = pulseIn(myEchoPin, HIGH);
  cm = ((duration * 0.034) / 2);

  Serial.print("Distance");
  Serial.println(cm);
  delay(1000);

  if (cm < threshold) {
    digitalWrite(myRedLED, HIGH);
    digitalWrite(myGreenLED, LOW);
    lcd.setCursor(0,0);
    lcd.print("Welcome");
    lcd.setCursor(0, 1);
    lcd.print("Get Ticket");
    
    if (buttonState == HIGH) {
      digitalWrite(myRedLED, LOW);
      digitalWrite(myGreenLED, HIGH);
      lcd.setCursor(0,0);
      lcd.print("Proceed");

      // open gate when button is pressed
      myServoMotor.write(90); // 90 degree angle
      delay(3000);

      Serial.println("car is moving away");

      myServoMotor.write(0); // turn angle to 0 degrees
      delay(2000);
      
      Serial.println("next car should proceed");
    }
  }
  return 0;
}