import { Component, ViewChild, OnInit } from '@angular/core';

import { M1c2Component } from './../m1/m1c2/m1c2.component';

@Component({
  selector: 'app-p4',
  templateUrl: './p4.component.html',
  styleUrls: ['./p4.component.css']
})
export class P4Component implements OnInit {
  @ViewChild('m1c2') m1c2: M1c2Component;

  pageName = 'Page no. 4';

  constructor() { }

  ngOnInit(): void {
  }

  onClick(): void {
    console.log('On Click');
    if (this.m1c2) {
      this.m1c2.updateChart();
    }
  }

  onStart(): void {
    console.log('On Start');
    if (this.m1c2) {
      this.m1c2.start();
    }
  }

  onStop(): void {
    console.log('On Stop');
    if (this.m1c2) {
      this.m1c2.stop();
    }
  }
}
