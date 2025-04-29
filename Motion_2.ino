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


// loop
void loop() { //note: IR sensor 1 = no light detected (black - on line), 0 = light reflected (white - off line)
  encoderRcount = rodom.getCount();
  encoderLcount = lodom.getCount();
  encoderDiff = - encoderRcount + encoderLcount;

  Serial.print(" countL:   ");
  Serial.print(encoderLcount);
  Serial.print("  ");
  
  Serial.print(" countR:   ");
  Serial.print(encoderRcount);
  Serial.print("  ");
  
  if (numActions > 5){
    stopMove(1000);
    Serial.print("  done");
    digitalWrite(led,HIGH);
  }
  else if (numActions % 2 == 0){
    if (encoderDiff < 1425){
      turnLeft(10);
      delay(20);
    }
    else{
      stopMove(100);
      numActions++;
      delay(1900);
    }
  }

  else if(numActions % 2 == 1){
    if (encoderDiff > 0){
      turnLeftBackwards(10);
      delay(20);
    }  
    else{
      stopMove(100);
      numActions++;
      delay(1900);
    }
  }
  Serial.print("\n");
}
