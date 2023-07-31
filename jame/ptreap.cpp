#include <bits/stdc++.h>
#define f first
#define s second
#define mp make_pair
using namespace std;
typedef long long ll;
const ll mod = 1e9 + 7;
const ll N = 3e7;
// Cope Counter = 2147483647

int n, cnt;
int l[N], r[N], sz[N];
ll val[N], sum[N], pr[N];
bool flip[N];

ll rng(void) {
  static ll x = 123456789, y = 362436069, z = 521288629;
  ll t;
  x ^= x << 16;
  x ^= x >> 5;
  x ^= x << 1;
  t = x, x = y, y = z, z = t ^ x ^ y;
  return x ^ y ^ z;
}
int node(int a) {
  cnt++;
  l[cnt] = r[cnt] = flip[cnt] = 0;
  sz[cnt] = 1;
  val[cnt] = sum[cnt] = a;
  pr[cnt] = rng() % mod + 1;
  return cnt;
}
int copy(int u) {
  cnt++;
  l[cnt] = l[u], r[cnt] = r[u], pr[cnt] = pr[u], sz[cnt] = sz[u];
  val[cnt] = val[u], sum[cnt] = sum[u], flip[cnt] = flip[u];
  return cnt;
}
void pull(int u) {
  sum[u] = val[u] + sum[l[u]] + sum[r[u]];
  sz[u] = 1 + sz[l[u]] + sz[r[u]];
}
void push(int u) {
  if(!flip[u]) return;
  if(l[u] != 0) l[u] = copy(l[u]);
  if(r[u] != 0) r[u] = copy(r[u]);
  swap(l[u], r[u]);
  if(l[u] != 0) flip[l[u]] ^= flip[u];
  if(r[u] != 0) flip[r[u]] ^= flip[u];
  flip[u] = 0;
}
int find(int u, int i) {
  push(u);
  int a = sz[l[u]];
  if(a == i) return u;
  if(a < i) return find(r[u], i - a - 1);
  return find(l[u], i);
}
pair<int, int> split(int u, int i) {
  if(u == 0) return mp(0, 0);
  push(u);
  u = copy(u);
  if(sz[l[u]] < i) {
    auto b = split(r[u], i - sz[l[u]] - 1);
    r[u] = b.f;
    pull(u);
    return mp(u, b.s);
  }
  auto b = split(l[u], i);
  l[u] = b.s;
  pull(u);
  return mp(b.f, u);
}
pair<pair<int, int>, int> query(int u, int l, int r) {
  auto a = split(u, r), b = split(a.f, l);
  return mp(b, a.s);
}
int merge(int u, int v) {
  if(u == 0) return v;
  if(v == 0) return u;
  push(u), push(v);
  if(pr[u] > pr[v]) r[u] = merge(r[u], v);
  else l[v] = merge(u, l[v]);
  pull(u), pull(v);
  return (pr[u] > pr[v]) ? u : v;
}
int insert(int u, int i, ll val) {
  auto a = split(u, i);
  return merge(merge(a.f, node(val)), a.s);
}
int del(int u, int i) {
  auto v = query(u, i, i + 1);
  return merge(v.f.f, v.s);
}
void print(int u) {
  push(u);
  if(l[u] != 0) print(l[u]);
  cout << val[u] << " ";
  if(r[u] != 0) print(r[u]);
}

signed main() {
  ios::sync_with_stdio(0);
  cin.tie(0);
  l[0] = r[0] = pr[0] = val[0] = sum[0] = sz[0] = flip[0] = 0;
  int q, op, type;
  cin >> q;
  int tree[q + 3];
  cnt = 0, tree[0] = 0;
  ll lastans = 0, a, b;
  for(int i = 0; i < q; i++) {
    cin >> op >> type;
    tree[i + 1] = tree[op];
    if(type == 1) {
      cin >> a >> b;
      a ^= lastans, b ^= lastans;
      tree[i + 1] = insert(tree[i + 1], a, b);
    } else if(type == 2) {
      cin >> a;
      a ^= lastans;
      tree[i + 1] = del(tree[i + 1], a - 1);
    } else if(type == 3) {
      cin >> a >> b;
      a ^= lastans, b ^= lastans;
      auto u = query(tree[i + 1], a - 1, b);
      flip[u.f.s] ^= true;
      tree[i + 1] = merge(merge(u.f.f, u.f.s), u.s);
    } else {
      cin >> a >> b;
      a ^= lastans, b ^= lastans;
      auto u = query(tree[i + 1], a - 1, b);
      cout << sum[u.f.s] << "\n";
      lastans = sum[u.f.s];
      tree[i + 1] = merge(merge(u.f.f, u.f.s), u.s);
    }
  }
}
