import { Injectable } from '@angular/core';
import { from, Observable } from 'rxjs';

@Injectable({
  providedIn: 'root'
})
export class ConceptService {

  constructor() { }

  getRandomNumber(range: NumberRange): number {
    const minimum = Math.ceil(range.from);
    const maximum = Math.floor(range.to);
    return Math.floor(Math.random() * (maximum - minimum)) + minimum;
  }

  getRandomMatrix(range: MatrixRange, numberRange: NumberRange): Array<Array<number>> {
    const result = [];
    for (let i = 0; i < range.columnCount; i++) {
      for (let j = 0; j < range.rowCount; j++) {
        result.push([i, j, this.getRandomNumber(numberRange)]);
      }
    }
    return result;
  }

  getTimerObservable(first: number, second: number): Observable<string> {
    return new Observable<string>((observer) => {
      observer.next('Start Processing...');
      setTimeout(() => observer.next('Still Processing ...'), first);
      setTimeout(() => observer.complete(), second);
    });
  }
}
