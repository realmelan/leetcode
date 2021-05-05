//
//  kthSmallest.cpp
//  leetcode
//
//  Created by Song Ding on 8/1/20.
//  Copyright © 2020 Song Ding. All rights reserved.
//

#include "common.h"
using namespace std;

namespace kthSmallest {
/*
// TODO: copy problem statement here
 378. Kth Smallest Element in a Sorted Matrix
 Medium

 2473

 130

 Add to List

 Share
 Given a n x n matrix where each of the rows and columns are sorted in ascending order, find the kth smallest element in the matrix.

 Note that it is the kth smallest element in the sorted order, not the kth distinct element.

 Example:

 matrix = [
    [ 1,  5,  9],
    [10, 11, 13],
    [12, 13, 15]
 ],
 k = 8,

 return 13.
 Note:
 You may assume k is always valid, 1 ≤ k ≤ n2.
*/
class Solution {
public:
    // TODO: copy function signature here
    int kthSmallest(vector<vector<int>>& matrix, int k) {
        int row = matrix.size(), col = matrix[0].size();
        int l = matrix[0][0], r = matrix[row-1][col-1];
        // invariant: few[l-1] < k && few[r]>=k
        while (l < r) {
            int m = l + (r-l) / 2;
            int j = 0, cnt = 0;
            for (int i = row - 1; i >= 0; --i) {
                for (; j < col; ++j) {
                    if (matrix[i][j] > m) {
                        break;
                    }
                }
                cnt += j;
            }
            if (cnt < k) {
                l = m+1;
            } else {
                r = m;
            }
        }
        return l;
        /*
        int ans = 0, diff = INT_MAX;
        for (auto& v  : matrix) {
            for (auto i : v) {
                if (i <= l && diff > l - i) {
                    ans = i;
                    diff = l-i;
                }
            }
        }
        return ans;
         */
    }
private:
};
}

/*
int main() {
    // TODO: define parameter type here
    struct param {
        vector<vector<int>> matrix;
        int k;
    };
    // TODO: prepare parameters here
    vector<struct param> params {
        //{ {{ 1,  5,  9},{10, 11, 13},{12, 13, 15}},8 },
        { {{1,2},{1,3}},3}
    };
    // TODO: provide expected results here
    vector<int> answers {
    };
    
    for (auto& dp : params) {
        cout << endl;
        clock_t tstart = clock();
        auto res = kthSmallest::Solution().kthSmallest(dp.matrix, dp.k);
        cout << res << endl;
        cout << clock() - tstart << endl;
    }

    return 0;
}
//*/
