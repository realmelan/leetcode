//
//  maxEnvelopes.cpp
//  leetcode
//
//  Created by  Song Ding on 3/8/18.
//  Copyright © 2018 Song Ding. All rights reserved.
//

#include "common.h"
using namespace std;
/**
 354. Russian Doll Envelopes
 Hard

 734

 29

 Favorite

 Share
 You have a number of envelopes with widths and heights given as a pair of integers (w, h). One envelope can fit into another if and only if both the width and height of one envelope is greater than the width and height of the other envelope.

 What is the maximum number of envelopes can you Russian doll? (put one inside other)

 Note:
 Rotation is not allowed.

 Example:

 Input: [[5,4],[6,4],[6,7],[2,3]]
 Output: 3
 Explanation: The maximum number of envelopes you can Russian doll is 3 ([2,3] => [5,4] => [6,7]).
 */
namespace maxEnvelopes {
    class Solution {
    public:
        /**
         Greedy algorithm:
         NOTE: envelopes can't be rotated.
         
         
         */
        int maxEnvelopes(vector<pair<int, int>>& envelopes) {
            vector<pair<int,int>>& elps = envelopes;
            sort(elps.begin(), elps.end(), [](const pair<int,int>& a, const pair<int,int>& b){
                if (a.second != b.second) {
                    return a.second < b.second;
                } else {
                    return a.first > b.first;
                }
            });
            
            // recording min width for each i russion dolls
            int res = 0;
            vector<int> minWidth{0};
            for (const auto& p : elps) {
                int w = p.first;
                auto it = lower_bound(minWidth.begin(), minWidth.end(), w);
                --it;
                int n = distance(minWidth.begin(), it);
                ++n;
                if (res < n) {
                    res = n;
                }
                if (n + 1 > minWidth.size()) {
                    minWidth.push_back(w);
                } else {
                    if (minWidth[n] > w) {
                        minWidth[n] = w;
                    }
                }
            }
            return res;
        }
    };
}
/*
int main() {
    vector<pair<int, int>> envelopes {
        {46,89},{50,53},{52,68},{72,45},{77,81}
    };
    
    cout << maxEnvelopes::Solution().maxEnvelopes(envelopes) << endl;
}
// */
