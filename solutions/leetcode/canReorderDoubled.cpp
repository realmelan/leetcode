// canReorderDoubled.cpp
// leetcode
//
// Created by  Song Ding on 4/25/19.
// Copyright © 2019 Song Ding. All rights reserved.
//
#include "common.h"
using namespace std;

namespace canReorderDoubled {

class Solution {
public:
    /**
     * First divide the array into two parts, positives and negatives.
     * For each part, sort the integers based on absolute value
     * and check whether each element has a match.
     */
    bool canReorderDoubled(vector<int>& A) {
        multiset<int> neg;
        multiset<int> pos;
        for (auto i : A) {
            if (i > 0) {
                pos.insert(i);
            } else {
                neg.insert(-i);
            }
        }
        
        if (neg.size() % 2 || pos.size() % 2) {
            return false;
        }
        
        while (neg.size()) {
            int a = *(neg.begin());
            int b = a << 1;
            auto it = neg.find(b);
            if (it == neg.end()) {
                return false;
            } else {
                neg.erase(it);
                neg.erase(neg.begin());
            }
        }
        while (pos.size()) {
            int a = *(pos.begin());
            int b = a << 1;
            auto it = pos.find(b);
            if (it == pos.end()) {
                return false;
            } else {
                pos.erase(it);
                pos.erase(pos.begin());
            }
        }
        return true;
    }

private:
};

}

/*/
int main() {
    // TODO: prepare parameters here
    vector< vector<int> > A {
        {3,1,3,6},
        {2,1,2,6},
        {4,-2,2,-4},
        {1,2,4,16,8,4}
    };

    vector< bool  > answers {
        false,
        false,
        true,
        false
    };
    int i = 3;

    // TODO: add return type and paramters.
    clock_t tstart = clock();
    auto res = canReorderDoubled::Solution().canReorderDoubled(A[i]);
    cout << clock() - tstart << endl;
    cout << res << endl;
    return 0;
}
//*/
