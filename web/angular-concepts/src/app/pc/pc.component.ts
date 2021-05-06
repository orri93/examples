import { Component, OnInit } from '@angular/core';
import { Subscription, Observable, interval } from 'rxjs';

import * as moment from 'moment';

import { DataService } from './../shared/services/data.service';

const INTERVAL = 1000;

@Component({
  selector: 'app-pc',
  templateUrl: './pc.component.html',
  styleUrls: ['./pc.component.css']
})
export class PcComponent implements OnInit {

  pageName = 'Page no. C';
  current = '';
  last = '';
  time: string;
  span: string;
  counter = 0;

  private observable: Observable<number>;
  private timer: Subscription;

  constructor(private dataService: DataService) {
    this.observable = interval(INTERVAL);
    this.dataService.step = moment.duration(INTERVAL, 'milliseconds');
  }

  ngOnInit(): void {
    const promise = this.dataService.load();
    promise.then(
      value => {
        console.log('Promise fulfilled');
        this.time = this.dataService.time.format();
        this.span = this.dataService.span.asMinutes() + ' min';
        this.timer = this.observable.subscribe( next => this.onTimer() );
      },
      error => {
        console.error(error);
      }
    );
  }

  private onTimer(): void {
    const t: moment.Moment = this.dataService.next();
    const l: moment.Moment = t.clone().subtract(this.dataService.span);
    this.current = t.format();
    this.last = l.format();
  }
}
