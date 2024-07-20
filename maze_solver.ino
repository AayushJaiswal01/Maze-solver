
#include <QTRSensors.h>
const int buttonPin = 2;  
#define NUM_SENSORS 6     // number of sensors used
#define TIMEOUT       2500  // waits for 2500 microseconds for sensor outputs to go 0
#define EMITTER_PIN   QTR_NO_EMITTER_PIN    // emitter is controlled by digital pin 2
#define Kp .1
//#define Kd .06
//#define Ki .01
#define MaxSpeed 100
#define BaseSpeed 80
// sensors 0 through 7 are connected to digital pins 3 througwh 10, respectively
QTRSensorsRC qtrrc((unsigned char[]) {A5,A4,A3,A2,A1,A0},NUM_SENSORS, TIMEOUT, EMITTER_PIN);
unsigned int sensorValues[NUM_SENSORS];
#define leapTime 90
#define pwm1 1//pwma
#define rightMotor1 10//
#define rightMotor2 11   //
#define pwm2 3  //pwmb
#define leftMotor1  9//ina1
#define leftMotor2  6//
#define led 13
   unsigned int position = qtrrc.readLine(sensorValues);
int leftNudge;
int replaystage;
int rightNudge;
char path[100] = {};
int pathLength;
int readLength;
void setup(){

  pinMode(pwm1, OUTPUT);
  pinMode(rightMotor1, OUTPUT);
  pinMode(rightMotor2, OUTPUT);
  pinMode(pwm1,OUTPUT);
  pinMode(leftMotor1, OUTPUT);
  pinMode(leftMotor2, OUTPUT);
  pinMode(led, OUTPUT);
  Serial.begin(9600);
  analogWrite(led, 0);
    delay(500);
  pinMode(13, OUTPUT);
  analogWrite(13, HIGH);    // turn on Arduino's LED to indicate we are in calibration mode
  for (int i = 0; i < 20; i++)  // make the calibration take about 10 seconds
  {
    qtrrc.calibrate();
      analogWrite(pwm1,100);
  analogWrite(rightMotor1,80);
  analogWrite(rightMotor2, 0);
  analogWrite(pwm2,100);
  analogWrite(leftMotor1,0);
  analogWrite(leftMotor2, 80);// reads all sensors 10 times at 2500 us per read (i.e. ~25 ms per call)
  }
    for (int i = 0; i < 30; i++)  // make the calibration take about 10 seconds
  {
    qtrrc.calibrate();
      analogWrite(pwm1,100);
  analogWrite(rightMotor1,0);
  analogWrite(rightMotor2, 100);
  analogWrite(pwm2,100);
  analogWrite(leftMotor1,100);
  analogWrite(leftMotor2, 0);// reads all sensors 10 times at 2500 us per read (i.e. ~25 ms per call)
  }
    for (int i = 0; i < 18; i++)  // make the calibration take about 10 seconds
  {
    qtrrc.calibrate();
      analogWrite(pwm1,100);
  analogWrite(rightMotor1,100);
  analogWrite(rightMotor2, 0);
  analogWrite(pwm2,100);
  analogWrite(leftMotor1,0);
  analogWrite(leftMotor2, 100);// reads all sensors 10 times at 2500 us per read (i.e. ~25 ms per call)
  }
  analogWrite(13, 0);     // turn off Arduino's LED to indicate we are through with calibration
 analogWrite(leftMotor1, 0);
    analogWrite(leftMotor2, 0);
    analogWrite(rightMotor1, 0);
    analogWrite(rightMotor2, 0);

 delay(3000);

}
void loop(){
 
readSensors();
 readSensors();
if( ( sensorValues[2]>600 || sensorValues[3]>600 || sensorValues[4]>600) && sensorValues[0]<600 && sensorValues[6]<600 ){
  straight();
  readSensors();
}
else
{
  readSensors();
  turns();
}

}
 void turns(){
 if( sensorValues[0]>600 && sensorValues[6]>600 ){//to check maze is finishef or not
    if (sensorValues[3]<600)
     {     analogWrite(pwm1,120);
  analogWrite(rightMotor1,120);
  analogWrite(rightMotor2, 0);
  analogWrite(pwm2,120);
  analogWrite(leftMotor1,120);
  analogWrite(leftMotor2, 0);
  delay(10);
      turnLeft();
     }else{
     analogWrite(pwm1,120);
  analogWrite(rightMotor1,120);
  analogWrite(rightMotor2, 0);
  analogWrite(pwm2,120);
  analogWrite(leftMotor1,120);
  analogWrite(leftMotor2, 0);
    delay(leapTime);
    readSensors();
    
    if(sensorValues[0]>600 && sensorValues[6]>600 && sensorValues[3]>600){
      done();
    }
    if(sensorValues[0]<600 && sensorValues[6]<600){ 
      turnLeft();
    }
     }
  }
  
  
 /*if(  sensorValues[0]<600 && sensorValues[6]<600 && sensorValues[3]>600 ){//to check maze is finishef or not
     analogWrite(pwm1,120);
  analogWrite(rightMotor1,120);
  analogWrite(rightMotor2, 0);
  analogWrite(pwm2,120);
  analogWrite(leftMotor1,120);
  analogWrite(leftMotor2, 0);
    delay(40);
      turnTleft();
    
  }
  */
  if(sensorValues[0]>600 && sensorValues[3]>600){ // if you can turn left then turn left
         analogWrite(pwm1,120);
  analogWrite(rightMotor1,120);
  analogWrite(rightMotor2, 0);
  analogWrite(pwm2,120);
  analogWrite(leftMotor1,120);
  analogWrite(leftMotor2, 0);
    delay(leapTime);
    readSensors();
      
      if(sensorValues[0]<600 ){
        turnLeft();
      }
     /* else{
        done();
      }
*/  }
     if(sensorValues[0]>600 &&sensorValues[3]<600 && sensorValues[2]<600 && sensorValues[5]<600 ){//135 left
      {
        analogWrite(pwm1,120);
        analogWrite(rightMotor1,120);
        analogWrite(rightMotor2, 0);
        analogWrite(pwm2,120);
        analogWrite(leftMotor1,120);
        analogWrite(leftMotor2, 0);  
        delay(40);
        turnSmallLeft();
      }
      
    }
  if(sensorValues[6]>600  && sensorValues[0]<600){//right
     analogWrite(pwm1,120);
  analogWrite(rightMotor1,120);
  analogWrite(rightMotor2, 0);
  analogWrite(pwm2,120);
  analogWrite(leftMotor1,120);
  analogWrite(leftMotor2, 0);
    delay(40);
    readSensors();
   
    if(sensorValues[0]>600 && sensorValues[3]>600  ){//left
      delay(leapTime-40);
      readSensors();
      if(sensorValues[6]>600 &&sensorValues[3]>600 && sensorValues[0]>600){
        done();
      }
     
      else{
        turnLeft();
        return;
      }
    }
    if (sensorValues[6]>600 &&sensorValues[5]>600 && sensorValues[3]>600 && sensorValues[2]<600 && sensorValues[1]<600 && sensorValues[0]<600 )
    {
      turnRight();
      return;
    }
    delay(leapTime-30);
    readSensors();
    if(sensorValues[6]<600 &&
      sensorValues[3]<600 && sensorValues[5]<600){
      turnRight();
      return;
    }
    path[pathLength]='S';
    Serial.println("s");
    pathLength++;
    Serial.print("Path length: ");
    Serial.println(pathLength);
    if(path[pathLength-2]=='B'){
    Serial.println("shortening path");
    shortPath();
     }
    straight();
  }
  readSensors();
  if(sensorValues[0]<600 && sensorValues[2]<600 && sensorValues[3]<600 
    && sensorValues[6]<600 && sensorValues[1]<600 && sensorValues[4]<600 && sensorValues[5]<600)
    {
     analogWrite(pwm1,120);
     analogWrite(rightMotor1,120);
     analogWrite(rightMotor2, 0);
     analogWrite(pwm2,120);
     analogWrite(leftMotor1,0);
     analogWrite(leftMotor2, 120);
     delay(100);
        if (sensorValues[0]>600 || sensorValues[1]>600|| sensorValues[2]>600)
        {
          turnLeft();  
        }
        else
        {
         turnAround();
        }
  }
  
 

}

void readSensors(){
  
   unsigned int  line_position = qtrrc.readLine(sensorValues); 

}



void done(){
  analogWrite(leftMotor1, 0);
    analogWrite(leftMotor2, 0);
    analogWrite(rightMotor1, 0);
    analogWrite(rightMotor2, 0);
  replaystage=1;
  path[pathLength]='D';
  pathLength++;
 while(sensorValues[0]<600){
   analogWrite(led, HIGH);
   
    readSensors();
  
 }
 

delay(5000);
replay();
}

void turnTleft()
{ 
while(sensorValues[2]>600 ||sensorValues[4]>600){
  analogWrite(pwm1,120);
  analogWrite(rightMotor1,0);
  analogWrite(rightMotor2, 120);
  analogWrite(pwm2,120);
  analogWrite(leftMotor1,120);
  analogWrite(leftMotor2, 0);

    delay(2);
     analogWrite(leftMotor1, 0);
    analogWrite(leftMotor2, 0);
    analogWrite(rightMotor1, 0);
    analogWrite(rightMotor2, 0);
    delay(2);
    readSensors();
  }
    
  while(sensorValues[4]<600 ) {
   analogWrite(pwm1,120);
  analogWrite(rightMotor1,0);
  analogWrite(rightMotor2, 120);
  analogWrite(pwm2,120);
  analogWrite(leftMotor1,120);
  analogWrite(leftMotor2, 0);

    delay(2);
    analogWrite(leftMotor1, 0);
    analogWrite(leftMotor2, 0);
    analogWrite(rightMotor1, 0);
    analogWrite(rightMotor2, 0);
    delay(2);
    readSensors();
  
  }
  
  
  if(replaystage==0){
    path[pathLength]='t';
    Serial.println("t");
    pathLength++;
    Serial.print("Path length: ");
    Serial.println(pathLength);
      
  }
}
void turnSmallLeft()
{ 
while(sensorValues[2]>600 ||sensorValues[4]>600){
  analogWrite(pwm1,120);
  analogWrite(rightMotor1,0);
  analogWrite(rightMotor2, 120);
  analogWrite(pwm2,120);
  analogWrite(leftMotor1,120);
  analogWrite(leftMotor2, 0);

    delay(2);
     analogWrite(leftMotor1, 0);
    analogWrite(leftMotor2, 0);
    analogWrite(rightMotor1, 0);
    analogWrite(rightMotor2, 0);
    delay(1);
    readSensors();
  }
    
  while(sensorValues[4]<600 ) {
   analogWrite(pwm1,120);
  analogWrite(rightMotor1,0);
  analogWrite(rightMotor2, 120);
  analogWrite(pwm2,120);
  analogWrite(leftMotor1,120);
  analogWrite(leftMotor2, 0);

    delay(2);
    analogWrite(leftMotor1, 0);
    analogWrite(leftMotor2, 0);
    analogWrite(rightMotor1, 0);
    analogWrite(rightMotor2, 0);
    delay(1);
    readSensors();
  
  }
  
  
  if(replaystage==0){
    path[pathLength]='m';
    Serial.println("m");
    pathLength++;
    Serial.print("Path length: ");
    Serial.println(pathLength);
      
  }

    
  
}
void turnLeft()
{ 
while(sensorValues[2]>600 ||sensorValues[4]>600){
  analogWrite(pwm1,120);
  analogWrite(rightMotor1,0);
  analogWrite(rightMotor2, 120);
  analogWrite(pwm2,120);
  analogWrite(leftMotor1,120);
  analogWrite(leftMotor2, 0);

    delay(2);
     analogWrite(leftMotor1, 0);
    analogWrite(leftMotor2, 0);
    analogWrite(rightMotor1, 0);
    analogWrite(rightMotor2, 0);
    delay(1);
    readSensors();
  }
    
  while(sensorValues[4]<600 ) {
   analogWrite(pwm1,120);
  analogWrite(rightMotor1,0);
  analogWrite(rightMotor2, 120);
  analogWrite(pwm2,120);
  analogWrite(leftMotor1,120);
  analogWrite(leftMotor2, 0);

    delay(2);
    analogWrite(leftMotor1, 0);
    analogWrite(leftMotor2, 0);
    analogWrite(rightMotor1, 0);
    analogWrite(rightMotor2, 0);
    delay(1);
    readSensors();
  
  }
  
 

    
  if(replaystage==0){
    path[pathLength]='L';
    Serial.println("l");
    pathLength++;
    Serial.print("Path length: ");
    Serial.println(pathLength);
      if(path[pathLength-2]=='B'){
    Serial.println("shortening path");
        shortPath();
      }
  }
}

void turnRight(){

    
while(sensorValues[4]>600){
  analogWrite(pwm1,120);
  analogWrite(rightMotor1,120);
  analogWrite(rightMotor2, 0);
  analogWrite(pwm2,120);
  analogWrite(leftMotor1,0);
  analogWrite(leftMotor2, 120);
    delay(2);
     analogWrite(leftMotor1, 0);
    analogWrite(leftMotor2, 0);
    analogWrite(rightMotor1, 0);
    analogWrite(rightMotor2, 0);
    delay(1);
    readSensors();
  }
   while(sensorValues[4]<600){
       analogWrite(pwm1,120);
  analogWrite(rightMotor1,120);
  analogWrite(rightMotor2, 0);
  analogWrite(pwm2,120);
  analogWrite(leftMotor1,0);
  analogWrite(leftMotor2, 120);
    delay(2);
     analogWrite(leftMotor1, 0);
    analogWrite(leftMotor2, 0);
    analogWrite(rightMotor1, 0);
    analogWrite(rightMotor2, 0);
    delay(1);
    readSensors();
  }
   while(sensorValues[2]<600){
  analogWrite(pwm1,120);
  analogWrite(rightMotor1,120);
  analogWrite(rightMotor2, 0);
  analogWrite(pwm2,120);
  analogWrite(leftMotor1,0);
  analogWrite(leftMotor2, 120);
    delay(2);
    analogWrite(leftMotor1, 0);
    analogWrite(leftMotor2, 0);
    analogWrite(rightMotor1, 0);
    analogWrite(rightMotor2, 0);
    delay(1);
    readSensors();
  }
  if(replaystage==0){
  path[pathLength]='R';
  Serial.println("r");
  pathLength++;
  Serial.print("Path length: ");
  Serial.println(pathLength);
    if(path[pathLength-2]=='B'){
      Serial.println("shortening path");
      shortPath();
    }
  }
 
}

void turnSmallRight(){

    
while(sensorValues[4]>600){
  analogWrite(pwm1,120);
  analogWrite(rightMotor1,120);
  analogWrite(rightMotor2, 0);
  analogWrite(pwm2,120);
  analogWrite(leftMotor1,0);
  analogWrite(leftMotor2, 120);
    delay(2);
     analogWrite(leftMotor1, 0);
    analogWrite(leftMotor2, 0);
    analogWrite(rightMotor1, 0);
    analogWrite(rightMotor2, 0);
    delay(1);
    readSensors();
  }
   while(sensorValues[4]<600){
       analogWrite(pwm1,120);
  analogWrite(rightMotor1,120);
  analogWrite(rightMotor2, 0);
  analogWrite(pwm2,120);
  analogWrite(leftMotor1,0);
  analogWrite(leftMotor2, 120);
    delay(2);
     analogWrite(leftMotor1, 0);
    analogWrite(leftMotor2, 0);
    analogWrite(rightMotor1, 0);
    analogWrite(rightMotor2, 0);
    delay(1);
    readSensors();
  }
   while(sensorValues[2]<600){
  analogWrite(pwm1,120);
  analogWrite(rightMotor1,120);
  analogWrite(rightMotor2, 0);
  analogWrite(pwm2,120);
  analogWrite(leftMotor1,0);
  analogWrite(leftMotor2, 120);
    delay(2);
    analogWrite(leftMotor1, 0);
    analogWrite(leftMotor2, 0);
    analogWrite(rightMotor1, 0);
    analogWrite(rightMotor2, 0);
    delay(1);
    readSensors();
  }
  if(replaystage==0){
  path[pathLength]='q';
  Serial.println("q");
  pathLength++;
  Serial.print("Path length: ");
  Serial.println(pathLength);
    
  }
 
}
void straight(){
                                                                                                                                                                                                                                                                                             
    int lastError = 0;
    int line_position = qtrrc.readLine(sensorValues);
    int error = line_position - 2500;
    //int error1 = error - lastError;
    //int error2 = (2.0 / 3.0) * error2 + error ;
    int motorSpeed = Kp * error;// + Kd * error1 + Ki * error2;
    int rightMotorSpeed = BaseSpeed - motorSpeed;
    int leftMotorSpeed = BaseSpeed + motorSpeed;
    if (rightMotorSpeed > MaxSpeed ) rightMotorSpeed = MaxSpeed; // prevent the motor from going beyond max speed
    if (leftMotorSpeed > MaxSpeed ) leftMotorSpeed = MaxSpeed; // prevent the motor from going beyond max speed
    if (rightMotorSpeed < 0)rightMotorSpeed = 0;
    if (leftMotorSpeed < 0)leftMotorSpeed = 0;
    analogWrite(pwm1, rightMotorSpeed);
    analogWrite(pwm2, leftMotorSpeed);
    analogWrite(rightMotor1,rightMotorSpeed);
    analogWrite(rightMotor2, 0);
    analogWrite(leftMotor1,leftMotorSpeed);
    analogWrite(leftMotor2, 0); 

    lastError = error;
  
    qtrrc.readLine(sensorValues);
  
  
 
}
void turnAround(){
  analogWrite(pwm1,140);
  analogWrite(rightMotor1,140);
  analogWrite(rightMotor2, 0);
  analogWrite(pwm2,140);
  analogWrite(leftMotor1,140);
  analogWrite(leftMotor2, 0);
    delay(50);
   while(sensorValues[4]<600){
      analogWrite(pwm1,160);
  analogWrite(rightMotor1,0);
  analogWrite(rightMotor2,140);
  analogWrite(pwm2,140);
  analogWrite(leftMotor1,140);
  analogWrite(leftMotor2, 0);
    delay(2);
     analogWrite(leftMotor1, 0);
    analogWrite(leftMotor2, 0);
    analogWrite(rightMotor1, 0);
    analogWrite(rightMotor2, 0);
    delay(1);
    readSensors();
  }
   /*while(ir_reading <200){
      analogWrite(pwm1,160);
  analogWrite(rightMotor1,0);
  analogWrite(rightMotor2,HIGH);
  analogWrite(pwm2,160);
  analogWrite(leftMotor1,HIGH);
  analogWrite(leftMotor2, 0);
    delay(2);
     analogWrite(leftMotor1, 0);
    analogWrite(leftMotor2, 0);
    analogWrite(rightMotor1, 0);
    analogWrite(rightMotor2, 0);
    delay(1);
    readSensors();
  }*/
  path[pathLength]='B';
  pathLength++;
  straight();
  Serial.println("b");
  Serial.print("Path length: ");
  Serial.println(pathLength);
}
void turnOAround(){
     analogWrite(pwm1,50);
  analogWrite(rightMotor1,50);
  analogWrite(rightMotor2,0);
  analogWrite(pwm2,50);
  analogWrite(leftMotor1,50);
  analogWrite(leftMotor2, 0);
   while(sensorValues[3]<600){
      analogWrite(pwm1,160);
  analogWrite(rightMotor1,0);
  analogWrite(rightMotor2,160);
  analogWrite(pwm2,140);
  analogWrite(leftMotor1,160);
  analogWrite(leftMotor2, 0);
    delay(2);
     analogWrite(leftMotor1, 0);
    analogWrite(leftMotor2, 0);
    analogWrite(rightMotor1, 0);
    analogWrite(rightMotor2, 0);
    delay(1);
    readSensors();
   }
   /*while(ir_reading <200){
      analogWrite(pwm1,160);
  analogWrite(rightMotor1,0);
  analogWrite(rightMotor2,160);
  analogWrite(pwm2,160);
  analogWrite(leftMotor1,160);
  analogWrite(leftMotor2, 0);
    delay(2);
     analogWrite(leftMotor1, 0);
    analogWrite(leftMotor2, 0);
    analogWrite(rightMotor1, 0);
    analogWrite(rightMotor2, 0);
    delay(1);
    readSensors();
  }*/
  path[pathLength]='B';
  pathLength++;
  straight();
  Serial.println("b");
  Serial.print("Path length: ");
  Serial.println(pathLength);
}

void shortPath(){
 int shortDone=0;
  if(path[pathLength-3]=='L' && path[pathLength-1]=='R'  ){
    pathLength-=3;
    path[pathLength]='B';
  Serial.println("test1");
    shortDone=1;
  }
   
  if(path[pathLength-3]=='L' && path[pathLength-1]=='S'  && shortDone==0){
    pathLength-=3;
    path[pathLength]='R';
  Serial.println("test2");
    shortDone=1;
  }
   
  if(path[pathLength-3]=='R' && path[pathLength-1]=='L'  && shortDone==0){
    pathLength-=3;
    path[pathLength]='B';
  Serial.println("test3");
    shortDone=1;
  }
  
   
  if(path[pathLength-3]=='S' && path[pathLength-1]=='L'&& shortDone==0){
    pathLength-=3;
    path[pathLength]='R';
  Serial.println("test4");
    shortDone=1;
  }
     
  if(path[pathLength-3]=='S' && path[pathLength-1]=='S'   &&shortDone==0){
    pathLength-=3;
    path[pathLength]='B';
  Serial.println("test5");
    shortDone=1;
  }
    if(path[pathLength-3]=='L' && path[pathLength-1]=='L' && shortDone==0){
    pathLength-=3;
    path[pathLength]='S';
  Serial.println("test6");
    shortDone=1;
  }
  
  path[pathLength+1]='D';
  path[pathLength+2]='D';
  pathLength++;
  Serial.print("Path length: ");
  Serial.println(pathLength);
  printPath();
}




void printPath(){
  Serial.println("+++++++++++++++++");
  int x;
  while(x<=pathLength){
  Serial.println(path[x]);
  x++;
  }
  Serial.println("+++++++++++++++++");
}


void replay(){
   readSensors();
 if(sensorValues[0]>600 &&sensorValues[6]>600){
    straight();
  }
      
 
  else{
    if(path[readLength]=='D'){
      analogWrite(pwm1,200);
       analogWrite(leftMotor1, 200);
    analogWrite(leftMotor2, 0);
     analogWrite(pwm2,200);
    analogWrite(rightMotor1, 200);
  analogWrite(rightMotor2, 0);
    delay(80);
    analogWrite(leftMotor1, 0);
    analogWrite(leftMotor2, 0);
    analogWrite(rightMotor1, 0);
    analogWrite(rightMotor2, 0);
      endMotion();
    }

 
    if(path[readLength]=='L'){
      if(sensorValues[3]<600)
      {   
     analogWrite(pwm1,120);
     analogWrite(rightMotor1,120);
     analogWrite(rightMotor2, 0);
     analogWrite(pwm2,120);
     analogWrite(leftMotor1,120);
     analogWrite(leftMotor2, 0);
     delay(10);
  turnLeft();
      }
      else{
       analogWrite(pwm1,120);
     analogWrite(leftMotor1,120);
     analogWrite(leftMotor2, 0);
      analogWrite(pwm2,120);
    analogWrite(rightMotor1, 120);
    analogWrite(rightMotor2,0);
    delay(leapTime);
      turnLeft();
      }
    }
    if(path[readLength]=='R'){
             analogWrite(pwm1,120);
     analogWrite(leftMotor1,120);
     analogWrite(leftMotor2, 0);
      analogWrite(pwm2,120);
    analogWrite(rightMotor1, 120);
    analogWrite(rightMotor2,0);
    delay(30);
    if(sensorValues[6]>600 && sensorValues[3]<600 && sensorValues[2]<600 && sensorValues[1]<600)
    {
      turnRight();
    }
    else{
      delay(leapTime-30);
    turnRight();
    }
    }
    if(path[readLength]=='S'){
           analogWrite(pwm1,200);
     analogWrite(leftMotor1,200);
     analogWrite(leftMotor2, 0);
      analogWrite(pwm2,200);
    analogWrite(rightMotor1, 200);
    analogWrite(rightMotor2,0);
    delay(leapTime);
    straight();
    }
 
    if(path[readLength]=='m'){
           analogWrite(pwm1,120);
     analogWrite(leftMotor1,120);
     analogWrite(leftMotor2, 0);
      analogWrite(pwm2,120);
    analogWrite(rightMotor1, 120);
    analogWrite(rightMotor2,0);
    delay(50);
    turnSmallLeft();
    }
    
    if(path[readLength]=='q'){
           analogWrite(pwm1,120);
     analogWrite(leftMotor1,120);
     analogWrite(leftMotor2, 0);
      analogWrite(pwm2,120);
    analogWrite(rightMotor1, 120);
    analogWrite(rightMotor2,0);
    delay(50);
    turnSmallRight();
    }
    
        if(path[readLength]=='t'){
           analogWrite(pwm1,120);
     analogWrite(leftMotor1,120);
     analogWrite(leftMotor2, 0);
      analogWrite(pwm2,120);
    analogWrite(rightMotor1, 120);
    analogWrite(rightMotor2,0);
    delay(30);
    turnTleft();
    }

  
    
    readLength++;
  }
    
  replay();

}

void endMotion(){
    analogWrite(led, 0);
    delay(500);
    analogWrite(led, HIGH);
    delay(200);
      analogWrite(led, 0);
    delay(200);
    analogWrite(led, HIGH);
    delay(500);
  endMotion();
}
