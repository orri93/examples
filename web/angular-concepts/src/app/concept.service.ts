import { Injectable } from '@angular/core';
import { Observable } from 'rxjs';

@Injectable({
  providedIn: 'root'
})
export class ConceptService {

  constructor() { }

  getTimerObservable(first: number, second: number): Observable<string> {
    return new Observable<string>((observer) => {
      observer.next('Start Processing...');
      setTimeout(() => observer.next('Still Processing ...'), first);
      setTimeout(() => observer.complete(), second);
    });
  }
}
