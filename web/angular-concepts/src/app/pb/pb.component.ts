import { Component, ViewChild } from '@angular/core';
import { DebugService } from './../shared/services/debug.service';
import { M6c1Component } from './../m6/m6c1/m6c1.component'

@Component({
  selector: 'app-pb',
  templateUrl: './pb.component.html',
  styleUrls: ['./pb.component.css']
})
export class PbComponent {
  @ViewChild('m6c1') m6c1: M6c1Component;

  pageName = 'Page no. B';

  constructor() { }

  onSizeChanged(size: ChartSize): void {
    console.log('On Size Changed');
    if (size) {
      DebugService.consoleLogSize(size, '  Size');
    } else {
      console.warn('  Size is undefined');
    }
  }
}
