#include <iostream>
#include <cmath>
using namespace std;

// Modular exponentiation: computes a^b mod p
int modpow(int a, int b, int p) {
    int result = 1;
    a %= p;
    while (b > 0) {
        if (b % 2 == 1) result = (1LL * result * a) % p;
        a = (1LL * a * a) % p;
        b /= 2;
    }
    return result;
}

bool is_quadratic_residue(int a, int p) {
    return modpow(a, (p - 1) / 2, p) == 1;
}


int mod_sqrt(int n, int p) {
    if (n == 0) return 0;
    if (!is_quadratic_residue(n, p)) return -1; 

    
    if (p % 4 == 3) {
        return modpow(n, (p + 1) / 4, p);
    }

    int Q = p - 1, S = 0;
    while (Q % 2 == 0) {
        Q /= 2;
        S++;
    }

    int z = 2;
    while (is_quadratic_residue(z, p)) z++;

    int c = modpow(z, Q, p);
    int R = modpow(n, (Q + 1) / 2, p);
    int t = modpow(n, Q, p);
    int M = S;

    while (t != 1) {
        int i = 1;
        int temp = modpow(t, 2, p);
        while (temp != 1) {
            temp = modpow(temp, 2, p);
            i++;
        }

        int b = modpow(c, 1 << (M - i - 1), p);
        c = (1LL * b * b) % p;
        t = (1LL * t * c) % p;
        R = (1LL * R * b) % p;
        M = i;
    }

    return R;
}

int main() {
    int n = 10, p = 13;
    int root = mod_sqrt(n, p);
    if (root == -1)
        cout << "No square root exists modulo " << p << endl;
    else
        cout << "Square root of " << n << " modulo " << p << " is " << root << endl;
    return 0;
}
