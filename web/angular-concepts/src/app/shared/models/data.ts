export interface Point {
  depth: number;
  value: number;
}

export interface DataPoint {
  time: number;
  points: Point[];
}
