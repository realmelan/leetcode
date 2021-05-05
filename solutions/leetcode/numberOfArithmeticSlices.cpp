// numberOfArithmeticSlices.cpp
// leetcode
//
// Created by  Song Ding on 3/25/18.
// Copyright © 2018 Song Ding. All rights reserved.
//
#include "common.h"
using namespace std;

namespace numberOfArithmeticSlices {
/**
 413. Arithmetic Slices
 Medium

 711

 138

 Favorite

 Share
 A sequence of number is called arithmetic if it consists of at least three elements and if the difference between any two consecutive elements is the same.

 For example, these are arithmetic sequence:

 1, 3, 5, 7, 9
 7, 7, 7, 7
 3, -1, -5, -9
 The following sequence is not arithmetic.

 1, 1, 2, 5, 7

 A zero-indexed array A consisting of N numbers is given. A slice of that array is any pair of integers (P, Q) such that 0 <= P < Q < N.

 A slice (P, Q) of array A is called arithmetic if the sequence:
 A[P], A[p + 1], ..., A[Q - 1], A[Q] is arithmetic. In particular, this means that P + 1 < Q.

 The function should return the number of arithmetic slices in the array A.


 Example:

 A = [1, 2, 3, 4]

 return: 3, for 3 arithmetic slices in A: [1, 2, 3], [2, 3, 4] and [1, 2, 3, 4] itself.
 */

class Solution {
public:
    /**
     * this is for 413. Arithmetic Slices
     */
    int numberOfArithmeticSlices(vector<int>& A) {
        int n = A.size();
        int res = 0;
        vector<unordered_map<long,int>> s(n);
        for (int i = 1; i < n; ++i) {
            long diff = (long)A[i] - A[i-1];
            res += s[i-1][diff];
            s[i][diff] += s[i-1][diff] + 1;
        }
        return res;
    }
    /**
     * this is for 446. Arithmetic Slices II - Subsequence
     * for each A[i], A[j](j<i) pair, check whether an arithmetic can be formed.
     *  when check arithmetic seq of A[i], only need to check A[j][diff], and then update
     *  A[i][diff] as necessary.
     */
    int numberOfArithmeticSlices_2(vector<int>& A) {
        int n = A.size();
        vector<unordered_map<long,int>> s(n);
        int res = 0;
        for (int i = 0; i < n; ++i) {
            // for each A[i], add # of arithmetic seqs it contributes.
            for (int j = i - 1; j >= 0; --j) {
                long diff = (long)A[i] - A[j];
                res += s[j][diff];
                s[i][diff] += s[j][diff] + 1;
            }
        }
        return res;
    }
    int numberOfArithmeticSlices2(vector<int>& A) {
        int res = 0;
        int n = A.size();
        if (n <= 0) {
            return 0;
        }
        
        map<int, int> ac;
        for (auto i : A) {
            ++ac[i];
        }
        
        for (const auto& p : ac) {
            int c = p.second;
            res += (1 << c) - 1 - c - c*(c-1)/2;
        }
        
        vector<pair<int,int>> cnc;
        int last = A.front();
        int c = 1;
        for (int i = 1; i < n; ++i) {
            if (A[i] == last) {
                ++c;
            } else {
                cnc.push_back(make_pair(last, c));
                c = 1;
            }
            last = A[i];
        }
        cnc.push_back(make_pair(last, c));
        
        // not same number
        n = cnc.size();
        for (int i = 0; i < n; ++i) {
            int start = cnc[i].first;
            int fc = cnc[i].second;
            for (int j = i + 1; j < n; ++j) {
                long next = cnc[j].first;
                int sc = cnc[j].second;
                
                long gap = next - start;
                if (gap == 0) {
                    continue;
                }
                long target = next + gap;
                if (target > INT_MAX) {
                    continue;
                }
                
                find(cnc, j + 1, target, gap, fc * sc, res);
            }
        }
        
        return res;
    }
private:
    void find(vector<pair<int, int>>& cnc, int start, long target, long gap, int base, int& res) {
        for (int k = start; k < cnc.size(); ++k) {
            if (cnc[k].first == target) {
                int nb = base * cnc[k].second;
                res += nb;
                if (target + gap <= INT_MAX) {
                    find(cnc, k + 1, target + gap, gap, nb, res);
                }
            }
        }
    }
};

}

/*/
int main() {
    // TODO: prepare parameters here
    vector<int> A{
        1,2,3,4,5,6
        //2,4,6,8,10
        //2,2,3,4
        //2,2,3,3,4
        //0,1,2,2,2
        //0,2000000000,-294967296
        //-2147483648,0,-2147483648
        //1,1,1,1
        //2,2,2,3,3,3,4,4,4,5,5,5
        //79,20,64,28,67,81,60,58,97,85,92,96,82,89,46,50,15,2,36,44,54,2,90,37,7,79,26,40,34,67,64,28,60,89,46,31,9,95,43,19,47,64,48,95,80,31,47,19,72,99,28,46,13,9,64,4,68,74,50,28,69,94,93,3,80,78,23,80,43,49,77,18,68,28,13,61,34,44,80,70,55,85,0,37,93,40,47,47,45,23,26,74,45,67,34,20,33,71,48,96
        //2147483638,2147483639,2147483640,2147483641,2147483642,2147483643,2147483644,2147483645,2147483646,2147483647,-2147483648,-2147483647,-2147483646,-2147483645,-2147483644,-2147483643,-2147483642,-2147483641,-2147483640,-2147483639
    };
    // TODO: add return type and paramters.
    clock_t start = clock();
    auto res = numberOfArithmeticSlices::Solution().numberOfArithmeticSlices(A);
    cout << clock() - start << endl;
    cout << res << endl;
    return 0;
}
//*/
