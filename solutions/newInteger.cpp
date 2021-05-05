// newInteger.cpp
// leetcode
//
// Created by  Song Ding on 11/7/19.
// Copyright © 2019 Song Ding. All rights reserved.
//
#include "common.h"
using namespace std;

namespace newInteger {
/*
// TODO: copy problem statement here
 660. Remove 9

 Start from integer 1, remove any integer that contains 9 such as 9, 19, 29...

 So now, you will have a new integer sequence: 1, 2, 3, 4, 5, 6, 7, 8, 10, 11, ...

 Given a positive integer n, you need to return the n-th integer after removing. Note that 1 will be the first integer.

 Example 1:

 Input: 9
 Output: 10
 Hint: n will not exceed 9 x 10^8.
 */

class Solution {
public:
    /**
     * consider this like there are only 9 digits to choose from 0-8, but the base is still 10.
     * when a counter reaches 8, it has to become 10.
     */
    int newInteger(int n) {
        vector<int> digit;
        while (n) {
            digit.push_back(n%9);
            n /= 9;
        }
        int res = 0;
        for (auto it = digit.rbegin(); it != digit.rend(); ++it) {
            res *= 10;
            res += *it;
        }
        return res;
    }
    /**
     * count # of integers having '9' in 10, 100, 1000, ...
     * let count(i) = # of integers having 9 in [10^i, 10^(i+1)-1]
     * and sum(i) = # of integers having 9 in [1, 10^(i+1)-1]
     * then count(i) = 10^i+sum(i-1)*8, for number starting with '9' plus numbers starting with 1-8,
     * but subsequent digits having 9, which = sum(i-1).
     *
     * now for n, keep increasing i until at k, that n can't cover all numbers till 10^(k+1)-1.
     * However, this is complicated.
     */
    int newInteger_wrong(int n) {
        ++n;
        vector<int> count9{1}, count{9}, sum9{1}, sum{9};
        int base = 10;
        while (n > sum.back()) {
            //n -= count.back();
            
            count9.push_back(base + sum9.back()*8);
            sum9.push_back(sum9.back() + count9.back());
            count.push_back(base*10 - sum9.back());
            sum.push_back(sum.back() + count.back());
            
            base *= 10;
        }
        
        sum.pop_back();
        n -= sum.back();
        int res = 0;
        count.pop_back();
        while (n && count.size()) {
            res *= 10;
            res += n / count.back() + 1;
            n %= count.back();
            count.pop_back();
        }
        res *= 10;
        res += n-1;
        return res;
    }

private:
};

}

/*/
int main() {
    // TODO: define parameter type here
    struct d {
        int n;
    };
    // TODO: prepare parameters here
    vector<struct d> p {
        {9},
        {18},
        {17},
    };

    vector< int > answers {
        10,
        20,
        18,
    };

    // TODO: update paramters.
    for (auto& dp : p) {
        cout << endl;
        clock_t tstart = clock();
        auto res = newInteger::Solution().newInteger(dp.n);
        cout << clock() - tstart << endl;
        cout << res << endl;
    }
    return 0;
}
//*/
