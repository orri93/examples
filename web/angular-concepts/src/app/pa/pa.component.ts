import { Component, ViewChild } from '@angular/core';
import { M5c1Component } from './../m5/m5c1/m5c1.component'

@Component({
  selector: 'app-pa',
  templateUrl: './pa.component.html',
  styleUrls: ['./pa.component.css']
})
export class PaComponent {
  @ViewChild('m5c1') m5c1: M5c1Component;

  pageName = 'Page no. A';

  constructor() { }
}
