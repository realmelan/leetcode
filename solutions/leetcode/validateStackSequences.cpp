// validateStackSequences.cpp
// leetcode
//
// Created by  Song Ding on 5/30/19.
// Copyright © 2019 Song Ding. All rights reserved.
//
#include "common.h"
using namespace std;

namespace validateStackSequences {
/*
// TODO: copy problem statement here
 946. Validate Stack Sequences
 Medium
 
 240
 
 6
 
 Favorite
 
 Share
 Given two sequences pushed and popped with distinct values, return true if and only if this could have been the result of a sequence of push and pop operations on an initially empty stack.
 
 
 
 Example 1:
 
 Input: pushed = [1,2,3,4,5], popped = [4,5,3,2,1]
 Output: true
 Explanation: We might do the following sequence:
 push(1), push(2), push(3), push(4), pop() -> 4,
 push(5), pop() -> 5, pop() -> 3, pop() -> 2, pop() -> 1
 Example 2:
 
 Input: pushed = [1,2,3,4,5], popped = [4,3,5,1,2]
 Output: false
 Explanation: 1 cannot be popped before 2.
 
 
 Note:
 
 0 <= pushed.length == popped.length <= 1000
 0 <= pushed[i], popped[i] < 1000
 pushed is a permutation of popped.
 pushed and popped have distinct values.
 */

class Solution {
public:
    /**
     * check each number of the pushed, if it matches the top of
     * popped, just pop it from work stack, if not, push it to stack.
     *
     * if the work stack is empty then it is valid.
     */
    bool validateStackSequences(vector<int>& pushed, vector<int>& popped) {
        stack<int> w;
        int i = 0, j = 0;
        int in = pushed.size();
        int on = popped.size();
        while (i < in && j < on) {
            if (w.size() && w.top() == popped[j]) {
                w.pop();
                ++j;
            } else {
                w.push(pushed[i]);
                ++i;
            }
        }
        while (j < on && w.size() && w.top() == popped[j]) {
            w.pop();
            ++j;
        }
        return w.empty();
    }

private:
};

}

/*/
int main() {
    // TODO: define parameter type here
    struct d {
        vector<int> pushed;
        vector<int> popped;
    };
    // TODO: prepare parameters here
    vector<struct d> p {
        {{1,2,3,4,5},{4,5,3,2,1}},
        {{1,2,3,4,5},{4,3,5,1,2}}
    };

    vector< bool > answers {
        true,
        false
    };

    // TODO: update paramters.
    for (auto& dp : p) {
        cout << endl;
        clock_t tstart = clock();
        auto res = validateStackSequences::Solution().validateStackSequences(dp.pushed, dp.popped);
        cout << clock() - tstart << endl;
        cout << res << endl;
    }
    return 0;
}
//*/
