// Daniel Shiffman
// https://thecodingtrain.com/CodingChallenges/145-2d-ray-casting.html
// https://youtu.be/TOEi6T2mtHo

// 2D Ray Casting

let crystal;
let paths = [];
let lamp;
let A, B, C, D;
let xoff = 0;
let yoff = 10000;
let iterDepth = 10;
let scale = 4;

function processRay(ray, walls) {
  let newRay = ray.myreflect(walls)
  // console.log("newRay", newRay)

  if (newRay) {
    return newRay
  } else {
    console.log("Ray did not bounce on wall", ray)
    return null
  }
}

function setup() {
  createCanvas(windowWidth, windowHeight);
  // frameRate(1)
  A = createVector(100 * scale, -10 * scale)
  B = createVector(-100 * scale, -15 * scale)
  C = createVector(-100 * scale, 15 * scale)
  D = createVector(100 * scale, 15 * scale)
  crystal = new Crystal(A, B, C, D);

  for (let a = 1; a <= 360; a += 36) {
    let p = new Path(1e6);
    p.rays.push(new Ray(createVector(0, 0), p5.Vector.fromAngle(radians(a))));
    paths.push(p);
  }
  for (let i = 0; i < iterDepth; i += 1) {
    for (let path of paths) {
      // console.log(path.rays.slice(-1)[0])
      path.rays.push(processRay(path.rays.slice(-1)[0], crystal.walls))
    }
  }

}

function draw() {
  background(0);
  translate(width / 2, height / 2)
  crystal.show();
  for (let path of paths)
    path.show()
  // for (let i = 0; i < iterDepth; i += 1) {
  //   rays.push(propagator.rays)
  //   propagator.rays[0] = propagator.processRay(propagator.rays[0], crystal.walls);
  // }
}
