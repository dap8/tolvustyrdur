
// Canvas.
let canvas = document.getElementById("canvas");
let ctx = canvas.getContext("2d");
var simulation_paused = false;

let mouse = {
	isDown: false,
	x: 0,
	y: 0,
	last_x: 0,
	last_y: 0,
}

// Add some listeners
canvas.addEventListener("mousedown", (e) => {
	mouse.isDown = true;
	grabWall(mouse.x, mouse.y);
});

canvas.addEventListener("mousemove", (e) => {
	let rect = canvas.getBoundingClientRect();
	mouse.last_x = mouse.x;
	mouse.last_y = mouse.y;
	mouse.x = e.clientX - rect.left;
	mouse.y = e.clientY - rect.top;
	if(!mouse.isDown || mSimulation.grabbedWall == null) return;
	let x_movement = mouse.x - mouse.last_x;
	let y_movement = mouse.y - mouse.last_y;
	mSimulation.grabbedWall.move(x_movement, y_movement);
});

canvas.addEventListener("mouseup", (e) => {
	mouse.isDown = false;
	mSimulation.grabbedWall = null;
});

window.addEventListener("keypress", (e) => {
	switch(e.keyCode){
		case 112: // P
			simulation_paused = !simulation_paused
			console.log("Simulation_paused: " + simulation_paused);
	}
}, false);
	
/////////////////// Game engine stuff ///////////////////

function Simulation(fps) {
  	this.delay = 1000 / fps;
  	this.walls = [new Wall(100,100,150,"vertical"),
  					new Wall(200,200,300,"horizontal"),
  					new Wall(600,400,140,"vertical"),
  					new Wall(800,600,150,"horizontal"),
  					new Wall(350,350,150,"vertical"),
  					new Wall(400,250,300,"horizontal"),
  					new Wall(700,450,200,"vertical"),
  					new Wall(430,150,220,"vertical"),
  					new Wall(50,500,250,"horizontal"),
  					new Wall(570,330,"vertical"),
  					new Wall(120,490,320,"horizontal")];
  	this.maze = new Maze(this.walls);
  	this.cars = [];
  	this.grabbedWall = null;
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

	// Clear the canvas
  	ctx.clearRect(0, 0, canvas.width, canvas.height);

 	// Render all the cars
  	for(car of this.cars){
  		car.render(ctx);
  	}

  	// Render the maze
  	this.maze.render(ctx);

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
	let obstacles = maze.walls;
	let expression = this.direction;
	
	switch(expression) {
	    case Direction.RIGHT:
	        for(let i = 0; i < obstacles.length; i++)
	        {

	        }
	        break;
	    case Direction.LEFT:
	        
	        break;
	    case Direction.FORWARD:

	    	break;
	    default:
	        console.log('invalid direction');
	        break;
	}
	
}

SharpSensor.prototype.findDistance = function() {

	let amInsideWall;
	
}

SharpSensor.prototype.update = function() {

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

function Wall(x, y, height, direction) {
  	this.x = x;
  	this.y = y;
  	if(direction == "horizontal") {
  		this.width = height;
  		this.height = 20;
  	} else {
  		this.width = 20;
  		this.height = height;
  	}
  	this.direction = direction;
}

Wall.prototype.move = function(x_movement, y_movement) {
	this.x = this.x + x_movement;
	this.y = this.y + y_movement;
}


Wall.prototype.render = function(ctx) {
	// RENDER WALL //
	ctx.fillStyle = "black";
	ctx.fillRect(this.x - this.width/2, this.y - this.height/2, this.width, this.height);
}

/////////////////////////////////////////////////

////////////// Maze stuff //////////////////////

function Maze(walls) {
	this.walls = walls;
}

Maze.prototype.render = function(ctx) {
	for(wall of this.walls) {
		wall.render(ctx);
	}
}

////////////////////////////////////////////////

///////////// Start the simulation //////////////

let mSimulation = new Simulation(60);
mSimulation.init();

////////////////// Mod stuff ////////////////////////////

function grabWall(x, y){
	for(wall of mSimulation.walls) {
		if(x > wall.x - wall.width/2 && x < wall.x + wall.width/2 &&
		   y > wall.y - wall.height/2 && y < wall.y + wall.height/2){
			mSimulation.grabbedWall = wall;
			console.log("what's in the box???");
		return;
		}
	}
	mSimulation.grabbedWall = null;
}

/////////////////////////////////////////////////////////

const maze = mSimulation.maze;
