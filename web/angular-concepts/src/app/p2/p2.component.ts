import { Component, OnInit } from '@angular/core';
import * as $ from 'jquery';

@Component({
  selector: 'app-p2',
  templateUrl: './p2.component.html',
  styleUrls: ['./p2.component.css']
})
export class P2Component implements OnInit {

  pageName = 'Page no. 2';

  constructor() { }

  ngOnInit(): void {
    const p2p = $('#p2p');
    p2p.text('Hello World!');
  }

}
