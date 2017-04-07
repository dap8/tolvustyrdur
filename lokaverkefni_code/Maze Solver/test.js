
// Canvas.
var ctx = document.getElementById("canvas");

////////////////// Car stuff //////////////////////

function Car(loc_x, loc_y, rot){
	this.init();
}

Car.prototype.init = function() {
	this.motor_1 = new Motor();
	this.motor_2 = new Motor();
}

Car.prototype.move = function() {
	console.log("Move");
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
	
}

Motor.prototype.power = function(speed, direction) {
	
}

/////////////////////////////////////////////////

/////////////// Sensor stuff ////////////////////

function Sensor(direction){
	this.init();
}

Sensor.prototype.init = function() {
	
}

Sensor.prototype.check = function() {
	
}

Sensor.prototype.setPosition = function() {
	
}

Sensor.prototype.setRotation = function() {
	
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