// Daniel Shiffman
// https://thecodingtrain.com/CodingChallenges/145-2d-ray-casting.html
// https://youtu.be/TOEi6T2mtHo

// 2D Ray Casting

let crystal;
let X0 = 50;
let paths = [];
let A, B, C, D;
let nRays = 100000;
let nAPD = 0;
let nAngle = 0;
let iterDepth = 30;
let debugAngle = 15;
let criticalAngle = 27.44;
let scale = 4;
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
  button.position(10, 270)
  button.mousePressed(recalculate)
  slider = createSlider(1, 199, X0);
  slider.position(10, 195);
  slider.style('width', '150px');
  let BF = 21.28
  let BR = 28.75
  A = createVector(100 * scale, BR / 2 * scale)
  B = createVector(-100 * scale, BR / 2 * scale)
  C = createVector(-100 * scale, -BR / 2 * scale)
  D = createVector(100 * scale, BF - BR / 2 * scale)
  crystal = new Crystal(A, B, C, D);

  for (let a = 1; a <= nRays; a += 1) {
    let p = new Path(1e6);
    p.append(new Ray(createVector((X0 - 100) * scale, 0), p5.Vector.fromAngle(radians(a / nRays * 360))));
    paths.push(p);
  }
  for (let i = 0; i <= iterDepth; i += 1) {
    for (let path of paths) {
      // console.log(path.rays.slice(-1)[0])
      path.append(processRay(path.rays.slice(-1)[0], crystal.walls))
    }
  }
  for (let path of paths)
    path.len()
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
  text(`nDangling: ${nRays - nAPD - nAngle}`, 10, 180)
  text(`xPosition: ${slider.value()}`, 10, 240)
  translate(width / 2, height / 2)

  for (let i = 0; i < paths.length; i += 1) {
    let path = paths[i]
    if (i % 100 == 0)
      path.show()
  }
  crystal.show();
  push()
  strokeWeight(8)
  stroke('red')
  point((X0 - 100) * scale, 0)
  pop()
}
