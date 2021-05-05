// candy.cpp
// leetcode
//
// Created by  Song Ding on 3/22/18.
// Copyright © 2018 Song Ding. All rights reserved.
//
#include "common.h"
using namespace std;

namespace candy {

class Solution {
public:
    /**
     find all bottoms, and assign 1 to each bottom.
     For nodes between bottom and peak, increase by 1 as
     it becomes far from bottom.
     
     scan from left to right, and when a child has higher
     rating than its left child, increase candy by 1 more than
     its left child. other children get 1 candy.
     
     Same for right.
     
     now, all children will get two candy assignments. Pick the larger
     of the two.
     */
    int candy(vector<int>& ratings) {
        int n = ratings.size();
        vector<int> rightward(n, 1), leftward(n, 1);
        for (int i = 1; i < n; ++i) {
            if (ratings[i] > ratings[i - 1]) {
                rightward[i] = rightward[i - 1] + 1;
            }
        }
        for (int i = n - 2; i >= 0; --i) {
            if (ratings[i] > ratings[i + 1]) {
                leftward[i] = leftward[i + 1] + 1;
            }
        }
        
        int res = 0;
        for (int i = 0; i < n; ++i) {
            res += max(leftward[i], rightward[i]);
        }
        return res;
    }

private:
};

}

/*/
int main() {
    // TODO: prepare parameters here
    vector<int> ratings {
        //1
        //1,2
        //2,1
        //1,2,2
        //2,1,2
        //1,2,3
        3,2,1
    };
    // TODO: add return type and paramters.
    clock_t start = clock();
    auto res = candy::Solution().candy(ratings);
    cout << clock() - start << endl;
    cout << res << endl;
    return 0;
}
//*/
