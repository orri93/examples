import { NgModule } from '@angular/core';
import { CommonModule } from '@angular/common';
import { M4c1Component } from './m4c1/m4c1.component';
import { M4c2Component } from './m4c2/m4c2.component';

@NgModule({
  declarations: [
    M4c1Component,
    M4c2Component
  ],
  imports: [
    CommonModule
  ],
  exports: [
    M4c1Component,
    M4c2Component
  ]
})
export class M4Module { }
