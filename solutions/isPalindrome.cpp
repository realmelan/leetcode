//
//  isPalindrome.cpp
//  leetcode
//
//  Created by Song Ding on 1/19/21.
//  Copyright © 2021 Song Ding. All rights reserved.
//

#include "common.h"
using namespace std;

namespace isPalindrome {
/*
// TODO: copy problem statement here
 234. Palindrome Linked List
 Easy

 4475

 414

 Add to List

 Share
 Given a singly linked list, determine if it is a palindrome.

 Example 1:

 Input: 1->2
 Output: false
 Example 2:

 Input: 1->2->2->1
 Output: true
 Follow up:
 Could you do it in O(n) time and O(1) space?
*/
class Solution {
public:
    // TODO: copy function signature here
    bool isPalindrome(ListNode* head) {
        int len = 0;
        ListNode* cur = head;
        while (cur) {
            ++len;
            cur = cur->next;
        }
        ListNode* mid = head;
        int i = 0;
        while (i < len/2) {
            mid = mid->next;
            ++i;
        }
        
        ListNode* tail = reverse(mid);
        mid->next = nullptr;
        ListNode* t = tail;
        while (t && head && t != head && t->val == head->val) {
            t = t->next;
            head = head->next;
        }
        reverse(tail);
        tail->next = nullptr;
        return t == nullptr;
    }
    ListNode* reverse(ListNode* head) {
        if (!head->next) {
            return head;
        } else {
            ListNode* t = reverse(head->next);
            head->next->next = head;
            return t;
        }
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
        {{1,2,3,1,1}}
    };
    // TODO: provide expected results here
    vector<bool> answers {
    };
    
    for (auto& dp : params) {
        cout << endl;
        clock_t tstart = clock();
        auto res = isPalindrome::Solution().isPalindrome(toList(dp.nodeVals));
        cout << res << endl;
        cout << clock() - tstart << endl;
    }

    return 0;
}
//*/
