//#include <rcc.h>

int in1 = 5; //out 1 and 2 are for left wheel
int in2 = 6;
int in3 = 7; //out 3 and 4 are for right wheel
int in4 = 8;

void stopMove(int del){
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW); //left wheel stop
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW); //right wheel stop
  delay(del);
}

void goForward(int del){
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW); //left wheel turn forward
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW); //right wheel turn forward
  delay(del);
  stopMove(1); //stop after moving
}

void turnLeft(int del){
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW); //left wheel stop
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW); //right wheel turn forward
  delay(del);
  stopMove(1); //stop after moving
}

void turnLeftBackwards(int del){
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW); //left wheel stop
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH); //right wheel turn back
  delay(del);
  stopMove(1);
}

void turnRight(int del){
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW); //left wheel turn forward
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW); //right wheel stop
  delay(del);
  stopMove(1); //stop after moving
}

void turnRightBackwards(int del){
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH); //left wheel turn forward
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW); //right wheel stop
  delay(del);
  stopMove(1); //stop after moving
}

void goBackward(int del){ //UPDATE REQUIRED FOR WEIRD WIRING
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH); //left wheel turn backward
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH); //right wheel turn backward
  delay(del);
  stopMove(1); //stop after moving
}
