import { Component } from '@angular/core';
import { M5Configuration } from './../m5.configuration';

@Component({
  selector: 'app-m5c1',
  templateUrl: './m5c1.component.html',
  styleUrls: ['./m5c1.component.css']
})
export class M5c1Component {
  componentName = 'Module no. 5 - Component no. 1';

  size: ChartSize;

  constructor() {
    const configuration = M5Configuration.settings;
    if (configuration) {
      console.log('Getting size from M5 Module Configuration');
      this.size = {
        width: configuration.size.width,
        height: configuration.size.height };
    } else {
      console.error('M5 Module Configuration is undefined');
      this.size = { width: 0, height: 0 };
    }
  }
}
