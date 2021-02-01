import { Action } from '@ngrx/store';
import { I1 } from '../models/i1.model';

export const I1_ADD = '[I1] Add';
export const I1_REMOVE = '[I1] Remove';

export class AddI1 implements Action {
  readonly type = I1_ADD;
  constructor(public payload: I1) {}
}

export class RemoveI1 implements Action {
  readonly type = I1_REMOVE;
  constructor(public payload: number) {}
}

export type Actions = AddI1 | RemoveI1;
