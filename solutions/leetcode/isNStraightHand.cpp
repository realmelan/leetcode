// isNStraightHand.cpp
// leetcode
//
// Created by  Song Ding on 5/21/19.
// Copyright © 2019 Song Ding. All rights reserved.
//
#include "common.h"
using namespace std;

namespace isNStraightHand {
/*
// TODO: copy problem statement here
 846. Hand of Straights
 Medium
 
 272
 
 39
 
 Favorite
 
 Share
 Alice has a hand of cards, given as an array of integers.
 
 Now she wants to rearrange the cards into groups so that each group is size W, and consists of W consecutive cards.
 
 Return true if and only if she can.
 
 
 
 Example 1:
 
 Input: hand = [1,2,3,6,2,3,4,7,8], W = 3
 Output: true
 Explanation: Alice's hand can be rearranged as [1,2,3],[2,3,4],[6,7,8].
 Example 2:
 
 Input: hand = [1,2,3,4,5], W = 4
 Output: false
 Explanation: Alice's hand can't be rearranged into groups of 4.
 
 
 Note:
 
 1 <= hand.length <= 10000
 0 <= hand[i] <= 10^9
 1 <= W <= hand.length
 */

class Solution {
public:
    /**
     * let count[i] = # of card i
     * starting from the smallest card, and check whether there are consecutive W cards.
     * And decrease the card count for the W cards if they exist.
     */
    bool isNStraightHand(vector<int>& hand, int W) {
        map<int, int> count;
        for (auto i : hand) {
            ++count[i];
        }
        
        while (count.size()) {
            auto it = count.begin();
            int card = it->first;
            int cnt = it->second;
            int lastCnt = cnt;
            it = count.erase(it);
            int i = 1;
            for (; i < W && it != count.end(); ++i) {
                ++card;
                if (it->first != card || it->second < lastCnt) {
                    return false;
                }
                
                lastCnt = it->second;
                it->second -= cnt;
                if (it->second == 0) {
                    it = count.erase(it);
                } else {
                    ++it;
                }
            }
            if (i < W) {
                return false;
            }
        }
        return true;
    }

private:
};

}

/*/
int main() {
    // TODO: define parameter type here
    struct d {
        vector<int> hand;
        int W;
    };
    // TODO: prepare parameters here
    vector<struct d> p {
        {{1,2,3,6,2,3,4,7,8},3},
        {{1,2,3,4,5},4}
    };

    vector< bool > answers {
        true,
        false
    };

    // TODO: update paramters.
    for (auto& dp : p) {
        cout << endl;
        clock_t tstart = clock();
        auto res = isNStraightHand::Solution().isNStraightHand(dp.hand, dp.W);
        cout << clock() - tstart << endl;
        cout << res << endl;
    }
    return 0;
}
//*/
