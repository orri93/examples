import { Component, OnInit } from '@angular/core';
import { Observable } from 'rxjs';
import { Store } from '@ngrx/store';
import { AppState } from './../app.state';
import { Tutorial } from './../models/tutorial.model';
import * as TutorialActions from './../actions/tutorial.actions';

@Component({
  selector: 'app-c3',
  templateUrl: './c3.component.html',
  styleUrls: ['./c3.component.css']
})
export class C3Component implements OnInit {
  componentName = 'Component no. 3';

  constructor(private store: Store<AppState>) { }

  addTutorial(name: string, url: string): void {
    this.store.dispatch(new TutorialActions.AddTutorial({ name, url }));
  }

  ngOnInit(): void {
  }
}
