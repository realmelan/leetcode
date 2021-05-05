//
//  reverseList.cpp
//  leetcode
//
//  Created by Song Ding on 6/28/20.
//  Copyright © 2020 Song Ding. All rights reserved.
//

#include "common.h"
using namespace std;

namespace reverseList {
/*
// TODO: copy problem statement here
 206. Reverse Linked List
 Easy

 4406

 89

 Add to List

 Share
 Reverse a singly linked list.

 Example:

 Input: 1->2->3->4->5->NULL
 Output: 5->4->3->2->1->NULL
 Follow up:

 A linked list can be reversed either iteratively or recursively. Could you implement both?
*/
class Solution {
public:
    // TODO: copy function signature here
    ListNode* reverseList(ListNode* head) {
        if (!head || !head->next) {
            return head;
        }
        ListNode* t = reverseList(head->next);
        head->next->next = head;
        head->next = nullptr;
        return t;
    }
    
private:
};
}

/*
int main() {
    // TODO: define parameter type here
    struct param {
        vector<int> nodeVals;
    };
    // TODO: prepare parameters here
    vector<struct param> params {
        {{1,2,3,4,5}},
    };
    // TODO: provide expected results here
    vector<vector<int>> answers {
        {5,4,3,2,1},
    };
    
    for (auto& dp : params) {
        cout << endl;
        clock_t tstart = clock();
        auto res = reverseList::Solution().reverseList(toList(dp.nodeVals));
        cout << res << endl;
        cout << clock() - tstart << endl;
    }

    return 0;
}
//*/
