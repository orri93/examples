import { BrowserModule } from '@angular/platform-browser';
import { NgModule, APP_INITIALIZER } from '@angular/core';
import { FormsModule } from '@angular/forms';

import { HttpClientModule, HttpClientXsrfModule } from '@angular/common/http';

import { AppRoutingModule } from './app-routing.module';
import { AppComponent } from './app.component';
import { AppConfiguration } from './app.configuration';

import { MatSliderModule } from '@angular/material/slider';
import { MatButtonModule } from '@angular/material/button';
import { MatInputModule } from '@angular/material/input';
import { MatIconModule } from '@angular/material/icon';

import { HpComponent } from './hp/hp.component';
import { P1Component } from './p1/p1.component';
import { BrowserAnimationsModule } from '@angular/platform-browser/animations';
import { P2Component } from './p2/p2.component';

export function initializeApp(appConfiguration: AppConfiguration): any {
  return () => appConfiguration.load();
}

@NgModule({
  declarations: [
    AppComponent,
    HpComponent,
    P1Component,
    P2Component
  ],
  imports: [
    BrowserModule,
    FormsModule,
    AppRoutingModule,
    HttpClientModule,
    HttpClientXsrfModule,
    BrowserAnimationsModule,
    MatSliderModule,
    MatButtonModule,
    MatInputModule,
    MatIconModule
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
