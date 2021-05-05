// minEatingSpeed.cpp
// leetcode
//
// Created by  Song Ding on 5/15/19.
// Copyright © 2019 Song Ding. All rights reserved.
//
#include "common.h"
using namespace std;

namespace minEatingSpeed {
/*
 875. Koko Eating Bananas
 Medium
 
 284
 
 31
 
 Favorite
 
 Share
 Koko loves to eat bananas.  There are N piles of bananas, the i-th pile has piles[i] bananas.  The guards have gone and will come back in H hours.
 
 Koko can decide her bananas-per-hour eating speed of K.  Each hour, she chooses some pile of bananas, and eats K bananas from that pile.  If the pile has less than K bananas, she eats all of them instead, and won't eat any more bananas during this hour.
 
 Koko likes to eat slowly, but still wants to finish eating all the bananas before the guards come back.
 
 Return the minimum integer K such that she can eat all the bananas within H hours.
 
 
 
 Example 1:
 
 Input: piles = [3,6,7,11], H = 8
 Output: 4
 Example 2:
 
 Input: piles = [30,11,23,4,20], H = 5
 Output: 30
 Example 3:
 
 Input: piles = [30,11,23,4,20], H = 6
 Output: 23
 
 
 Note:
 
 1 <= piles.length <= 10^4
 piles.length <= H <= 10^9
 1 <= piles[i] <= 10^9
 */
class Solution {
public:
    /**
     * use binary search to find the minimum.
     * The upper bound can be determined by the largest pile
     * divided by the hours for each pile.
     * The lower bound can be determined by the smallest pile.
     *
     * The invariant is:
     * time(r) <= H while time(l) > H.
     */
    int minEatingSpeed(vector<int>& piles, int H) {
        int n = piles.size();
        sort(piles.begin(), piles.end());
        long r = (long)piles[n-1] * n / H + 1;
        long l = (long)piles[0] * n / H;
        while (r - l > 1) {
            int m = (l + r) / 2;
            int t = time(piles, m);
            if (t > H) {
                l = m;
            } else {
                r = m;
            }
        }
        return r;
    }

private:
    int time(const vector<int>& piles, int s) {
        int t = 0;
        for (auto i : piles) {
            t += (i + s - 1) / s;
        }
        return t;
    }
};

}

/*/
int main() {
    // TODO: prepare parameters here
    struct d {
        vector<int> piles;
        int H;
    };
    vector<struct d> p {
        {{3,6,7,11},8},
        {{30,11,23,4,20},5},
        {{30,11,23,4,20},6}
    };

    vector<  int > answers {
        4,
        30,
        23
    };
    int i = 2;

    // TODO: add return type and paramters.
    clock_t tstart = clock();
    auto res = minEatingSpeed::Solution().minEatingSpeed(p[i].piles, p[i].H);
    cout << clock() - tstart << endl;
    cout << res << endl;
    return 0;
}
//*/
