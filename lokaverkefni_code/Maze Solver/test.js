
// Canvas.
<<<<<<< .mine
let canvas = document.getElementById("canvas");
let ctx = canvas.getContext("2d");
var simulation_paused = false;
||||||| .r17
var ctx = document.getElementById("canvas");
=======
let canvas = document.getElementById("canvas");
let ctx = canvas.getContext("2d");
>>>>>>> .r19

// Add an onClick listener to the canvas to be able to pause the game
canvas.addEventListener("click", (e) => {simulation_paused = !simulation_paused});


/////////////////// Game engine stuff ///////////////////

function Simulation(fps) {
  	this.delay = 1000 / fps;
  	this.maze = null;
  	this.cars = [];
}

Simulation.prototype.init = function() {
	// Add one car to the game
	this.cars.push(new Car(400,400,0,"Pétur Ofurbíll"));
	this.iterate = this.iterate.bind(this);

	// Start the game engine
  	setInterval(this.iterate, this.delay);
}

Simulation.prototype.iterate = function() {
	this.update();
	this.render(ctx);
}

Simulation.prototype.update = function() {
	if(simulation_paused) return;

  	for(car of this.cars){
  		car.update();
  	}
}

Simulation.prototype.render = function(ctx) {
	if(simulation_paused) return;

 	// Render all the cars
  	for(car of this.cars){
  		car.render(ctx);
  	}

  	// Render the maze
  	//this.maze.render(ctx);

  	// Fill and draw everything
  	ctx.stroke();
}

///////////////////////////////////////////////////

////////////////// Car stuff //////////////////////

function Car(x, y, rot, name){
	this.NAME = name;
  	this.width = 40;
  	this.height = 40;
  	this.fillColor = "red";
  	this.outlineColor = "black";
	this.name = name;
	this.x = x;
	this.y = y;
	this.rot = rot;
  	this.MOTOR_1_SPEED = 0;
  	this.MOTOR_2_SPEED = 0;
  	this.MOTOR_1_DIRECTION = 1; // 1 or -1
  	this.MOTOR_2_DIRECTION = 1; // 1 or -1
	this.init();
}

let Direction = {
	FORWARD : 'F',
	RIGHT: 'R',
	LEFT: 'L',
	BACKWARD: 'B'
}

Car.prototype.init = function() {
	console.log(this.name + " ready to go!");
	this.SharpSensor_1 = new SharpSensor(Direction.FORWARD, this.rot);
	this.SharpSensor_2 = new SharpSensor(Direction.RIGHT, this.rot);
	this.SharpSensor_3 = new SharpSensor(Direction.LEFT, this.rot);
  	this.GyroSensor = new GyroSensor();
}

Car.prototype.move = function() {

}

Car.prototype.setRotation = function() {
	
}

Car.prototype.setPosition = function() {

}

Car.prototype.update = function() {
	this.checkSensors();
  	//this.runMotors();
  	this.move();
}

Car.prototype.checkSensors = function() {
  
}

Car.prototype.render = function(ctx) {
	// RENDER CAR //
	ctx.fillStyle = this.fillColor;
  	ctx.fillRect(this.x - this.width/2, this.y - this.width/2, this.width, this.height);
  	ctx.moveTo(this.x, this.y);
  	ctx.lineTo(this.x, this.y - this.height/2);
}

///////////////////////////////////////////////////

//////////////// Motor stuff //////////////////////

function Motor() {
	this.init();
}

Motor.prototype.init = function() {
	console.log("Motor started!");
}

Motor.prototype.power = function(speed, direction) {
	
}

Motor.prototype.setSpeed = function(speed) {
	this.speed = speed;
}

Motor.prototype.setDirection = function(direction) {
	this.direction = direction;
}

/////////////////////////////////////////////////

/////////////// Sharp sensor stuff ////////////////////

function SharpSensor(direction,rotation, x, y){
	this.init();
	this.direction = direction;
	this.rotation = rotation;
	this.x = x;
	this.y = y;
}

SharpSensor.prototype.init = function() {
	console.log("Sharp sensor started");
}

SharpSensor.prototype.check = function() {
	let obstacles = Maze.walls;
	
	switch(expression) {
	    case Direction.RIGHT:
	        for(let i = 0; i<obstacles.length; i++)
	        {

	        }
	        break;
	    case Direction.LEFT:
	        
	        break;
	    case Direction.FORWARD:
	    default:
	        console.log('invalid direction');
	}
	
}

SharpSensor.prototype.findDistance() {

	let amInsideWall;
	
}

SharpSensor.prototype.update() {

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

/////////////////////////////////////////////////

///////////// Start the simulation //////////////

function Maze(walls) {
	this.walls = walls;
}

let mSimulation = new Simulation(60);
mSimulation.init();

let walls = [new Wall(20,20,20,30), new Wall(10,10,10,30)];
let maze = new Maze(walls);
