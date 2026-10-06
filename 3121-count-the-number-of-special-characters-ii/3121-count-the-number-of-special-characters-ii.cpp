class Solution {
public:
    int numberOfSpecialChars(string word) {
        vector<int> firstUpper(26, -1);
        vector<int> lastLower(26, -1);

        for (int i = 0; i < word.size(); i++) {
            if (islower(word[i])) {
                lastLower[word[i] - 'a'] = i;
            } else {
                if (firstUpper[word[i] - 'A'] == -1)
                    firstUpper[word[i] - 'A'] = i;
            }
        }

        int ans = 0;

        for (int i = 0; i < 26; i++) {
            if (lastLower[i] != -1 && firstUpper[i] != -1 &&
                lastLower[i] < firstUpper[i]) {
                ans++;
            }
        }

        return ans;
    }
};