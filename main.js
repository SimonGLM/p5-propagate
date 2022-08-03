// p5-propagate
// Light propagation simulation to quantify light yield non-linearities
// in PANDA EMC Barrel Type-1 crystals.
// This simulation ignores partial reflection for angles below critical and ignores scattering from the wrapping back into the crystal.

// Heavily inspired and derived from:
// Daniel Shiffman
// https://thecodingtrain.com/CodingChallenges/145-2d-ray-casting.html
// https://youtu.be/TOEi6T2mtHo


let crystal;
let X0 = 100;
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
let pathstodraw;
let shortest;
let longest;

function processRay(path, walls) {
  let ray = path.rays.slice(-1)[0]
  if (ray == null)
    return null
  if (ray.lastBounce == crystal.walls[1]) {
    nAPD += 1
    path.absorbedBy = 'APD'
    return null
  }
  let newRay = ray.myreflect(walls)
  if (!newRay)
    throw "No newRay created"

  if (ray.lastBounce) {
    // console.log(ray.dir.angleBetween(ray.lastBounce.norm()))
    if (abs(ray.dir.angleBetween(ray.lastBounce.norm())) < radians(criticalAngle)) {// left crystal
      nAngle += 1;
      path.absorbedBy = 'Wrapping'
      return null
    }
  }
  return newRay
}

function setup() {
  // if (nRays * iterDepth > 1e5) {
  // console.log("Restricting framerate to 5")
  frameRate(5)
  // }

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
      path.append(processRay(path, crystal.walls))
    }
  }
}

function recalculate(x = -1) {
  if (x == -1)
    X0 = slider.value()
  else
    X0 = x
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
  pathstodraw = null
  setup()
}

function sample(N) {

  console.log("X, nRays, nAPD, nAngle, ratio")
  for (let i = 0; i < N; i += 1) {
    let x = map(i, 0, N, 1, 199)
    recalculate(x)
    console.log(x, ", ", nRays, ", ", nAPD, ", ", nAngle, ", ", nAPD / nRays)
  }
}

function draw() {
  X0 = slider.value()
  background(255);
  textSize(16);
  stroke(0)
  fill(255)
  text(`FPS: ${frameRate().toFixed(1)}`, 10, 30)
  text(`iteration limit: ${iterDepth}`, 10, 60)
  text(`nRays: ${nRays}`, 10, 90)
  text(`nAPD: ${nAPD}`, 10, 120)
  text(`nAngle: ${nAngle}`, 10, 150)
  text(`nAbsorbed: ${nAbsorbed}`, 10, 180)
  text(`nDangling: ${nRays - nAPD - nAngle - nAbsorbed}`, 10, 210)
  text(`xPosition: ${slider.value()}`, 10, 270)
  translate(width / 2, height / 2)

  if (!pathstodraw) { // suffle once per recalculation
    let consider = paths//paths.filter(path => path.absorbedBy == 'APD')
    if (nRays > 2000)
      pathstodraw = getRandomSubarray(consider, 2000)
    else
      pathstodraw = paths
    pathstodraw.sort((a, b) => { return -a.pathLength + b.pathLength })
  }
  shortest = pathstodraw.slice(-1)[0]
  longest = pathstodraw[0]
  for (let path of pathstodraw)
    path.show()
  // for (let i = 0; i < paths.length; i += 1) {
  //   let path = paths[i]
  //   if (i % (nRays / 1000) < 1)
  //     path.show()
  // }
  crystal.show();
  push()
  strokeWeight(8)
  stroke('lightblue')
  point((X0 - 100) * scale, (BR - crystal.getWidth(X0)) / 2 * scale)
  pop()
}

function getRandomSubarray(arr, size) {
  var shuffled = arr.slice(0), i = arr.length, temp, index;
  while (i--) {
    index = Math.floor((i + 1) * Math.random());
    temp = shuffled[index];
    shuffled[index] = shuffled[i];
    shuffled[i] = temp;
  }
  return shuffled.slice(0, size);
}
