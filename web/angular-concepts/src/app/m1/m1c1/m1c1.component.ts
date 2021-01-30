import { Component, ViewChild, OnInit } from '@angular/core';

import * as Highcharts from 'highcharts';

@Component({
  selector: 'app-m1c1',
  templateUrl: './m1c1.component.html',
  styleUrls: ['./m1c1.component.css']
})
export class M1c1Component implements OnInit {
  @ViewChild('m1c1chart') chart: Highcharts.Chart;

  componentName = 'Module no. 1 - Component no. 1';

  data = [1, 2, 3];

  Highcharts: typeof Highcharts = Highcharts;
  chartOptions: Highcharts.Options = {
    series: [{
      data: this.data,
      type: 'line'
    }]
  };

  constructor() {
  }

  ngOnInit(): void {
  }
}
