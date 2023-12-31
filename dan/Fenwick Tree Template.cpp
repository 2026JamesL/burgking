// One Indexed
struct BITree {
    int size; vector<long long> ranges;
    BITree (int n, int *arr = {}) {
        size = n; ranges = vector<long long> (size+1, 0);
        if (arr == NULL) return;
        for (int i = 1; i <= size; i++) {
            ranges[i] += arr[i];
            if (i + (i&-i) <= size) {
                ranges[i + i&-i] += ranges[i];
            }
        }
    }
    long long pSum(int a) {
        long long sum = 0;
        while (a > 0) sum += ranges[a], a -= a&-a;
        return sum;
    }
    long long query(int a, int b) {return pSum(b) - pSum(a-1);}
    void update(int a, int change) {
        while (a <= size) ranges[a] += change, a += a&-a;
    }
};
