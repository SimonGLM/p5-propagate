class Path {
  constructor(max_len = Infinity) {
    this.max_len = max_len
    this.rays = [];
    this.pathLength = 0;
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
    let from = color(0, 3, 255, 64)
    let to = color(145, 254, 21, 64)

    strokeWeight(2)
    stroke(lerpColor(from, to, this.pathLength / 2000));
    for (let i = 1; i < this.rays.length; i += 1) {
      if (this.rays[i] == null)
        continue
      // this.rays[i].show() // for debug only, shows ray.dir and normal vectors
      line(this.rays[i].pos.x, this.rays[i].pos.y, this.rays[i - 1].pos.x, this.rays[i - 1].pos.y);
    }
    pop()
  }
}