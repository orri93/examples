import { NgModule } from '@angular/core';
import { CommonModule } from '@angular/common';

import { HighchartsChartModule } from 'highcharts-angular';

import { M1c1Component } from './m1c1/m1c1.component';
import { M1c2Component } from './m1c2/m1c2.component';
import { M1c3Component } from './m1c3/m1c3.component';

@NgModule({
  declarations: [
    M1c1Component,
    M1c2Component,
    M1c3Component
  ],
  imports: [
    CommonModule,
    HighchartsChartModule
  ],
  exports: [
    M1c1Component,
    M1c2Component,
    M1c3Component
  ]
})
export class M1Module { }
