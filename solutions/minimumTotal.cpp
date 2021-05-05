//
//  minimumTotal.cpp
//  leetcode
//
//  Created by Song Ding on 8/15/20.
//  Copyright © 2020 Song Ding. All rights reserved.
//

#include "common.h"
using namespace std;

namespace minimumTotal {
/*
// TODO: copy problem statement here
 120. Triangle
 Medium

 2123

 250

 Add to List

 Share
 Given a triangle, find the minimum path sum from top to bottom. Each step you may move to adjacent numbers on the row below.

 For example, given the following triangle

 [
      [2],
     [3,4],
    [6,5,7],
   [4,1,8,3]
 ]
 The minimum path sum from top to bottom is 11 (i.e., 2 + 3 + 5 + 1 = 11).

 Note:

 Bonus point if you are able to do this using only O(n) extra space, where n is the total number of rows in the triangle.
*/
class Solution {
public:
    // TODO: copy function signature here
    int minimumTotal(vector<vector<int>>& triangle) {
        vector<vector<int>> dp = triangle;
        for (int i = 1; i < triangle.size(); ++i) {
            for (int j = 0; j <= i; ++j) {
                dp[i][j] += min(j>=1?dp[i-1][j-1]:INT_MAX, j< i ? dp[i-1][j] : INT_MAX);
            }
        }
        return *min_element(begin(dp.back()), end(dp.back()));
    }
private:
};
}

/*
int main() {
    // TODO: define parameter type here
    struct param {
        vector<vector<int>> triangle;
    };
    // TODO: prepare parameters here
    vector<struct param> params {
        {{
               {2},
              {3,4},
             {6,5,7},
            {4,1,8,3}
        }},
    };
    // TODO: provide expected results here
    vector<int> answers {
    };
    
    for (auto& dp : params) {
        cout << endl;
        clock_t tstart = clock();
        auto res = minimumTotal::Solution().minimumTotal(dp.triangle);
        cout << res << endl;
        cout << clock() - tstart << endl;
    }

    return 0;
}
//*/
