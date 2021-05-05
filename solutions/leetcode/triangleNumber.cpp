//
//  triangleNumber.cpp
//  leetcode
//
//  Created by  Song Ding on 11/6/17.
//  Copyright © 2017 Song Ding. All rights reserved.
//

#include "common.h"

using namespace std;

namespace triangleNumber {
    class Solution {
    public:
        /**
         Sort the nums into ascending order
         
         For the i-th element in nums, consider the length's that
         are smaller, i.e. elements before i in nums.
         1, for all possible pairs that can form a triange with (i - 1)
         -th, find a possible upperbound using binary search(log(n))
         2, consider i-th and (i-1)th element, and another element
         from 1'st to the (i - 2)'th element.
         
         Because each step of 1 or 2 takes O(log(n)), thus the total
         cost after sort is O(nlog(n)).
         
         */
        int triangleNumber(vector<int>& nums) {
            int len = nums.size();
            if (len <= 2) {
                return 0;
            }
            
            sort(nums.begin(), nums.end());
            auto rit = remove(nums.begin(), nums.end(), 0);
            nums.erase(rit, nums.end());
            len = nums.size();
            if (len <= 2) {
                return 0;
            }
            
            int count = 0;
            int lastElem = nums[0];
            int lastIndex = 0;
            vector<int> sorted{lastElem};
            map<int, int> elemCounts;
            auto it = nums.begin();
            for (int i = 1; i < len; ++i) {
                int c = nums[i];
                if (c != lastElem) {
                    sorted.push_back(c);
                    // do calculation
                    int elemCount = i - lastIndex;
                    elemCounts[lastElem] = elemCount;
                    
                    // find triangles with two equal sides
                    // find next element which is no less than 2 * lastElem
                    if (elemCount >= 2) {
                        auto nit = lower_bound(it, nums.end(), 2*lastElem);
                        int validSideCount = nit - nums.begin() - elemCount;
                        count += elemCount * (elemCount - 1) / 2 * validSideCount;
                        
                        
                        // find triangles with 3 equal sides
                        count += elemCount * (elemCount - 1) * (elemCount - 2) / 6;
                    }
                    
                    
                    lastElem = c;
                    lastIndex = i;
                }
            }
            
            int elemCount = len - lastIndex;
            elemCounts[lastElem] = elemCount;
            if (elemCount >= 2) {
                int validSideCount = len - elemCount;
                count += elemCount * (elemCount - 1) / 2 * validSideCount;
                count += elemCount * (elemCount - 1) * (elemCount - 2) / 6;
            }
            
            len = sorted.size();
            if (len <= 2) {
                return count;
            }
            
            // find triangles with all sides are different
            vector<pair<int, int>> pairs;
            auto bit = sorted.begin();
            for (int i = 2; i < len; ++i) {
                int c = sorted[i];
                int b = sorted[i - 1];
                advance(bit, 1);
                
                // consider possible pairs in pairSums from previous element
                auto pit = upper_bound(pairs.begin(), pairs.end(), c,
                                       [](int val, const pair<int, int>& p){return val < p.first + p.second;});
                if (pit != pairs.begin()) {
                    pairs.erase(pairs.begin(), pit);
                }
                
                // consider c, b, and another element before b.
                auto ait = upper_bound(sorted.begin(), bit, c - b);
                for (; ait != bit; ++ait) {
                    pairs.push_back(make_pair(*ait, b));
                }
                
                for (auto kv : pairs) {
                    count += elemCounts[kv.first] * elemCounts[kv.second] * elemCounts[c];
                }
                
                sort(pairs.begin(), pairs.end(),
                     [](const pair<int, int>& p1, const pair<int, int>& p2){
                         return (p1.first + p1.second) < (p2.first + p2.second);
                     });
            }
            return count;
        }
    };
}
/*
int main() {
    //vector<int> nums{66,99,36,44,26,99,32,64,19,69};
    vector<int> nums{82,15,23,82,67,0,3,92,11};
    cout << triangleNumber::Solution().triangleNumber(nums) << endl;
    return 0;
}
*/
