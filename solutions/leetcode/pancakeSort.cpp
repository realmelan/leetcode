// pancakeSort.cpp
// leetcode
//
// Created by  Song Ding on 6/1/19.
// Copyright © 2019 Song Ding. All rights reserved.
//
#include "common.h"
using namespace std;

namespace pancakeSort {
/*
// TODO: copy problem statement here
 969. Pancake Sorting
 Medium
 
 126
 
 148
 
 Favorite
 
 Share
 Given an array A, we can perform a pancake flip: We choose some positive integer k <= A.length, then reverse the order of the first k elements of A.  We want to perform zero or more pancake flips (doing them one after another in succession) to sort the array A.
 
 Return the k-values corresponding to a sequence of pancake flips that sort A.  Any valid answer that sorts the array within 10 * A.length flips will be judged as correct.
 
 
 
 Example 1:
 
 Input: [3,2,4,1]
 Output: [4,2,4,3]
 Explanation:
 We perform 4 pancake flips, with k values 4, 2, 4, and 3.
 Starting state: A = [3, 2, 4, 1]
 After 1st flip (k=4): A = [1, 4, 2, 3]
 After 2nd flip (k=2): A = [4, 1, 2, 3]
 After 3rd flip (k=4): A = [3, 2, 1, 4]
 After 4th flip (k=3): A = [1, 2, 3, 4], which is sorted.
 Example 2:
 
 Input: [1,2,3]
 Output: []
 Explanation: The input is already sorted, so there is no need to flip anything.
 Note that other answers, such as [3, 3], would also be accepted.
 */

class Solution {
public:
    /**
     * recursive:
     * always try to flip the largest to top and then to bottom.
     */
    vector<int> pancakeSort(vector<int>& A) {
        int n = A.size();
        vector<int> res;
        
        vector<int> B(A);
        int len = B.size();
        while (len > 1) {
            int maxe = B[0];
            int maxi = 0;
            for (int i = 1; i < len; ++i) {
                if (B[i] > maxe) {
                    maxe = B[i];
                    maxi = i;
                }
            }
            if (maxi == len - 1) {
                --len;
                continue;
            }
            
            if (maxi) {
                res.push_back(maxi+1);
            }
            
            
            res.push_back(len);
            
            vector<int> C;
            for (int i = len - 1; i > maxi; --i) {
                C.push_back(B[i]);
            }
            for (int i = 0; i < maxi; ++i) {
                C.push_back(B[i]);
            }
            B.swap(C);
            len = B.size();
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
        vector<int> A;
    };
    // TODO: prepare parameters here
    vector<struct d> p {
        {{3,2,4,1}},
        {{1,2,3}}
        
    };

    vector< vector<int> > answers {
        {4,2,4,3},
        {}
    };

    // TODO: update paramters.
    for (auto& dp : p) {
        cout << endl;
        clock_t tstart = clock();
        auto res = pancakeSort::Solution().pancakeSort(dp.A);
        cout << clock() - tstart << endl;
        cout << res << endl;
    }
    return 0;
}
//*/
