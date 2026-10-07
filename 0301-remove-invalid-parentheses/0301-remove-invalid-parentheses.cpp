class Solution {
public:
    vector<string> removeInvalidParentheses(string s) {
        vector<string> ans;
        unordered_set<string> visited;
        queue<string> q;

        q.push(s);
        visited.insert(s);

        bool found = false;

        while (!q.empty()) {
            string cur = q.front();
            q.pop();

            // Check if current string is valid
            int balance = 0;
            bool valid = true;

            for (char c : cur) {
                if (c == '(') {
                    balance++;
                }
                else if (c == ')') {
                    balance--;

                    if (balance < 0) {
                        valid = false;
                        break;
                    }
                }
            }

            if (balance != 0) {
                valid = false;
            }

            if (valid) {
                ans.push_back(cur);
                found = true;
            }

            // If we already found valid strings,
            // don't remove any more characters.
            if (found) {
                continue;
            }

            // Generate strings by removing one parenthesis
            for (int i = 0; i < cur.size(); i++) {
                if (cur[i] != '(' && cur[i] != ')') {
                    continue;
                }

                string next = cur.substr(0, i) + cur.substr(i + 1);

                if (visited.find(next) == visited.end()) {
                    visited.insert(next);
                    q.push(next);
                }
            }
        }

        return ans;
    }
};