class Solution {
public:
    struct Node {
        int pref[5];
        int prod;

        Node() {
            for (int i = 0; i < 5; i++) pref[i] = 0;
            prod = 1;
        }
    };

    int k;
    vector<Node> seg;

    Node merge(const Node &a, const Node &b) {
        Node res;

        res.prod = (a.prod * b.prod) % k;

        for (int i = 0; i < k; i++) {
            res.pref[i] = a.pref[i];
        }

        for (int i = 0; i < k; i++) {
            int r = (a.prod * i) % k;
            res.pref[r] += b.pref[i];
        }

        return res;
    }

    void build(int idx, int l, int r, vector<int>& nums) {
        if (l == r) {
            int rmd = nums[l] % k;
            seg[idx].pref[rmd] = 1;
            seg[idx].prod = rmd;
            return;
        }

        int mid = (l + r) >> 1;

        build(idx << 1, l, mid, nums);
        build(idx << 1 | 1, mid + 1, r, nums);

        seg[idx] = merge(seg[idx << 1], seg[idx << 1 | 1]);
    }

    void update(int idx, int l, int r, int pos, int val) {
        if (l == r) {
            for (int i = 0; i < k; i++) {
                seg[idx].pref[i] = 0;
            }

            int rmd = val % k;
            seg[idx].pref[rmd] = 1;
            seg[idx].prod = rmd;
            return;
        }

        int mid = (l + r) >> 1;

        if (pos <= mid)
            update(idx << 1, l, mid, pos, val);
        else
            update(idx << 1 | 1, mid + 1, r, pos, val);

        seg[idx] = merge(seg[idx << 1], seg[idx << 1 | 1]);
    }

    Node query(int idx, int l, int r, int ql, int qr) {
        if (ql <= l && r <= qr)
            return seg[idx];

        int mid = (l + r) >> 1;

        if (qr <= mid)
            return query(idx << 1, l, mid, ql, qr);

        if (ql > mid)
            return query(idx << 1 | 1, mid + 1, r, ql, qr);

        Node left = query(idx << 1, l, mid, ql, qr);
        Node right = query(idx << 1 | 1, mid + 1, r, ql, qr);

        return merge(left, right);
    }

    vector<int> resultArray(vector<int>& nums, int K, vector<vector<int>>& queries) {
        k = K;
        int n = nums.size();

        seg.resize(4 * n + 5);

        build(1, 0, n - 1, nums);

        vector<int> ans;
        ans.reserve(queries.size());

        for (auto &q : queries) {
            update(1, 0, n - 1, q[0], q[1]);

            Node res = query(1, 0, n - 1, q[2], n - 1);

            ans.push_back(res.pref[q[3]]);
        }

        return ans;
    }
};