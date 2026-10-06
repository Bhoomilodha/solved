class Solution {
public:
    struct Node {
        long long ways = 0;
        long long sum = 0;
    };

    long long solve(long long n) {
        if (n <= 0) return 0;

        string s = to_string(n);
        int len = s.size();

        // dp[pos][tight][startedDigits][prevPrev][prev]
        Node dp[20][2][3][10][10] = {};

        dp[0][1][0][0][0].ways = 1;

        for (int pos = 0; pos < len; pos++) {
            for (int tight = 0; tight <= 1; tight++) {
                for (int cnt = 0; cnt <= 2; cnt++) {
                    for (int a = 0; a < 10; a++) {
                        for (int b = 0; b < 10; b++) {

                            Node cur = dp[pos][tight][cnt][a][b];
                            if (cur.ways == 0) continue;

                            int limit = tight ? s[pos] - '0' : 9;

                            for (int d = 0; d <= limit; d++) {
                                int ntight =
                                    tight && (d == s[pos] - '0');

                                // Still skipping leading zeros
                                if (cnt == 0 && d == 0) {
                                    dp[pos + 1][ntight][0][0][0].ways
                                        += cur.ways;
                                    dp[pos + 1][ntight][0][0][0].sum
                                        += cur.sum;
                                }

                                // First digit
                                else if (cnt == 0) {
                                    dp[pos + 1][ntight][1][0][d].ways
                                        += cur.ways;
                                    dp[pos + 1][ntight][1][0][d].sum
                                        += cur.sum;
                                }

                                // Second digit
                                else if (cnt == 1) {
                                    dp[pos + 1][ntight][2][b][d].ways
                                        += cur.ways;
                                    dp[pos + 1][ntight][2][b][d].sum
                                        += cur.sum;
                                }

                                // Third or later digit
                                else {
                                    long long add = 0;

                                    // b is the middle digit
                                    if ((b > a && b > d) ||
                                        (b < a && b < d)) {
                                        add = 1;
                                    }

                                    dp[pos + 1][ntight][2][b][d].ways
                                        += cur.ways;

                                    dp[pos + 1][ntight][2][b][d].sum
                                        += cur.sum + cur.ways * add;
                                }
                            }
                        }
                    }
                }
            }
        }

        long long ans = 0;

        for (int tight = 0; tight <= 1; tight++) {
            for (int a = 0; a < 10; a++) {
                for (int b = 0; b < 10; b++) {
                    ans += dp[len][tight][2][a][b].sum;
                }
            }
        }

        return ans;
    }

    long long totalWaviness(long long num1, long long num2) {
        return solve(num2) - solve(num1 - 1);
    }
};