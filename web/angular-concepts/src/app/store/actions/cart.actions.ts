import { Action } from '@ngrx/store';

export enum CartActionTypes {
  ACTION_INCREMENT = '[Cart] Increment',
  ACTION_DECREMENT = '[Cart] Decrement',
  Reset = '[Cart] Reset',
}

export class CartIncrement implements Action {
  readonly type = CartActionTypes.ACTION_INCREMENT;
  constructor(public payload: { counter: number }) {}
}

export class CartDecrement implements Action {
  readonly type = CartActionTypes.ACTION_DECREMENT;
  constructor(public payload: { counter: number }) {}
}

export class CartReset implements Action {
  readonly type = CartActionTypes.Reset;
}
