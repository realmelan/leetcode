// flatten.cpp
// leetcode
//
// Created by  Song Ding on 6/9/19.
// Copyright © 2019 Song Ding. All rights reserved.
//
#include "common.h"
using namespace std;

namespace flatten {
/*
// TODO: copy problem statement here
 430. Flatten a Multilevel Doubly Linked List
 Medium
 
 345
 
 55
 
 Favorite
 
 Share
 You are given a doubly linked list which in addition to the next and previous pointers, it could have a child pointer, which may or may not point to a separate doubly linked list. These child lists may have one or more children of their own, and so on, to produce a multilevel data structure, as shown in the example below.
 
 Flatten the list so that all the nodes appear in a single-level, doubly linked list. You are given the head of the first level of the list.
 
 
 
 Example:
 
 Input:
 1---2---3---4---5---6--NULL
 |
 7---8---9---10--NULL
 |
 11--12--NULL
 
 Output:
 1-2-3-7-8-11-12-9-10-4-5-6-NULL
 
 
 Explanation for the above example:
 
 Given the following multilevel doubly linked list:
 
 
 
 
 We should return the following flattened doubly linked list:
 

 */

class Solution {
public:
    /**
     * //TODO: explain algorithm here
     */
    Node* flatten(Node* head) {
        return NULL;
    }

private:
};

}

/*/
int main() {
    // TODO: define parameter type here
    struct d {
    };
    // TODO: prepare parameters here
    vector<struct d> p {
        {}
    };

    vector<  > answers {
    };

    // TODO: update paramters.
    for (auto& dp : p) {
        cout << endl;
        clock_t tstart = clock();
        auto res = flatten::Solution().flatten(dp.);
        cout << clock() - tstart << endl;
        cout << res << endl;
    }
    return 0;
}
//*/
