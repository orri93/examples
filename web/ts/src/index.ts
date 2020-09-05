import * as _ from 'lodash';

async function hello() {
  return 'world'
}


type Style = 'bold' | 'italic' | 0 | 1 | 2;
type MyList = [number, string, boolean];
type MyListOptional = [number?, string?, boolean?];

interface Person {
  first: string,
  last: string
};

interface FreePerson {
  first: string,
  last: string,
  [key: string]: any
};

// Generics
class Observable<T> {
  constructor(public value: T) {}
}

function pow(x: number, n: number): string {
  return Math.pow(x, n).toString();
}

function testingvoid(x: number, y: number, s?: string): void {
  console.log("X * Y: " + (x * y).toString());
}

let onum: Observable<number>;
let oper: Observable<Person>;
let z = new Observable(23);

let font: Style;

font = 0;

const person: Person = {
  first: 'Jeff',
  last: 'Delney'
};

const personb: FreePerson = {
  first: 'Usain',
  last: 'Bolt',
  fast: true
};

const arr: number[] = [];

arr.push(1);

const parr: Person[] = [];
parr.push({first: 'Orri', last: 'Testing'});

const larr: MyList = [12, 'rr', true];

const loarr: MyListOptional = [];

let powstr: string = pow(3, 4);

testingvoid(3, 4);
testingvoid(3, 4, 'asdf');
