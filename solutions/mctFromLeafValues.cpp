//
//  mctFromLeafValues.cpp
//  leetcode
//
//  Created by Song Ding on 8/14/20.
//  Copyright © 2020 Song Ding. All rights reserved.
//

#include "common.h"
using namespace std;

namespace mctFromLeafValues {
/*
// TODO: copy problem statement here
 1130. Minimum Cost Tree From Leaf Values
 Medium

 1245

 102

 Add to List

 Share
 Given an array arr of positive integers, consider all binary trees such that:

 Each node has either 0 or 2 children;
 The values of arr correspond to the values of each leaf in an in-order traversal of the tree.  (Recall that a node is a leaf if and only if it has 0 children.)
 The value of each non-leaf node is equal to the product of the largest leaf value in its left and right subtree respectively.
 Among all possible binary trees considered, return the smallest possible sum of the values of each non-leaf node.  It is guaranteed this sum fits into a 32-bit integer.

  

 Example 1:

 Input: arr = [6,2,4]
 Output: 32
 Explanation:
 There are two possible trees.  The first has non-leaf node sum 36, and the second has non-leaf node sum 32.

     24            24
    /  \          /  \
   12   4        6    8
  /  \               / \
 6    2             2   4
  

 Constraints:

 2 <= arr.length <= 40
 1 <= arr[i] <= 15
 It is guaranteed that the answer fits into a 32-bit signed integer (ie. it is less than 2^31).
*/
class Solution {
public:
    // TODO: copy function signature here
    // https://leetcode.com/problems/minimum-cost-tree-from-leaf-values/discuss/339959/One-Pass-O(N)-Time-and-Space
    int mctFromLeafValues(vector<int>& arr) {
        int res = 0;
        stack<int> s;
        s.push(INT_MAX);
        for (int i = 0; i < arr.size(); ++i) {
            while (s.size() && arr[i] > s.top()) {
                int c = s.top(); s.pop();
                res += c * min(arr[i], s.top());
            }
            s.push(arr[i]);
        }
        while (s.size() > 2) {
            int c = s.top();
            s.pop();
            res += c * s.top();
        }
        return res;
    }
private:
};
}

/*
int main() {
    // TODO: define parameter type here
    struct param {
        vector<int> arr;
    };
    // TODO: prepare parameters here
    vector<struct param> params {
        {{6,2,4}}
    };
    // TODO: provide expected results here
    vector<int> answers {
        32
    };
    
    for (auto& dp : params) {
        cout << endl;
        clock_t tstart = clock();
        auto res = mctFromLeafValues::Solution().mctFromLeafValues(dp.arr);
        cout << res << endl;
        cout << clock() - tstart << endl;
    }

    return 0;
}
//*/
