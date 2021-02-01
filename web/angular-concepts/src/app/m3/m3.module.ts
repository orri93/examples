import { NgModule } from '@angular/core';
import { BrowserAnimationsModule } from '@angular/platform-browser/animations';
import { CommonModule } from '@angular/common';
import { FormsModule } from '@angular/forms';

import { MatButtonModule } from '@angular/material/button';
import { MatInputModule } from '@angular/material/input';

import { M3c1Component } from './m3c1/m3c1.component';
import { M3c2Component } from './m3c2/m3c2.component';

@NgModule({
  declarations: [
    M3c1Component,
    M3c2Component
  ],
  imports: [
    CommonModule,
    FormsModule,
    BrowserAnimationsModule,
    MatButtonModule,
    MatInputModule
  ],
  exports: [
    M3c1Component,
    M3c2Component
  ]
})
export class M3Module { }
