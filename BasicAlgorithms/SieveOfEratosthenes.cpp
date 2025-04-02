
/*The algorithm is very simple: at the beginning we write down all numbers between 2 and n . We mark all proper multiples of 2 (since 2 is the smallest prime number) as composite. A proper multiple of a number x , is a number greater than x and divisible by x . Then we find the next number that hasn't been marked as composite, in this case it is 3. Which means 3 is prime, and we mark all proper multiples of 3 as composite. The next unmarked number is 5, which is the next prime number, and we mark all proper multiples of it. And we continue this procedure until we have processed all numbers in the row.*/

/*The idea behind is this: A number is prime, if none of the smaller prime numbers divides it. Since we iterate over the prime numbers in order, we already marked all numbers, which are divisible by at least one of the prime numbers, as divisible. Hence if we reach a cell and it is not marked, then it isn't divisible by any smaller prime number and therefore has to be prime.*/

// int n;
// vector <bool> is_prime(n+1, true);
// is_prime[0] = is_prime[1] = false;
// for (int i = 2; i <= n; i++) {
//     if (is_prime[i] && (long long)i * i <= n) {
//         for (int j = i * i; j <= n; j += i)
//             is_prime[j] = false;
//     }
// }


/*Sieving till root :->*/

// int n;
// vector<bool> is_prime(n+1, true);
// is_prime[0] = is_prime[1] = false;
// for (int i = 2; i * i <= n; i++) {
//     if (is_prime[i]) {
//         for (int j = i * i; j <= n; j += i)
//             is_prime[j] = false;
//     }
// }


/*Segmented Sieve :-> */


// int count_primes(int n) {
//     const int S = 10000;

//     vector<int> primes;
//     int nsqrt = sqrt(n);
//     vector<char> is_prime(nsqrt + 2, true);
//     for (int i = 2; i <= nsqrt; i++) {
//         if (is_prime[i]) {
//             primes.push_back(i);
//             for (int j = i * i; j <= nsqrt; j += i)
//                 is_prime[j] = false;
//         }
//     }

//     int result = 0;
//     vector<char> block(S);
//     for (int k = 0; k * S <= n; k++) {
//         fill(block.begin(), block.end(), true);
//         int start = k * S;
//         for (int p : primes) {
//             int start_idx = (start + p - 1) / p;
//             int j = max(start_idx, p) * p - start;
//             for (; j < S; j += p)
//                 block[j] = false;
//         }
//         if (k == 0)
//             block[0] = block[1] = false;
//         for (int i = 0; i < S && start + i <= n; i++) {
//             if (block[i])
//                 result++;
//         }
//     }
//     return result;
// }


/*Find primes in Range L,R :-> */


// vector<char> segmentedSieve(long long L, long long R) {
//     // generate all primes up to sqrt(R)
//     long long lim = sqrt(R);
//     vector<char> mark(lim + 1, false);
//     vector<long long> primes;
//     for (long long i = 2; i <= lim; ++i) {
//         if (!mark[i]) {
//             primes.emplace_back(i);
//             for (long long j = i * i; j <= lim; j += i)
//                 mark[j] = true;
//         }
//     }

//     vector<char> isPrime(R - L + 1, true);
//     for (long long i : primes)
//         for (long long j = max(i * i, (L + i - 1) / i * i); j <= R; j += i)
//             isPrime[j - L] = false;
//     if (L == 1)
//         isPrime[0] = false;
//     return isPrime;
// }