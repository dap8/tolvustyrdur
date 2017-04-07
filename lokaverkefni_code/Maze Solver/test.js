
// Canvas.
let canvas = document.getElementById("canvas");
let ctx = canvas.getContext("2d");

////////////////// Car stuff //////////////////////

function Car(x, y, rot, name){
	this.NAME = name;
	this.X = x;
	this.Y = y;
	this.ROT = rot;
  this.MOTOR_1_SPEED = 0;
  this.MOTOR_2_SPEED = 0;
  this.MOTOR_1_DIRECTION = 1; // 1 or -1
  this.MOTOR_2_DIRECTION = 1; // 1 or -1
	this.init();
}

let Direction = {
	FORWARD : 'F',
	RIGHT: 'R',
	LEFT: 'L'
}

Car.prototype.init = function() {
	console.log(this.name + " ready to go!");
	this.SharpSensor_1 = new SharpSensor(Direction.FORWARD);
	this.SharpSensor_2 = new SharpSensor(Direction.RIGHT);
	this.SharpSensor_3 = new SharpSensor(Direction.LEFT);
  this.GyroSensor = new GyroSensor();
}

Car.prototype.move = function() {
	console.log(this.name + "on the move!");
}

Car.prototype.setRotation = function() {
	
}

Car.prototype.setPosition = function() {

}

Car.prototype.update = function() {
	this.checkSensors();
  this.runMotors();
  this.move();
}

Car.prototype.checkSensors = function() {
  
}

Car.prototype.render = function(ctx) {
	// RENDER CAR //
  ctx.rect(20,20,150,100);
	ctx.stroke();
}

/////////////////////////////////////////////////

/////////////// Sharp sensor stuff ////////////////////

function SharpSensor(direction){
	this.init();
	this.direction = direction;
}

SharpSensor.prototype.init = function() {
	console.log("Sharp sensor started");
}

SharpSensor.prototype.check = function() {
	let obstacles = Maze.walls;
	switch(expression) {
	    case Direction.RIGHT:
	        
	        break;
	    case Direction.LEFT:
	        
	        break;
	    case Direction.FORWARD:
	    default:
	        console.log('invalid direction');
	}
	
}

SharpSensor.prototype.setPosition = function() {
	
}

SharpSensor.prototype.setRotation = function() {
	
}



/////////////////////////////////////////////////

//////////////// Gyro sensor stuff //////////////

function GyroSensor(direction){
	this.init();
}

GyroSensor.prototype.init = function() {
	console.log("Gyro sensor started!");
}

GyroSensor.prototype.check = function() {
	
}

GyroSensor.prototype.setPosition = function() {
	
}

GyroSensor.prototype.setRotation = function() {
	
}

/////////////////////////////////////////////////

/////////////// Wall stuff //////////////////////

function Wall(x1, y1, x2, y2) {
  this.x1 = x1;
  this.y1 = y1;
  this.x2 = x2;
	this.y2 = y2;  

}

Wall.prototype.render = function(ctx) {
	// RENDER WALL //
}


function Maze(walls) {
	this.walls = walls;
}



let walls = [new Wall(20,20,20,30), new Wall(10,10,10,30)];


let maze = new Maze(walls);
let car_1 = new Car(1,2,3,"Pétur Ofurbíll");

car_1.move();