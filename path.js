class Path {
  constructor(max_len = Infinity) {
    this.max_len = max_len
    this.rays = [];
    this.pathLength = 0;
  }

  append(ray) {
    this.rays.push(ray)
  }

  len() {
    this.pathLength = 0
    for (let ray of this.rays) {
      if (!ray)
        continue
      this.pathLength += ray.len
    }
    return this.pathLength
  }

  show() {
    push()
    colorMode(HSB, 4000, 255, 255, 255);
    strokeWeight(2)
    stroke(this.pathLength, 255, 255, 64);
    for (let i = 1; i < this.rays.length; i += 1) {
      if (this.rays[i] == null)
        continue
      // this.rays[i].show() // for debug only, shows ray.dir and normal vectors
      line(this.rays[i].pos.x, this.rays[i].pos.y, this.rays[i - 1].pos.x, this.rays[i - 1].pos.y);
    }
    pop()
  }
}