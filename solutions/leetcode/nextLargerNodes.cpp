// nextLargerNodes.cpp
// leetcode
//
// Created by  Song Ding on 5/30/19.
// Copyright © 2019 Song Ding. All rights reserved.
//
#include "common.h"
using namespace std;

namespace nextLargerNodes {
/*
// TODO: copy problem statement here
 1019. Next Greater Node In Linked List
 Medium
 
 180
 
 14
 
 Favorite
 
 Share
 We are given a linked list with head as the first node.  Let's number the nodes in the list: node_1, node_2, node_3, ... etc.
 
 Each node may have a next larger value: for node_i, next_larger(node_i) is the node_j.val such that j > i, node_j.val > node_i.val, and j is the smallest possible choice.  If such a j does not exist, the next larger value is 0.
 
 Return an array of integers answer, where answer[i] = next_larger(node_{i+1}).
 
 Note that in the example inputs (not outputs) below, arrays such as [2,1,5] represent the serialization of a linked list with a head node value of 2, second node value of 1, and third node value of 5.
 
 
 
 Example 1:
 
 Input: [2,1,5]
 Output: [5,5,0]
 Example 2:
 
 Input: [2,7,4,3,5]
 Output: [7,0,5,5,0]
 Example 3:
 
 Input: [1,7,5,1,9,2,5,1]
 Output: [7,9,9,9,0,5,0,0]
 
 
 Note:
 
 1 <= node.val <= 10^9 for each node in the linked list.
 The given list has length in the range [0, 10000].
 */

class Solution {
public:
    /**
     * //TODO: explain algorithm here
     */
    vector<int> nextLargerNodes(ListNode* head) {
        vector<int> res(10000, -1);
        stack<pair<int,int>> s;
        ListNode* c = head;
        int idx = 0;
        while (c) {
            while (s.size() && s.top().first < c->val) {
                int t = s.top().second;
                s.pop();
                res[t] = c->val;
            }
            s.push(make_pair(c->val, idx++));
            c = c->next;
        }
        while (s.size()) {
            int t = s.top().second;
            s.pop();
            res[t] = 0;
        }
        res.resize(idx);
        return res;
    }

private:
};

}

/*/
int main() {
    // TODO: define parameter type here
    struct d {
        vector<int> vals;
    };
    // TODO: prepare parameters here
    vector<struct d> p {
        {{2,1,5}},
        {{2,7,4,3,5}},
        {{1,7,5,1,9,2,5,1}}
    };

    vector< vector<int> > answers {
        {5,5,0},
        {7,0,5,5,0},
        {7,9,9,9,0,5,0,0}
    };

    // TODO: update paramters.
    for (auto& dp : p) {
        cout << endl;
        clock_t tstart = clock();
        auto res = nextLargerNodes::Solution().nextLargerNodes(toList(dp.vals));
        cout << clock() - tstart << endl;
        cout << res << endl;
    }
    return 0;
}
//*/
