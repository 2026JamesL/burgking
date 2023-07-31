#include <bits/stdc++.h>
#define f first
#define s second
#define mp make_pair
using namespace std;
typedef long long ll;
//const ll mod = 1e9 + 7;
const ll mod = 998244353;
const ll N = 1e6 + 1;
// Cope Counter = 2147483647

int ch[2][N], p[N], flip[N];
ll val[N], sum[N], sz[N], mul[N], add[N];
int cnt;

int node(ll a) {
  cnt++;
  ch[0][cnt] = ch[1][cnt] = p[cnt] = flip[cnt] = add[cnt] = 0;
  sz[cnt] = mul[cnt] = 1;
  val[cnt] = sum[cnt] = a;
  return cnt;
}
void pull(int u) {
  sum[u] = (sum[ch[0][u]] + sum[ch[1][u]] + val[u]) % mod;
  sz[u] = sz[ch[0][u]] + sz[ch[1][u]] + 1;
}
void apply(int u, ll a, ll b) {
  val[u] = (val[u] * a + b) % mod;
  sum[u] = (sum[u] * a + b * sz[u]) % mod;
  mul[u] = (mul[u] * a) % mod;
  add[u] = (add[u] * a + b) % mod;
}
void push(int u) {
  if(flip[u]) swap(ch[0][u], ch[1][u]);
  if(ch[0][u]) {
    apply(ch[0][u], mul[u], add[u]);
    flip[ch[0][u]] ^= flip[u];
  }
  if(ch[1][u]) {
    apply(ch[1][u], mul[u], add[u]);
    flip[ch[1][u]] ^= flip[u];
  }
  mul[u] = 1, add[u] = flip[u] = 0;
}
int dir(int u) {
  if(p[u] == 0) return -1;
  return (ch[1][p[u]] == u);
}
void rotate(int u) {
  int du = dir(u);
  if(du == -1) return;
  int par = p[u];
  if(p[par]) ch[dir(par)][p[par]] = u;
  p[u] = p[par], p[par] = u;
  if(ch[!du][u]) p[ch[!du][u]] = par;
  ch[du][par] = ch[!du][u], ch[!du][u] = par;
  pull(par), pull(u);
}
void splay(int u) {
  while(dir(u) != -1) {
    if(dir(p[u]) != -1) {
      if(dir(u) == dir(p[u])) rotate(p[u]);
      else rotate(u);
    }
    rotate(u);
  }
}
void find(int u, int i, int &x) {
  push(u);
  ll a = sz[ch[0][u]];
  while(a != i) {
    u = ch[a < i][u];
    if(a < i) i = i - a - 1;
    if(u) push(u);
    a = sz[ch[0][u]];
  }
  splay(u);
  x = u;
}
void split(int u, int i, int &x, int &y) {
  x = 0, y = 0;
  if(i < 0) {
    y = u;
    return;
  }
  find(u, i, x);
  if(!ch[1][x]) return;
  y = ch[1][x];
  ch[1][x] = p[y] = 0;
  pull(x);
}
void query(int u, int l, int r, int &x, int &y, int &z) {
  split(u, r - 1, y, z);
  split(y, l - 1, x, y);
}
void merge(int u, int v, int &x) {
  if(!u || !v) {
    x = u + v;
    return;
  }
  find(u, sz[u] - 1, x);
  ch[1][x] = v, p[v] = x;
  pull(x);
}
void insert(int u, int i, ll val, int &x) {
  if(i == sz[u]) {
    merge(u, node(val), x);
    return;
  }
  int y;
  split(u, i - 1, x, y);
  merge(x, node(val), x), merge(x, y, x);
}
void del(int u, int i, int &x) {
  int y, z;
  query(u, i, i + 1, x, y, z);
  merge(x, z, x);
}
void print(int u) {
  if(!u) return;
  push(u);
  print(ch[0][u]);
  cout << val[u] << " ";
  print(ch[1][u]);
}

signed main() {
  ios::sync_with_stdio(0);
  cin.tie(0);
  cnt = 0;
  ch[0][0] = ch[1][0] = p[0] = flip[0] = mul[0] = add[0] = val[0] = sum[0] = sz[0] = 0;
  int n, q, tree = 0;
  cin >> n >> q;
  ll a;
  for(ll i = 0; i < n; i++) {
    cin >> a;
    merge(tree, node(a), tree);
  }
  int type, j, l, r;
  ll b, c;
  for(int i = 0; i < q; i++) {
    cin >> type;
    if(type == 0) {
      cin >> j >> a;
      insert(tree, j, a, tree);
    } else if(type == 1) {
      cin >> j;
      del(tree, j, tree);
    } else if(type == 2) {
      cin >> l >> r;
      int x, y, z;
      query(tree, l, r, x, y, z);
      flip[y] ^= 1;
      merge(x, y, tree), merge(tree, z, tree);
    } else if(type == 3) {
      cin >> l >> r >> b >> c;
      int x, y, z;
      query(tree, l, r, x, y, z);
      apply(y, b, c);
      merge(x, y, tree), merge(tree, z, tree);
    } else {
      cin >> l >> r;
      int x, y, z;
      query(tree, l, r, x, y, z);
      cout << sum[y] << "\n";
      merge(x, y, tree), merge(tree, z, tree);
    }
  }
}