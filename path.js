class Path {
  constructor(max_len = Infinity) {
    this.max_len = max_len
    this.rays = [];
  }
  show() {
    // colorMode(HSB);
    stroke(255, 100);
    for (let i = 1; i < this.rays.length; i += 1) {
      // stroke(rays.traveled / 500 % 360, 255, 255, 20);
      line(this.rays[i].pos.x, this.rays[i].pos.y, this.rays[i - 1].pos.x, this.rays[i - 1].pos.y);
    }
  }
}