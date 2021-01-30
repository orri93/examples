import { Component, ViewChild, AfterViewInit, OnInit } from '@angular/core';
import { flatten } from '@angular/compiler';
import { Subscription, interval, Subject, AsyncSubject, BehaviorSubject } from 'rxjs';
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
export class M1c2Component implements OnInit, AfterViewInit {
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
  chartCallback;
  updateFlag = false;

  private chart: any;

  private data: Array<Array<number>>;

  private isInitialized: Subject<boolean>;
  private subscriptions: Subscription[];

  constructor(private conceptService: ConceptService) {
    const configuration = AppConfiguration.settings.hchm;
    const self = this;

    this.chartCallback = c => {
      // saving chart reference
      self.chart = c;

      self.data = self.conceptService.getRandomMatrix(
        configuration.matrixRange,
        configuration.numberRange);
      const adjustedData = this.adjust(this.data, configuration.size);

      self.chart.series[0].update( { data: adjustedData, type: 'heatmap' });
    };

    this.isInitialized = new Subject<boolean>();
    this.subscriptions = [];
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
  }

  ngOnInit(): void {
  }

  ngAfterViewInit(): void {
    const configuration = AppConfiguration.settings.hchm;
    const self = this;
    this.subscriptions.push(interval(configuration.interval)
      .pipe(takeUntil(self.isInitialized))
      .subscribe(() => {
        this.renderChart();
      }));
  }
}
