//
//  findLengthOfShortestSubarray.cpp
//  leetcode
//
//  Created by Song Ding on 3/16/21.
//  Copyright © 2021 Song Ding. All rights reserved.
//

#include "common.h"
using namespace std;

namespace findLengthOfShortestSubarray {
/*
// TODO: copy problem statement here
 1574. Shortest Subarray to be Removed to Make Array Sorted
 Medium

 504

 17

 Add to List

 Share
 Given an integer array arr, remove a subarray (can be empty) from arr such that the remaining elements in arr are non-decreasing.

 A subarray is a contiguous subsequence of the array.

 Return the length of the shortest subarray to remove.

  

 Example 1:

 Input: arr = [1,2,3,10,4,2,3,5]
 Output: 3
 Explanation: The shortest subarray we can remove is [10,4,2] of length 3. The remaining elements after that will be [1,2,3,3,5] which are sorted.
 Another correct solution is to remove the subarray [3,10,4].
 Example 2:

 Input: arr = [5,4,3,2,1]
 Output: 4
 Explanation: Since the array is strictly decreasing, we can only keep a single element. Therefore we need to remove a subarray of length 4, either [5,4,3,2] or [4,3,2,1].
 Example 3:

 Input: arr = [1,2,3]
 Output: 0
 Explanation: The array is already non-decreasing. We do not need to remove any elements.
 Example 4:

 Input: arr = [1]
 Output: 0
  

 Constraints:

 1 <= arr.length <= 10^5
 0 <= arr[i] <= 10^9
*/
class Solution {
public:
    // TODO: copy function signature here
    int findLengthOfShortestSubarray(vector<int>& arr) {
        int n = arr.size(), r = n-1, res = 1;
        while (r > 0 && arr[r-1]<=arr[r]) {
            --r;
        }
        if (r <= 0) {
            return 0;
        }
        res = n-r;
        for (int i = 0; i < r && (i == 0 || arr[i-1] <= arr[i]); ++i) {
            while (r < n && arr[r] < arr[i]) {
                ++r;
            }
            res = max(res, i+1+n-r);
        }
        return n-res;
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
        {{1,2,3,10,4,2,3,5}},
    };
    // TODO: provide expected results here
    vector<int> answers {
    };
    
    for (auto& dp : params) {
        cout << endl;
        clock_t tstart = clock();
        auto res = findLengthOfShortestSubarray::Solution().findLengthOfShortestSubarray(dp.arr);
        cout << res << endl;
        cout << clock() - tstart << endl;
    }

    return 0;
}
//*/
