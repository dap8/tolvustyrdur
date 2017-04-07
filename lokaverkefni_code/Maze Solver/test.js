
// Canvas.
var ctx = document.getElementById("canvas");

////////////////// Car stuff //////////////////////

function Car(x, y, rot, name){
	this.name = name;
	this.x = x;
	this.y = y;
	this.rot = rot;
	this.init();
}

Car.prototype.init = function() {
	console.log(this.name + " ready to go!");
	this.motor_1 = new Motor();
	this.motor_2 = new Motor();
	this.SharpSensor_1 = new SharpSensor
}

Car.prototype.move = function() {
	console.log(this.name + "on the move!");
}

Car.prototype.setRotation = function() {

}

Car.prototype.setPosition = function() {

}

Car.prototype.update = function() {
	this.move();
}

Car.prototype.render = function(ctx) {
	// RENDER CAR //
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

function SharpSensor(direction){
	this.init();
}

SharpSensor.prototype.init = function() {
	console.log("Sharp sensor started");
}

SharpSensor.prototype.check = function() {
	
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

}

Wall.prototype.render = function(ctx) {
	// RENDER WALL //
}




var car_1 = new Car(1,2,3);
car_1.move();