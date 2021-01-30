import { Component, ViewChild, OnInit } from '@angular/core';

import { M1c1Component } from './../m1/m1c1/m1c1.component';

@Component({
  selector: 'app-p3',
  templateUrl: './p3.component.html',
  styleUrls: ['./p3.component.css']
})
export class P3Component implements OnInit {
  @ViewChild('m1c1') m1c1: M1c1Component;

  pageName = 'Page no. 3';

  constructor() { }

  ngOnInit(): void {
  }

}
