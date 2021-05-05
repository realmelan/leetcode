//
//  findSubsequences.cpp
//  leetcode
//
//  Created by  Song Ding on 11/19/17.
//  Copyright © 2017 Song Ding. All rights reserved.
//

#include "common.h"

using namespace std;

namespace findSubsequences {
    class Solution {
    public:
        /**
         step 1: add 100 to all integers to make then non-negative
         step 2: for each integer, store the result in a vector of set<vector<int>>,
         so that when looping through the elements, we can easily locate results
         ending at previous elements.
         
         Set is used to remove duplicates.
         
         */
        vector<vector<int>> findSubsequences(vector<int>& nums) {
            vector<vector<int>> res;
            int len = nums.size();
            if (len <= 1) {
                return res;
            }
            
            for (int i = 0; i < len; ++i) {
                nums[i] += 100;
            }
            
            vector<set<vector<int>>> tres(201);
            if (nums[0] <= nums[1]) {
                tres[nums[1]].insert(vector<int>{nums[0], nums[1]});
            }
            
            for (int i = 2; i < len; ++i) {
                int e = nums[i];
                set<vector<int>> eres;
                for (int j = 0; j < i; ++j) {
                    if (nums[j] <= e) {
                        eres.insert(vector<int>{nums[j], e});
                        for (auto v : tres[nums[j]]) {
                            v.push_back(e);
                            eres.insert(v);
                        }
                    }
                }
                tres[e].insert(eres.begin(), eres.end());
            }
            
            for (const auto& s : tres) {
                for (auto v : s) {
                    for (auto & i : v) {
                        i -= 100;
                    }
                    res.push_back(v);
                }
            }
            return res;
        }
    };
}
/*
int main() {
    vector<int> v{4,6,7,7};
    vector<vector<int>> s = findSubsequences::Solution().findSubsequences(v);
    for (auto v : s) {
        for (auto i : v) {
            cout << i << ",";
        }
        cout << endl;
    }
    return 0;
}
*/
