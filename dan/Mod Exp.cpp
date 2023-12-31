int exp(long long a, int b) {
    int mod = 1e9+7;
    long long ans = 1;
    while (b > 0) {
        if (b&1) ans = (ans*a)%mod;
        a = (a*a)%mod, b >>= 1;
    }
    return ans;
}
