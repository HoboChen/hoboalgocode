class Solution {
private:
    set<vector<int>> res;

    void dfs(const vector<int>& candi, int pos, vector<int> tmp, int target) {
        if (candi[pos] == target) {
            tmp.push_back(target);
            res.insert(tmp);
            return;
        }
        if (candi[pos] > target) {
            return;
        }
        if (pos != candi.size() - 1)
            dfs(candi, pos + 1, tmp, target);
        tmp.push_back(candi[pos]);
        if (pos != candi.size() - 1)
            dfs(candi, pos + 1, tmp, target - candi[pos]);
        return;
    }

public:
    vector<vector<int>> combinationSum2(vector<int>& candidates, int target) {
        sort(candidates.begin(), candidates.end());
        vector<int> t;
        dfs(candidates, 0, t, target);
        vector<vector<int>> q(res.begin(), res.end());
        return q;
    }
};