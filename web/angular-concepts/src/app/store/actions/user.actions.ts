import { Action } from '@ngrx/store';
import { User } from '../models/user';

export enum UserActionTypes {
  ACTION_LOGOUT = '[User] Logout',
  ACTION_LOGIN = '[User] Login'
}

export class UserLogout implements Action {
  readonly type = UserActionTypes.ACTION_LOGOUT;
}

export class UserLogin implements Action {
  readonly type = UserActionTypes.ACTION_LOGIN;
  constructor(public payload: { user: User }) {}
}
