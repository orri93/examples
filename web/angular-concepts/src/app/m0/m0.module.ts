import { NgModule } from '@angular/core';
import { CommonModule } from '@angular/common';

import { MatCardModule } from '@angular/material/card';
import { MatGridListModule } from '@angular/material/grid-list';
import { MatButtonModule } from '@angular/material/button';

import { M0c1Component } from './m0c1/m0c1.component';
import { M0c2Component } from './m0c2/m0c2.component';
import { M0c0Component } from './m0c0/m0c0.component';
import { M0c3Component } from './m0c3/m0c3.component';
import { M0c4Component } from './m0c4/m0c4.component';

@NgModule({
  declarations: [
    M0c0Component,
    M0c1Component,
    M0c2Component,
    M0c3Component,
    M0c4Component
  ],
  imports: [
    CommonModule,
    MatCardModule,
    MatGridListModule,
    MatButtonModule
  ],
  exports: [
    M0c0Component,
    M0c1Component,
    M0c2Component,
    M0c3Component,
    M0c4Component
  ],
})
export class M0Module { }
