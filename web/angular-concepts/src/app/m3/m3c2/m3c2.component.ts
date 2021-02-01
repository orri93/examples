import { Component, OnInit } from '@angular/core';
import { Store } from '@ngrx/store';
import { R1State } from './../../store/reducers/r1.reducer';
import * as A1Actions from './../../store/actions/a1.actions';

@Component({
  selector: 'app-m3c2',
  templateUrl: './m3c2.component.html',
  styleUrls: ['./m3c2.component.css']
})
export class M3c2Component implements OnInit {
  componentName = 'Module no. 3 - Component no. 2';

  constructor(private store: Store<R1State>) { }

  addI1(name: string, value: number): void {
    this.store.dispatch(new A1Actions.AddI1({ name, value }));
  }

  ngOnInit(): void {
  }
}
