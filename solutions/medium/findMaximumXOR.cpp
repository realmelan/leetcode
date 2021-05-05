// findMaximumXOR.cpp
// leetcode
//
// Created by  Song Ding on 9/30/19.
// Copyright © 2019 Song Ding. All rights reserved.
//
#include "common.h"
using namespace std;

namespace findMaximumXOR {
/*
// TODO: copy problem statement here
 421. Maximum XOR of Two Numbers in an Array
 Medium

 793

 155

 Favorite

 Share
 Given a non-empty array of numbers, a0, a1, a2, … , an-1, where 0 ≤ ai < 231.

 Find the maximum result of ai XOR aj, where 0 ≤ i, j < n.

 Could you do this in O(n) runtime?

 Example:

 Input: [3, 10, 5, 25, 2, 8]

 Output: 28

 Explanation: The maximum result is 5 ^ 25 = 28.
 */

class Solution {
public:
    int findMaximumXOR3(vector<int>& nums) {
        int res = 0, mask = 0;
        for (int i = 31; i >= 0; --i) {
            unordered_set<int> m;
            mask |= (1<<i);
            int tres = (res | (1<<i));
            for (auto k : nums) {
                if (m.count((k&mask)^tres)) {
                    res = tres;
                    break;
                }
                m.insert(k&mask);
            }
        }
        return res;
    }
    /**
     * starting from the most significant bit, and test whether 1 can be set, given previouse result.
     * say at the i-th bit, we can result prefix res(i), and we want to test whether 1 can be set at i+1-th
     * bit:
     *  get all i+1-th prefix of nums into a hashmap, and then test whether res(i) | (1<<31-i-1) can be obtained
     *  using 2 i+1-th prefix nums, a, b. This test can be done, by test whether res(i+1)^a exists in the hashmap or not.
     * see https://leetcode.com/problems/maximum-xor-of-two-numbers-in-an-array/discuss/91049/Java-O(n)-solution-using-bit-manipulation-and-HashMap
     */
    int findMaximumXOR(vector<int>& nums) {
        int res = 0, mask = 0;
        for (int i = 31; i >= 0; --i) {
            mask |= (1 << i);
            unordered_set<int> prefix;
            for (auto num : nums) {
                prefix.insert(num & mask);
            }
            int t = res | (1 << i);
            for (auto p : prefix) {
                if (prefix.count(p^t)) {
                    res = t;
                    break;
                }
            }
        }
        return res;
    }
    /**
     * starting from first bit, divide nums into a pair of num array, whose first bit is 0 and 1 respectively.
     * then iteratively divide the pair into multiple pairs based on next bit.
     */
    int findMaximumXOR2(vector<int>& nums) {
        int n = nums.size();
        if (n<=1) {
            return nums[0];
        }
        vector<pair<vector<int>, vector<int>>> cur;
        for (int i = 31; i >= 0; --i) {
            int bit = (1 << i);
            if (cur.size()) {
                vector<pair<vector<int>,vector<int>>> next;
                for (auto& pg : cur) {
                    auto& g1 = pg.first;
                    auto& g2 = pg.second;
                    
                    // divide g1 into bit1, bit0
                    vector<int> g1bit1, g1bit0;
                    for (auto num : g1) {
                        if (bit & num) {
                            g1bit1.push_back(num);
                        } else {
                            g1bit0.push_back(num);
                        }
                    }
                    // divide g2 into bit1, bit0
                    vector<int> g2bit1, g2bit0;
                    for (auto num : g2) {
                        if (bit & num) {
                            g2bit1.push_back(num);
                        } else {
                            g2bit0.push_back(num);
                        }
                    }
                    if (g1bit1.size() && g2bit0.size())  {
                        next.push_back(make_pair(g1bit1, g2bit0));
                    }
                    if (g1bit0.size() && g2bit1.size()) {
                        next.push_back(make_pair(g1bit0, g2bit1));
                    }
                }
                if (next.size()) {
                    cur.swap(next);
                }
            } else {
                vector<int> bit1, bit0;
                for (auto num : nums) {
                    if (bit & num) {
                        bit1.push_back(num);
                    } else {
                        bit0.push_back(num);
                    }
                }
                if (bit1.size() < n && bit0.size() < n) {
                    cur.push_back(make_pair(bit1, bit0));
                }
            }
        }
        
        auto& pg = cur[0];
        return pg.first[0] ^ pg.second[0];
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
        {{0}},
        {{3, 10, 5, 25, 2, 8}},
    };

    vector< int > answers {
        0,
        28,
    };

    // TODO: update paramters.
    for (auto& dp : p) {
        cout << endl;
        clock_t tstart = clock();
        auto res = findMaximumXOR::Solution().findMaximumXOR3(dp.nums);
        cout << clock() - tstart << endl;
        cout << res << endl;
    }
    return 0;
}
//*/
