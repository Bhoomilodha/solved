class Solution {
public:
    vector<int> stringIndices(vector<string>& wordsContainer, vector<string>& wordsQuery) {
        struct Node {
            int child[26];
            int index = -1;

            Node() {
                fill(child, child + 26, -1);
            }
        };

        vector<Node> trie(1);

        // Find shortest word in container for default answer
        int defaultIndex = 0;
        for (int i = 1; i < wordsContainer.size(); i++) {
            if (wordsContainer[i].size() < wordsContainer[defaultIndex].size()) {
                defaultIndex = i;
            }
        }

        // Insert words in reverse (suffix trie)
        for (int i = 0; i < wordsContainer.size(); i++) {
            string &s = wordsContainer[i];
            int node = 0;

            // Root stores best answer for empty suffix
            if (trie[node].index == -1 ||
                s.size() < wordsContainer[trie[node].index].size()) {
                trie[node].index = i;
            }

            for (int j = s.size() - 1; j >= 0; j--) {
                int c = s[j] - 'a';

                if (trie[node].child[c] == -1) {
                    trie[node].child[c] = trie.size();
                    trie.emplace_back();
                }

                node = trie[node].child[c];

                if (trie[node].index == -1 ||
                    s.size() < wordsContainer[trie[node].index].size()) {
                    trie[node].index = i;
                }
            }
        }

        vector<int> ans;

        for (string &s : wordsQuery) {
            int node = 0;
            int best = trie[0].index;

            for (int j = s.size() - 1; j >= 0; j--) {
                int c = s[j] - 'a';

                if (trie[node].child[c] == -1)
                    break;

                node = trie[node].child[c];
                best = trie[node].index;
            }

            ans.push_back(best);
        }

        return ans;
    }
};