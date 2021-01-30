import { NgModule } from '@angular/core';
import { CommonModule } from '@angular/common';

import { HighchartsChartModule } from 'highcharts-angular';

import { M1c1Component } from './m1c1/m1c1.component';

@NgModule({
  declarations: [M1c1Component],
  imports: [
    CommonModule,
    HighchartsChartModule
  ],
  exports: [
    M1c1Component
  ]
})
export class M1Module { }
