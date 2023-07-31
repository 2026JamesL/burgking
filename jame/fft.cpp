#include <bits/stdc++.h>
#define f first
#define s second
#define mp make_pair
using namespace std;
typedef long long ll;
typedef complex<double> cd;
const ll mod = 1e9 + 7;
// Cope Counter = 2147483647

vector<cd> fft(int n, vector<cd> arr, bool inv) {
  vector<cd> val = arr, nxt(n);
  for(int i = 2; i <= n; i *= 2) {
    double angle = 2.0 * acos(-1) / i;
    if(inv) angle *= -1;
    cd omega(cos(angle), sin(angle));
    for(int j = 0; j < n; j += i) {
      for(int k = 0; k < i / 2; k++) {
        nxt[k + j] = val[k + j / 2] + pow(omega, k) * val[k + (j + n) / 2];
        nxt[k + j + i / 2] = val[k + j / 2] - pow(omega, k) * val[k + (j + n) / 2];
      }
    }
    val = nxt;
  }
  if(inv) {
    for(int i = 0; i < n; i++) val[i] /= n;
  }
  return val;
}