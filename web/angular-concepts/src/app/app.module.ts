import { BrowserModule } from '@angular/platform-browser';
import { BrowserAnimationsModule } from '@angular/platform-browser/animations';
import { NgModule, APP_INITIALIZER } from '@angular/core';
import { FormsModule } from '@angular/forms';

import { HttpClientModule, HttpClientXsrfModule } from '@angular/common/http';

import { AppRoutingModule } from './app-routing.module';
import { AppComponent } from './app.component';
import { AppConfiguration } from './app.configuration';

import { M1Module } from './m1/m1.module';

import { MatSliderModule } from '@angular/material/slider';
import { MatButtonModule } from '@angular/material/button';
import { MatInputModule } from '@angular/material/input';
import { MatIconModule } from '@angular/material/icon';

// import { HighchartsChartComponent } from 'highcharts-angular';

import { HpComponent } from './hp/hp.component';
import { P1Component } from './p1/p1.component';
import { P2Component } from './p2/p2.component';
import { P3Component } from './p3/p3.component';
import { C1Component } from './c1/c1.component';

export function initializeApp(appConfiguration: AppConfiguration): any {
  return () => appConfiguration.load();
}

@NgModule({
  declarations: [
    AppComponent,
    HpComponent,
    P1Component,
    P2Component,
    C1Component,
    P3Component
  ],
  imports: [
    BrowserModule,
    FormsModule,
    AppRoutingModule,
    HttpClientModule,
    HttpClientXsrfModule,
    BrowserAnimationsModule,
    // HighchartsChartComponent,
    MatSliderModule,
    MatButtonModule,
    MatInputModule,
    MatIconModule,
    M1Module
  ],
  providers: [
    AppConfiguration, {
      provide: APP_INITIALIZER,
      useFactory: initializeApp,
      deps: [AppConfiguration],
      multi: true
    }
  ],
  bootstrap: [AppComponent]
})
export class AppModule { }
