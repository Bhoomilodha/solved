class Solution {
public:
    char processStr(string s, long long k) {
        const long long INF = 1000000000000000LL;

        int n = s.size();
        vector<long long> len(n + 1, 0);

        // Store length after every operation.
        for (int i = 0; i < n; i++) {
            char c = s[i];

            if (c >= 'a' && c <= 'z') {
                len[i + 1] = min(INF, len[i] + 1);
            }
            else if (c == '*') {
                len[i + 1] = max(0LL, len[i] - 1);
            }
            else if (c == '#') {
                len[i + 1] = min(INF, len[i] * 2);
            }
            else { // '%'
                len[i + 1] = len[i];
            }
        }

        if (k >= len[n])
            return '.';

        // Work backwards to find which original character
        // ends up at index k.
        for (int i = n - 1; i >= 0; i--) {
            char c = s[i];
            long long oldLen = len[i];

            if (c >= 'a' && c <= 'z') {
                // This character was appended at index oldLen.
                if (k == oldLen)
                    return c;
            }
            else if (c == '*') {
                // Removing the last character does not change
                // the position of any remaining character.
            }
            else if (c == '#') {
                // result = oldResult + oldResult
                if (oldLen > 0)
                    k %= oldLen;
            }
            else { // '%'
                // result was reversed.
                if (oldLen > 0)
                    k = oldLen - 1 - k;
            }
        }

        return '.';
    }
};