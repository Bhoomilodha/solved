class Solution {
public:
    bool canReach(string s, int minJump, int maxJump) {
        int n = s.size();
        vector<bool> dp(n, false);
        dp[0] = true;

        int reachable = 0;

        for (int i = 1; i < n; i++) {
            int add = i - minJump;
            if (add >= 0 && dp[add])
                reachable++;

            int remove = i - maxJump - 1;
            if (remove >= 0 && dp[remove])
                reachable--;

            if (s[i] == '0' && reachable > 0)
                dp[i] = true;
        }

        return dp[n - 1];
    }
};