#include <iostream>
#include <cmath>
#include <unordered_map>
using namespace std;

// Modular exponentiation: computes (a^b mod m)
int modpow(int a, int b, int m) {
    int result = 1;
    a %= m;
    while (b > 0) {
        if (b % 2 == 1) result = (result * a) % m;
        a = (a * a) % m;
        b /= 2;
    }
    return result;
}

// Discrete logarithm using Baby-step Giant-step algorithm
int discrete_log(int b, int c, int m, int a = 1) {
    if ((a - c) % m == 0) return 0;

    int n = (int)(sqrt(m)) + 1;
    unordered_map<int, int> baby;

    int value = a;
    for (int i = 0; i < n; ++i) {
        baby[value] = i;
        value = (value * b) % m;
    }

    int factor = modpow(b, n, m);
    value = c;
    for (int j = 0; j <= n; ++j) {
        if (baby.find(value) != baby.end()) {
            return j * n - baby[value];
        }
        value = (value * factor) % m;
    }

    return -1;
}

int main() {
    int a = 1, b = 2, c = 8, m = 13;
    int x = discrete_log(b, c, m, a);
    if (x != -1)
        cout << "Solution found: x = " << x << endl;
    else
        cout << "No solution exists.\n";
    return 0;
}
