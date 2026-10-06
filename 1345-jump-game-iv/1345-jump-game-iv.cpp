class Solution {
public:
    int minJumps(vector<int>& arr) {
        int n = arr.size();
        
        unordered_map<int, vector<int>> mp;
        for (int i = 0; i < n; i++) {
            mp[arr[i]].push_back(i);
        }
        
        queue<int> q;
        vector<bool> visited(n, false);
        
        q.push(0);
        visited[0] = true;
        int steps = 0;
        
        while (!q.empty()) {
            int size = q.size();
            
            while (size--) {
                int i = q.front();
                q.pop();
                
                if (i == n - 1)
                    return steps;
                
                if (i + 1 < n && !visited[i + 1]) {
                    visited[i + 1] = true;
                    q.push(i + 1);
                }
                
                if (i - 1 >= 0 && !visited[i - 1]) {
                    visited[i - 1] = true;
                    q.push(i - 1);
                }
                
                for (int j : mp[arr[i]]) {
                    if (!visited[j]) {
                        visited[j] = true;
                        q.push(j);
                    }
                }
                
                mp[arr[i]].clear();
            }
            
            steps++;
        }
        
        return -1;
    }
};