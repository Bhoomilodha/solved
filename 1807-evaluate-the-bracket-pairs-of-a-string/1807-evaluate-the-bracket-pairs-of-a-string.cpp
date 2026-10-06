class Solution {
public:
    string evaluate(string s, vector<vector<string>>& knowledge) {
        unordered_map<string, string> mp;

        // Store key-value pairs
        for (auto &x : knowledge) {
            mp[x[0]] = x[1];
        }

        string ans;

        for (int i = 0; i < s.size(); i++) {
            if (s[i] == '(') {
                string key;
                i++;

                // Get key until ')'
                while (s[i] != ')') {
                    key += s[i];
                    i++;
                }

                // Replace with value or '?'
                if (mp.find(key) != mp.end()) {
                    ans += mp[key];
                } else {
                    ans += "?";
                }
            } 
            else {
                ans += s[i];
            }
        }

        return ans;
    }
};