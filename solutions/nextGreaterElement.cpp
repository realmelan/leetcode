// nextGreaterElement.cpp
// leetcode
//
// Created by  Song Ding on 10/22/19.
// Copyright © 2019 Song Ding. All rights reserved.
//
#include "common.h"
using namespace std;

namespace nextGreaterElement {
/*
// TODO: copy problem statement here
 556. Next Greater Element III

 Given a positive 32-bit integer n, you need to find the smallest 32-bit integer which has exactly the same digits existing in the integer n and is greater in value than n. If no such positive 32-bit integer exists, you need to return -1.

 Example 1:

 Input: 12
 Output: 21
 Example 2:

 Input: 21
 Output: -1
 */

class Solution {
public:
    /**
     * This looks like Knuth's next permutation.
     * Scan from right to left, and find first position i such that n[i] < n[i+1]
     * then, find a value k in n[i+1...n] that is >n[i], swap n[i] and n[k].
     * then reverse n[i+1] to n[n].
     */
    int nextGreaterElement(int n) {
        vector<int> d;
        while (n) {
            d.push_back(n%10);
            n /= 10;
        }
        int nd = d.size();
        int i = 1;
        while (i < nd && d[i] >= d[i-1]) {
            ++i;
        }
        if (i >= nd) {
            return -1;
        }
        
        int j = 0;
        while (j < i && d[j] <= d[i]) {
            ++j;
        }
        swap(d[i], d[j]);
        std::reverse(d.begin(), d.begin() + i);
        int res = 0;
        // it might overflow
        for (j = nd-1; j >= 0; --j) {
            res *= 10;
            if (res < 0) {
                return -1;
            }
            res += d[j];
            if (res < 0) {
                return -1;
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
        int n;
    };
    // TODO: prepare parameters here
    vector<struct d> p {
        //{12},
        //{21},
        //{230241},
        {12443322},
    };

    vector< int > answers {
        21,
        -1,
        230412,
        13222344
    };

    // TODO: update paramters.
    for (auto& dp : p) {
        cout << endl;
        clock_t tstart = clock();
        auto res = nextGreaterElement::Solution().nextGreaterElement(dp.n);
        cout << clock() - tstart << endl;
        cout << res << endl;
    }
    return 0;
}
//*/
