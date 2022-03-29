import { NgModule } from '@angular/core';
import { CommonModule } from '@angular/common';
import { FormsModule } from '@angular/forms';

import { MatButtonModule } from '@angular/material/button';
import { MatInputModule } from '@angular/material/input';

import { M7c1Component } from './m7c1/m7c1.component';

@NgModule({
  declarations: [
    M7c1Component
  ],
  imports: [
    CommonModule,
    FormsModule,
    MatButtonModule,
    MatInputModule
  ],
  exports: [
    M7c1Component
  ]
})
export class M7Module { }
