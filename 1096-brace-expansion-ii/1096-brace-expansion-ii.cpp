class Solution {
public:
    string s;
    int i = 0;

    set<string> expression() {
        set<string> ans = term();

        while (i < s.size() && s[i] == ',') {
            i++;
            set<string> temp = term();
            ans.insert(temp.begin(), temp.end());
        }

        return ans;
    }

    set<string> term() {
        set<string> ans = {""};

        while (i < s.size() && s[i] != '}' && s[i] != ',') {
            set<string> cur;

            if (s[i] == '{') {
                i++;
                cur = expression();
                i++;
            }
            else {
                cur.insert(string(1, s[i]));
                i++;
            }

            set<string> temp;

            for (string a : ans) {
                for (string b : cur) {
                    temp.insert(a + b);
                }
            }

            ans = temp;
        }

        return ans;
    }

    vector<string> braceExpansionII(string expression) {
        s = expression;
        i = 0;

        set<string> ans = this->expression();

        return vector<string>(ans.begin(), ans.end());
    }
};