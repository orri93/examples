import { Action } from '@ngrx/store';
import { createSelector } from '@ngrx/store';
import { I1 } from './../models/i1.model';
import * as A1Actions from './../actions/a1.actions';

export interface R1State {
  i1s: I1[];
}

const initialState: R1State = { i1s: [
  { name: 'First', value: 10 },
  { name: 'Second', value: 20 },
  { name: 'Third', value: 30 }
]};

export function r1reducer(state: R1State = initialState, action: A1Actions.Actions): R1State {
  switch (action.type) {
    case A1Actions.I1_ADD:
      return {
        ...state,
        i1s: [...state.i1s, action.payload]
      };
    case A1Actions.I1_REMOVE:
      const i1s = state.i1s.slice();
      i1s.splice(action.payload, 1);
      return {
        ...state,
        i1s
      };
    default:
      return state;
  }
}

export const selectR1State = (state) => state.r1State;
export const selectI1s = createSelector(selectR1State, (state) => state.i1s);
