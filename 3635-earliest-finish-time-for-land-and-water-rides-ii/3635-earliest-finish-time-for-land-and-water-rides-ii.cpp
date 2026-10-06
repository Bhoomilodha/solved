class Solution {
public:
    int earliestFinishTime(vector<int>& landStartTime, vector<int>& landDuration,
                           vector<int>& waterStartTime, vector<int>& waterDuration) {
        
        auto solve = [&](vector<int>& s1, vector<int>& d1,
                         vector<int>& s2, vector<int>& d2) {
            
            int m = s2.size();

            vector<pair<int, int>> rides;
            for (int i = 0; i < m; i++) {
                rides.push_back({s2[i], d2[i]});
            }

            sort(rides.begin(), rides.end());

            // prefixMinDur[i] = minimum duration among rides[0..i]
            vector<int> prefixMinDur(m);
            prefixMinDur[0] = rides[0].second;

            for (int i = 1; i < m; i++) {
                prefixMinDur[i] = min(prefixMinDur[i - 1], rides[i].second);
            }

            // suffixMinFinish[i] = minimum (start + duration) among rides[i..m-1]
            vector<int> suffixMinFinish(m);
            suffixMinFinish[m - 1] = rides[m - 1].first + rides[m - 1].second;

            for (int i = m - 2; i >= 0; i--) {
                suffixMinFinish[i] = min(
                    suffixMinFinish[i + 1],
                    rides[i].first + rides[i].second
                );
            }

            int ans = INT_MAX;

            for (int i = 0; i < s1.size(); i++) {
                int finish1 = s1[i] + d1[i];

                // Find first ride in category 2 that opens after finish1
                int pos = upper_bound(
                    rides.begin(), rides.end(),
                    make_pair(finish1, INT_MAX)
                ) - rides.begin();

                // Ride 2 is already open
                if (pos > 0) {
                    ans = min(ans, finish1 + prefixMinDur[pos - 1]);
                }

                // Ride 2 opens after ride 1 finishes
                if (pos < m) {
                    ans = min(ans, suffixMinFinish[pos]);
                }
            }

            return ans;
        };

        // Land -> Water
        int ans1 = solve(
            landStartTime, landDuration,
            waterStartTime, waterDuration
        );

        // Water -> Land
        int ans2 = solve(
            waterStartTime, waterDuration,
            landStartTime, landDuration
        );

        return min(ans1, ans2);
    }
};