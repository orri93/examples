import { Injectable } from '@angular/core';
import { HttpClient } from '@angular/common/http';
import { M5ModuleConfiguration } from './m5-module-configuration.model';

const CONFIGURATION_ASSETS_PATH = '/assets/configuration/m5.json';

@Injectable()
export class M5Configuration {
  static settings: M5ModuleConfiguration;
  constructor(private http: HttpClient) {}
  load(): Promise<void> {
    const jsonFile = CONFIGURATION_ASSETS_PATH;
    return new Promise<void>((resolve, reject) => {
      this.http.get(jsonFile).toPromise()
        .then((response: M5ModuleConfiguration) => {
          M5Configuration.settings = response as M5ModuleConfiguration;
          resolve();
        }).catch((response: any) => {
          reject(`Could not load file '${jsonFile}': ${JSON.stringify(response)}`);
        });
    });
  }
}
