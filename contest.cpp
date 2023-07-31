#include <bits/stdc++.h>
using namespace std;

class def {

	//consts
	#define INTM (long long)0x3f3f3f3f3f
	#define INTN (int)1e5 + 10
	
	//breaks & continues
	#define break break;
	#define con continue;

	//misc
	#define all(x) x.begin(),x.end()
	#define ll long long
	#define lb long double
	#define sz(x) ((int)x.size())
	
	//1d vectors
	#define vll vector<ll>
	#define vi vector<int>
	#define vb vector<bool>
	#define v(x) vector<x>
	
	//2d vectors
	#define vvb vector<vector<bool>>
	#define vv(x) vector<vector<x>>
	#define vvi vector<vector<int>>
	#define vvll vector<vector<ll>>
	
	//pairs
	#define p(x, y) pair<x, y>
	#define pii pair<int,int>
	#define pll pair<ll,ll>

	//loops
	#define F0R(i, k) for (int i = 0; i <(k); i ++) 
	#define loopT(t) IN(t) while(t--)
	#define FOR(i, x, y) for (int i = x; i < y; i ++)

	//input
	#define IN(i) cin >> i;
	#define INV(i, n) for (int j = 0; j < n; j ++) {IN(i[j])} 
	#define INV2(v, n, m) for (int i = 0; i < n; i ++) {INV(v[i],m)}

	//output
	#define OUT(i) cout << i << endl;
	#define out(i) cout << i << " ";
	#define OUTV(v) for(auto i : v) {cout << i << " ";}
	#define OUTV2(x) for (auto v : x) {OUTV(v) OUT("")}

	//configs
	#define SETIO ios::sync_with_stdio(false);cin.tie(0);
};
void solve() {

}

signed main(){
    int t;
    cin >> t;
    while(t--)solve();
    return 0;
}
