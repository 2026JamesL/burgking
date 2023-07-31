#include <bits/stdc++.h>
#define f first
#define s second
#define mp make_pair
using namespace std;
typedef long long ll;
const ll mod = 1e9 + 7;
// Cope Counter = 2147483647

ll n, q;
template<class T, int N> struct bit {
  ll bit[N] = {0};
  void update(ll i, ll val) {
    while(i <= n) {
      bit[i] = (bit[i] + val) % mod;
      i += i & (-i);
    }
    return;
  }
  ll query(ll i) {
    ll sum = 0;
    while(i > 0) {
      sum = (sum + bit[i]) % mod;
      i -= i & (-i);
    }
    return sum;
  }
};

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);
  cin >> n >> q;
  ll arr[n];
  bit<int, 200001> t;
  for(ll i = 0; i < n; ++i) {
    cin >> arr[i];
    t.update(i + 1, arr[i]);
  }
  ll type, a, b;
  for(ll i = 0; i < q; ++i) {
    cin >> a >> b;
    type = 2;
    if(type == 1) {
      t.update(a, b - arr[a - 1]);
      arr[a - 1] = b;
    } else {
      cout << t.query(b) - t.query(a - 1) << "\n";
    }
  }
}