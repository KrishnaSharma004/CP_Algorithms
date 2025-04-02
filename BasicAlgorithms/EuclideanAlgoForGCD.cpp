// /*code :->  */

// int gcd (int a, int b) {
//     if (b == 0)
//         return a;
//     else
//         return gcd (b, a % b);
// }

// /*Using the ternary operator in C++, we can write it an on-liner*/

// int gcd (int a, int b) {
//     return b ? gcd (b, a % b) : a;
// }

// /*The non-recursive Implimentation*/
// int gcd (int a, int b) {
//     while (b) {
//         a %= b;
//         //swap(a, b); not commented,use in the code.
//     }
//     return a;
// }

// /*Using only these properties, and some fast bitwise functions from GCC, we can implement a fast version:*/

// int gcd(int a, int b) {
//     if (!a || !b)
//         return a | b;
//     unsigned shift = __builtin_ctz(a | b);
//     a >>= __builtin_ctz(a);
//     do {
//         b >>= __builtin_ctz(b);
//         if (a > b)
//             //swap(a, b);
//         b -= a;
//     } while (b);
//     return a << shift;
// }
