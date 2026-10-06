class Solution {
public:
    vector<bool> getResults(vector<vector<int>>& queries) {
        const int MAXX = 50000;

        // Fenwick tree stores maximum free gap ending at each position
        vector<int> bit(MAXX + 2, 0);
        set<int> obstacles;
        obstacles.insert(0);

        auto update = [&](int idx, int val) {
            for (; idx <= MAXX + 1; idx += idx & -idx)
                bit[idx] = max(bit[idx], val);
        };

        auto query = [&](int idx) {
            int res = 0;
            for (; idx > 0; idx -= idx & -idx)
                res = max(res, bit[idx]);
            return res;
        };

        // We need offline processing because inserting an obstacle
        // changes the gap before the next obstacle.
        vector<int> coords;
        for (auto &q : queries) {
            if (q[0] == 1)
                coords.push_back(q[1]);
        }

        sort(coords.begin(), coords.end());
        coords.erase(unique(coords.begin(), coords.end()), coords.end());

        // Segment tree storing maximum gap for obstacle intervals.
        int m = coords.size();
        vector<int> seg(4 * (m + 5), 0);

        auto updateSeg = [&](auto&& self, int node, int l, int r,
                             int pos, int val) -> void {
            if (l == r) {
                seg[node] = val;
                return;
            }

            int mid = (l + r) / 2;

            if (pos <= mid)
                self(self, node * 2, l, mid, pos, val);
            else
                self(self, node * 2 + 1, mid + 1, r, pos, val);

            seg[node] = max(seg[node * 2], seg[node * 2 + 1]);
        };

        auto querySeg = [&](auto&& self, int node, int l, int r,
                            int ql, int qr) -> int {
            if (ql > r || qr < l)
                return 0;

            if (ql <= l && r <= qr)
                return seg[node];

            int mid = (l + r) / 2;

            return max(
                self(self, node * 2, l, mid, ql, qr),
                self(self, node * 2 + 1, mid + 1, r, ql, qr)
            );
        };

        // Easier and reliable approach: ordered set + segment tree
        // over all possible positions.
        set<int> s;
        s.insert(0);

        vector<int> gaps(MAXX + 1, 0);
        gaps[0] = 0;

        // Segment tree over positions: gap ending at position x
        int N = MAXX + 1;
        vector<int> tree(4 * N);

        auto setValue = [&](auto&& self, int node, int l, int r,
                            int pos, int val) -> void {
            if (l == r) {
                tree[node] = val;
                return;
            }

            int mid = (l + r) / 2;

            if (pos <= mid)
                self(self, node * 2, l, mid, pos, val);
            else
                self(self, node * 2 + 1, mid + 1, r, pos, val);

            tree[node] = max(tree[node * 2], tree[node * 2 + 1]);
        };

        auto getMax = [&](auto&& self, int node, int l, int r,
                          int ql, int qr) -> int {
            if (ql > r || qr < l)
                return 0;

            if (ql <= l && r <= qr)
                return tree[node];

            int mid = (l + r) / 2;

            return max(
                self(self, node * 2, l, mid, ql, qr),
                self(self, node * 2 + 1, mid + 1, r, ql, qr)
            );
        };

        vector<bool> ans;

        for (auto &q : queries) {
            int type = q[0];
            int x = q[1];

            if (type == 1) {
                auto it = s.lower_bound(x);
                int right = (it == s.end() ? x : *it);
                int left = *prev(it == s.end() ? s.end() : next(it));

                // Find actual predecessor safely
                auto nxt = s.lower_bound(x);
                int r = (nxt == s.end() ? MAXX + 1 : *nxt);
                int l = *prev(nxt);

                s.insert(x);

                // Gap ending at x
                setValue(setValue, 1, 0, MAXX, x, x - l);

                // Gap ending at old right obstacle
                if (r <= MAXX)
                    setValue(setValue, 1, 0, MAXX, r, r - x);
            } 
            else {
                int sz = q[2];

                // Find the last obstacle <= x
                auto it = s.upper_bound(x);
                --it;
                int last = *it;

                // Any complete gap before the last obstacle
                int best = getMax(getMax, 1, 0, MAXX, 0, last);

                // Gap from the last obstacle to x
                best = max(best, x - last);

                ans.push_back(best >= sz);
            }
        }

        return ans;
    }
};