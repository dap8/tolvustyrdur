/*
 * Sensor variables
 * 
 */

#define sensor_front A0 // Sharp IR GP2Y0A41SK0F (4-30cm, analog)
//#define sensor_right A1 // Sharp IR GP2Y0A41SK0F (4-30cm, analog)
//#define sensor_left A2 // Sharp IR GP2Y0A41SK0F (4-30cm, analog)

const int COLLISION_DISTANCE = 5; //This variables defines the distance that 



struct directions
{
   char FORWARD = 'f';
   char RIGHT = 'r';
   char LEFT = 'l';
};

typedef struct directions Directions;

const char CURRENT_DIRECTION = Direction.FORWARD;

/*
 * Motor variables
 */

 //motor A connected between A01 and A02
//motor B connected between B01 and B02

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
}

void loop(){
  move(1, 255, 1); //motor 1, full speed, left
  move(2, 255, 1); //motor 2, full speed, left

  delay(1000); //go for 1 second
  stop(); //stop
  delay(250); //hold for 250ms until move again

  move(1, 128, 0); //motor 1, half speed, right
  move(2, 128, 0); //motor 2, half speed, right

  delay(1000);
  stop();
  delay(250);
}

/*
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
*/
void chooseDirection()
{
  int rightDist = check(Directions.RIGHT);
  int frontDist = check(Directions.FRONT);
  int leftDist = check(Directions.LEFT);

  char choice = determineBestDirection(rightDist,frontDist,leftDist);  
}

/**
* Finds the best direction to take
* 
* @param {char} side - the side you want to check for, 'f' for front, 'r' for right, 'l' for left
* @returns {int} - the distance to an obstacle in cm
*/

char determineBestDirection(int right, int front, int left)
{
  if(right >= COLLISION_DISTANCE) return Directions.RIGHT;
  if(front >= COLLISION_DISTANCE) return Directions.FRONT;
  return Direction.LEFT;  
}


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

/**
* Checks the distance to a obstacle on a given side
* 
* @param {char} side - the side you want to check for, 'f' for front, 'r' for right, 'l' for left
* @returns {int} - the distance to an obstacle in cm
*/
int check(char side)
{
  switch (side) {
    case Directions.RIGHT:
      float volts = analogRead(sensor_right)*0.0048828125;
      break;
    case Directions.FRONT:
      float volts = analogRead(sensor_front)*0.0048828125;
      break;
    case Directions.LEFT:
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

void stop(){
//enable standby  
  digitalWrite(STBY, LOW); 
}