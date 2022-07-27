// Daniel Shiffman
// https://thecodingtrain.com/CodingChallenges/145-2d-ray-casting.html
// https://youtu.be/TOEi6T2mtHo

// 2D Ray Casting

class Boundary {
  constructor(x1, y1, x2, y2) {
    this.a = createVector(x1, y1);
    this.b = createVector(x2, y2);
  }

  show(H = 0, S = 0, B = 255, weight = 3) {
    push()
    colorMode(HSB, 255)
    stroke(H, S, B)
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
