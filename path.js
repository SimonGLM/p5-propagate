class Path {
  constructor(max_len = Infinity) {
    this.max_len = max_len
    this.rays = [];
    this.pathLength = 0;
    this.absorbedBy = null;
  }

  append(ray) {
    if (ray)
      this.pathLength += ray.len
    this.rays.push(ray)
  }

  // len() {
  //   this.pathLength = 0
  //   for (let ray of this.rays) {
  //     if (!ray)
  //       continue
  //     this.pathLength += ray.len
  //   }
  //   return this.pathLength
  // }

  show() {
    push()
    colorMode(RGB);
    let from = color(0, 3, 255, 96)
    let to = color(145, 254, 21, 96)

    strokeWeight(2)
    stroke(lerpColor(from, to, this.pathLength / 2000));
    if (this.absorbedBy == 'Wrapping')
      stroke(color(255, 0, 0, 32))
    for (let i = 1; i < this.rays.length; i += 1) {
      if (this.rays[i] == null)
        continue
      // this.rays[i].show() // for debug only, shows ray.dir and normal vectors
      line(this.rays[i].pos.x, this.rays[i].pos.y, this.rays[i - 1].pos.x, this.rays[i - 1].pos.y);
    }
    pop()
  }
  show2() {
    push()
    colorMode(HSB);
    let from = color(90, 196, 96, 4)
    let to = color(270, 255, 255, 4)

    strokeWeight(2)
    stroke(lerpColor(from, to, map(this.pathLength, shortest.pathLength, longest.pathLength, 0, 1)));

    for (let i = this.rays.length - 1; i >= 0; i -= 1) {
      if (this.rays[i] == null || this.rays[i - 1] == null)
        continue
      // this.rays[i].show() // for debug only, shows ray.dir and normal vectors
      line(this.rays[i].pos.x, this.rays[i].pos.y, this.rays[i - 1].pos.x, this.rays[i - 1].pos.y);
    }
    pop()
  }
}