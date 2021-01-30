import { Component, Input, ViewChild, OnInit } from '@angular/core';
import { MatInputModule } from '@angular/material/input';

@Component({
  selector: 'app-c1',
  templateUrl: './c1.component.html',
  styleUrls: ['./c1.component.css']
})
export class C1Component implements OnInit {
  @Input() text: string;
  @Input() real: number;

  componentName = 'Component no. 1';

  constructor() { }

  ngOnInit(): void {
  }
}
