// sortList.cpp
// leetcode
//
// Created by  Song Ding on 6/17/19.
// Copyright © 2019 Song Ding. All rights reserved.
//
#include "common.h"
using namespace std;

namespace sortList {
/*
// TODO: copy problem statement here
 148. Sort List
 Medium
 
 1468
 
 77
 
 Favorite
 
 Share
 Sort a linked list in O(n log n) time using constant space complexity.
 
 Example 1:
 
 Input: 4->2->1->3
 Output: 1->2->3->4
 Example 2:
 
 Input: -1->5->3->4->0
 Output: -1->0->3->4->5
 */

class Solution {
public:
    /**
     * quick sort, by moving vals instead of moving pointers
     */
    ListNode* sortList(ListNode* head) {
        return NULL;
    }

private:
};

}

/*/
int main() {
    // TODO: define parameter type here
    struct d {
        vector<int> nodeVals;
    };
    // TODO: prepare parameters here
    vector<struct d> p {
        {{4,2,1,3}},
        {{-1,5,3,4,0}}
    };

    vector< vector<int> > answers {
        {1,2,3,4},
        {-1,0,3,4,5}
    };

    // TODO: update paramters.
    for (auto& dp : p) {
        cout << endl;
        clock_t tstart = clock();
        auto res = sortList::Solution().sortList(toList(dp.nodeVals));
        cout << clock() - tstart << endl;
        cout << res << endl;
    }
    return 0;
}
//*/
