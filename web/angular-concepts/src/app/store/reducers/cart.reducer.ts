import { Cart } from '../models/cart';
import { CartActionTypes } from '../actions/cart.actions';
import { createSelector } from '@ngrx/store';

export interface CartState {
  cart: Cart;
}

const initialCartState: CartState = {
  cart: new Cart({
    counter: 0
  })
};

export function cartReducer(cartState = initialCartState, action): CartState {
  switch (action.type) {
    case CartActionTypes.ACTION_DECREMENT:
      console.log('Decrement previous state: ', cartState);
      return {
        ...cartState, // no other properties, can be removed
        cart: new Cart({ counter: action.payload.counter })
      };
    case CartActionTypes.ACTION_INCREMENT:
      console.log('Increment previous state: ', cartState);
      return {
        ...cartState, // no other properties, can be removed
        cart: new Cart({ counter: action.payload.counter })
      };
    case CartActionTypes.Reset:
      console.log('Reset previous state: ', cartState);
      return {
        ...cartState,
        cart: new Cart({ counter: 0 })
      };
    default:
      console.log('Cart Reducer ignore action: ' + action.type);
      return cartState;
  }
}

export const selectCartState = (state) => state.cartState;
export const selectCart = createSelector(selectCartState, (state) => state.cart);
