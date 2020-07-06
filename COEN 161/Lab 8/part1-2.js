import * as variables from './variables.js';

const { 
  num1, num2, num3, num4,
  str1, str2, str3, str4 
} = variables;

// What does this statement log and why?
// Prints "2.01" because 1+1.01 is 2.01
console.log(num1 + num2);

// What does this statement log and why?
//"Uncaught TypeError: Assignment to constant variable" - constants cannot have their values changed
console.log(num1 += num2);

// What does this statement log and why?
//"NaN" - tring to add 1e3 (1000) to an undefined
console.log(num3 + num4);

// What does this statement log and why?
//"Uncaught SyntaxError: Identifier 'num4' has already been declared" - num4 has been declared as a constant (undefined), so value of num4 cannot be changed
let num4 = 0;
console.log(num3 + num4);

// What does this statement log and why?
//"hello world" - concatenates strings "hello" and "world"
console.log(str1, str3);

// What does this statement log and why?
//"hello there world undefined" - concatenates "hello", "there", and "world" but str4 is undefined
console.log(str1, str2, str3, str4);
