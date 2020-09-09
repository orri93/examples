import { ComponentFixture, TestBed } from '@angular/core/testing';

import { EcdHeatmapChartLcjsComponent } from './ecd-heatmap-chart-lcjs.component';

describe('EcdHeatmapChartLcjsComponent', () => {
  let component: EcdHeatmapChartLcjsComponent;
  let fixture: ComponentFixture<EcdHeatmapChartLcjsComponent>;

  beforeEach(async () => {
    await TestBed.configureTestingModule({
      declarations: [ EcdHeatmapChartLcjsComponent ]
    })
    .compileComponents();
  });

  beforeEach(() => {
    fixture = TestBed.createComponent(EcdHeatmapChartLcjsComponent);
    component = fixture.componentInstance;
    fixture.detectChanges();
  });

  it('should create', () => {
    expect(component).toBeTruthy();
  });
});
