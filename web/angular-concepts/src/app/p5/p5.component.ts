import { Component, ViewChild, OnInit } from '@angular/core';

import { M1c3Component } from './../m1/m1c3/m1c3.component';

@Component({
  selector: 'app-p5',
  templateUrl: './p5.component.html',
  styleUrls: ['./p5.component.css']
})
export class P5Component implements OnInit {
  @ViewChild('m1c3') m1c3: M1c3Component;

  pageName = 'Page no. 5';

  constructor() { }

  ngOnInit(): void {
  }

  onClick(): void {
    console.log('On Click');
    if (this.m1c3) {
      this.m1c3.updateChart();
    }
  }
}
