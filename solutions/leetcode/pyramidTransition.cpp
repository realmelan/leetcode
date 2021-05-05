// pyramidTransition.cpp
// leetcode
//
// Created by  Song Ding on 9/4/18.
// Copyright © 2018 Song Ding. All rights reserved.
//
#include "common.h"
using namespace std;

namespace pyramidTransition {

class Solution {
public:
    /**
     * go over the bottom string to find all possible next level strings.
     * then recursively deal the next level strings.
     *
     */
    bool pyramidTransition(string bottom, vector<string>& allowed) {
        vector<set<string>> dict(ALLOWED);
        for (const auto& a : allowed) {
            int id = (a[0] - 'A') * 7 + a[1] - 'A';
            dict[id].insert(a.substr(2, 1));
        }
        unordered_map<string, bool> memo;
        return goodLevel(bottom, dict, memo);
    }

private:
    const static int ALLOWED = 49;
    bool goodLevel(const string& level, const vector<set<string>>& dict, unordered_map<string, bool>& memo) {
        int len = level.size();
        if (len <= 1) {
            return true;
        }
        
        auto it = memo.find(level);
        if (it != memo.end()) {
            return it->second;
        };
        
        set<string> next;
        int id = (level[0] - 'A') * 7 + level[1] - 'A';
        next = dict[id];
        for (int i = 2; i < len; ++i) {
            int id = (level[i-1] - 'A') * 7 + level[i] - 'A';
            if (dict[id].empty()) {
                return false;
            }
            set<string> tmp;
            for (const auto& s : dict[id]) {
                for (const auto& w : next) {
                    tmp.insert(w + s);
                }
            }
            next.swap(tmp);
        }
        
        for (const auto& n : next) {
            if (goodLevel(n, dict, memo)) {
                memo[level] = true;
                return true;
            }
        }
        memo[level] = false;
        return false;
    }
};

}

/*/
int main() {
    // TODO: prepare parameters here
    string bottom = "AABA";
    vector<string> allowed {
        "AAA", "AAB", "ABA", "ABB", "BAC"
    };

    // TODO: add return type and paramters.
    clock_t start = clock();
    auto res = pyramidTransition::Solution().pyramidTransition(bottom, allowed);
    cout << clock() - start << endl;
    cout << res << endl;
    return 0;
}
//*/
