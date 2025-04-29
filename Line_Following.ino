#include <rcc.h>

Right_Dir_Odom rodom;
Left_Dir_Odom lodom;

int encoderRcount;
int encoderLcount;
int encoderDiff;

//updates sensors[] -- returns nothing to avoid memory leaks, dangling pointers, etc.
//scales with numSensors as long as IR inputs are in sequential pin #s

int numActions = 0;


const int numSensors = 3; //number of sensors attatched to car

const int IR1 = A2; // Front left IR sensor
const int IR2 = A1; // Front middle IR sensor
const int IR3 = A0; // Front right IR sensor

int sensors[numSensors]; //most recent values of IR sensors

void updateSensors(){ 
  sensors[0] = digitalRead(IR1);
  sensors[1] = digitalRead(IR2);
  sensors[2] = digitalRead(IR3);
}

const int movementStep = 25; //time each movement step is executed for (in ms)

const int encoderL1 = 12; // two encoder pins for each
const int encoderL2 = 2;
const int encoderR1 = 3;
const int encoderR2 = 4;

const int led = 13;

int numReadings = 0;

// setup
void setup() {
  Serial.begin(115200);
  pinMode(encoderR1, INPUT);
  pinMode(encoderL1, INPUT);
  pinMode(led,OUTPUT);
  digitalWrite(led, LOW);

}

void loop() { //note: IR sensor 1 = no light detected (black - on line), 0 = light reflected (white - off line)
  updateSensors();
  numReadings++;
  
  //printing a bunch of stuff for debugging
  Serial.print("sensor states: ");
  for (int i : sensors){ //prints sensor vals for debugging
    Serial.print(i);
    Serial.print("  ");
  } 

  
  // 3 sensor implementation -- 0 = white paper, 1 = detects line
  if (sensors[0] == 0 && sensors [1] == 0 && sensors[2] == 0){ // all see paper -- append for turning later
    turnLeft(movementStep);
    Serial.print("   left");
  }
  else if(sensors[0] == 1 && sensors [1] == 1 && sensors[2] == 1){ //all see line -- append for turning later
    if (numReadings > 10000){
      stopMove(1000);
      digitalWrite(led,HIGH);
      Serial.print("Done");
    }
    else if (numReadings > 50){
      goForward(25);
      stopMove(50);
      if (sensors[0] == 1 && sensors [1] == 1 && sensors[2] == 1){
        numReadings += 1000;
      }
      else{
        numReadings = 0;
      }
    }
    else{
      turnRight(movementStep);
      Serial.print("   Right");
    }
  }
  else if(sensors[0] == 0 && sensors[1] == 1 && sensors[2] == 0){ // only middle on -- go fwd
    goForward(movementStep);
    Serial.print("   FWD");
  }
  else if(sensors[0] == 0 && sensors[2] == 1){ //Right turning condition
    turnRight(movementStep);
    Serial.print("   Right");
  }
  else if(sensors[0] == 1 && sensors[2] == 0){ //Left turn condition
    turnLeft(movementStep*2);
    Serial.print("  Left");
  }
  else if(sensors[0] == 1 && sensors[1] == 0 && sensors[2] == 1){ //corner case, just move to get out
    Serial.print("  left");
  }
  

  stopMove(50);
 
  Serial.print("  Reading #: ");
  Serial.print(numReadings);
  Serial.print("\n");
}
