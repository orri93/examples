import { BrowserModule } from '@angular/platform-browser';
import { BrowserAnimationsModule } from '@angular/platform-browser/animations';
import { NgModule, APP_INITIALIZER } from '@angular/core';
import { FormsModule } from '@angular/forms';
import { StoreModule } from '@ngrx/store';

import { HttpClientModule, HttpClientXsrfModule } from '@angular/common/http';

// Enough to add the Resize Event module into the module that use it (M6)
// import { AngularResizedEventModule } from 'angular-resize-event';

import { MatSliderModule } from '@angular/material/slider';
import { MatButtonModule } from '@angular/material/button';
import { MatInputModule } from '@angular/material/input';
import { MatIconModule } from '@angular/material/icon';

import { AppRoutingModule } from './app-routing.module';
import { AppComponent } from './app.component';
import { AppConfiguration } from './app.configuration';

import { reducers } from './store/reducers';

import { M0Module } from './m0/m0.module';
import { M1Module } from './m1/m1.module';
import { M2Module } from './m2/m2.module';
import { M3Module } from './m3/m3.module';
import { M4Module } from './m4/m4.module';
import { M5Module } from './m5/m5.module';
import { M6Module } from './m6/m6.module';
import { M7Module } from './m7/m7.module';

import { HpComponent } from './hp/hp.component';
import { C1Component } from './c1/c1.component';
import { C2Component } from './c2/c2.component';
import { C3Component } from './c3/c3.component';
import { P0Component } from './p0/p0.component';
import { P1Component } from './p1/p1.component';
import { P2Component } from './p2/p2.component';
import { P3Component } from './p3/p3.component';
import { P4Component } from './p4/p4.component';
import { P5Component } from './p5/p5.component';
import { P6Component } from './p6/p6.component';
import { P7Component } from './p7/p7.component';
import { P8Component } from './p8/p8.component';
import { P9Component } from './p9/p9.component';
import { PaComponent } from './pa/pa.component';
import { PbComponent } from './pb/pb.component';
import { PcComponent } from './pc/pc.component';
import { PdComponent } from './pd/pd.component';

export function initializeApp(appConfiguration: AppConfiguration): any {
  return () => appConfiguration.load();
}

@NgModule({
  declarations: [
    AppComponent,
    HpComponent,
    C1Component,
    C2Component,
    C3Component,
    P0Component,
    P1Component,
    P2Component,
    P3Component,
    P4Component,
    P5Component,
    P6Component,
    P7Component,
    P8Component,
    P9Component,
    PaComponent,
    PbComponent,
    PcComponent,
    PdComponent
  ],
  imports: [
    BrowserModule,
    FormsModule,
    AppRoutingModule,
    HttpClientModule,
    HttpClientXsrfModule,
    // AngularResizedEventModule,
    StoreModule.forRoot(reducers),
    BrowserAnimationsModule,
    MatSliderModule,
    MatButtonModule,
    MatInputModule,
    MatIconModule,
    M0Module,
    M1Module,
    M2Module,
    M3Module,
    M4Module,
    M5Module,
    M6Module,
    M7Module
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
