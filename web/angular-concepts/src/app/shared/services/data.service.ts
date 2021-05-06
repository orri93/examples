import { Injectable } from '@angular/core';
import { HttpClient } from '@angular/common/http';

import * as _ from 'lodash';
import * as moment from 'moment';

import { DataPoint } from './../models/data';
import { first } from 'rxjs/operators';

const TESTING_ASSETS_PATH = '/assets/data/datapoints.json';

@Injectable({
  providedIn: 'root'
})
export class DataService {

  step: moment.Duration;
  span: moment.Duration;
  time: moment.Moment;

  private dataPoints: DataPoint[];

  constructor(private http: HttpClient) { }

  public loadDataPoints(): Promise<DataPoint[]> {
    return new Promise<DataPoint[]>((resolve, reject) => {
      this.http.get(TESTING_ASSETS_PATH).toPromise()
        .then((response: DataPoint[]) => {
          this.dataPoints = response;
          this.calculate();
          resolve(response);
        })
        .catch((response: any) => {
          reject(`Could not load file '${TESTING_ASSETS_PATH}': ${JSON.stringify(response)}`);
        });
    });
  }

  public load(): Promise<void> {
    return new Promise<void>((resolve, reject) => {
      this.http.get(TESTING_ASSETS_PATH).toPromise()
        .then((response: DataPoint[]) => {
          this.dataPoints = response;
          this.calculate();
          resolve();
        })
        .catch((response: any) => {
          reject(`Could not load file '${TESTING_ASSETS_PATH}': ${JSON.stringify(response)}`);
        });
    });
  }

  public next(): moment.Moment {
    return this.time.add(this.step);
  }

  private calculate(): void {
    const firstDataPoint: DataPoint = _.first(this.dataPoints);
    const lastDataPoint: DataPoint = _.last(this.dataPoints);
    const firstTime = moment(firstDataPoint.time);
    const lastTime = moment(lastDataPoint.time);
    this.span = moment.duration(lastTime.diff(firstTime));
    this.time = lastTime;
    console.log('Data Range from ' + firstTime.format() + ' to ' + lastTime.format());
    console.log('Time Span is ' + this.span.asMinutes() + ' minutes');
  }
}
