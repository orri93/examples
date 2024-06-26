import { Injectable } from '@angular/core';
import { HttpClient } from '@angular/common/http';
import { environment } from './../environments/environment';

@Injectable()
export class AppConfiguration {
  static settings: ApplicationConfiguration;

  constructor(private http: HttpClient) {}

  load(): Promise<void> {
    const jsonFile = `${environment.configurationFile}`;
    console.log('Load configuration from ' + jsonFile);
    return new Promise<void>((resolve, reject) => {
      this.http.get(jsonFile).toPromise()
        .then((response: ApplicationConfiguration) => {
          AppConfiguration.settings = (response as ApplicationConfiguration);
          resolve();
        }).catch((response: any) => {
          reject(`Could not load file '${jsonFile}': ${JSON.stringify(response)}`);
        });
    });
  }
}
