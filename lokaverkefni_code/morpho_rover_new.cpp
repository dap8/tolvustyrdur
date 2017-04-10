//motor A connected between A01 and A02
//motor B connected between B01 and B02
#define sensor_front A1 // Sharp IR GP2Y0A41SK0F (4-30cm, analog)
#define sensor_right A2 // Sharp IR GP2Y0A41SK0F (4-30cm, analog)
#define sensor_left A3 // Sharp IR GP2Y0A41SK0F (4-30cm, analog)

const int COLLISION_DISTANCE = 5; //This variables defines the distance that determines whether there is about to be a collision

const int CRUISING_SPEED = 96;
int MOTOR1_SPEED = CRUISING_SPEED;
int MOTOR2_SPEED = CRUISING_SPEED;

const boolean RIGHT = true;
const boolean LEFT = false;

//DELAYS
const int TURNING_DELAY = 200;
const int TURNING_DURATION = 350;
const int PREPARE_DELAY = 700;

//MOTOR1(LEFT) VALUES
const int MOTOR1_ID = 0; //LEFT MOTOR
const int MOTOR1_FORWARD = 0;
const int MOTOR1_BACKWARD = 1;

//MOTOR2(RIGHT) VALUES
const int MOTOR2_ID = 1; // RIGHT MOTOR
const int MOTOR2_FORWARD = 1;
const int MOTOR2_BACKWARD = 0;

//SENSOR SIDES
const int SIDE_FRONT = 0;
const int SIDE_RIGHT = 1;
const int SIDE_LEFT = 2;

//DIRECTIONS
const int DIRECTION_FORWARD = 0;
const int DIRECTION_BACKWARD = 1;


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

float* stabilize(int dist_left, int dist_right){
  
  if(dist_left > 30 || dist_left < 1) dist_left = 30;
  if(dist_right > 30 || dist_right < 1) dist_right = 30;
  float* stabilization_factors = new float[2];
  float total_dist = dist_left + dist_right;
  float left_proportion = dist_left / total_dist;
  float right_proportion = dist_right / total_dist;

  /*Serial.println("total dist: ");
  Serial.println(total_dist);
  Serial.println("right proportion: ");
  Serial.println(right_proportion);
  Serial.println("left proportion: ");
  Serial.println(left_proportion);*/
  if(dist_left > dist_right) {
    float x = (1 / left_proportion) * right_proportion;
    if(x < 0.80) x = 0.80;
    stabilization_factors[0] = x;
    stabilization_factors[1] = 1;
  } else {
    float y = (1 / right_proportion) * left_proportion;
    if(y < 0.80) y = 0.80;
    stabilization_factors[0] = 1;
    stabilization_factors[1] = y;
  }

  return stabilization_factors;
}

void loop(){
  int distance_forward = check(SIDE_FRONT);
  int distance_right = check(SIDE_RIGHT);
  int distance_left = check(SIDE_LEFT);
  
  float* stabilization_factors = stabilize(distance_left, distance_right);
  /*Serial.println("motor1 factor: ");
  Serial.println(stabilization_factors[0]);
  Serial.println("motor2 factor: ");
  Serial.println(stabilization_factors[1]);*/
  //delay(1000);
  MOTOR2_SPEED = floor(CRUISING_SPEED * stabilization_factors[0]);
  MOTOR1_SPEED = floor(CRUISING_SPEED * stabilization_factors[1]);
  
  move(0, MOTOR1_SPEED, MOTOR1_FORWARD);
  move(1, MOTOR2_SPEED, MOTOR2_FORWARD);
  //turn(RIGHT);
  delay(25);
}

float measure( int side){
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
  if(motor == MOTOR2_ID){
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

/**
* Does a left or right turn
* 
* @param {boolean} right - contains true if you are supposed to turn right, false if you are supposed to turn left
*/

void turn(boolean right){
  //Keyra áfram í einhvern x tíma
  prepareForTurn(CRUISING_SPEED);
  if(right)
  {
    delay(TURNING_DELAY);
    move(MOTOR1_ID,CRUISING_SPEED,MOTOR1_BACKWARD);
    move(MOTOR2_ID,CRUISING_SPEED,MOTOR2_FORWARD);
    delay(TURNING_DURATION);
    stop();
  }
  
  else {
    delay(TURNING_DELAY);
    move(MOTOR1_ID,CRUISING_SPEED,MOTOR1_FORWARD);
    move(MOTOR2_ID,CRUISING_SPEED,MOTOR2_BACKWARD);
    delay(TURNING_DURATION);
    stop();
  }
  delay(TURNING_DELAY);

}

void prepareForTurn(int speed){   
    move(MOTOR1_ID,speed,MOTOR1_FORWARD);
    move(MOTOR2_ID,speed,MOTOR2_FORWARD);
    delay(PREPARE_DELAY);
    stop();
}

/**
* Finds the best direction to take
* 
* @param {char} side - the side you want to check for, 'f' for front, 'r' for right, 'l' for left
* @returns {int} - the distance to an obstacle in cm
*/
/*
char determineBestDirection(int right, int front, int left)
{
  if(right >= COLLISION_DISTANCE) return aSides.RIGHT;
  if(front >= COLLISION_DISTANCE) return aSides.FRONT;
  return aSides.LEFT;
}

*/

/**
* Checks the distance to a obstacle on a given side
* 
* @param {char} side - the side you want to check for, '0' for front, '1' for right, '2' for left
* @returns {int} - the distance to an obstacle in cm
*/
int check(int side)
{
  float volts;
  switch (side) {
    case SIDE_RIGHT:
      volts = analogRead(sensor_right)*0.0048828125;
      break;
    case SIDE_FRONT:
      volts = analogRead(sensor_front)*0.0048828125;
      break;
    case SIDE_LEFT:
      volts = analogRead(sensor_left)*0.0048828125;
      break;
    default: 
      // if nothing else matches, do the default
      // default is optional
    break;
  }
    
  int distance = 13*pow(volts, -1); // distance in cm worked out from datasheet graph
  return distance;
}