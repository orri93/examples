import { BrowserModule } from '@angular/platform-browser';
import { NgModule } from '@angular/core';

import { AppRoutingModule } from './app-routing.module';
import { AppComponent } from './app.component';
import { EcdHeatmapChartLcjsComponent } from './ecd-heatmap-chart-lcjs/ecd-heatmap-chart-lcjs.component';

@NgModule({
  declarations: [
    AppComponent,
    EcdHeatmapChartLcjsComponent
  ],
  imports: [
    BrowserModule,
    AppRoutingModule
  ],
  providers: [],
  bootstrap: [AppComponent]
})
export class AppModule { }
