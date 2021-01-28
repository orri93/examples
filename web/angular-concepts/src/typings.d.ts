/**
 * Typing definition for the Application Configuration
 */

interface TimerObservableConfiguration {
  first: number;
  second: number;
}

interface ApplicationConfiguration {
  timer: TimerObservableConfiguration
  a: string;
  b: number;
}
