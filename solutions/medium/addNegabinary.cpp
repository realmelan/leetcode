// addNegabinary.cpp
// leetcode
//
// Created by  Song Ding on 6/17/19.
// Copyright © 2019 Song Ding. All rights reserved.
//
#include "common.h"
using namespace std;

namespace addNegabinary {
/*
// TODO: copy problem statement here
 1073. Adding Two Negabinary Numbers
 Medium
 
 42
 
 22
 
 Favorite
 
 Share
 Given two numbers arr1 and arr2 in base -2, return the result of adding them together.
 
 Each number is given in array format:  as an array of 0s and 1s, from most significant bit to least significant bit.  For example, arr = [1,1,0,1] represents the number (-2)^3 + (-2)^2 + (-2)^0 = -3.  A number arr in array format is also guaranteed to have no leading zeros: either arr == [0] or arr[0] == 1.
 
 Return the result of adding arr1 and arr2 in the same format: as an array of 0s and 1s with no leading zeros.
 
 
 
 Example 1:
 
 Input: arr1 = [1,1,1,1,1], arr2 = [1,0,1]
 Output: [1,0,0,0,0]
 Explanation: arr1 represents 11, arr2 represents 5, the output represents 16.
 
 
 Note:
 
 1 <= arr1.length <= 1000
 1 <= arr2.length <= 1000
 arr1 and arr2 have no leading zeros
 arr1[i] is 0 or 1
 arr2[i] is 0 or 1
 */

class Solution {
public:
    /**
     * starting from the least significant bit:
     *  at odd bit:
     *          current bit, current+1 bit, current+2 bit
     *   0,0 => 0,0,0
     *   1,0 => 1,0,0
     *   1,1 => 0,1,1
     *
     *  at even bit:
     *   0,0 => 0,0,0
     *   1,0 => 1,0,0
     *   1,1 => 0,1,1
     */
    vector<int> addNegabinary(vector<int>& arr1, vector<int>& arr2) {
        vector<int> res;
        int n1 = arr1.size();
        int n2 = arr2.size();
        if (n1 < n2) {
            swap(arr1, arr2);
            swap(n1, n2);
        }
        res.reserve(n1);
        for (int i = n2; i < n1; ++i) {
            arr2.insert(arr2.begin(), 0);
        }
        
        int carry1 = 0;
        int i = n1 - 1;
        for (int i = n1 - 1; i >= 0; --i) {
            /*
            int s = arr1[i] + arr2[i] + carry1;
            switch (s) {
                case 0:
                    res.push_back(0);
                    carry1 = carry2;
                    carry2 = 0;
                    break;
                case 1:
                    res.push_back(1);
                    carry1 = carry2;
                    carry2 = 0;
                    break;
                case 2:
                    res.push_back(0);
                    carry1 = carry2;
                    carry1 += 1;
                    carry2 = 1;
                    if (carry1 == 2) {
                        carry1 = 0;
                        carry2 = 0;
                    }
                    break;
                case 3:
                    res.push_back(1);
                    carry1 = carry2;
                    carry1 += 1;
                    carry2 = 1;
                    if (carry1 == 2) {
                        carry1 = 0;
                        carry2 = 0;
                    }
                    break;
            }
             */
            carry1 += arr1[i] + arr2[i];
            res.push_back(carry1 & 1);
            carry1 = -(carry1 >> 1);
        }
        if (carry1) {
            res.push_back(1);
        }
        while (res.size() > 1 && res.back() == 0) {
            res.pop_back();
        }
        reverse(res.begin(), res.end());
        return res;
    }

private:
};

}

/*/
int main() {
    // TODO: define parameter type here
    struct d {
        vector<int> arr1;
        vector<int> arr2;
    };
    // TODO: prepare parameters here
    vector<struct d> p {
        {{1,1,1,1,1},{1,0,1}},
        {{1},{1,1}}
    };

    vector< vector<int> > answers {
        {1,0,0,0,0},
        {0}
    };

    // TODO: update paramters.
    for (auto& dp : p) {
        cout << endl;
        clock_t tstart = clock();
        auto res = addNegabinary::Solution().addNegabinary(dp.arr1, dp.arr2);
        cout << clock() - tstart << endl;
        cout << res << endl;
    }
    return 0;
}
//*/
