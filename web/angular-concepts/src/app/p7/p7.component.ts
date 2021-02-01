import { Component, ViewChild, OnInit } from '@angular/core';

import { C2Component } from './../c2/c2.component';

@Component({
  selector: 'app-p7',
  templateUrl: './p7.component.html',
  styleUrls: ['./p7.component.css']
})
export class P7Component implements OnInit {
  @ViewChild('c2') c2: C2Component;

  pageName = 'Page no. 7';

  constructor() { }

  ngOnInit(): void {
  }

}
