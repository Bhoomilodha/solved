class Solution {
public:
    int minimumEffort(vector<vector<int>>& tasks) {
        // Sort by (minimum - actual) in decreasing order
        sort(tasks.begin(), tasks.end(), [](const vector<int>& a, const vector<int>& b) {
            return (a[1] - a[0]) > (b[1] - b[0]);
        });

        int energy = 0;
        int current = 0;

        for (auto& task : tasks) {
            int actual = task[0];
            int minimum = task[1];

            // Energy needed before starting this task
            energy = max(energy, current + minimum);

            current += actual;
        }

        return energy;
    }
};