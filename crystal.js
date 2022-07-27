class Crystal {
  constructor(p1, p2, p3, p4) {
    this.walls = [new Boundary(p1.x, p1.y, p2.x, p2.y),
    new Boundary(p2.x, p2.y, p3.x, p3.y),
    new Boundary(p3.x, p3.y, p4.x, p4.y),
    new Boundary(p4.x, p4.y, p1.x, p1.y)]
  }

  show() {
    this.walls[0].show();
    this.walls[2].show();
    this.walls[3].show();
    this.walls[1].show(255, 0, 0, 5);
  }
}