// deckRevealedIncreasing.cpp
// leetcode
//
// Created by  Song Ding on 6/1/19.
// Copyright © 2019 Song Ding. All rights reserved.
//
#include "common.h"
using namespace std;

namespace deckRevealedIncreasing {
/*
// TODO: copy problem statement here
 950. Reveal Cards In Increasing Order
 Medium
 
 306
 
 60
 
 Favorite
 
 Share
 In a deck of cards, every card has a unique integer.  You can order the deck in any order you want.
 
 Initially, all the cards start face down (unrevealed) in one deck.
 
 Now, you do the following steps repeatedly, until all cards are revealed:
 
 Take the top card of the deck, reveal it, and take it out of the deck.
 If there are still cards in the deck, put the next top card of the deck at the bottom of the deck.
 If there are still unrevealed cards, go back to step 1.  Otherwise, stop.
 Return an ordering of the deck that would reveal the cards in increasing order.
 
 The first entry in the answer is considered to be the top of the deck.
 
 
 
 Example 1:
 
 Input: [17,13,11,2,3,5,7]
 Output: [2,13,3,11,5,17,7]
 Explanation:
 We get the deck in the order [17,13,11,2,3,5,7] (this order doesn't matter), and reorder it.
 After reordering, the deck starts as [2,13,3,11,5,17,7], where 2 is the top of the deck.
 We reveal 2, and move 13 to the bottom.  The deck is now [3,11,5,17,7,13].
 We reveal 3, and move 11 to the bottom.  The deck is now [5,17,7,13,11].
 We reveal 5, and move 17 to the bottom.  The deck is now [7,13,11,17].
 We reveal 7, and move 13 to the bottom.  The deck is now [11,17,13].
 We reveal 11, and move 17 to the bottom.  The deck is now [13,17].
 We reveal 13, and move 17 to the bottom.  The deck is now [17].
 We reveal 17.
 Since all the cards revealed are in increasing order, the answer is correct.
 
 
 Note:
 
 1 <= A.length <= 1000
 1 <= A[i] <= 10^6
 A[i] != A[j] for all i != j
 */

class Solution {
public:
    /**
     * reverse the ordering:
     *   use a deque, always move the bottom card to top and push top a new card.
     */
    vector<int> deckRevealedIncreasing(vector<int>& deck) {
        sort(deck.begin(), deck.end(), greater<int>());
        deque<int> w;
        for (auto i : deck) {
            w.push_front(i);
            int b = w.back();
            w.push_front(b);
            w.pop_back();
        }
        int f = w.front();
        w.pop_front();
        w.push_back(f);
        
        vector<int> res;
        while (w.size()) {
            res.push_back(w.front());
            w.pop_front();
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
        vector<int> deck;
    };
    // TODO: prepare parameters here
    vector<struct d> p {
        {{17,13,11,2,3,5,7}}
    };

    vector< vector<int> > answers {
        {2,13,3,11,5,17,7}
    };

    // TODO: update paramters.
    for (auto& dp : p) {
        cout << endl;
        clock_t tstart = clock();
        auto res = deckRevealedIncreasing::Solution().deckRevealedIncreasing(dp.deck);
        cout << clock() - tstart << endl;
        cout << res << endl;
    }
    return 0;
}
//*/
