#include <ESP8266WiFi.h>  // esp8266
//#include <WiFi.h>       // esp32

// Click to install http://librarymanager/All#NTPtime
// See also https://github.com/DenysChuhlib/NTPtime/blob/main/examples/Watch/Watch.ino
#include <NTPtime.h>
NTPtime Time(2); //UA in +2 time zone
DSTime dst(3, 0, 7, 3, 10, 0, 7, 4); //https://en.wikipedia.org/wiki/Eastern_European_Summer_Time
uint8_t timerM;

#include <7Segment.h>
TM1637 disp(D7, D6); // esp8266
//TM1637 disp(2, 15); // esp32

void setup() {
  disp.setBrightness(7);

  disp.setAllDel(40);

  Serial.begin(115200);
  
  WiFi.begin("WIFI_SSID", "WIFI_PASS");
  while (WiFi.status() != WL_CONNECTED) delay(10);
  Serial.println("Connected");

  Time.setDSTauto(&dst);
  Time.begin();
}

void loop() {
  Time.updateOnTime(0,0,1);
  Time.tick();

  if (Time.everyM(timerM, 1)) {
    timerM = Time.minute();
    disp.twistClock(Time.hour(), Time.minute(), true, true);
  }

  disp.tickDisplay();
}
