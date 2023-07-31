struct UF {
    vector<int> arr; vector<int> sz;

    int N;

    UF(int n) {
        N = n;

        arr.resize(n); sz.resize(n);

        for (int i = 0; i < n; i++) {
            arr[i] = i; sz[i] = 1;
        }
    }

    void resize(int n) {
        N = n;
        
        arr.resize(N); sz.resize(N);
    }

    bool onion(int p, int q) {
        int i = root(p); int j = root(q);

        if (i == j) return false;

        if (sz[i] < sz[j]) {
            arr[i] = j; sz[j] += sz[i];
        } else {
            arr[j] = i; sz[i] += sz[j];
        }

        return true;
    }

    bool onion(pair<int, int> pos) {
        return onion(pos.first, pos.second);
    }

    bool connected(int p, int q) {
        return root(p) == root(q);
    }

    int root(int i) {
        while (i != arr[i]) {
            arr[i] = arr[arr[i]]; i = arr[i];
        }

        return i;
    }
}; 
