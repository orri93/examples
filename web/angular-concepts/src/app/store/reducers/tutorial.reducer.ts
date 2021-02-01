import { Action } from '@ngrx/store';
import { createSelector } from '@ngrx/store';
import { Tutorial } from './../models/tutorial.model';
import * as TutorialActions from './../actions/tutorial.actions';

export interface TutorialState {
  tutorials: Tutorial[];
}

const initialState: TutorialState = { tutorials: [{
  name: 'Root Initial Tutorial',
  url: 'http://google.com'
}]};

export function tutorialReducer(state: TutorialState = initialState, action: TutorialActions.Actions): TutorialState {
  switch (action.type) {
    case TutorialActions.ADD_TUTORIAL:
      return {
        ...state,
        tutorials: [...state.tutorials, action.payload]
      };
    case TutorialActions.REMOVE_TUTORIAL:
      const tutorials = state.tutorials.slice();
      tutorials.splice(action.payload, 1);
      return {
        ...state,
        tutorials
      };
    default:
      console.log('Tutorial Reducer ignore action: ' + action);
      return state;
  }
}

export const selectTutorialState = (state) => state.tutorialState;
export const selectTutorials = createSelector(selectTutorialState, (state) => state.tutorials);
