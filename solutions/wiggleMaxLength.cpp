// wiggleMaxLength.cpp
// leetcode
//
// Created by  Song Ding on 10/30/19.
// Copyright © 2019 Song Ding. All rights reserved.
//
#include "common.h"
using namespace std;

namespace wiggleMaxLength {
/*
// TODO: copy problem statement here
 376. Wiggle Subsequence
 Medium

 666

 52

 Favorite

 Share
 A sequence of numbers is called a wiggle sequence if the differences between successive numbers strictly alternate between positive and negative. The first difference (if one exists) may be either positive or negative. A sequence with fewer than two elements is trivially a wiggle sequence.

 For example, [1,7,4,9,2,5] is a wiggle sequence because the differences (6,-3,5,-7,3) are alternately positive and negative. In contrast, [1,4,7,2,5] and [1,7,4,5,5] are not wiggle sequences, the first because its first two differences are positive and the second because its last difference is zero.

 Given a sequence of integers, return the length of the longest subsequence that is a wiggle sequence. A subsequence is obtained by deleting some number of elements (eventually, also zero) from the original sequence, leaving the remaining elements in their original order.

 Example 1:

 Input: [1,7,4,9,2,5]
 Output: 6
 Explanation: The entire sequence is a wiggle sequence.
 Example 2:

 Input: [1,17,5,10,13,15,10,5,16,8]
 Output: 7
 Explanation: There are several subsequences that achieve this length. One is [1,17,10,13,10,16,8].
 Example 3:

 Input: [1,2,3,4,5,6,7,8,9]
 Output: 2
 Follow up:
 Can you do it in O(n) time?
 */

class Solution {
public:
    /**
     * TODO: need to understand why it works
     * https://leetcode.com/problems/wiggle-subsequence/discuss/84887/C%2B%2B-0ms-O(N)-dynamic-programming-solution
     * p => # of change of direction if the last is change to up
     * q => # of change of direction if the last is change to down.
     */
    int wiggleMaxLength(vector<int>& nums) {
        int n = nums.size();
        int up = 1, down = 1;
        for (int i = 1; i < n; ++i) {
            if (nums[i] > nums[i-1]) {
                /** If nums[i] > nums[i-1], then we can use nums[i] to make a longer subsequence of type U
                    Proof: We consider a subsequence of type D in {0,...,i-1} (its length is down[i-1]).
                    Let N be the last number of this subsequence.
                    - If nums[i] > N, then we can add nums[i] to the subsequence and it gives us a longer
                    valid subsequence of type U.
                    - If nums[i] <= N, then:
                    (1) N cannot be nums[i-1], because nums[i-1] < nums[i] <= N i.e. nums[i-1] < N
                    (2) We can replace N with nums[i-1] (we still have a valid
                    subsequence of type D since N >= nums[i] > nums[i-1] i.e. N > nums[i-1]),
                    and then add nums[i] to the subsequence, and we have a longer subsequence of type U.
                    Therefore up[i] = down[i-1] + 1
                    
                    There is no gain in using nums[i] to make a longer subsequence of type D.
                    Proof: Let N be the last number of a subsequence of type U
                    in {0,...,i-1}.
                    Assume we can use nums[i] to make a longer subsequence of type D. Then:
                    (1) N cannot be nums[i-1], otherwise we would not be able to use nums[i]
                    to make a longer subsequence of type D as nums[i] > nums[i-1]
                    (2) Necessarily nums[i] < N, and therefore nums[i-1] < N since nums[i-1] < nums[i].
                    But this means that we could have used nums[i-1] already to make a longer
                    subsequence of type D.
                    So even if we can use nums[i], there is no gain in using it, so we keep the old value of
                    down (down[i] = down[i-1])
                */
                up = down + 1;
            } else if (nums[i] < nums[i-1]) {
                down = up + 1;
            }
        }
        return min(n, max(up, down));
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
        {{1,7,4,9,2,5}},
        {{1,17,5,10,13,15,10,5,16,8}},
        {{1,2,3,4,5,6,7,8,9}},
    };

    vector< int > answers {
        6,
        7,
        2,
    };

    // TODO: update paramters.
    for (auto& dp : p) {
        cout << endl;
        clock_t tstart = clock();
        auto res = wiggleMaxLength::Solution().wiggleMaxLength(dp.nums);
        cout << clock() - tstart << endl;
        cout << res << endl;
    }
    return 0;
}
//*/
