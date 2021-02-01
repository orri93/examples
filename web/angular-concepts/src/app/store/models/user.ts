export class User {
  uName: string;
  isAdmin: boolean;
  ts: string;
  loggedIn: boolean;
  constructor(data: any) {
    Object.assign(this, data);
  }
}
