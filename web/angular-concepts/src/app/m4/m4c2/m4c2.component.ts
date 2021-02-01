import { Component, OnInit } from '@angular/core';
import { Store, select } from '@ngrx/store';
import { Observable } from 'rxjs';
import { UserState, selectUser, mTstamp } from './../../store/reducers/user.reducer';
import { UserLogout, UserLogin } from './../../store/actions/user.actions';

@Component({
  selector: 'app-m4c2',
  templateUrl: './m4c2.component.html',
  styleUrls: ['./m4c2.component.css']
})
export class M4c2Component implements OnInit {
  componentName = 'Module no. 4 - Component no. 2';

  user$: Observable<any>;

  constructor(private store: Store<UserState>) {
    this.user$ = store.pipe(select(selectUser));
  }

  ngOnInit(): void {
  }

  login(): void {
    this.store.dispatch(new UserLogin(
      { user: { uName: 'Rij', isAdmin: true, loggedIn: true, ts: mTstamp() } }
    ));
  }

  logout(): void {
     this.store.dispatch(new UserLogout());
  }
}
