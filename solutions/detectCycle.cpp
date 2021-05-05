//
//  detectCycle.cpp
//  leetcode
//
//  Created by Song Ding on 6/28/20.
//  Copyright © 2020 Song Ding. All rights reserved.
//

#include "common.h"
using namespace std;

namespace detectCycle {
/*
// TODO: copy problem statement here
 142. Linked List Cycle II
 Medium

 2633

 210

 Add to List

 Share
 Given a linked list, return the node where the cycle begins. If there is no cycle, return null.

 To represent a cycle in the given linked list, we use an integer pos which represents the position (0-indexed) in the linked list where tail connects to. If pos is -1, then there is no cycle in the linked list.

 Note: Do not modify the linked list.

  

 Example 1:

 Input: head = [3,2,0,-4], pos = 1
 Output: tail connects to node index 1
 Explanation: There is a cycle in the linked list, where tail connects to the second node.


 Example 2:

 Input: head = [1,2], pos = 0
 Output: tail connects to node index 0
 Explanation: There is a cycle in the linked list, where tail connects to the first node.


 Example 3:

 Input: head = [1], pos = -1
 Output: no cycle
 Explanation: There is no cycle in the linked list.


  

 Follow-up:
 Can you solve it without using extra space?
*/
class Solution {
public:
    // TODO: copy function signature here
    ListNode *detectCycle(ListNode *head) {
        ListNode *f = head, *s = head;
        while (f && f->next) {
            f = f->next->next;
            s = s->next;
            if (f == s) {
                break;
            }
        }
        if (!f || !f->next) {
            return nullptr;
        }
        f = head;
        while (f != s) {
            f = f->next;
            s = s->next;
        }
        return f;
    }
    
private:
};
}

/*
int main() {
    // TODO: define parameter type here
    struct param {
    };
    // TODO: prepare parameters here
    vector<struct param> params {
    };
    // TODO: provide expected results here
    vector<int> answers {
        0
    };
    // create list
    ListNode* head = new ListNode(1);
    head->next = new ListNode(2);
    head->next->next = head;
    
    //for (auto& dp : params) {
        cout << endl;
        clock_t tstart = clock();
        auto res = detectCycle::Solution().detectCycle(head);
        //cout << res << endl;
        cout << clock() - tstart << endl;
    //}

    return 0;
}
//*/
