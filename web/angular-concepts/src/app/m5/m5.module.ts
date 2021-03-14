import { NgModule, APP_INITIALIZER } from '@angular/core';
import { CommonModule } from '@angular/common';
import { HttpClientModule, HttpClientXsrfModule } from '@angular/common/http';
import { M5Configuration } from './m5.configuration';
import { M5c1Component } from './m5c1/m5c1.component';

export function initializeModule(moduleConfiguration: M5Configuration): any {
  return () => moduleConfiguration.load();
}

@NgModule({
  declarations: [
    M5c1Component
  ],
  imports: [
    CommonModule,
    HttpClientModule,
    HttpClientXsrfModule
  ],
  exports: [
    M5c1Component
  ],
  providers: [
    M5Configuration, {
      provide: APP_INITIALIZER,
      useFactory: initializeModule,
      deps: [ M5Configuration ],
      multi: true
    }
  ]
})
export class M5Module { }
