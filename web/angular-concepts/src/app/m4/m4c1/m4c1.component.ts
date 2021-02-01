import { Component } from '@angular/core';
import { Observable } from 'rxjs';
import { Store, select } from '@ngrx/store';

import { CartDecrement, CartIncrement, CartReset } from './../../store/actions/cart.actions';
import { CartState, selectCart } from './../../store/reducers/cart.reducer';

@Component({
  selector: 'app-m4c1',
  templateUrl: './m4c1.component.html',
  styleUrls: ['./m4c1.component.css']
})
export class M4c1Component {
  componentName = 'Module no. 4 - Component no. 1';

  counter = 0;

  constructor(private store: Store<CartState>) {
    store.pipe(select(selectCart)).subscribe((cart) => {
      this.counter = cart.counter;
    });
  }

  increment(): void {
    this.store.dispatch(new CartIncrement({ counter: this.counter + 1 }));
  }

  decrement(): void {
    this.store.dispatch(new CartDecrement({ counter: this.counter - 1 }));
  }

  reset(): void {
    this.store.dispatch(new CartReset());
  }
}
