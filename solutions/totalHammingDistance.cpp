// totalHammingDistance.cpp
// leetcode
//
// Created by  Song Ding on 10/26/19.
// Copyright © 2019 Song Ding. All rights reserved.
//
#include "common.h"
using namespace std;

namespace totalHammingDistance {
/*
// TODO: copy problem statement here
 477. Total Hamming Distance
 Medium

 610

 44

 Favorite

 Share
 The Hamming distance between two integers is the number of positions at which the corresponding bits are different.

 Now your job is to find the total Hamming distance between all pairs of the given numbers.

 Example:
 Input: 4, 14, 2

 Output: 6

 Explanation: In binary representation, the 4 is 0100, 14 is 1110, and 2 is 0010 (just
 showing the four bits relevant in this case). So the answer will be:
 HammingDistance(4, 14) + HammingDistance(4, 2) + HammingDistance(14, 2) = 2 + 2 + 2 = 6.
 Note:
 Elements of the given array are in the range of 0 to 10^9
 Length of the array will not exceed 10^4.
 */

class Solution {
public:
    /**
     * get the # of numbers that have 1 on the i-th bit, k
     * then the # of numbers having 0 on the i-th bit is n - k.
     * result will be k*(n-k) for each bit
     */
    int totalHammingDistance(vector<int>& nums) {
        int n = nums.size();
        vector<int> bit1(32, 0);
        for (int i = 0; i < 32; ++i) {
            int b = (1 << i);
            for (auto d : nums) {
                if (d & b) {
                    ++bit1[i];
                }
            }
        }
        int res = 0;
        for (int i = 0; i < 32; ++i) {
            res += bit1[i] * (n - bit1[i]);
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
        vector<int> nums;
    };
    // TODO: prepare parameters here
    vector<struct d> p {
        {{4, 14, 2}},
    };

    vector< int > answers {
        6,
    };

    // TODO: update paramters.
    for (auto& dp : p) {
        cout << endl;
        clock_t tstart = clock();
        auto res = totalHammingDistance::Solution().totalHammingDistance(dp.nums);
        cout << clock() - tstart << endl;
        cout << res << endl;
    }
    return 0;
}
//*/
