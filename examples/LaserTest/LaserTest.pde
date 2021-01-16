import laser.helios.*;

ProcessingLaser laser;

void setup() {
  size(400,400);
  smooth();
  
  laser = new ProcessingLaser(this);
  
}

void draw() {
  background(0);
  fill(255);
  //text(hello.sayHello(), 40, 200);
}
