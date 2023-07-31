#include <bits/stdc++.h>
#define f first
#define s second
#define mp make_pair
using namespace std;
typedef long long ll;
//const ll mod = 1e9 + 7;
const ll mod = 998244353;
// Cope Counter = 2147483647

ll po(ll b, ll p) {
  ll a = 1;
  while(p > 0) {
    if(p % 2 == 1) a = a * b % mod;
    b = b * b % mod;
    p /= 2;
  }
  return a;
}
vector<ll> ntt(ll n, vector<ll> arr, bool inv) {
  vector<ll> val = arr, nxt(n);
  for(ll i = 2; i <= n; i *= 2) {
    ll omega = 5;
    if(inv) omega = po(5, mod - 2);
    omega = po(omega, po(2, 23) / i * 119);
    for(ll j = 0; j < n; j += i) {
      for(ll k = 0; k < i / 2; k++) {
        nxt[k + j] = (val[k + j / 2] + po(omega, k) * val[k + (j + n) / 2]) % mod;
        nxt[k + j + i / 2] = (val[k + j / 2] - po(omega, k) * val[k + (j + n) / 2] % mod + mod) % mod;
      }
    }
    val = nxt;
  }
  if(inv) {
    for(ll i = 0; i < n; i++) val[i] = val[i] * po(n, mod - 2) % mod;
  }
  return val;
}