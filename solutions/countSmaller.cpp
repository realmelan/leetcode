// countSmaller.cpp
// leetcode
//
// Created by  Song Ding on 10/2/19.
// Copyright © 2019 Song Ding. All rights reserved.
//
#include "common.h"
using namespace std;

namespace countSmaller {
/*
// TODO: copy problem statement here
 315. Count of Smaller Numbers After Self
 Hard

 1428

 61

 Favorite

 Share
 You are given an integer array nums and you have to return a new counts array. The counts array has the property where counts[i] is the number of smaller elements to the right of nums[i].

 Example:

 Input: [5,2,6,1]
 Output: [2,1,1,0]
 Explanation:
 To the right of 5 there are 2 smaller elements (2 and 1).
 To the right of 2 there is only 1 smaller element (1).
 To the right of 6 there is 1 smaller element (1).
 To the right of 1 there is 0 smaller element.
 */

class Solution {
public:
    /**
     * use mergeSort to count how many right elements are replaced before a left element during merge.
     * https://leetcode.com/problems/count-of-smaller-numbers-after-self/discuss/76584/Mergesort-solution
     */
    vector<int> countSmaller(vector<int>& nums) {
        // internal value: 0=>val, 1=>index
        int n = nums.size();
        vector<int> res(n, 0);
        vector<vector<int>> valIdx(n);
        for (int i = 0; i < n; ++i) {
            valIdx[i] = {nums[i],i};
        }
        mergeSort(valIdx, 0, n-1, res);
        return res;
    }
private:
    void mergeSort(vector<vector<int>>& valIdx, int left, int right, vector<int>& res) {
        if (left == right) {
            return;
        }
        int mid = (left + right) / 2;
        mergeSort(valIdx, left, mid, res);
        mergeSort(valIdx, mid+1, right, res);
        
        // how to merge inplace?
        vector<vector<int>> tmp;
        int i = left;
        int j = mid+1;
        while (i <= mid || j <= right) {
            if (j > right || (i <= mid && valIdx[i][0] <= valIdx[j][0])) {
                tmp.push_back(valIdx[i]);
                res[valIdx[i][1]] += j - mid - 1; // elements from mid+1 to j-1 are smaller than valIdx[i] and on the right of it.
                ++i;
            } else {
                tmp.push_back(valIdx[j]);
                ++j;
            }
        }
        // put tmp back in place
        for (int i = left; i <= right; ++i) {
            swap(valIdx[i], tmp[i-left]);
        }
    }
    
};

}

/*/
int main() {
    // TODO: define parameter type here
    struct d {
        vector<int> nums;
    };
    // TODO: prepare parameters here
    vector<struct d> p {
        {{5,2,6,1}},
    };

    vector< vector<int> > answers {
        {2,1,1,0},
    };

    // TODO: update paramters.
    for (auto& dp : p) {
        cout << endl;
        clock_t tstart = clock();
        auto res = countSmaller::Solution().countSmaller(dp.nums);
        cout << clock() - tstart << endl;
        cout << res << endl;
    }
    return 0;
}
//*/
