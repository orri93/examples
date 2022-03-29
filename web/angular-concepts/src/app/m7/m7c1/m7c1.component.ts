import { Component, OnInit } from '@angular/core';
import { NgForm } from '@angular/forms';
import { Location } from '@angular/common';
import { Store } from '@ngrx/store';
import { Subscription } from 'rxjs';
import * as _ from 'lodash';

@Component({
  selector: 'app-m7c1',
  templateUrl: './m7c1.component.html',
  styleUrls: ['./m7c1.component.css']
})
export class M7c1Component implements OnInit {

  componentName = 'Module no. 7 - Component no. 1';

  public enableInput: boolean = false;

  constructor() { }

  ngOnInit(): void {
    let self = this;

    self.enableInput = true;
  }

  public onSave() {
    console.log("On Save");
  }
}
