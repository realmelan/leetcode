// sortTransformedArray.cpp
// leetcode
//
// Created by  Song Ding on 10/30/19.
// Copyright © 2019 Song Ding. All rights reserved.
//
#include "common.h"
using namespace std;

namespace sortTransformedArray {
/*
// TODO: copy problem statement here
 360. Sort Transformed Array

 Given a sorted array of integers nums and integer values a, b and c. Apply a function of the form f(x) = ax^2 + bx + c to each element x in the array.

 The returned array must be in sorted order.

 Expected time complexity: O(n)

 Example:

 nums = [-4, -2, 2, 4], a = 1, b = 3, c = 5,

 Result: [3, 9, 15, 33]

 nums = [-4, -2, 2, 4], a = -1, b = 3, c = 5

 Result: [-23, -5, 1, 7]
 Credits:
 Special thanks to @elmirap for adding this problem and creating all test cases.
 */

class Solution {
public:
    /**
     * when a >= 0, max value will be from the ends; otherwise, min value will be from the ends.
     */
    vector<int> sortTransformedArray2(vector<int>& nums, int a, int b, int c) {
        int n = nums.size(), i = 0, j = n - 1;
        vector<int> res(n);
        int idx = a >= 0 ? n - 1 : 0;
        while (i <= j) {
            if (a >= 0) {
                res[idx--] = cal(nums[i], a, b, c) >= cal(nums[j], a, b, c) ? cal(nums[i++], a, b, c) : cal(nums[j--], a, b, c);
            } else {
                res[idx++] = cal(nums[i], a, b, c) >= cal(nums[j], a, b, c) ? cal(nums[j--], a, b, c) : cal(nums[i++], a, b, c);
            }
        }
        return res;
    }
    int cal(int x, int a, int b, int c) {
        return a * x * x + b * x + c;
    }
    
    /**
     * first of all, change a to positive integers if a is negative, change b accordingly.
     * if a and b are both positive or 0, then the order will remain the same
     *
     * let's consider a>0&&b<0:
     * when k = b/a, sign of ax^2+bx changes, so divide the array into two group of <k and >k.
     * when x < k, the value decrease as x increase, and vice verca when x > k.
     * then do a merge sort.
     */
    vector<int> sortTransformedArray(vector<int>& nums, int a, int b, int c) {
        vector<int> res;
        int n = nums.size();
        if (a == 0) {
            if (b >= 0) {
                for (auto i : nums) {
                    res.push_back(b*i+c);
                }
            } else {
                for (auto it = nums.rbegin(); it != nums.rend(); ++it) {
                    res.push_back(b*(*it)+c);
                }
            }
        } else {
            int k = -b/a;
            vector<int> left, right;
            int i = 0;
            for (; i < n && nums[i] < k; ++i) {
                int x = nums[i];
                left.push_back(a*x*x + b*x+c);
            }
            for (; i < n; ++i) {
                int x = nums[i];
                right.push_back(a*x*x + b*x + c);
            }
            // now merge left and right
            if (a > 0) {
                i = left.size() - 1;
                k = 0;
                while (i >= 0 && k < right.size()) {
                    if (left[i] < right[k]) {
                        res.push_back(left[i--]);
                    } else {
                        res.push_back(right[k++]);
                    }
                }
                while (i >= 0) {
                    res.push_back(left[i--]);
                }
                while (k < right.size()) {
                    res.push_back(right[k++]);
                }
            } else {
                i = 0;
                k = right.size() - 1;
                while (i < left.size() && k >= 0) {
                    if (left[i] < right[k]) {
                        res.push_back(left[i++]);
                    } else {
                        res.push_back(right[k--]);
                    }
                }
                while (i < left.size()) {
                    res.push_back(left[i++]);
                }
                while (k >= 0) {
                    res.push_back(right[k--]);
                }
            }
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
        vector<int> nums;
        int a;
        int b;
        int c;
    };
    // TODO: prepare parameters here
    vector<struct d> p {
        {{-4, -2, 2, 4},1,3,5,},
        {{-4, -2, 2, 4},-1,3,5},
    };

    vector< vector<int> > answers {
    };

    // TODO: update paramters.
    for (auto& dp : p) {
        cout << endl;
        clock_t tstart = clock();
        auto res = sortTransformedArray::Solution().sortTransformedArray(dp.nums, dp.a, dp.b, dp.c);
        cout << clock() - tstart << endl;
        cout << res << endl;
    }
    return 0;
}
//*/
