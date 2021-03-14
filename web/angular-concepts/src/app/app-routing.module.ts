import { NgModule } from '@angular/core';
import { Routes, RouterModule } from '@angular/router';

import { HpComponent } from './hp/hp.component';
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

const routes: Routes = [
  { path: '', component: HpComponent },
  { path: 'p0', component: P0Component, data: { type: 'page', name: 'Page 0' } },
  { path: 'p1', component: P1Component, data: { type: 'page', name: 'Page 1' } },
  { path: 'p2', component: P2Component, data: { type: 'page', name: 'Page 2' } },
  { path: 'p3', component: P3Component, data: { type: 'page', name: 'Page 3' } },
  { path: 'p4', component: P4Component, data: { type: 'page', name: 'Page 4' } },
  { path: 'p5', component: P5Component, data: { type: 'page', name: 'Page 5' } },
  { path: 'p6', component: P6Component, data: { type: 'page', name: 'Page 6' } },
  { path: 'p7', component: P7Component, data: { type: 'page', name: 'Page 7' } },
  { path: 'p8', component: P8Component, data: { type: 'page', name: 'Page 8' } },
  { path: 'p9', component: P9Component, data: { type: 'page', name: 'Page 9' } },
  { path: 'pa', component: PaComponent, data: { type: 'page', name: 'Page A' } },
  { path: 'pb', component: PbComponent, data: { type: 'page', name: 'Page B' } }
];

@NgModule({
  imports: [RouterModule.forRoot(routes)],
  exports: [RouterModule]
})
export class AppRoutingModule { }
