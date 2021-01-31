/**
 * Typing definition for the Application Configuration
 */

interface NumberRange {
  from: number;
  to: number;
}

interface MatrixRange {
  columnCount: number;
  rowCount: number;
}

interface ChartSize {
  width: number;
  height: number;
}

interface ChartAxes {
  x: number,
  y: number,
  size: ChartSize
}

interface DataRange {
  x: NumberRange;
  y: NumberRange;
  z: NumberRange;
}

interface Parsing {
  dateTime: string;
}

interface Formatting {
  time: string;
}

interface D3Configuration {
  size: ChartSize;
  range: DataRange;
  axes: ChartAxes;
  parsing: Parsing;
  formatting: Formatting;
  interval: number;
}

interface HighchartsHeatmapConfiguration {
  numberRange: NumberRange;
  matrixRange: MatrixRange;
  size: ChartSize;
  interval: number;
}

interface TimerObservableConfiguration {
  first: number;
  second: number;
}

interface ApplicationConfiguration {
  d3: D3Configuration;
  hchm: HighchartsHeatmapConfiguration;
  timer: TimerObservableConfiguration;
  a: string;
  b: number;
}
