import { Component, ViewChild, OnInit } from '@angular/core';

import { M2c1Component } from './../m2/m2c1/m2c1.component';

@Component({
  selector: 'app-p6',
  templateUrl: './p6.component.html',
  styleUrls: ['./p6.component.css']
})
export class P6Component implements OnInit {
  @ViewChild('m2c1') m2c1: M2c1Component;

  pageName = 'Page no. 6';

  constructor() { }

  ngOnInit(): void {
  }

  onStart(): void {
    console.log('On Start');
    if (this.m2c1) {
      this.m2c1.start();
    }
  }

  onStop(): void {
    console.log('On Stop');
    if (this.m2c1) {
      this.m2c1.stop();
    }
  }

  onReset(): void {
    console.log('On Reset');
    if (this.m2c1) {
      this.m2c1.reset();
    }
  }
}
