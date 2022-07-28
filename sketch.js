// Daniel Shiffman
// https://thecodingtrain.com/CodingChallenges/145-2d-ray-casting.html
// https://youtu.be/TOEi6T2mtHo

// 2D Ray Casting

let crystal;
let X0 = 1;
let paths = [];
let A, B, C, D;
let BF = 21.28
let BR = 28.75
let nRays = 1000;
let nAPD = 0;
let nAngle = 0;
let nAbsorbed = 0;
let iterDepth = 100;
let debugAngle = -47;
let criticalAngle = 27.44;
let scale = 6;
let slider;
let button;

function processRay(ray, walls) {
  if (ray == null)
    return null
  if (ray.lastBounce == crystal.walls[1]) {
    nAPD += 1
    return null
  }
  let newRay = ray.myreflect(walls)
  if (!newRay)
    throw "No newRay created"

  if (ray.lastBounce) {
    // console.log(ray.dir.angleBetween(ray.lastBounce.norm()))
    if (abs(ray.dir.angleBetween(ray.lastBounce.norm())) < radians(criticalAngle)) {// left crystal
      nAngle += 1;
      return null
    }
  }
  return newRay
}

function setup() {
  if (nRays * iterDepth > 1e3) {
    console.log("Restricting framerate to 5")
    frameRate(5)
  }

  createCanvas(windowWidth, windowHeight);
  button = createButton('recalculate')
  button.position(10, 300)
  button.mousePressed(recalculate)
  slider = createSlider(1, 199, X0);
  slider.position(10, 225);
  slider.style('width', '150px');
  A = createVector(100 * scale, BR / 2 * scale)
  B = createVector(-100 * scale, BR / 2 * scale)
  C = createVector(-100 * scale, -BR / 2 * scale)
  D = createVector(100 * scale, -(BF - BR / 2) * scale)
  crystal = new Crystal(A, B, C, D);

  for (let a = 1; a <= nRays; a += 1) {
    let p = new Path(3e3);
    p.append(new Ray(createVector((X0 - 100) * scale, (BR - crystal.getWidth(X0)) / 2 * scale), p5.Vector.fromAngle(radians(a / nRays * 360)))); //
    paths.push(p);
  }
  for (let i = 0; i <= iterDepth; i += 1) {
    for (let path of paths) {
      path.append(processRay(path.rays.slice(-1)[0], crystal.walls))
    }
  }
}

function recalculate() {
  X0 = slider.value()
  slider.remove()
  delete paths
  button.remove()
  delete button
  button = null
  delete slider
  slider = null
  paths = []
  nAPD = 0
  nAngle = 0
  setup()
}

function draw() {
  X0 = slider.value()
  background(0);
  textSize(16);
  stroke(0)
  fill(255)
  text(`FPS: ${frameRate().toFixed(1)}`, 10, 30)
  text(`iterations: ${iterDepth}`, 10, 60)
  text(`nRays: ${nRays}`, 10, 90)
  text(`nAPD: ${nAPD}`, 10, 120)
  text(`nAngle: ${nAngle}`, 10, 150)
  text(`nAbsorbed: ${nAbsorbed}`, 10, 180)
  text(`nDangling: ${nRays - nAPD - nAngle - nAbsorbed}`, 10, 210)
  text(`xPosition: ${slider.value()}`, 10, 270)
  translate(width / 2, height / 2)

  paths.sort((a, b) => { return -a.pathLength + b.pathLength })
  for (let i = 0; i < paths.length; i += 1) {
    let path = paths[i]
    if (i % (nRays / 1000) < 1)
      path.show()
  }
  crystal.show();
  push()
  strokeWeight(8)
  stroke('red')
  point((X0 - 100) * scale, (BR - crystal.getWidth(X0)) / 2 * scale)
  pop()
}
