import { Component, ElementRef, ViewChild, AfterViewInit, OnInit } from '@angular/core';
import { Observable } from 'rxjs';
import { AppConfiguration } from './../app.configuration';

import { ConceptService } from './../concept.service';

import { C1Component } from './../c1/c1.component';

@Component({
  selector: 'app-p1',
  templateUrl: './p1.component.html',
  styleUrls: ['./p1.component.css']
})
export class P1Component implements OnInit, AfterViewInit {
  @ViewChild('tp') tpr: ElementRef;
  @ViewChild('p1c1') p1c1: C1Component;

  pageName = 'Page no. 1';

  t1: string;
  t2: string;
  n1: number;

  observable: Observable<string>;

  constructor(private conceptService: ConceptService) {
    const timer = AppConfiguration.settings.timer;
    this.n1 = AppConfiguration.settings.b;
    this.t1 = AppConfiguration.settings.a;
    this.t2 = 'Nothing';
    this.observable = conceptService.getTimerObservable(timer.first, timer.second);
  }

  ngOnInit(): void {
  }

  ngAfterViewInit(): void {
    const pe = this.tpr.nativeElement as HTMLParagraphElement;
    pe.innerHTML = this.t2;

    this.observable.subscribe(
      data => {
        console.log(data);
        pe.innerHTML = data;
        this.p1c1.text = data;
        this.p1c1.real += 1.0;
      },
      error => {
        console.error(error);
        pe.innerHTML = error;
        this.p1c1.text = error;
        this.p1c1.real += 1.0;
      },
      () => {
        const message = 'Process Completed!';
        console.log(message);
        pe.innerHTML = message;
        this.p1c1.text = message;
        this.p1c1.real -= 1.0;
      }
    );
  }

}
