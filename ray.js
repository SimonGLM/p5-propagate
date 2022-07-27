// Daniel Shiffman
// https://thecodingtrain.com/CodingChallenges/145-2d-ray-casting.html
// https://youtu.be/TOEi6T2mtHo

// 2D Ray Casting

class Ray {
  constructor(pos, dir, lastBounce = null) {
    this.pos = pos;
    this.dir = dir;
    this.len = 0;
    this.lastBounce = lastBounce;
  }

  show() {
    push()
    fill('red')
    stroke('red')
    strokeWeight(3)
    ellipse(this.pos.x, this.pos.y, 10)
    line(this.pos.x, this.pos.y, this.pos.x + this.dir.x * 30, this.pos.y + this.dir.y * 30)
    stroke('green')
    line(this.pos.x, this.pos.y, this.pos.x + this.lastBounce.norm().x * 30, this.pos.y + this.lastBounce.norm().y * 30)
    pop()
  }

  myreflect(walls) {
    let closest = null;
    let record = Infinity;
    let normal;
    let bounce;
    for (let wall of walls) {
      if (wall == this.lastBounce)
        continue
      const pt = this.intersect(wall);
      if (pt) {
        bounce = wall;
        const d = p5.Vector.dist(this.pos, pt);
        if (d < record) {
          record = d;
          closest = pt;
          normal = wall.norm()
        }
      }
    }
    if (closest) { //found pt where ray intersects first
      let newRay = new Ray(closest, this.dir.copy(), bounce);
      this.len = this.pos.dist(closest)
      newRay.len = this.pos.dist(closest)
      newRay.dir.reflect(normal);
      return newRay;
    } else { throw "No intersection with boundary" }
  }


  intersect(wall) {
    const x1 = wall.a.x;
    const y1 = wall.a.y;
    const x2 = wall.b.x;
    const y2 = wall.b.y;

    const x3 = this.pos.x;
    const y3 = this.pos.y;
    const x4 = this.pos.x + this.dir.x;
    const y4 = this.pos.y + this.dir.y;

    const den = (x1 - x2) * (y3 - y4) - (y1 - y2) * (x3 - x4);
    if (den == 0) {
      return;
    }

    const t = ((x1 - x3) * (y3 - y4) - (y1 - y3) * (x3 - x4)) / den;
    const u = -((x1 - x2) * (y1 - y3) - (y1 - y2) * (x1 - x3)) / den;
    if (t > 0 && t < 1 && u > 0) {
      const pt = createVector();
      pt.x = x1 + t * (x2 - x1);
      pt.y = y1 + t * (y2 - y1);
      return pt;
    } else {
      return;
    }
  }
}
