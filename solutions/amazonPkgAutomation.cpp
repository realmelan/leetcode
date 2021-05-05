//
//  amazonPkgAutomation.cpp
//  leetcode
//
//  Created by Song Ding on 11/11/20.
//  Copyright © 2020 Song Ding. All rights reserved.
//

#include "common.h"
using namespace std;

namespace amazonPkgAutomation {
/*
// TODO: copy problem statement here
 Position: New Grad
 Platform: SHL
 Location: USA
 Date: Sep 2020

 Amazon's Fulfillment Center consists of a packaging bay where orders are automatically packaged in groups(n). The first group can only have 1 item and all the subsequent groups can have one item more than the previous group. Given a list of items on groups, perform certain operations in order to satisfy the constraints required by packaging automation.
 The conditions are as follows:

 The first group must contain 1 item only.
 For all other groups, the difference between the number of items in adjacent groups must not be greater than 1. In other words, for 1<=i<n, arr[i]-arr[i-1]<=1
 To accomplish this, the following operations are available.

 Rearrange the groups in any way.
 Reduce any group to any number that is at least 1
 Write an algorithm to find the maximum number of items that can be packaged in the last group with the conditions in place.

 Input
 The function/method consists of two arguments:
 numGroups, an integer representing the number of groups(n);
 arr, a list of integers representing the number of items in each group

 Output
 Return an integer representing the maximum items that can be packaged for the final group of the list given the conditions above.

 Examples:
 Input: numGroups = 4, arr = [1,3,2,2]
 Output: 3

 Input: numGroups = 4, arr = [3,2,3,5]
 Output: 4
*/
class Solution {
public:
    // TODO: copy function signature here
    int amazonPkgAutomation(vector<int>& items) {
        int n = items.size();
        vector<int> cnt(n+1, 0);
        for (auto i : items) {
            if (i <= n) {
                ++cnt[i];
            }
        }
        int i = 0, s = 1;
        while (i < n-1 && s < n) {
            i += cnt[s];
            ++s;
        }
        return s;
    }
private:
};
}

/*
int main() {
    // TODO: define parameter type here
    struct param {
        vector<int> items;
    };
    // TODO: prepare parameters here
    vector<struct param> params {
        {{1,3,2,2}},
        {{3,2,3,5}},
    };
    // TODO: provide expected results here
    vector<int> answers {
    };
    
    for (auto& dp : params) {
        cout << endl;
        clock_t tstart = clock();
        auto res = amazonPkgAutomation::Solution().amazonPkgAutomation(dp.items);
        cout << res << endl;
        cout << clock() - tstart << endl;
    }

    return 0;
}
//*/
