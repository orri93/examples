import { Component, Output, EventEmitter, ViewChild, ElementRef } from '@angular/core';
import { ResizedEvent } from 'angular-resize-event';
import * as _ from 'lodash';
import { SizeService } from './../../shared/services/size.service';
import { DebugService } from './../../shared/services/debug.service';
import { M6c2Component } from './../m6c2/m6c2.component';

@Component({
  selector: 'app-m6c1',
  templateUrl: './m6c1.component.html',
  styleUrls: ['./m6c1.component.css']
})
export class M6c1Component {
  @ViewChild('m6c2') m6c2: M6c2Component;
  // Can't have View Child on element for resizing event
  // @ViewChild('cdiv') cdiv: ElementRef;
  @Output() sizeChangedEvent = new EventEmitter<ChartSize>();

  componentName = 'Module no. 6 - Component no. 1';

  size: ChartSize = { width: 0, height: 0 };

  constructor() { }

  onChildResized(event: ResizedEvent): void {
    const oldSize: ChartSize = SizeService.resizedEventOldSize(event);
    const newSize: ChartSize = SizeService.resizedEventNewSize(event);
    console.log('On Child Div Resized');
    DebugService.consoleLogSize(oldSize, '  Old size');
    DebugService.consoleLogSize(newSize, '  New size');
    this.size = _.clone(newSize);
    this.sizeChangedEvent.emit(newSize);
  }
}
