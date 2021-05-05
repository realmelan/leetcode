// numSubarraysWithSum.cpp
// leetcode
//
// Created by  Song Ding on 4/29/19.
// Copyright © 2019 Song Ding. All rights reserved.
//
#include "common.h"
using namespace std;

namespace numSubarraysWithSum {
/**
 930. Binary Subarrays With Sum
 Medium

 508

 25

 Add to List

 Share
 In an array A of 0s and 1s, how many non-empty subarrays have sum S?

  

 Example 1:

 Input: A = [1,0,1,0,1], S = 2
 Output: 4
 Explanation:
 The 4 subarrays are bolded below:
 [1,0,1,0,1]
 [1,0,1,0,1]
 [1,0,1,0,1]
 [1,0,1,0,1]
  

 Note:

 A.length <= 30000
 0 <= S <= A.length
 A[i] is either 0 or 1.
 */
class Solution {
public:
    int numSubarraysWithSum(vector<int>& A, int S) {
        int res = 0;
        vector<int> sumCount;
        int count = 1;
        int curSum = 0;
        for (auto i : A) {
            if (i) {
                sumCount.push_back(count);
                count = 0;
                ++curSum;
            }
            ++count;
        }
        sumCount.push_back(count);
        //cout << sumCount << endl;
        for (int i = 0; i + S < sumCount.size(); ++i) {
            if (S == 0) {
                res += sumCount[i] * (sumCount[i]-1) / 2;
            } else {
                res += sumCount[i] * sumCount[i + S];
            }
        }
        return res;
    }

private:
};

}

/*/
int main() {
    // TODO: prepare parameters here
    vector< pair<vector<int>,int> > AS {
        {{1,0,1,0,1},2},
        {{1,0,1,0,1},3},
        {{0,0,0,0,0},0},
        {{0,0,0,0,0,0,1,0,0,0},0}
    };

    vector< int  > answers {
        4,
        1,
        15,
        27
    };
    int i = 1;

    // TODO: add return type and paramters.
    clock_t tstart = clock();
    auto res = numSubarraysWithSum::Solution().numSubarraysWithSum(AS[i].first, AS[i].second);
    cout << clock() - tstart << endl;
    cout << res << endl;
    return 0;
}
//*/
