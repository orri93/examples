import { Component, OnInit } from '@angular/core';
import { Store } from '@ngrx/store';
import { Tutorial } from './../store/models/tutorial.model';
import { TutorialState } from './../store/reducers/tutorial.reducer';
import * as TutorialActions from './../store/actions/tutorial.actions';

@Component({
  selector: 'app-c3',
  templateUrl: './c3.component.html',
  styleUrls: ['./c3.component.css']
})
export class C3Component implements OnInit {
  componentName = 'Component no. 3';

  constructor(private store: Store<TutorialState>) { }

  addTutorial(name: string, url: string): void {
    this.store.dispatch(new TutorialActions.AddTutorial({ name, url }));
  }

  ngOnInit(): void {
  }
}
