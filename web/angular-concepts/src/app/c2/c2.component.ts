import { Component, OnInit } from '@angular/core';
import { Observable } from 'rxjs';
import { Store, select } from '@ngrx/store';
import { Tutorial } from './../store/models/tutorial.model';
import { TutorialState, selectTutorials } from './../store/reducers/tutorial.reducer';
import * as TutorialActions from './../store/actions/tutorial.actions';

@Component({
  selector: 'app-c2',
  templateUrl: './c2.component.html',
  styleUrls: ['./c2.component.css']
})
export class C2Component implements OnInit {
  componentName = 'Component no. 2';
  tutorials$: Observable<Tutorial[]>;

  constructor(private store: Store<TutorialState>) {
    this.tutorials$ = store.pipe(select(selectTutorials));
  }

  delTutorial(index: number): void {
    this.store.dispatch(new TutorialActions.RemoveTutorial(index));
  }

  ngOnInit(): void {
  }
}
