//motor A connected between A01 and A02
//motor B connected between B01 and B02
#define sensor_front A1 // Sharp IR GP2Y0A41SK0F (4-30cm, analog)
#define sensor_right A2 // Sharp IR GP2Y0A41SK0F (4-30cm, analog)
#define sensor_left A3 // Sharp IR GP2Y0A41SK0F (4-30cm, analog)

const int COLLISION_DISTANCE = 5; //This variables defines the distance that determines whether there is about to be a collision

const int MOTOR1_ID = 0;
const int MOTOR2_ID = 1;

struct directions
{
   char FORWARD = 'f';
   char RIGHT = 'r';
   char LEFT = 'l';
};

typedef struct directions DIRECTIONS;
DIRECTIONS aDirections;

const char CURRENT_DIRECTION = Direction.FORWARD;

struct motor1 
{
    int FORWARD = 0;
    int BACKWARD = 1;
    
}

typedef struct motor1 MOTOR1;
  
struct MOTOR2 
{
    int FORWARD = 1;
    int BACKWARD = 0;
    
}

typedef struct motor2 MOTOR2;

MOTOR1 aMotor1;
MOTOR2 aMotor2;


int STBY = 10; //standby

//Motor A
int PWMA = 3; //Speed control 
int AIN1 = 9; //Direction
int AIN2 = 8; //Direction

//Motor B
int PWMB = 5; //Speed control
int BIN1 = 11; //Direction
int BIN2 = 12; //Direction

void setup(){
  pinMode(STBY, OUTPUT);

  pinMode(PWMA, OUTPUT);
  pinMode(AIN1, OUTPUT);
  pinMode(AIN2, OUTPUT);

  pinMode(PWMB, OUTPUT);
  pinMode(BIN1, OUTPUT);
  pinMode(BIN2, OUTPUT);

    Serial.begin(9600); // start the serial port
}

void loop(){
  float volts = analogRead(sensor)*0.0048828125;  // value from sensor * (5/1024)
  int distance = 13*pow(volts, -1); // worked out from datasheet graph
  // int distance = check(aDirections.FORWARD);
  float volts2 = analogRead(sensor2)*0.0048828125;  // value from sensor * (5/1024)
  int distance2 = 13*pow(volts2, -1); // worked out from datasheet graph
  // int distance = check(aDirections.RIGHT);
  float volts3 = analogRead(sensor3)*0.0048828125;  // value from sensor * (5/1024)
  int distance3 = 13*pow(volts3, -1); // worked out from datasheet graph
  // int distance = check(aDirections.LEFT);

  if (distance2 > 10){
    move(0,128,0);
    move(1,128,1);
    delay(200);
    stop();
    delay(500);
    move(0,128,1);
    move(1,128,1);
    delay(350);
    stop();
  }

  move(0,128,0);
  move(1,128,1);
  delay(350);
  stop();
  delay(1000);
  
  
}


void move(int motor, int speed, int direction){
//Move specific motor at speed and direction
//motor: 0 for B 1 for A
//speed: 0 is off, and 255 is full speed
//direction: 0 clockwise, 1 counter-clockwise

  digitalWrite(STBY, HIGH); //disable standby

  boolean inPin1 = LOW;
  boolean inPin2 = HIGH;

  if(direction == 1){
    inPin1 = HIGH;
    inPin2 = LOW;
  }

  if(motor == 1){
    digitalWrite(AIN1, inPin1);
    digitalWrite(AIN2, inPin2);
    analogWrite(PWMA, speed);
  }else{
    digitalWrite(BIN1, inPin1);
    digitalWrite(BIN2, inPin2);
    analogWrite(PWMB, speed);
  }
}

void stop(){
//enable standby  
  digitalWrite(STBY, LOW); 
}


void chooseDirection()
{
  int rightDist = check(aDirections.RIGHT);
  int frontDist = check(aDirections.FRONT);
  int leftDist = check(aDirections.LEFT);

  //char choice = determineBestDirection(rightDist,frontDist,leftDist);  
}

/**
* Finds the best direction to take
* 
* @param {char} side - the side you want to check for, 'f' for front, 'r' for right, 'l' for left
* @returns {int} - the distance to an obstacle in cm
*/

char determineBestDirection(int right, int front, int left)
{
  if(right >= COLLISION_DISTANCE) return aDirections.RIGHT;
  if(front >= COLLISION_DISTANCE) return aDirections.FRONT;
  return aDirections.LEFT;
}

/*
void move(char direction)
{
    switch (direction) {
    case Directions.RIGHT:
      //Do a 90 degree turn to the right and then move forward x cm
      break;
    case Directions.FRONT:
      //Move forward x cm
      break;
    case Directions.LEFT:
      //Do a 90 degree turn to the left and then move forward x cm
      break;
    default: 
      // if nothing else matches, do the default
      // default is optional
    break;
  }
  
}

*/

/**
* Checks the distance to a obstacle on a given side
* 
* @param {char} side - the side you want to check for, 'f' for front, 'r' for right, 'l' for left
* @returns {int} - the distance to an obstacle in cm
*/
int check(char side)
{
  switch (side) {
    case aDirections.RIGHT:
      float volts = analogRead(sensor_right)*0.0048828125;
      break;
    case aDirections.FRONT:
      float volts = analogRead(sensor_front)*0.0048828125;
      break;
    case aDirections.LEFT:
      float volts = analogRead(sensor_left)*0.0048828125;
      break;
    default: 
      // if nothing else matches, do the default
      // default is optional
    break;
  }
    
  int distance = 13*pow(volts, -1); // distance in cm worked out from datasheet graph
  return distance;
}