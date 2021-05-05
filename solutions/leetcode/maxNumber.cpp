// maxNumber.cpp
// leetcode
//
// Created by  Song Ding on 4/1/18.
// Copyright © 2018 Song Ding. All rights reserved.
//
#include "common.h"
using namespace std;

namespace maxNumber {
/**
 321. Create Maximum Number
 Hard

 771

 245

 Add to List

 Share
 Given two arrays of length m and n with digits 0-9 representing two numbers. Create the maximum number of length k <= m + n from digits of the two. The relative order of the digits from the same array must be preserved. Return an array of the k digits.

 Note: You should try to optimize your time and space complexity.

 Example 1:

 Input:
 nums1 = [3, 4, 6, 5]
 nums2 = [9, 1, 2, 5, 8, 3]
 k = 5
 Output:
 [9, 8, 6, 5, 3]
 Example 2:

 Input:
 nums1 = [6, 7]
 nums2 = [6, 0, 4]
 k = 5
 Output:
 [6, 7, 6, 0, 4]
 Example 3:

 Input:
 nums1 = [3, 9]
 nums2 = [8, 9]
 k = 3
 Output:
 [9, 8, 9]
 */
class Solution {
public:
    vector<int> maxNumber2(vector<int>& nums1, vector<int>& nums2, int k) {
        vector<int> res(k, 0);
        int n1 = nums1.size(), n2 = nums2.size();
        // keep s1 - k1 integers from nums1, keep k-i from nums2
        int s1 = max(0, k-n2), k1 = min(k, n1);
        for (int i = s1; i <= k1; ++i) {
            vector<int> v1;
            for (int j = 0; j < n1; ++j) {
                while (v1.size() && v1.size() + n1-j > i && v1.back() < nums1[j]) {
                    v1.pop_back();
                }
                v1.push_back(nums1[j]);
            }
            vector<int> v2;
            for (int j = 0; j < n2; ++j) {
                while (v2.size() && v2.size() + n2-j > (k-i) && v2.back() < nums2[j]) {
                    v2.pop_back();
                }
                v2.push_back(nums2[j]);
            }
            
            // merge v1 and v2
            vector<int> t;
            int p = 0, q = 0;
            while (p < i || q < k-i) {
                int j = 0;
                //TODO: why this comparison would work?
                while (p+j < i && q+j < k-i && v1[p+j] == v2[q+j]) {
                    ++j;
                }
                if (p+j >= i || (q+j < k-i && v1[p+j] < v2[q+j])) {
                    t.push_back(v2[q++]);
                } else {
                    t.push_back(v1[p++]);
                }
            }
            res = max(res, t);
        }
        return res;
    }
    /**
     Find max sequence of length 1 to n for each array.
     then for different combinations of (i,j) where i + j = k, find the
     largest combinations using the max sequences.
     */
    vector<int> maxNumber(vector<int>& nums1, vector<int>& nums2, int k) {
        vector<int> res;
        int n1 = nums1.size();
        int n2 = nums2.size();
        if (k <= 0) {
            return res;
        }
        
        // for each array, find the largest sequence of length from 1 to k
        // then for each possible combination: i from nums1, k - i from nums2.
        int k1 = min(n1, k);
        vector<vector<int>> maxSeq1(k1 + 1);
        vector<vector<int>> seq1(n1);
        for (int i = 0; i < n1; ++i) {
            if (i) {
                seq1[i].push_back(std::max(nums1[i], seq1[i - 1].back()));
            } else {
                seq1[i].push_back(nums1[i]);
            }
            if (maxSeq1[1] < seq1[i]) {
                maxSeq1[1] = seq1[i];
            }
        }
        for (int i = 2; i <= k1; ++i) {
            vector<vector<int>> cur(n1);
            cur[i - 1] = seq1[i - 2];
            cur[i - 1].push_back(nums1[i - 1]);
            maxSeq1[i] = cur[i - 1];
            for (int j = i; j < n1; ++j) {
                cur[j] = cur[j - 1];
                vector<int> t(seq1[j - 1]);
                t.push_back(nums1[j]);
                if (cur[j] < t) {
                    cur[j].swap(t);
                }
                if (maxSeq1[i] < cur[j]) {
                    maxSeq1[i] = cur[j];
                }
            }
            seq1.swap(cur);
        }
        int k2 = min(n2, k);
        vector<vector<int>> maxSeq2(k2 + 1);
        vector<vector<int>> seq2(n2);
        for (int i = 0; i < n2; ++i) {
            if (i) {
                seq2[i].push_back(std::max(nums2[i], seq2[i - 1].back()));
            } else {
                seq2[i].push_back(nums2[i]);
            }
            if (maxSeq2[1] < seq2[i]) {
                maxSeq2[1] = seq2[i];
            }
        }
        for (int i = 2; i <= k2; ++i) {
            vector<vector<int>> cur(n2);
            cur[i - 1] = seq2[i - 2];
            cur[i - 1].push_back(nums2[i - 1]);
            maxSeq2[i] = cur[i - 1];
            for (int j = i; j < n2; ++j) {
                cur[j] = cur[j - 1];
                vector<int> t(seq2[j - 1]);
                t.push_back(nums2[j]);
                if (cur[j] < t) {
                    cur[j].swap(t);
                }
                if (maxSeq2[i] < cur[j]) {
                    maxSeq2[i] = cur[j];
                }
            }
            seq2.swap(cur);
        }
        
        // now two max seq's are ready, loop through all possible combinations
        for (int i = 0; i <= k1; ++i) {
            if (k - i > k2) {
                continue;
            }
            int j = k - i;
            // compose the vector for this combination, by pick larger from two sequences
            vector<int> t;
            int i1 = 0;
            int i2 = 0;
            while (i1 < i && i2 < j) {
                if (maxSeq1[i][i1] > maxSeq2[j][i2]) {
                    t.push_back(maxSeq1[i][i1++]);
                } else if (maxSeq1[i][i1] < maxSeq2[j][i2]){
                    t.push_back(maxSeq2[j][i2++]);
                } else {
                    //if (i1 + 1 < i && maxSeq1[i1 + 1])
                    int ii1 = i1 + 1;
                    int ii2 = i2 + 1;
                    while (ii1 < i && ii2 < j && maxSeq1[i][ii1] == maxSeq2[j][ii2]) {
                        ++ii1;
                        ++ii2;
                    }
                    if (ii1 >= i) {
                        t.push_back(maxSeq2[j][i2++]);
                    } else if (ii2 >= j) {
                        t.push_back(maxSeq1[i][i1++]);
                    } else {
                        if (maxSeq1[i][ii1] < maxSeq2[j][ii2]) {
                            t.push_back(maxSeq2[j][i2++]);
                        } else {
                            t.push_back(maxSeq1[i][i1++]);
                        }
                    }
                }
            }
            while (i1 < i) {
                t.push_back(maxSeq1[i][i1++]);
            }
            while (i2 < j) {
                t.push_back(maxSeq2[j][i2++]);
            }
            if (res < t) {
                res.swap(t);
            }
        }
        return res;
    }

private:
};

}

/*/
int main() {
    // TODO: prepare parameters here
    struct d {
        vector<int> nums1;
        vector<int> nums2;
        int k;
    };
    // TODO: prepare parameters here
    vector<struct d> p {
        //{{3, 4, 6, 5},{9, 1, 2, 5, 8, 3},5},
        //{{3,4,8,9,3,0},{6,1,9,1,1,2},6},
        //{{3,9},{8,9},3},
        {{3,8,5,3,4},{8,7,3,6,8},5},
        {{2,5,6,4,4,0},{7,3,8,0,6,5,7,6,2},15}
    };

    vector< vector<int> > answers {
        {9,8,6,5,3},
        {9,9,3,1,2,0},
        {9,8,9},
        {8,8,8,5,4},
        {7,3,8,2,5,6,4,4,0,6,5,7,6,2,0}
    };

    // TODO: update paramters.
    for (auto& dp : p) {
        cout << endl;
        clock_t tstart = clock();
        auto res = maxNumber::Solution().maxNumber2(dp.nums1, dp.nums2, dp.k);
        cout << clock() - tstart << endl;
        cout << res << endl;
    }
    return 0;
}
//*/
