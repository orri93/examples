import { Component, OnInit } from '@angular/core';
import { Observable } from 'rxjs';
import { Store, select } from '@ngrx/store';
import { I1 } from './../../store/models/i1.model';
import { R1State, selectI1s } from './../../store/reducers/r1.reducer';
import * as A1Actions from './../../store/actions/a1.actions';

@Component({
  selector: 'app-m3c1',
  templateUrl: './m3c1.component.html',
  styleUrls: ['./m3c1.component.css']
})
export class M3c1Component implements OnInit {
  componentName = 'Module no. 3 - Component no. 1';

  i1s$: Observable<I1[]>;

  constructor(private store: Store<R1State>) {
    this.i1s$ = store.pipe(select(selectI1s));
  }

  delI1(index: number): void {
    this.store.dispatch(new A1Actions.RemoveI1(index));
  }

  ngOnInit(): void {
  }
}
