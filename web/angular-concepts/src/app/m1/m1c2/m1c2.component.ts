import { Component, ViewChild, OnInit, OnDestroy } from '@angular/core';
import { flatten } from '@angular/compiler';
import { Subscription, Observable, interval } from 'rxjs';
import { takeUntil } from 'rxjs/operators';

import * as Highcharts from 'highcharts/highstock';

import { AppConfiguration } from './../../app.configuration';
import { ConceptService } from './../../concept.service';

const boost = require('highcharts/modules/boost.js');
boost(Highcharts);
const heatmap = require('highcharts/modules/heatmap.js');
heatmap(Highcharts);

@Component({
  selector: 'app-m1c2',
  templateUrl: './m1c2.component.html',
  styleUrls: ['./m1c2.component.css']
})
export class M1c2Component implements OnInit, OnDestroy {
  componentName = 'Module no. 1 - Component no. 2';

  Highcharts: typeof Highcharts = Highcharts;
  chartOptions: Highcharts.Options = {
    chart: {
      animation: false,
      type: 'heatmap'
    },
    tooltip: { enabled: false },
    boost: {
      enabled: true,
      allowForce: false,
      seriesThreshold: null,
      useGPUTranslations: true,
      usePreallocated: false
    },
    title: { text: 'Module 1 Component 2 Heatmap' },
    credits: { enabled: false },
    exporting: { enabled: false },
    xAxis: { minPadding: 0, maxPadding: 0 },
    yAxis: { minPadding: 0, maxPadding: 0 },
    colorAxis: {
      stops: [
        [0.00, '#07049b'],  // Dark blue
        [0.30, '#02f7f3'],  // Cyan
        [0.35, '#09f725'],  // Green
        [0.50, '#f4ec04'],  // Yellow
        [0.70, '#f79d01'],  // Orange
        [1.00, '#8c0101']   // Dark red
      ],
      reversed: false,
      startOnTick: false,
      endOnTick: false,
      maxPadding: 0
    },
    legend: {
      align: 'right',
      verticalAlign: 'middle',
      layout: 'vertical',
      y: 5,
      symbolHeight: 195
    },
    series: [{
      name: 'Initial Data',
      type: 'heatmap',
      borderWidth: 1,
      turboThreshold: 0
    }]
  };
  chartConstructor = 'chart';
  updateFlag = false;
  chartCallback;

  private chart: any;
  private data: any;
  private atColumn: number;

  private observable: Observable<number>;
  private timer: Subscription;

  constructor(private conceptService: ConceptService) {
    const configuration = AppConfiguration.settings.hchm;
    const self = this;

    this.observable = interval(configuration.interval);

    this.chartCallback = c => {
      // saving chart reference
      self.chart = c;
    };

    this.atColumn = configuration.matrixRange.columnCount;
  }

  private adjust(points: Array<Array<number>>, chartSize: ChartSize): Array<any> {
    const result: Array<Array<number>> = [];
    const availablePoints = chartSize.width * chartSize.height;
    const pointsAmount = points.length;
    const pointsCounter = Math.floor(pointsAmount / availablePoints);
    if (pointsAmount > availablePoints) {
      for (let i = 0; i < pointsAmount; i += pointsCounter) {
        result.push(points[i]);
      }
    } else {
      return points;
    }
    return result;
  }

  private renderChart(): void {
    const configuration = AppConfiguration.settings.hchm;
    const self = this;
    const chart: Highcharts.Chart = this.chart;

    console.log('Render Chart with update');

    for (let j = 0; j < configuration.matrixRange.rowCount; j++) {
      const p = [
        this.atColumn,                                                  // X
        j,                                                              // Y
        this.conceptService.getRandomNumber(configuration.numberRange)  // Z
      ];
      /*
        * Add the point with Shift
        * A point is shifted off the start of the series as one is appended
        * to the end.
        * https://api.highcharts.com/class-reference/Highcharts.Series#addPoint
        */
      chart.series[0].addPoint(
        /* The point options
          * If options is a single number,
          * a point with that y value is appended to the series. */
        p,
        false,  /* Redraw */
        true,   /* Shift */
        false,  /* Animation */
        false   /* With Event */
        );
    }
    this.atColumn++;

    chart.redraw(true);
  }

  private onTimer(): void {
    this.renderChart();
  }

  private createTimer(): void {
    this.timer = this.observable.subscribe(( x => { this.onTimer(); }));
  }

  updateChart(): void {
    const configuration = AppConfiguration.settings.hchm;
    const self = this;
    const chart = this.chart;

    self.chartOptions.title = {
      text: 'Updated title!'
    };

    self.data = self.conceptService.getRandomMatrix(
      configuration.matrixRange,
      configuration.numberRange);
    const adjustedData = this.adjust(this.data, configuration.size);

    self.chart.series[0].update( {data: adjustedData, type: 'heatmap' } );

    self.updateFlag = true;
  }

  start(): void {
    if (this.timer) {
      if (this.timer.closed) {
        this.createTimer();
      } else {
        console.warn('Timer is still opened');
      }
    } else {
      this.createTimer();
    }
  }

  stop(): void {
    if (this.timer) {
      if (this.timer.closed) {
        console.warn('Timer is already closed');
      } else {
        this.timer.unsubscribe();
      }
    } else {
      console.warn('The timer is still undefined');
    }
  }

  ngOnInit(): void {
  }

  ngOnDestroy(): void {
    if (this.timer && !this.timer.closed) {
      this.timer.unsubscribe();
    }
  }
}
