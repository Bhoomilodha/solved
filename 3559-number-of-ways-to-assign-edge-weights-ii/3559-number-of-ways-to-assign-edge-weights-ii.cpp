class Solution {
public:
    vector<int> assignEdgeWeights(vector<vector<int>>& edges, vector<vector<int>>& queries) {
        const int MOD = 1e9 + 7;

        int n = edges.size() + 1;
        int LOG = 17; // 2^17 > 1e5

        vector<vector<int>> graph(n + 1);

        for (auto &e : edges) {
            graph[e[0]].push_back(e[1]);
            graph[e[1]].push_back(e[0]);
        }

        vector<vector<int>> up(LOG, vector<int>(n + 1));
        vector<int> depth(n + 1, 0);

        // Build parent and depth
        queue<int> q;
        q.push(1);
        up[0][1] = 0;

        vector<bool> visited(n + 1, false);
        visited[1] = true;

        while (!q.empty()) {
            int u = q.front();
            q.pop();

            for (int v : graph[u]) {
                if (visited[v]) continue;

                visited[v] = true;
                depth[v] = depth[u] + 1;
                up[0][v] = u;
                q.push(v);
            }
        }

        // Binary lifting table
        for (int j = 1; j < LOG; j++) {
            for (int i = 1; i <= n; i++) {
                up[j][i] = up[j - 1][up[j - 1][i]];
            }
        }

        auto lca = [&](int u, int v) {
            if (depth[u] < depth[v])
                swap(u, v);

            int diff = depth[u] - depth[v];

            for (int j = 0; j < LOG; j++) {
                if (diff & (1 << j))
                    u = up[j][u];
            }

            if (u == v) return u;

            for (int j = LOG - 1; j >= 0; j--) {
                if (up[j][u] != up[j][v]) {
                    u = up[j][u];
                    v = up[j][v];
                }
            }

            return up[0][u];
        };

        // pow2[i] = 2^i % MOD
        vector<long long> pow2(n + 1, 1);
        for (int i = 1; i <= n; i++) {
            pow2[i] = (pow2[i - 1] * 2) % MOD;
        }

        vector<int> ans;

        for (auto &query : queries) {
            int u = query[0];
            int v = query[1];

            int w = lca(u, v);
            int dist = depth[u] + depth[v] - 2 * depth[w];

            if (dist == 0)
                ans.push_back(0);
            else
                ans.push_back(pow2[dist - 1]);
        }

        return ans;
    }
};