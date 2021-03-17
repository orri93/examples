import { Component, Input } from '@angular/core';

@Component({
  selector: 'app-m6c2',
  templateUrl: './m6c2.component.html',
  styleUrls: ['./m6c2.component.css']
})
export class M6c2Component {
  @Input() size: ChartSize;

  componentName = 'Module no. 6 - Component no. 2';

  constructor() { }
}
