//
//  summaryRanges.cpp
//  leetcode
//
//  Created by Song Ding on 2/20/20.
//  Copyright © 2020 Song Ding. All rights reserved.
//

#include "common.h"
using namespace std;

namespace summaryRanges {
/*
// TODO: copy problem statement here
 228. Summary Ranges
 Medium

 519

 473

 Add to List

 Share
 Given a sorted integer array without duplicates, return the summary of its ranges.

 Example 1:

 Input:  [0,1,2,4,5,7]
 Output: ["0->2","4->5","7"]
 Explanation: 0,1,2 form a continuous range; 4,5 form a continuous range.
 Example 2:

 Input:  [0,2,3,4,6,8,9]
 Output: ["0","2->4","6","8->9"]
 Explanation: 2,3,4 form a continuous range; 8,9 form a continuous range.
*/
class Solution {
public:
    // TODO: copy function signature here
    vector<string> summaryRanges(vector<int>& nums) {
        vector<string> res;
        int n = nums.size();
        if (n <= 0) {
            return res;
        }
        
        int start = 0;
        for (int i = 1; i < n; ++i) {
            if (nums[i] != nums[i-1]+1) {
                ostringstream oss;
                if (i-1 == start) {
                    oss << nums[start];
                } else {
                    oss << nums[start] << "->" << nums[i-1];
                }
                res.push_back(oss.str());
                start = i;
            }
        }
        ostringstream oss;
        if (n-1 == start) {
            oss << nums[start];
        } else {
            oss << nums[start] << "->" << nums[n-1];
        }
        res.push_back(oss.str());
        return res;
    }
private:
};
}

/*
int main() {
    // TODO: define parameter type here
    struct param {
        vector<int> nums;
    };
    // TODO: prepare parameters here
    vector<struct param> params {
    };
    // TODO: provide expected results here
    vector<vector<string>> answers {
    };
    
    for (auto& dp : params) {
        cout << endl;
        clock_t tstart = clock();
        auto res = summaryRanges::Solution().summaryRanges(dp.nums);
        cout << res << endl;
        cout << clock() - tstart << endl;
    }

    return 0;
}
//*/
