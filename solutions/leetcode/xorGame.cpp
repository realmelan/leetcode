// xorGame.cpp
// leetcode
//
// Created by  Song Ding on 10/15/18.
// Copyright © 2018 Song Ding. All rights reserved.
//
#include "common.h"
using namespace std;

namespace xorGame {

class Solution {
public:
    /**
     * if there is odd # of 1's in allxor:
     *    if there is even # of nums having even # of 1's (even1); then
     *        bob wins. Here is how to win:
     *            if Alice picks odd1, then pick odd1
     *            if Alice picks even1, then pick even1
     *    if there is odd # of even1 nums; then
     *        Alice wins: Here is how to win:
     *             Pick even1 first
     *             if bob picks odd1, pick odd1
     *             if bob picks even1, pick even1
     *
     * if there is even # of 1's in allxor:
     *    there is contrary to the odd # of 1's.
     */
    bool xorGame(vector<int>& nums) {
        int odd = 0;
        int even = 0;
        int allxor = 0;
        for (auto i : nums) {
            allxor ^= i;
            if (isOdd1(i)) {
                ++odd;
            } else {
                ++even;
            }
        }
        
        if (allxor == 0) {
            return true;
        } else if (isOdd1(allxor)) {
            return even % 2;
        } else {
            return even % 2 == 0;
        }
    }
    
    /**
     * if allxor != 0, then there is at least one bit that is 1.
     * divide all numbers into two groups, one group with the bit not set(U), and the
     * other group with the bit set(V).
     * Then # of V is odd.
     *
     * if N (size of nums) is Even, then U is odd too, and Alice has a win strategy:
     *    picks from U.
     *    if Bob picks from U, pick from U.
     *    if Bob picks from V, pick from V.
     * So Bob will be the one who first picks from V and after Alice picks from V, the
     * # of V is still Odd, meaning Xor(V) still has the bit set and Bob can't win.
     */
    bool xorGame2(vector<int>& nums) {
        int allxor = 0;
        for (auto i : nums) {
            allxor ^= i;
        }
        return allxor == 0 || (nums.size() % 2 == 0);
    }

private:
    bool isOdd1(int i) {
        int cnt = 0;
        while (i) {
            cnt += i & 1;
            i >>= 1;
        }
        return cnt % 2;
    }
};

}

/*/
int main() {
    // TODO: prepare parameters here
    vector<int> nums {
        1,1,2,3
    };

    // TODO: add return type and paramters.
    clock_t start = clock();
    auto res = xorGame::Solution().xorGame(nums);
    cout << clock() - start << endl;
    cout << res << endl;
    return 0;
}
//*/
