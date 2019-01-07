//Solartracker.ino

//Dual axis solar tracking system
//by kgross@jensalt.com

#include <String.h>
int leftLDRpin = 0;// analog input pins for reading the LDR;s
int rightLDRpin = 1;
int upLDRpin = 2;
int downLDRpin = 3;
int up = 13;  //digitial output pin connected to relay to move unit up
int down = 12; // digital output pin connected to relay to move unit down
int left = 11; // digital output pin connected to relay to move unit left
int right = 10;// digital output pin connected to realy to move unit right

int leftLDR = 0;
int rightLDR = 0;
int upLDR = 0;
int downLDR = 0;
int elevation = 0;
int azmith = 0;
int elevationerror = 0;
int azmitherror = 100;
int count = 0;
int movetime = 2000; //amount of time to energize the relays to move the mount
int dark = 300; // set the value for dark to put the panel to sleep for the night.
boolean debug = true; // set to true to print out debugging into to serial console, false to skip printing
int delaytime=20000;//Set the delay time before checks on movement.

void setup() {
  // put your setup code here, to run once:

  Serial.begin(9600);

  pinMode(up, OUTPUT);
  pinMode(down, OUTPUT);
  pinMode(left, OUTPUT);
  pinMode(right, OUTPUT);
  
  digitalWrite(up, HIGH); // since relay is low triggered turn all relay outputs high.
  digitalWrite(down, HIGH);
  digitalWrite(left, HIGH);
  digitalWrite(right, HIGH);
}

void moveup(void) {
  digitalWrite(up, LOW);
  if (debug)   Serial.println("Moving up");
  delay(movetime);
  if (debug) Serial.println("done");
  digitalWrite(up, HIGH);

}
void movedown(void) {
  digitalWrite(down, LOW);
  if (debug) Serial.println("Moving down");
  delay(movetime);
  if (debug) Serial.println("done");
  digitalWrite(down, HIGH);
}
void moveleft(void) {
  digitalWrite(left, LOW);
  if (debug) Serial.println("Moving left");
  delay(movetime);
  if (debug) Serial.println("done");
  digitalWrite(left, HIGH);

}
void moveright(void) {
  digitalWrite(right, LOW);
  if (debug) Serial.println("Moving right");
  delay(movetime);
  if (debug) Serial.println("done");
  digitalWrite(right, HIGH);
}
void nightmove(void){
  digitalWrite(right,LOW);
  delay(movetime*4);
  digitalWrite(right,HIGH);
}
void loop() {



  // put your main code here, to run repeatedly:
  upLDR = analogRead(upLDRpin);
  downLDR = analogRead(downLDRpin);
  leftLDR = analogRead(leftLDRpin);
  rightLDR = analogRead(rightLDRpin);
  elevation = (upLDR - downLDR) - elevationerror; //compare up to down to determine if movement is needed;
  azmith = (leftLDR - rightLDR) - azmitherror; //compare east to west to determin if movement is needed;
  if (debug) Serial.print("Elevation: ");
  if (debug) Serial.print(elevation);
  if (debug) Serial.print(" Azmith: ");
  if (debug) Serial.println(azmith);
  if (debug) Serial.print("UP: ");
  if (debug) Serial.print(upLDR);
  if (debug) Serial.print(" Down: ");
  if (debug) Serial.print(downLDR);
  if (debug) Serial.print(" Left: ");
  if (debug) Serial.print(leftLDR);
  if (debug) Serial.print(" Right: ");
  if (debug) Serial.print(rightLDR);


 
  if (debug) Serial.println();
  
  
  if ((upLDR < dark) && (downLDR < dark) && (leftLDR < dark) && (rightLDR < dark)) {
   
    if (debug)  Serial.println("dark sleeping in debug so does not really sleep");
     nightmove();
    if (!debug)   delay(7200000);
    if (debug) delay(2000);
   
  }
  if (debug) Serial.println("Checking elevation");
  if (elevation > 100 || elevation < 100) {
    if (elevation < 1) {
      moveup();
    } else {
      movedown();
    }
  }
  if (debug) Serial.println("checking azmith");
  if (azmith > 100 || azmith < 100) {
    if (azmith < 1 ) {
      moveleft();
    } else  {
      moveright();

    }
  }
  if (!debug) delay(delaytime);// delay until next check so unit does not just move bank and forth.




}
