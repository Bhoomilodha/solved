class Solution {
public:
    int maxBuilding(int n, vector<vector<int>>& restrictions) {
        restrictions.push_back({1, 0});

        sort(restrictions.begin(), restrictions.end());

        // Left to right: make each restriction consistent
        // with the previous restriction.
        for (int i = 1; i < restrictions.size(); i++) {
            restrictions[i][1] = min(
                restrictions[i][1],
                restrictions[i - 1][1] + restrictions[i][0] - restrictions[i - 1][0]
            );
        }

        // Right to left
        for (int i = restrictions.size() - 2; i >= 0; i--) {
            restrictions[i][1] = min(
                restrictions[i][1],
                restrictions[i + 1][1] + restrictions[i + 1][0] - restrictions[i][0]
            );
        }

        long long ans = 0;

        // Find maximum possible height between consecutive restrictions.
        for (int i = 1; i < restrictions.size(); i++) {
            long long x1 = restrictions[i - 1][0];
            long long h1 = restrictions[i - 1][1];
            long long x2 = restrictions[i][0];
            long long h2 = restrictions[i][1];

            long long distance = x2 - x1;

            // Maximum peak between two endpoints with slope <= 1.
            ans = max(ans, (h1 + h2 + distance) / 2);
        }

        // Buildings after the last restriction can keep increasing.
        ans = max(
            ans,
            (long long)restrictions.back()[1] +
            (n - restrictions.back()[0])
        );

        return (int)ans;
    }
};