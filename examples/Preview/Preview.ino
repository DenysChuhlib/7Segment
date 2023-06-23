#include <7Segment.h>
TM1637 disp(D7, D6);

void setup() {
  disp.setBrightness(7);
  // put your setup code here, to run once:

}

void loop() {
  Digits7SRunningSring<> run;
  run.runningString("7Segment");
  run.setDel(200);

  if (run.tickAnimation()) disp.display(run);
  if (!run.isAnimation()) run.runningString("7Segment");
  // put your main code here, to run repeatedly:

}
