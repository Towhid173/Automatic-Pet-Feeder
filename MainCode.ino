#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include "RTClib.h"
#include <Servo.h>

Servo myservo;
// int pos = 0;

RTC_DS1307 rtc;
LiquidCrystal_I2C lcd(0x27, 16, 2);
char daysOfTheWeek[7][12] = {"Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"};


void setup ()
{
    Serial.begin(9600);

    //LCD
    lcd.init ();  // initialize the lcd
    lcd.backlight();//To Power ON the back light

    //Servo
    myservo.attach(9);
  


    if (! rtc.begin())
    {
        lcd.print("Couldn't find RTC");
        while (1);
    }
    if (! rtc.isrunning())
    {
        lcd.print("RTC is NOT running!");
    }
    //rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));//auto update from computer time
    //rtc.adjust(DateTime(2014, 1, 21, 3, 0, 0));// to set the time manually

    //IRSEnsor
    pinMode(7,OUTPUT);
    pinMode(3,INPUT);

}

void servo()
{
    int t;
    t=1;
    while(t--)
    {
        for (int pos = 180; pos >= 120; pos -= 1)   // goes from 0 degrees to 180 degrees int pos = 120; pos <= 180; pos += 1
        {
            // in steps of 1 degree
            myservo.write(pos);              // tell servo to go to position in variable 'pos'
            delay(20);                      // waits 15ms for the servo to reach the position
        }
        delay(3000);
        for (int pos = 120; pos <= 180; pos += 1)   // goes from 180 degrees to 0 degrees
        {
            myservo.write(pos);              // tell servo to go to position in variable 'pos'
            delay(20);                      // waits 15ms for the servo to reach the position
        }
        break;
    }
}
  

void loop ()
{
    //clock start
    DateTime now = rtc.now();
    lcd.setCursor(0, 1);
    lcd.print("TIME");
    lcd.print(" ");
    lcd.print(now.hour());
    lcd.print(':');
    lcd.print(now.minute());
    lcd.print(':');
    lcd.print(now.second());
    lcd.print("  ");
    lcd.setCursor(0, 0);
    lcd.print("DATE");
    lcd.print(" ");
    //lcd.print(daysOfTheWeek[now.dayOfTheWeek()]);
    //lcd.print(" ");
    lcd.print(now.day());
    lcd.print('/');
    lcd.print(now.month());
    lcd.print('/');
    lcd.print(now.year());
    lcd.print("  ");
    //clock end

    //IR Sensor start
    if (digitalRead(3)== HIGH)
    {
        digitalWrite(7,HIGH); //set low after all work done

        Serial.println("Food Alert!");

        delay(500);

        digitalWrite(7,LOW);

        delay(500);

    }
    else
    {
        digitalWrite(7,LOW);//set HIGH after all work done
        delay(10);
    }
    //IR Sensor end
    //servo start
    if(now.hour() == 1){
      if(now.minute() == 59 ){
        if(now.second()== 0 || now.second()==15 || now.second()==30 || now.second()==45 || now.second()==60 ){
          servo();
        }
      }
    }
    //servo end
    // servo();
}


  
