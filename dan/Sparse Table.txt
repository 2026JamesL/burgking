struct sparseTable {
    vector<vector<int>> st; int lg; string h;
    int MP(int a) {
        int i = 0;
        while ((1 << ++i) <= a);
        return i-1;
    }
    sparseTable(int n, int *init, string t) {
        int term, cP; h = t, lg = 1<<MP(n);
        st = vector<vector<int>> (lg+1, vector<int> (n));
        for (int i = 0; i < n; i++) st[0][i] = init[i];
        for (int i = 1; i <= lg; i++) {
            term = n-(1<<i)+1, cP = 1<<(i-1);
            for (int j = 0; j < term; j++) {
                if (h == "min") {
                    st[i][j] = min(st[i-1][j], st[i-1][j+cP]);
                } else st[i][j] = max(st[i-1][j], st[i-1][j+cP]);
            }
        }
    }
    int query(int l, int r) {
        if (l > r) swap(l, r);
        int fit = MP(r-l+1);
        if (h == "min") {
            return min(st[fit][l], st[fit][r-(1<<fit)+1]);
        } else return max(st[fit][l], st[fit][r-(1<<fit)+1]);
    }
};
