//
//  addTwoNumbers.cpp
//  leetcode
//
//  Created by Song Ding on 6/28/20.
//  Copyright © 2020 Song Ding. All rights reserved.
//

#include "common.h"
using namespace std;

namespace addTwoNumbers {
/*
// TODO: copy problem statement here
 445. Add Two Numbers II
 Medium

 1380

 150

 Add to List

 Share
 You are given two non-empty linked lists representing two non-negative integers. The most significant digit comes first and each of their nodes contain a single digit. Add the two numbers and return it as a linked list.

 You may assume the two numbers do not contain any leading zero, except the number 0 itself.

 Follow up:
 What if you cannot modify the input lists? In other words, reversing the lists is not allowed.

 Example:

 Input: (7 -> 2 -> 4 -> 3) + (5 -> 6 -> 4)
 Output: 7 -> 8 -> 0 -> 7
*/
class Solution {
public:
    // TODO: copy function signature here
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        int n1 = 0, n2 = 0;
        ListNode* h1 = l1, *h2 = l2;
        while (h1) {
            ++n1;
            h1 = h1->next;
        }
        while (h2) {
            ++n2;
            h2 = h2->next;
        }
        if (n1 < n2) {
            swap(l1, l2);
            swap(n1, n2);
        }
        ListNode head(0);
        ListNode* cur = &head;
        
        int i = 0;
        for (h1 = l1; i < n1-n2; ++i) {
            cur->next = new ListNode(h1->val);
            h1 = h1->next;
            cur = cur->next;
        }
        for (h2 = l2; i < n1; ++i) {
            cur->next = new ListNode(h1->val + h2->val);
            h1 = h1->next;
            h2 = h2->next;
            cur = cur->next;
        }
        
        cur = &head;
        while (cur) {
            ListNode* start = cur;
            cur = cur->next;
            while (cur && cur->val == 9) {
                cur = cur->next;
            }
            if (!cur) {
                break;
            }
            if (cur->val > 9) {
                ++start->val;
                start = start->next;
                while (start != cur) {
                    start->val = 0;
                    start = start->next;
                }
                start->val -= 10;
            }
        }
        if (head.val) {
            return new ListNode(1, head.next);
        }
        return head.next;
    }
private:
};
}

/*
int main() {
    // TODO: define parameter type here
    struct param {
        vector<int> nodeVals1;
        vector<int> nodeVals2;
    };
    // TODO: prepare parameters here
    vector<struct param> params {
        {{7,2,4,3},{5,6,4}},
        {{0},{7,4}},
        {{1},{9,9}},
    };
    // TODO: provide expected results here
    vector< vector<int> > answers {
        {7,8,0,7},
        {7,4},
        {1,0,0}
    };
    
    for (auto& dp : params) {
        cout << endl;
        clock_t tstart = clock();
        auto res = addTwoNumbers::Solution().addTwoNumbers(toList(dp.nodeVals1), toList(dp.nodeVals2));
        cout << res << endl;
        cout << clock() - tstart << endl;
    }

    return 0;
}
//*/
