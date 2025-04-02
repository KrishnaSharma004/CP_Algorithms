// /*The recursive approch, which is a direct translation of the recursive forluma : */


// long long binpow(long long a, long long b) {
//     if (b == 0)
//         return 1;
//     long long res = binpow(a, b / 2);
//     if (b % 2)
//         return res * res * a;
//     else
//         return res * res;
// }

// /*The second approach accomplishes the same task without recursion. It computes all the powers in a loop, and multiplies the ones with the corresponding set bit in  
// n . Although the complexity of both approaches is identical, this approach will be faster in practice since we don't have the overhead of the recursive calls.*/

// long long binpow(long long a, long long b) {
//     long long res = 1;
//     while (b > 0) {
//         if (b & 1)
//             res = res * a;
//         a = a * a;
//         b >>= 1;
//     }
//     return res;
// }
