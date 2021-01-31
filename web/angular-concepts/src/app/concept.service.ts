import { Injectable } from '@angular/core';
import { Observable } from 'rxjs';

const webkitRequestFullscreen = 'webkitRequestFullscreen';
const msRequestFullscreen = 'msRequestFullscreen';
const mozRequestFullScreen = 'mozRequestFullScreen';

@Injectable({
  providedIn: 'root'
})
export class ConceptService {

  static getRequestFullscreen(doc: Document): any {
    return doc.documentElement.requestFullscreen ||
    doc.documentElement[webkitRequestFullscreen] ||
    doc.documentElement[msRequestFullscreen] ||
    doc.documentElement[mozRequestFullScreen];
  }

  constructor() { }

  getAxisRange(range: NumberRange): NumberRange {
    return { from: range.from, to: range.to };
  }

  updateAxisRange(destination: NumberRange, source: NumberRange): void {
    destination.from = source.from;
    destination.to = source.to;
  }

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
