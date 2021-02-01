import { ActionReducerMap } from '@ngrx/store';
import { StoreState } from './../store.state';

import { r1reducer } from './../reducers/r1.reducer';
import { tutorialReducer } from './../reducers/tutorial.reducer';
import { userReducer } from './../reducers/user.reducer';
import { cartReducer } from './../reducers/cart.reducer';

export const reducers: ActionReducerMap<StoreState> = {
  r1State: r1reducer,
  tutorialState: tutorialReducer,
  userState: userReducer,
  cartState: cartReducer
};
