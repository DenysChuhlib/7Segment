#include <7Segment.h>
TM1637 disp(D7, D6);

void setup() {
  disp.setBrightness(7);
}

void loop() {
  Digits7SRunningString<> run;
  run.runningString("7Segment");
  run.setDel(200);

  if (run.tickAnimation()) disp.display(run);
  if (!run.isAnimation()) run.runningString("7Segment");
}
