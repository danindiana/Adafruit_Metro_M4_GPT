#include "RTC_SAMD51.h"
#include "DateTime.h"

RTC_SAMD51 rtc;
char daysOfTheWeek[7][12] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};

void setup() {
  Serial.begin(115200);
  rtc.begin();
  
  while (!Serial);  // Wait for Serial Monitor to open

  Serial.println("Enter current date and time in format: YYYY/MM/DD HH:MM:SS");
}

void loop() {
  DateTime now = rtc.now();

  // Print current time
  Serial.print(now.year(), DEC);
  Serial.print('/');
  Serial.print(now.month(), DEC);
  Serial.print('/');
  Serial.print(now.day(), DEC);
  Serial.print(" (");
  Serial.print(daysOfTheWeek[now.dayOfTheWeek()]);
  Serial.print(") ");
  Serial.print(now.hour(), DEC);
  Serial.print(':');
  Serial.print(now.minute(), DEC);
  Serial.print(':');
  Serial.println(now.second(), DEC);

  // Check for user input
  if (Serial.available()) {
    String input = Serial.readStringUntil('\n');

    // Parse user input
    int Year = input.substring(0, 4).toInt();
    int Month = input.substring(5, 7).toInt();
    int Day = input.substring(8, 10).toInt();
    int Hour = input.substring(11, 13).toInt();
    int Minute = input.substring(14, 16).toInt();
    int Second = input.substring(17, 19).toInt();

    // Adjust RTC
    DateTime dt(Year, Month, Day, Hour, Minute, Second);
    rtc.adjust(dt);
    Serial.println("RTC adjusted!");

    delay(1000);  // Optional delay
  }
}
