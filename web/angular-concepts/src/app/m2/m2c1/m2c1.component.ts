import { Component, ElementRef, ViewChild, Input, Output, AfterViewInit, OnInit, OnDestroy } from '@angular/core';
import { Subscription, Observable, interval } from 'rxjs';

import * as d3 from 'd3';

import { AppConfiguration } from './../../app.configuration';
import { ConceptService } from './../../concept.service';

const requestFullscreen = ConceptService.getRequestFullscreen(document);

@Component({
  selector: 'app-m2c1',
  templateUrl: './m2c1.component.html',
  styleUrls: ['./m2c1.component.css']
})
export class M2c1Component implements AfterViewInit, OnInit, OnDestroy {
  @ViewChild('canvas') canvas: ElementRef;
  @ViewChild('chart') chart: ElementRef;
  @Output() supportsFullscreen: boolean;

  componentName = 'Module no. 2 - Component no. 1';

  private parseDateTime;
  private formatTime;

  private observable: Observable<number>;
  private timer: Subscription;

  private d3HmDiv: any;
  private d3AxesSvg: any;
  private d3Canvas: any;
  private xScale: any;
  private yScale: any;

  private xRange: NumberRange;

  constructor(private conceptService: ConceptService) {
    const configuration = AppConfiguration.settings.d3;
    const parsing = configuration.parsing;
    const formatting = configuration.formatting;

    this.parseDateTime = d3.timeParse(parsing.dateTime);
    this.formatTime = d3.timeFormat(formatting.time);

    this.observable = interval(configuration.interval);
    this.supportsFullscreen = !!requestFullscreen;

    this.xRange = conceptService.getAxisRange(configuration.range.x);
  }

  private selectItems(): void {
    console.warn('Select D3 Items');

    this.d3HmDiv = d3.select('div#hm');
    this.d3AxesSvg = d3.select('svg#axes');
    this.d3Canvas = d3.select('canvas');
  }

  private styleItems(): void {
    const configuration = AppConfiguration.settings.d3;
    const size = configuration.size;
    const axes = configuration.axes;
    console.warn('Style D3 Items');

    this.d3HmDiv
      .style('position', 'relative')
      .style('width', (size.width + size.width + axes.x) + 'px')
      .style('height', (size.height + axes.size.height + axes.y) + 'px');

    this.d3AxesSvg
      .attr('width', size.width + axes.size.width + axes.x)
      .attr('height', size.height + axes.size.height + axes.y)
      .style('position', 'absolute')
      .style('left', (axes.x) + 'px')
      .style('top', (axes.y) + 'px');

    this.d3Canvas
      .style('position', 'absolute')
      .style('left', (axes.size.width + axes.x) + 'px')
      .style('top', (2 * axes.y) + 'px');
  }

  private createScales(): void {
    const configuration = AppConfiguration.settings.d3;
    const range = configuration.range;
    const size = configuration.size;

    this.xScale = d3.scaleLinear()
      .domain([range.x.from, range.x.to])
      .range([0, size.width]);

    this.yScale = d3.scaleLinear()
      .domain([range.y.from, range.y.to])
      .range([size.height, 0]);
  }

  private drawAxes(): void {
    const configuration = AppConfiguration.settings.d3;
    const size = configuration.size;
    const axes = configuration.axes;

    this.d3AxesSvg.append('g')
      .attr('id', 'xag')
      .attr('transform', 'translate(' + axes.x + ',' + (size.height + axes.y) + ')')
      .call(d3.axisBottom(this.xScale).tickFormat(d3.format('d')));
    this.d3AxesSvg.append('g')
      .attr('id', 'yag')
      .attr('transform', 'translate(' + axes.x + ', ' +  axes.y + ')')
      .call(d3.axisLeft(this.yScale));
  }

  private redrawAxes(): void {
    const configuration = AppConfiguration.settings.d3;
    const size = configuration.size;
    const axes = configuration.axes;

    d3.select('g#xag').remove();
    this.xScale = d3.scaleLinear()
      .domain([this.xRange.from, this.xRange.to])
      .range([0, size.width]);
    this.d3AxesSvg.append('g')
      .attr('id', 'xag')
      .attr('transform', 'translate(' + axes.x + ',' + (size.height + axes.y) + ')')
      .call(d3.axisBottom(this.xScale).tickFormat(d3.format('d')));
  }

  private onTimer(): void {
    console.log('On Timer');
    this.xRange.from++;
    this.xRange.to++;
    this.redrawAxes();
  }

  private createTimer(): void {
    this.timer = this.observable.subscribe(( x => { this.onTimer(); }));
  }

  start(): void {
    if (this.timer) {
      if (this.timer.closed) {
        this.createTimer();
      } else {
        console.warn('Timer is still opened');
      }
    } else {
      this.createTimer();
    }
  }

  stop(): void {
    if (this.timer) {
      if (this.timer.closed) {
        console.warn('Timer is already closed');
      } else {
        this.timer.unsubscribe();
      }
    } else {
      console.warn('The timer is still undefined');
    }
  }

  reset(): void {
    const configuration = AppConfiguration.settings.d3;
    console.log('Reset');
    this.conceptService.updateAxisRange(this.xRange, configuration.range.x);
    this.redrawAxes();
  }

  toggleFullscreen(): void {
    if (requestFullscreen) {
      requestFullscreen.bind(this.chart.nativeElement)();
    }
  }

  ngAfterViewInit(): void {
  }

  ngOnInit(): void {
    this.selectItems();
    this.styleItems();
    this.createScales();
    this.drawAxes();
  }

  ngOnDestroy(): void {
    if (this.timer && !this.timer.closed) {
      this.timer.unsubscribe();
    }
  }
}
