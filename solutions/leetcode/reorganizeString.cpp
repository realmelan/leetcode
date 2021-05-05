// reorganizeString.cpp
// leetcode
//
// Created by  Song Ding on 6/18/18.
// Copyright © 2018 Song Ding. All rights reserved.
//
#include "common.h"
using namespace std;

namespace reorganizeString {

class Solution {
public:
    /**
     * Count # of occurrence of each char. Sort them from most to fewest.
     *
     * Always select the most char that is different from the tail of the new
     * string, the decease its count by 1.
     *
     * Use priority queue.
     *
     */
    class PairCompare {
    public:
        bool operator()(const pair<char,int>& a, const pair<char,int>&b) {
            if (a.second != b.second) {
                return a.second < b.second;
            } else {
                return a.first > b.first;
            }
        }
        
    };
    string reorganizeString(string S) {
        priority_queue<pair<char,int>, vector<pair<char,int>>, PairCompare> charq;
        vector<int> cnt(26, 0);
        int n = S.size();
        for (int i = 0; i < n; ++i) {
            ++cnt[S[i] - 'a'];
        }
        for (int i = 0; i < 26; ++i) {
            if (cnt[i] > 0) {
                charq.push(make_pair(i + 'a', cnt[i]));
            }
        }
        
        string res("A");
        while (charq.size()) {
            auto most = charq.top();
            charq.pop();
            if (most.first == *(res.rbegin())) {
                if (charq.empty()) {
                    return "";
                }
                auto most2 = charq.top();
                charq.pop();
                charq.push(most);
                res.push_back(most2.first);
                if (--most2.second) {
                    charq.push(most2);
                }
            } else {
                res.push_back(most.first);
                if (--most.second) {
                    charq.push(most);
                }
            }
        }
        
        return res.substr(1);
    }

private:
};

}

/*/
int main() {
    // TODO: prepare parameters here
    string S = "aaab";

    // TODO: add return type and paramters.
    clock_t start = clock();
    auto res = reorganizeString::Solution().reorganizeString(S);
    cout << clock() - start << endl;
    cout << res << endl;
    return 0;
}
//*/
