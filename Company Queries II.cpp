#define N 200001
#define LG 20
#include <bits/stdc++.h>
using namespace std;
 
int ST[LG][2*N], c[N], s[N], r[N], o[N];
int n, q, a, b, cnt, l, cL, f;
 
void dfs(int v) {
    int cL = l++, cN = c[v]; r[cL] = v;
    o[v] = cnt, ST[0][cnt++] = cL;
    while (cN) {
        dfs(cN); cN = s[cN];
        ST[0][cnt++] = cL;
    }
}
 
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0); cin >> n >> q; 
    for (int i = 2; i <= n; i++) {
        cin >> a; // i is the child of a
        c[a] ? s[i] = s[c[a]], s[c[a]] = i : c[a] = i;
    }
    dfs(1);
    for (int i = 1; i < LG; i++) {
        for (int j = 0; j < 2*n-(1<<i); j++) {
            ST[i][j] = min(ST[i-1][j], ST[i-1][j+(1<<(i-1))]);
        }
    }
    while (q--) {
        cin >> a >> b; // LCA queries
        a = o[a], b = o[b], f = -1;
        if (a > b) swap(a, b);
        while (1<<(++f+1) <= b-a+1);
        cout << r[min(ST[f][a], ST[f][b-(1<<f)+1])] << "\n";
    }
}