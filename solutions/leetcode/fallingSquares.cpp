//
//  fallingSquares.cpp
//  leetcode
//
//  Created by  Song Ding on 2/7/18.
//  Copyright © 2018 Song Ding. All rights reserved.
//

#include "common.h"
using namespace std;

namespace fallingSquares {
    class Solution {
    public:
        /**
         Maintain a map to record the heights at each point(possibly two),
         when a square is to drop, check both left bottom and right bottom
         points to see which side lands on another square, and check all
         covered square sides.
         
         Using negative height for ending side to differentiate starting side
         and ending side.
         
         For each dropping square, compare its height with currently known max
         height, and update max height accordingly.
         */
        vector<int> fallingSquares(vector<pair<int, int>>& positions) {
            vector<int> res;
            int n = positions.size();
            if (n <= 0) {
                return res;
            }
            map<int, pair<int,int>> h;
            int left = positions[0].first;
            int len = positions[0].second;
            int right = left + len;
            h[left] = make_pair(0, len);
            h[right] = make_pair(-len, 0);
            
            int mh = len;
            res.push_back(len);
            for (int i = 1; i < n; ++i) {
                int left = positions[i].first;
                int len = positions[i].second;
                int right = left + len;
                
                auto lit = h.lower_bound(left);
                if (lit == h.end()) {
                    // right most square
                    h[left] = make_pair(0, len);
                    h[right] = make_pair(-len, 0);
                    
                    if (mh < len) {
                        mh = len;
                    }
                    res.push_back(mh);
                } else {
                    int ph = 0;
                    int lh = 0;
                    auto it = lit;
                    if (lit->second.first < 0) {
                        lh = lit->second.first;
                        if (lit->first > left) {
                            ph = -lh;
                        }
                    }
                    
                    // now it points to a starting point of a square
                    while (it != h.end() && it->first < right) {
                        // it points to a left side
                        if (it->second.second > ph) {
                            ph = it->second.second;
                        }
                        it = h.erase(it);
                    }
                    
                    ph += len;
                    
                    // deal with right
                    int rh = 0;
                    if (it != h.end() && it->second.first < 0) {
                        rh = -(lit->second.first);
                    }
                    h[left] = make_pair(lh, ph);
                    h[right] = make_pair(-ph, rh);
                    
                    if (ph > mh) {
                        mh = ph;
                    }
                    res.push_back(mh);
                }
            }
            return res;
        }
    };
}

/*
int main() {
    vector<pair<int,int>> p{
        {2,1},{2,9},{1,8}
    };
    vector<int> res = fallingSquares::Solution().fallingSquares(p);
    printVector(res);
    return 0;
}
 */
