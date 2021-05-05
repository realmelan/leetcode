// bagOfTokensScore.cpp
// leetcode
//
// Created by  Song Ding on 4/30/19.
// Copyright © 2019 Song Ding. All rights reserved.
//
#include "common.h"
using namespace std;

namespace bagOfTokensScore {

class Solution {
public:
    /**
     * always try to gain a point by picking the lowest token value;
     * when it is not possible to gain a point, trade 1 point with the
     * token of largest value
     */
    int bagOfTokensScore(vector<int>& tokens, int P) {
        sort(tokens.begin(), tokens.end());
        int n = tokens.size();
        int res = 0;
        int powerIdx = n - 1;
        int pointIdx = 0;
        while (pointIdx <= powerIdx) {
            if (P >= tokens[pointIdx]) {
                P -= tokens[pointIdx];
                ++pointIdx;
                ++res;
            } else {
                if (res <= 0 || pointIdx + 1 >= powerIdx) {
                    break;
                }
                P += tokens[powerIdx];
                --powerIdx;
                --res;
            }
        }
        return res;
    }

private:
};

}

/*/
int main() {
    // TODO: prepare parameters here
    vector< pair<vector<int>,int>> params {
        {{100}, 50},
        {{100,200}, 150},
        {{100,200,300,400}, 200}
    };

    vector<  int > answers {
        0,
        1,
        2
    };
    int i = 0;

    // TODO: add return type and paramters.
    clock_t tstart = clock();
    auto res = bagOfTokensScore::Solution().bagOfTokensScore(params[i].first, params[i].second);
    cout << clock() - tstart << endl;
    cout << res << endl;
    return 0;
}
//*/
