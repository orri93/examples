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
  hchm: HighchartsHeatmapConfiguration;
  timer: TimerObservableConfiguration
  a: string;
  b: number;
}
