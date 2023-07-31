struct BitTrie {
    vector<array<int, 2>> bit_trie;  // node 0 is root

    BitTrie() {
        bit_trie.resize(1); bit_trie[0][0] = 0; bit_trie[0][1] = 0;
    }

    void insert(int x) {
        int u = 0;

        for (int i = 7; i >= 0; i--) {
            int b = x >> i & 1;

            if (!bit_trie[u][b]) {
                // create new node
                int newId = (int) bit_trie.size();
                bit_trie.emplace_back();
                bit_trie[u][b] = newId;
            }

            u = bit_trie[u][b];
        }
    }

    // in this case, the query is the maximum XOR
    int query(int x) { // x is what is the query
        int u = 0; int ans = 0;
        for (int i = 7; i >= 0; i--) {
            // try to go down subtree with same bit first
            int b = (x >> i & 1) ^ 1;
            if (bit_trie[u][b]) {
                // opposite bit exists, so we can have 1 in xor
                ans |= 1 << i;
            } else {
                // go down opposite subtree
                b ^= 1;
            }

            u = bit_trie[u][b]; // go down
        }

        return ans;
    }
};
