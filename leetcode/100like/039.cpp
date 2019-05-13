class Solution {
private:
    void dfs(vector<int>& solution) {
        int sum = accumulate(solution.begin(), solution.end(), 0);
        if (sum == mTarget) {
            mAnswer.insert(solution);
            return;
        }
        for (int i = 0; i < mCandidates.size(); i++) {
            if (solution.size() && mCandidates[i] < solution.back()) {
                continue;
            }
            if (mCandidates[i] > mTarget - sum) {
                break;
            }
            vector<int> t = solution;
            t.push_back(mCandidates[i]);
            dfs(t);
        }
    }
    
    set<vector<int>> mAnswer;
    vector<int> mCandidates;
    int mTarget;
    
public:
    vector<vector<int>> combinationSum(vector<int>& candidates, int target) {
        mCandidates = candidates;
        mTarget = target;
        
        sort(mCandidates.begin(), mCandidates.end());
        
        vector<int> start;
        dfs(start);
        
        return vector<vector<int>>(mAnswer.begin(), mAnswer.end());
    }
};

// 24ms, 11.8MB