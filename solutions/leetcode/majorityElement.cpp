// majorityElement.cpp
// leetcode
//
// Created by  Song Ding on 6/4/18.
// Copyright © 2018 Song Ding. All rights reserved.
//
#include "common.h"
using namespace std;

namespace majorityElement {

class Solution {
public:
    /**
     * Boyer-Moore majority vote algorithm
     */
    vector<int> majorityElement(vector<int>& nums) {
        int n = nums.size();
        if (n <= 1) {
            return nums;
        }
        int count1 = 1, count2 = 0;
        int c1 = nums[0], c2 = nums[1];
        for (int i = 1; i < n; ++i) {
            if (nums[i] == c1) {
                ++count1;
            } else if (nums[i] == c2) {
                ++count2;
            } else if (count1 == 0) {
                c1 = nums[i];
                ++count1;
            } else if (count2 == 0) {
                c2 = nums[i];
                ++count2;
            } else {
                --count1;
                --count2;
            }
        }
        
        int c1c = 0, c2c = 0;
        for (auto i : nums) {
            if (i == c1) {
                ++c1c;
            } else if (i == c2) {
                ++c2c;
            }
        }
        vector<int> res;
        if (c1c > n / 3) {
            res.push_back(c1);
        }
        if (c2c > n / 3) {
            res.push_back(c2);
        }
        return res;
    }

private:
};

}

/*/
int main() {
    // TODO: prepare parameters here
    vector<int> nums{2,2};
    // TODO: add return type and paramters.
    clock_t start = clock();
    auto res = majorityElement::Solution().majorityElement(nums);
    cout << clock() - start << endl;
    cout << res << endl;
    return 0;
}
//*/
