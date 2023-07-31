#include <bits/stdc++.h>
#define f first
#define s second
#define mp make_pair
using namespace std;
typedef long long ll;
const ll mod = 1e9 + 7;
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