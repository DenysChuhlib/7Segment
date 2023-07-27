#include <7Segment.h>
TM1637 disp(D7, D6);

Digits7SRunningString<> run;

void setup() {
  disp.setBrightness(7);
  
  run.runningString("7Segment");
  //run.setDel(200); //default 200
}

void loop() {
  if (!run.isAnimation()) run.runningString("7Segment");
  if (run.tickAnimation()) disp.display(run);
}
