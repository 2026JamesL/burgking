#include <bits/stdc++.h>
using namespace std;
 
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); string s, pat; cin >> s >> pat;
    int count = 0, t = 0, p = 0;
    int kmp[pat.size()]; kmp[0] = 0;
    for (int i = 1; i < pat.size(); i++) {
        if (pat[kmp[i-1]] == pat[i]) kmp[i] = kmp[i-1]+1;
        else if (kmp[i-1] > 0) {
            kmp[i] = kmp[kmp[i-1]-1];
            if (pat[i] == pat[kmp[i]]) kmp[i]++;
            else kmp[i] = 0;
        } else kmp[i] = 0;
    }
    while (t < s.size()) {
        if (s[t] == pat[p]) {
            t++, p++;
            if (p == pat.size()) count++, p = kmp[p-1];
        } else {
            p == 0 ? t++, p++ : p = kmp[p-1];
        }
    }
    cout << count;
}
