// NumArray.cpp
// leetcode
//
// Created by  Song Ding on 9/13/18.
// Copyright © 2018 Song Ding. All rights reserved.
//
#include "common.h"
using namespace std;

namespace NumArray {

class NumArray {
public:
    NumArray(vector<int> nums) {
        int n = nums.size();
        int sum = 0;
        for (int i = 0; i < n; ++i) {
            sum += nums[i];
            _sums.push_back(sum);
        }
        _nums = nums;
    }
    
    void update(int i, int val) {
        for (int j = i; j < _nums.size(); ++j) {
            _sums[j] += val - _nums[i];
        }
        _nums[i] = val;
    }
    
    int sumRange(int i, int j) {
        if (i <= 0) {
            return _sums[j];
        } else {
            return _sums[j] - _sums[i - 1];
        }
    }
private:
    vector<int> _sums;
    vector<int> _nums;
};
    
}

/*/
int main() {
    vector<int> nums { 1,3,5 };
    
    NumArray::NumArray obj(nums);
    cout << obj.sumRange(0, 2) << endl;
    obj.update(1, 2);
    cout << obj.sumRange(0, 2) << endl;
    return 0;
}
//*/
