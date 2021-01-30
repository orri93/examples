import { Component, OnInit } from '@angular/core';

import * as Highcharts from 'highcharts';
import * as HighchartsMore from 'highcharts/highcharts-more';
import * as HighchartsExporting from 'highcharts/modules/exporting';

@Component({
  selector: 'app-m1c3',
  templateUrl: './m1c3.component.html',
  styleUrls: ['./m1c3.component.css']
})
export class M1c3Component implements OnInit {
  componentName = 'Module no. 1 - Component no. 3';

  title = 'app';
  data = [1, 2, 3, 6, 9];
  chart;
  updateFlag = false;
  Highcharts: typeof Highcharts = Highcharts;
  chartConstructor = 'chart';
  chartCallback;
  chartOptions: Highcharts.Options = {
    series: [{
      data: this.data,
      type: 'line'
    }],
    exporting: {
      enabled: true
    },
    yAxis: {
      allowDecimals: false,
      title: {
        text: 'Data'
      }
    }
  };

  constructor() {
    const self = this;

    this.chartCallback = c => {
      // saving chart reference
      self.chart = c;
    };
  }

  ngOnInit(): void {
  }

  updateChart(): void {
    const self = this;
    const chart = this.chart;

    chart.showLoading();
    setTimeout(() => {
      chart.hideLoading();

      self.chartOptions.series = [
        {
          data: [10, 25, 15],
          type: 'line'
        },
        {
          data: [12, 15, 10],
          type: 'line'
        }
      ];

      self.chartOptions.title = {
        text: 'Updated title!'
      };

      self.updateFlag = true;
    }, 2000);
  }
}
