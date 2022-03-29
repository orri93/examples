import { Component, ViewChild, OnInit } from '@angular/core';
import { M7c1Component } from './../m7/m7c1/m7c1.component'

@Component({
  selector: 'app-pd',
  templateUrl: './pd.component.html',
  styleUrls: ['./pd.component.css']
})
export class PdComponent implements OnInit {
  @ViewChild('m7c1') m7c1: M7c1Component;

  pageName = 'Page no. D';

  constructor() { }

  ngOnInit(): void {
  }

}
