class Solution {
public:
    int maxJumps(vector<int>& arr, int d) {
        int n = arr.size();
        vector<int> dp(n, 1);
        
        vector<int> indices(n);
        iota(indices.begin(), indices.end(), 0);
        
        sort(indices.begin(), indices.end(), [&](int a, int b) {
            return arr[a] < arr[b];
        });
        
        int ans = 1;
        
        for (int i : indices) {
            for (int j = i - 1; j >= max(0, i - d); j--) {
                if (arr[j] >= arr[i])
                    break;
                
                dp[i] = max(dp[i], dp[j] + 1);
            }
            
            for (int j = i + 1; j <= min(n - 1, i + d); j++) {
                if (arr[j] >= arr[i])
                    break;
                
                dp[i] = max(dp[i], dp[j] + 1);
            }
            
            ans = max(ans, dp[i]);
        }
        
        return ans;
    }
};