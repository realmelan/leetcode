//
//  sortList.cpp
//  leetcode
//
//  Created by Song Ding on 6/28/20.
//  Copyright © 2020 Song Ding. All rights reserved.
//

#include "common.h"
using namespace std;

namespace sortList {
/*
// TODO: copy problem statement here
 148. Sort List
 Medium

 2643

 127

 Add to List

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
    // TODO: copy function signature here
    ListNode* sortList(ListNode* head) {
        if (!head || !head->next) {
            return head;
        }
        
        ListNode* f = head, *s = head;
        while (f->next && f->next->next) {
            f = f->next->next;
            s = s->next;
        }
        ListNode* sh = s->next;
        s->next = nullptr;
        
        ListNode* h1 = sortList(head);
        ListNode* h2 = sortList(sh);
        // merge two lists
        ListNode nh(0);
        ListNode *cur = &nh;
        while (h1 && h2) {
            if (h1->val < h2->val) {
                cur->next = h1;
                h1 = h1->next;
            } else {
                cur->next = h2;
                h2 = h2->next;
            }
            cur = cur->next;
        }
        if (h1) {
            cur->next = h1;
        } else {
            cur->next = h2;
        }
        return nh.next;
    }
    // from https://leetcode.com/problems/sort-list/discuss/46712/Bottom-to-up(not-recurring)-with-o(1)-space-complextity-and-o(nlgn)-time-complextity
    ListNode* sortList2(ListNode* head) {
        if (!head || !head->next) {
            return head;
        }
        int len = 0;
        ListNode* h = head;
        while (h) {
            ++len;
            h = h->next;
        }
        ListNode p(0, head);
        for (int step = 1; step < len; step <<= 1) {
            ListNode *cur = p.next, *sh = nullptr, *nh = nullptr, *pt = &p;
            while (cur) {
                sh = split(cur, step);
                nh = split(sh, step);
                pt = merge(cur, sh, pt);
                cur = nh;
            }
        }
        return p.next;
    }
    ListNode* split(ListNode* head, int step) {
        int i = 0;
        ListNode* prev = head;
        while (head && i++ < step) {
            prev = head;
            head = head->next;
        }
        if (prev) {
            prev->next = nullptr;
        }
        return head;
    }
    ListNode* merge(ListNode* left, ListNode* right, ListNode* prevTail) {
        ListNode* h = prevTail;
        while (left || right) {
            if (!right || (left && left->val < right->val)) {
                h->next = left;
                left = left->next;
            } else {
                h->next = right;
                right = right->next;
            }
            h = h->next;
        }
        return h;
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
        {{4,2,1,3}},
    };
    // TODO: provide expected results here
    vector<vector<int>> answers {
    };
    
    for (auto& dp : params) {
        cout << endl;
        clock_t tstart = clock();
        auto res = sortList::Solution().sortList2(toList(dp.nodeVals));
        cout << res << endl;
        cout << clock() - tstart << endl;
    }

    return 0;
}
//*/
