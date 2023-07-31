struct LazyPropSegTree { // zero indexed
    vector<long long> sum, lazy;
    int N;

    LazyPropSegTree(int size) {
        N = size;
        sum.resize(4 * N);
        lazy.resize(4 * N);

        fill(sum.begin(), sum.end(), 0);
        fill(lazy.begin(), lazy.end(), 0);
    }

    void build(int curr_node, int left, int right, const vector<int> &arr) {
        if (left == right) {
            sum[curr_node] = arr[left];
            return;
        }

        int mid = left + (right - left) / 2;

        build(2 * curr_node, left, mid, arr);
        build(2 * curr_node + 1, mid + 1, right, arr);

        sum[curr_node] = sum[2 * curr_node] + sum[2 * curr_node + 1];
    }

    void push(int curr_node, int left, int right) {
        if (lazy[curr_node]) {
            if (left != right) {
                lazy[2 * curr_node] += lazy[curr_node];
                lazy[2 * curr_node + 1] += lazy[curr_node];
            }

            sum[curr_node] += (right - left + 1) * lazy[curr_node];
            lazy[curr_node] = 0;
        }
    }

    // range: [start, end]
    long long query(int curr_node, int left, int right, int start, int end) {
        push(curr_node, left, right);

        if (start > right || end < left) {
            return 0;
        }

        if (start <= left && right <= end) {
            return sum[curr_node];
        }

        int mid = left + (right - left) / 2;

        return query(2 * curr_node, left, mid, start, end) + query(2 * curr_node + 1, mid + 1, right, start, end);
    }

    // add val in range [start, end]
    void update(int curr_node, int left, int right, int start, int end, long long val) {
        push(curr_node, left, right);

        if (start > right || end < left) {
            return;
        }

        if (start <= left && right <= end) {
            lazy[curr_node] += val;
            push(curr_node, left, right);

            return;
        }

        int mid = left + (right - left) / 2;

        update(2 * curr_node, left, mid, start, end, val);
        update(2 * curr_node + 1, mid + 1, right, start, end, val);

        sum[curr_node] = sum[2 * curr_node] + sum[2 * curr_node + 1];
    }
};
