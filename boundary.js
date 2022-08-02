// Daniel Shiffman
// https://thecodingtrain.com/CodingChallenges/145-2d-ray-casting.html
// https://youtu.be/TOEi6T2mtHo

// 2D Ray Casting

class Boundary {
  constructor(x1, y1, x2, y2) {
    this.a = createVector(x1, y1);
    this.b = createVector(x2, y2);
  }

  show(R = 0, G = 0, B = 0, weight = 5) {
    push()
    colorMode(RGB, 255)
    stroke(R, G, B)
    strokeWeight(weight)
    line(this.a.x, this.a.y, this.b.x, this.b.y);
    pop()
  }

  norm() {
    let vecx = this.a.x - this.b.x
    let vecy = this.a.y - this.b.y
    return createVector(vecy, -vecx).normalize()
  }
}
