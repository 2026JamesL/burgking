#include <bits/stdc++.h>
#define f first
#define s second
#define mp make_pair
using namespace std;
typedef long long ll;
const ll mod = 1e9 + 7;
// Cope Counter = 2147483647

int n;
vector<int> adj[30001];

template<class T, int N> struct segTree {
  const T aeiou = -1e9;
  T cmb(T a, T b) {
    return max(a, b);
  }
  T seg[2 * N];
  segTree() {
    for(int i = 0; i < 2 * N; i++) seg[i] = aeiou;
  }
  void update(int i, T val) {
    i += n;
    seg[i] = val;
    while(i > 1) {
      i /= 2;
      seg[i] = cmb(seg[2 * i], seg[2 * i + 1]);
    }
  }
  T query(int l, int r) {
    int a = aeiou, b = aeiou;
    l += n, r += n + 1;
    while(l < r) {
      if(l & 1) a = cmb(a, seg[l++]);
      if(r & 1) b = cmb(b, seg[--r]);
      l /= 2, r /= 2;
    }
    return cmb(a, b);
  }
};

template<class T, int N> struct hld {
  int cur = 0;
  int p[N], d[N], heavy[N], head[N], idx[N];
  segTree<T, N> seg;
  hld() {
    cur = 0;
    for(int i = 0; i < n; i++) {
      p[i] = d[i] = head[i] = idx[i] = 0;
      heavy[i] = -1;
    }
    dfs(0);
    decomp(0, 0);
  }
  int dfs(int i) {
    int sz = 1, maxsz = 0;
    for(int j : adj[i]) {
      if(j != p[i]) {
        p[j] = i, d[j] = d[i] + 1;
        int cursz = dfs(j);
        sz += cursz;
        if(cursz > maxsz)
          heavy[i] = j, maxsz = cursz;
      }
    }
    return sz;
  }
  void decomp(int i, int h) {
    idx[i] = cur++, head[i] = h;
    if(heavy[i] != -1)
      decomp(heavy[i], h);
    for(int j : adj[i]) {
      if(j != heavy[i] && j != p[i])
        decomp(j, j);
    }
  }
  void update(int i, T val) {
    seg.update(idx[i], val);
  }
  T query(int u, int v) {
    T ans = 0;
    while(head[u] != head[v]) {
      if(d[head[u]] < d[head[v]])
        swap(u, v);
      ans = max(ans, seg.query(idx[head[u]], idx[u]));
      u = p[head[u]];
    }
    if(d[u] > d[v])
      swap(u, v);
    ans = max(ans, seg.query(idx[u], idx[v]));
    return ans;
  }
};