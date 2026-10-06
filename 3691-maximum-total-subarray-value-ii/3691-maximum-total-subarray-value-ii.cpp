class Solution {
public:
    int n, LOG;
    vector<vector<int>> stMax, stMin;
    vector<int> lg;

    void build(vector<int>& nums) {
        n = nums.size();
        LOG = 32 - __builtin_clz(n);

        stMax.assign(LOG, vector<int>(n));
        stMin.assign(LOG, vector<int>(n));
        lg.assign(n + 1, 0);

        for (int i = 2; i <= n; i++)
            lg[i] = lg[i / 2] + 1;

        for (int i = 0; i < n; i++) {
            stMax[0][i] = nums[i];
            stMin[0][i] = nums[i];
        }

        for (int j = 1; j < LOG; j++) {
            for (int i = 0; i + (1 << j) <= n; i++) {
                stMax[j][i] = max(
                    stMax[j - 1][i],
                    stMax[j - 1][i + (1 << (j - 1))]
                );

                stMin[j][i] = min(
                    stMin[j - 1][i],
                    stMin[j - 1][i + (1 << (j - 1))]
                );
            }
        }
    }

    int getValue(int l, int r) {
        int len = r - l + 1;
        int j = lg[len];

        int mx = max(
            stMax[j][l],
            stMax[j][r - (1 << j) + 1]
        );

        int mn = min(
            stMin[j][l],
            stMin[j][r - (1 << j) + 1]
        );

        return mx - mn;
    }

    long long maxTotalValue(vector<int>& nums, int k) {
        build(nums);

        // {value, left, right}
        priority_queue<
            tuple<int, int, int>
        > pq;

        // For every fixed left, the value increases as right increases.
        // So initially take the largest right endpoint.
        for (int l = 0; l < n; l++) {
            pq.push({getValue(l, n - 1), l, n - 1});
        }

        long long ans = 0;

        while (k--) {
            auto [value, l, r] = pq.top();
            pq.pop();

            ans += value;

            // Next best subarray for the same left endpoint.
            if (r > l) {
                pq.push({
                    getValue(l, r - 1),
                    l,
                    r - 1
                });
            }
        }

        return ans;
    }
};