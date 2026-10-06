class Solution {
public:
    int minMoves(vector<int>& nums, int limit) {
        int n = nums.size();

        // Difference array
        vector<int> diff(2 * limit + 2, 0);

        for (int i = 0; i < n / 2; i++) {
            int a = nums[i];
            int b = nums[n - 1 - i];

            int low = min(a, b);
            int high = max(a, b);

            // 2 moves initially
            diff[2] += 2;
            diff[2 * limit + 1] -= 2;

            // From low + 1 to high + limit -> at most 1 move
            diff[low + 1] -= 1;
            diff[high + limit + 1] += 1;

            // Exact sum already needs 0 moves
            diff[low + high] -= 1;
            diff[low + high + 1] += 1;
        }

        int ans = n;
        int moves = 0;

        for (int sum = 2; sum <= 2 * limit; sum++) {
            moves += diff[sum];
            ans = min(ans, moves);
        }

        return ans;
    }
};