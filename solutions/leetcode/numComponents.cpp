// numComponents.cpp
// leetcode
//
// Created by  Song Ding on 5/27/19.
// Copyright © 2019 Song Ding. All rights reserved.
//
#include "common.h"
using namespace std;

namespace numComponents {
/*
// TODO: copy problem statement here
 817. Linked List Components
 Medium
 
 208
 
 520
 
 Favorite
 
 Share
 We are given head, the head node of a linked list containing unique integer values.
 
 We are also given the list G, a subset of the values in the linked list.
 
 Return the number of connected components in G, where two values are connected if they appear consecutively in the linked list.
 
 Example 1:
 
 Input:
 head: 0->1->2->3
 G = [0, 1, 3]
 Output: 2
 Explanation:
 0 and 1 are connected, so [0, 1] and [3] are the two connected components.
 Example 2:
 
 Input:
 head: 0->1->2->3->4
 G = [0, 3, 1, 4]
 Output: 2
 Explanation:
 0 and 1 are connected, 3 and 4 are connected, so [0, 1] and [3, 4] are the two connected components.
 Note:
 
 If N is the length of the linked list given by head, 1 <= N <= 10000.
 The value of each node in the linked list will be in the range [0, N - 1].
 1 <= G.length <= 10000.
 G is a subset of all values in the linked list.
 */

class Solution {
public:
    /**
     * //TODO: explain algorithm here
     */
    int numComponents(ListNode* head, vector<int>& G) {
        unordered_set<int> gset(G.begin(), G.end());
        ListNode* c = head;
        bool hit = false;
        int res = 0;
        while (c) {
            if (gset.find(c->val) != gset.end()) {
                if (!hit) {
                    hit = true;
                    ++res;
                }
            } else {
                hit = false;
            }
            c = c->next;
        }
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
        vector<int> G;
    };
    // TODO: prepare parameters here
    vector<struct d> p {
        {{0,1,2,3},{0,1,3}},
        {{0,1,2,3,4},{0, 3, 1, 4}}
    };

    vector< int > answers {
        2,
        2
    };

    // TODO: update paramters.
    for (auto& dp : p) {
        cout << endl;
        clock_t tstart = clock();
        auto res = numComponents::Solution().numComponents(toList(dp.vals), dp.G);
        cout << clock() - tstart << endl;
        cout << res << endl;
    }
    return 0;
}
//*/
