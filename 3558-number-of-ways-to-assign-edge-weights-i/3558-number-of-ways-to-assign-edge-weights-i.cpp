class Solution {
public:
    int assignEdgeWeights(vector<vector<int>>& edges) {
        const long long MOD = 1000000007;
        int n = edges.size() + 1;

        vector<vector<int>> graph(n + 1);

        for (auto &e : edges) {
            graph[e[0]].push_back(e[1]);
            graph[e[1]].push_back(e[0]);
        }

        // Find maximum depth from node 1.
        queue<int> q;
        vector<int> depth(n + 1, -1);

        q.push(1);
        depth[1] = 0;

        int maxDepth = 0;

        while (!q.empty()) {
            int u = q.front();
            q.pop();

            for (int v : graph[u]) {
                if (depth[v] == -1) {
                    depth[v] = depth[u] + 1;
                    maxDepth = max(maxDepth, depth[v]);
                    q.push(v);
                }
            }
        }

        // Each edge can be 1 or 2.
        // An odd total requires an odd number of edges with weight 1.
        // For d edges, exactly 2^(d-1) assignments have odd sum.
        long long ans = 1;

        for (int i = 1; i < maxDepth; i++) {
            ans = (ans * 2) % MOD;
        }

        return ans;
    }
};