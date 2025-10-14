#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <RTClib.h>

LiquidCrystal_I2C lcd (0x27, 16,2);
RTC_DS3231 rtc;

int buzzer = 2;
int button = 3;
String val;


void setup() {
  pinMode(button,INPUT_PULLUP);
  pinMode(buzzer,OUTPUT);
  lcd.init();
  lcd.backlight();
  Wire.begin();
  
  if(!rtc.begin()){
    lcd.print("NO RTC FOUND!");
    while(true);
  }

  if(rtc.lostPower()){
    lcd.clear();
    lcd.print("RTC LOST POWER!");
    delay(2000);
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  }
  lcd.clear();
}


void loop() {
  DateTime now = rtc.now();
  

  int displayHour;
  if (now.hour() == 0) {
    displayHour = 12;
    val = "am";
  } else if (now.hour() < 12) {
    displayHour = now.hour();
    val = "am";
  } else if (now.hour() == 12) {
    displayHour = 12;
    val = "pm";
  } else {
    displayHour = now.hour() - 12;
    val = "pm";
  }
  lcd.setCursor(3, 0);
  if (displayHour < 10) lcd.print("0");
  lcd.print(displayHour);
  lcd.print(":");
  if (now.minute() < 10) lcd.print("0");
  lcd.print(now.minute());
  lcd.print(":");
  if (now.second() < 10) lcd.print("0");
  lcd.print(now.second());
  lcd.print(" ");
  lcd.print(val);


  

  lcd.setCursor(3, 1);
  lcd.print(now.month());
  lcd.print("/");
  lcd.print(now.day());
  lcd.print("/");
  lcd.print(now.year()); //-2000 if you only want the last 2 numbers

  if (digitalRead(button) == LOW) {
    digitalWrite(buzzer, HIGH);
    delay(100);
    digitalWrite(buzzer, LOW);


    lcd.clear();
    lcd.setCursor(2, 0);
    lcd.print("Hello!");
    lcd.setCursor(2, 1);
    if (val == "am") {
      lcd.print("Good Morning!");
    } else {
      lcd.print("Good Evening!");
    }
    delay(3000);
    lcd.clear();
    
  }



  delay(1000);
  


  // put your main code here, to run repeatedly:

}
