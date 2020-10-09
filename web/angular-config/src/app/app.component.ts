import { Component } from '@angular/core';
import { interval, Subscription } from 'rxjs';
import { AppConfiguration } from './app.configuration';

const MARKER_NAME_LOAD_START = "load-start";
const MARKER_NAME_LOAD_COMPLETED = "load-completed";
const MEASURE_LOAD = "load-measure";

const MARKER_NAME_TIMER_START = "timer-start";
const MARKER_NAME_TIMER_COMPLETED = "timer-completed";
const MEASURE_TIMER = "timer-measure";

const MARKER_NAME_INTERVAL_START = "interval-start";
const MARKER_NAME_INTERVAL_COMPLETED = "interval-completed";
const MEASURE_INTERVAL = "interval-measure";

@Component({
  selector: 'app-root',
  templateUrl: './app.component.html',
  styleUrls: ['./app.component.css']
})
export class AppComponent {
  
  timer: Subscription;

  timerCount = 0.0;
  timerSum = 0.0;
  timerArray: number[] = [];

  intervalCount = 0.0;
  intervalSum = 0.0;
  intervalArray: number[] = [];

  firstInterval = true;

  title = 'Angular configuration';

  sd(arr: number[], mean: number) {
    var sum = 0.0;
    arr.forEach(element => {
      var diff = element - mean;
      sum += diff * diff;
    });
    return Math.sqrt(sum / arr.length);
  }

  start() {
    let timerInterval = AppConfiguration.settings.timerInterval;
    console.log(`Start button clicked with timer interval as ${timerInterval}`);
    if(this.timer == null || this.timer.closed) {
      this.firstInterval = true;
      this.timer = interval(timerInterval).subscribe(( x => {
        this.onTimer();
      }));
      console.log("Starting timer subscription.");
    } else {
      console.log("Timer subscription already started.");
    }
  }

  stop() {
    console.log("Stop button clicked");
    if(this.timer.closed) {
      console.log("Timer already closed.");
    } else {
      console.log("Unsubscribe the timer.");
      this.timer.unsubscribe();
    }
  }

  onTimer(): void {

    if(!this.firstInterval) {
      performance.mark(MARKER_NAME_INTERVAL_COMPLETED);
      performance.measure(MEASURE_INTERVAL, MARKER_NAME_INTERVAL_START, MARKER_NAME_INTERVAL_COMPLETED);
      let performanceIntervalDivElement = document.getElementById("performance-interval-result-id");
      var entriesInterval = performance.getEntriesByType("measure");
      var firstIntervalEntry = entriesInterval[0];

      var intervalDuration = firstIntervalEntry.duration;
      this.intervalCount++;
      this.intervalSum += intervalDuration;
      this.intervalArray.push(intervalDuration);
      var averageInterval = this.intervalSum / this.intervalCount;
      var sdInterval = this.sd(this.intervalArray, averageInterval);

      performanceIntervalDivElement.innerHTML =
        "Interval. Last: " + intervalDuration +
        " ms, Average: " + averageInterval +
        " ms, SD: " + sdInterval +
        " ms, Count: " + this.intervalCount;

      performance.clearMarks();
      performance.clearMeasures();
    } else {
      console.log("First interval");
      this.firstInterval = false;
    }

    performance.mark(MARKER_NAME_TIMER_START);
    performance.mark(MARKER_NAME_INTERVAL_START);

    /* Work */
    
    performance.mark(MARKER_NAME_TIMER_COMPLETED);
    performance.measure(MEASURE_TIMER, MARKER_NAME_TIMER_START, MARKER_NAME_TIMER_COMPLETED);

    var performanceTimerDivElement = document.getElementById("performance-timer-result-id");
    var entriesTimer = performance.getEntriesByType("measure");
    var firstTimerEntry = entriesTimer[0];

    var timerDuration = firstTimerEntry.duration;
    this.timerCount++;
    this.timerSum += timerDuration;
    this.timerArray.push(timerDuration);
    var average = this.timerSum / this.timerCount;
    var sd = this.sd(this.timerArray, average);

    performanceTimerDivElement.innerHTML =
      "Timer. Last: " + timerDuration +
      " ms, Average: " + average +
      " ms, SD: " + sd +
      " ms, Count: " + this.timerCount;

    performance.clearMeasures();
  }

}
