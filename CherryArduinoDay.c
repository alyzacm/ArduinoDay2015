#include <SPI.h>  
#include <Pixy.h>

/* Drives a DC motor using 5v, low current and the sn754410 driver
!CAUTION! Do not stall the motor by preventing it from spinning!
*/

// This is the main Pixy object 
Pixy pixy;

//Pin Labels for motor 1
int Motor1PowerEN = 6;
int Motor1Logic1 = 8;
int Motor1Logic2 = 7;
//Pin labels for motor 2
int Motor2PowerEN = 5;
int Motor2Logic1 = 4;
int Motor2Logic2 = 2;

int topSpeed = 220;

//the setup routine runs once when you press rest:
void setup() {
      Serial.begin(9600);
      Serial.print("Starting...\n");

      pixy.init();
   /* initialize the digital pins as an output */
   //motor 1
   pinMode(Motor1PowerEN, OUTPUT);
   pinMode(Motor1Logic1, OUTPUT); 
   pinMode(Motor1Logic2, OUTPUT);

   //motor 2
   pinMode(Motor2PowerEN, OUTPUT);
   pinMode(Motor2Logic1, OUTPUT); 
   pinMode(Motor2Logic2, OUTPUT);
   
   //initialize the motor to low
   digitalWrite(Motor1PowerEN, LOW);
   digitalWrite(Motor2PowerEN, LOW);

}
//functions for motor 1
void SetMotor1Forward() {
  digitalWrite(Motor1Logic1, HIGH);
  digitalWrite(Motor1Logic2, LOW);
}

void SetMotor1Backward() {
  digitalWrite(Motor1Logic1, LOW);
  digitalWrite(Motor1Logic2, HIGH);
}

//functions for motor 2
void SetMotor2Forward() {
  digitalWrite(Motor2Logic1, HIGH);
  digitalWrite(Motor2Logic2, LOW);
}

void SetMotor2Backward() {
  digitalWrite(Motor2Logic1, LOW);
  digitalWrite(Motor2Logic2, HIGH);
}
//

void MoveStop() {
  //set the motor speed to 0
  digitalWrite(Motor1PowerEN, LOW);
  digitalWrite(Motor2PowerEN, LOW);
  //delay(50);
}

void MoveForward() {
//set the logic to spin motor one direction
  MoveStop();
  delay(10);
  SetMotor1Forward();
  SetMotor2Forward();

  //set the motor speed to full max. 5v
  analogWrite(Motor1PowerEN, topSpeed);
  analogWrite(Motor2PowerEN, topSpeed);
  //delay(50); 
}

void MoveBackward() {
  MoveStop();
  delay(10);
  SetMotor1Backward();
  SetMotor2Backward();
    
  analogWrite(Motor1PowerEN, topSpeed);
  analogWrite(Motor2PowerEN, topSpeed);  
  //delay(50);
}

void MoveSlightTurn(int veloc1,int veloc2)
{
  SetMotor1Forward();
  SetMotor2Forward();
  analogWrite(Motor1PowerEN,veloc1);
  analogWrite(Motor2PowerEN,veloc2);
}

void blocks() {
  static int i = 0;
  int j;
  uint16_t blocks;
  char buf[32]; 
  
  // grab blocks!
  blocks = pixy.getBlocks();
  
  // If there are detect blocks, print them!
  if (blocks)
  {
    i++;
    
    // do this (print) every 50 frames because printing every
    // frame would bog down the Arduino
    if(true)//if (i%5==0)
    {
      sprintf(buf, "Detected %d:\n", blocks);
      //Serial.print(buf);
      for (j=0; j<1; j++)
      {
        sprintf(buf, "  block %d: ", j);
        //Serial.print(buf); 
        //pixy.blocks[j].print();
        /*if(pixy.blocks[i].height<71) {
          MoveForward();
        }
        else{
          MoveStop();
        }
        */
        if(pixy.blocks[0].x >= 160 && pixy.blocks[0].x <= 190)
        {
          //go straight
          MoveForward();
        }
        else if(pixy.blocks[0].x < 150)
        {
          //turn left
          MoveSlightTurn(topSpeed - 150,topSpeed);
        }
        else if(pixy.blocks[0].x > 180)
        {
          //turn right
          MoveSlightTurn(topSpeed,topSpeed - 150);
        }
        else
        {
          MoveStop();
        }
      }
    }
  }  
}

//the loop routine runs over and over again forever:
void loop() {
  //MoveForward();
  //MoveStop();
  //MoveBackward();
  //MoveStop();
  blocks();

} 