// Lazy Prop Segment Tree
struct segTree {
    struct node {int l, r; long long v, lazy;};
    vector<node> st; int size;
    segTree(int n, int* init = {}) {
        long long nV;
        size = 1 << ceil(log2(n));
        st = vector<node> (size*2);
        for (int i = size; i < size*2; i++) {
            if (i < size+n && init != NULL) {
                st[i] = {i, i, init[i-size+1], 0};
            } else st[i] = {i, i, 0, 0};
        }
        for (int i = size-1; i >= 1; i--) {
            nV = st[i*2].v+st[i*2+1].v;
            st[i] = {st[i*2].l, st[i*2+1].r, nV, 0};
        }
    }
    void lazyProp(int node, long long v) {
        if (node < size) {
            st[node*2].lazy += v;
            st[node*2+1].lazy += v;
        }
        st[node].v += v*(st[node].r-st[node].l+1);
        st[node].lazy = 0;
    }
    void update(int v, int s, int e = -1, int node = 1) {
        if (e == -1) e = s;
        if (node == 1) s += size-1, e += size-1;
        if (st[node].lazy > 0) lazyProp(node, st[node].lazy);
        if (st[node].l >= s && st[node].r <= e) lazyProp(node, v);
        else if (!(st[node].l > e || st[node].r < s)) {
            update(v, s, e, node*2);
            update(v, s, e, node*2+1);
            st[node].v = st[node*2].v+st[node*2+1].v;
        }
    }
    long long query(int s, int e = -1, int node = 1) {
        long long ans;
        if (e == -1) e = s;
        if (node == 1) s += size-1, e += size-1;
        if (st[node].lazy > 0) lazyProp(node, st[node].lazy);
        if (st[node].l >= s && st[node].r <= e) return st[node].v;
        else if (st[node].l > e || st[node].r < s) return 0;
        else {
            ans = query(s, e, node*2) + query(s, e, node*2+1);
            st[node].v = st[node*2].v+st[node*2+1].v;
            return ans;
        }
    }
};


// Vanilla Segment Tree
struct segTree {
    struct node {int l, r; long long v;};
    vector<node> st; int size;
    segTree(int n) {
        size = 1 << ceil(log2(n)), st = vector<node> (size*2);
        for (int i = size*2-1; i >= 1; i--) {
            if (i >= size) st[i] = {i, i, 0};
            else st[i] = {st[i*2].l, st[i*2+1].r, 0};
        }
    }
    void update(int node, int change) {
        node += size; st[node].v = change;
        while (node > 1) {
            node /= 2;
            st[node].v = st[node*2].v+st[node*2+1].v;
        }
    }
    long long query(int s, int e, int node = 1) {
        if (node == 1) s += size, e += size;
        if (st[node].l >= s && st[node].r <= e) return st[node].v;
        else if (st[node].l > e || st[node].r < s) return 0;
        else return query(s, e, node*2) + query(s, e, node*2+1);
    }
};
