import { Component, OnInit } from '@angular/core';
import { AppConfiguration } from './../app.configuration';

@Component({
  selector: 'app-p1',
  templateUrl: './p1.component.html',
  styleUrls: ['./p1.component.css']
})
export class P1Component implements OnInit {
  text: string;
  n: number;

  constructor() {
    this.text = AppConfiguration.settings.a;
    this.n = AppConfiguration.settings.b;
  }

  ngOnInit(): void {}

}
