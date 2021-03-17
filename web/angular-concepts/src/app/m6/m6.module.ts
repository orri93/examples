import { NgModule } from '@angular/core';
import { CommonModule } from '@angular/common';
import { AngularResizedEventModule } from 'angular-resize-event';
import { M6c1Component } from './m6c1/m6c1.component';
import { M6c2Component } from './m6c2/m6c2.component';

@NgModule({
  declarations: [
    M6c1Component,
    M6c2Component
  ],
  imports: [
    CommonModule,
    AngularResizedEventModule
  ],
  exports: [
    M6c1Component,
    M6c2Component
  ]
})
export class M6Module { }
