vector<ll> factorial;

void generate_factorial(int m) {
    factorial.resize(m + 1);
    factorial[0] = 1;

    for (ll i = 1; i <= m; i++) {
        factorial[i] = factorial[i - 1] * i; factorial[i] += MOD; factorial[i] %= MOD;
    }
}
