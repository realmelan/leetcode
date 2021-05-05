//
//  insertSortedCircularList.cpp
//  leetcode
//
//  Created by Song Ding on 3/11/21.
//  Copyright © 2021 Song Ding. All rights reserved.
//

#include "common.h"
using namespace std;

namespace insertSortedCircularList {
/*
// TODO: copy problem statement here
given a sorted circular linked list, insert a value into it.
Note, the given node might not be the head (smallest).
*/
class Solution {
public:
    // TODO: copy function signature here
    ListNode* insertSortedCircularList(ListNode* cur, int val) {
        ListNode* largest = cur;
        while (largest->next != cur && largest->val <= largest->next->val) {
            largest = largest->next;
        }
        if (val >= largest->val) {
            ListNode* v = new ListNode(val, largest->next);
            largest->next = v;
            return v;
        }
        ListNode* t = largest;
        while (val > t->next->val) {
            t = t->next;
        }
        ListNode* v = new ListNode(val, t->next);
        t->next = v;
        return v;
    }
    
private:
};
}

/*
int main() {
    // TODO: define parameter type here
    struct param {
        vector<int> nodeVals;
        int val;
    };
    // TODO: prepare parameters here
    vector<struct param> params {
        {{3},3},
        {{3},2},
        {{5,7,8,2,4},2},
        {{3,3,3},3},
    };
    // TODO: provide expected results here
    vector<ListNode*> answers {
    };
    
    for (auto& dp : params) {
        cout << endl;
        clock_t tstart = clock();
        
        ListNode* head = toList(dp.nodeVals), *t = head;
        while (t->next) {
            t = t->next;
        }
        t->next = head;
        
        auto res = insertSortedCircularList::Solution().insertSortedCircularList(head, dp.val);
        //cout << res << endl;
        cout << clock() - tstart << endl;
    }

    return 0;
}
//*/
