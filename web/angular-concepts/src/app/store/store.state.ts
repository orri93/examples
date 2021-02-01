import { R1State } from './reducers/r1.reducer';
import { TutorialState } from './reducers/tutorial.reducer';
import { UserState } from './reducers/user.reducer';
import { CartState } from './reducers/cart.reducer';

export interface StoreState {
  r1State: R1State;
  tutorialState: TutorialState;
  userState: UserState;
  cartState: CartState;
}
