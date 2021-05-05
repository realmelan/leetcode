// judgePoint24.cpp
// leetcode
//
// Created by  Song Ding on 10/16/18.
// Copyright © 2018 Song Ding. All rights reserved.
//
#include "common.h"
using namespace std;

namespace judgePoint24 {

class Solution {
public:
    bool judgePoint24(vector<int>& nums) {
        vector<double> dnums;
        for (auto i : nums) {
            dnums.push_back(i);
        }
        
        set<double> res = values(dnums);
        for (auto d : res) {
            if (abs(d - 24) < 0.000001) {
                return true;
            }
        }
        return false;
    }

private:
    void addValues(set<double>& values, double v1, double v2) {
        values.insert(v1 * v2);
        values.insert(v1 + v2);
        values.insert(v1 - v2);
        values.insert(v2 - v1);
        if (v1 != 0) {
            values.insert(v2 / v1);
        }
        if (v2 != 0) {
            values.insert(v1 / v2);
        }
    }
    set<double> values(vector<double> nums) {
        set<double> res;
        int n = nums.size();
        if (n == 2) {
            addValues(res, nums[0], nums[1]);
        } else {
            for (int i = 0; i < n; ++i) {
                // 1 and other
                double val = nums[i];
                vector<double> rest(nums);
                rest.erase(rest.begin() + i);
                
                set<double> restValues = values(rest);
                for (double d : restValues) {
                    addValues(res, val, d);
                }
            }
            
            if (n == 4) {
                for (int i = 1; i < n; ++i) {
                    vector<double> first;
                    first.push_back(nums[0]);
                    first.push_back(nums[i]);
                    
                    vector<double> second;
                    for (int j = 1; j < n; ++j) {
                        if (j != i) {
                            second.push_back(nums[j]);
                        }
                    }
                    
                    set<double> firstValues = values(first);
                    set<double> secondValues = values(second);
                    
                    for (double fv : firstValues) {
                        for (double sv : secondValues) {
                            addValues(res, fv, sv);
                        }
                    }
                }
            }
        }
        return res;
        
    }
};

}

/*/
int main() {
    // TODO: prepare parameters here
    vector<int> nums {
        //1,2,1,2
        //8,1,6,6
        3,3,8,8
    };

    // TODO: add return type and paramters.
    clock_t start = clock();
    auto res = judgePoint24::Solution().judgePoint24(nums);
    cout << clock() - start << endl;
    cout << res << endl;
    return 0;
}
//*/
