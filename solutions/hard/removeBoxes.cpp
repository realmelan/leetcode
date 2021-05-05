//
//  removeBoxes.cpp
//  leetcode
//
//  Created by  Song Ding on 2/14/18.
//  Copyright © 2018 Song Ding. All rights reserved.
//

#include "common.h"
using namespace std;
/**
 546. Remove Boxes
 Hard
 
 423
 
 39
 
 Favorite
 
 Share
 Given several boxes with different colors represented by different positive numbers.
 You may experience several rounds to remove boxes until there is no box left. Each time you can choose some continuous boxes with the same color (composed of k boxes, k >= 1), remove them and get k*k points.
 Find the maximum points you can get.
 
 Example 1:
 Input:
 
 [1, 3, 2, 2, 2, 3, 4, 3, 1]
 Output:
 23
 Explanation:
 [1, 3, 2, 2, 2, 3, 4, 3, 1]
 ----> [1, 3, 3, 4, 3, 1] (3*3=9 points)
 ----> [1, 3, 3, 3, 1] (1*1=1 points)
 ----> [1, 1] (3*3=9 points)
 ----> [] (2*2=4 points)
 Note: The number of boxes n would not exceed 100.
 */

namespace removeBoxes {
    class Solution {
        /**
         * https://leetcode.com/problems/remove-boxes/discuss/101312/Memoization-DFS-C%2B%2B
         * Therefore, I designed the memoization matrix to be memo[l][r][k], the largest number we can get using lth to rth (inclusive) boxes with k same colored boxes as rth box appended at the end. Example, memo[l][r][3] represents the solution for this setting: [b_l, ..., b_r, A,A,A] with b_r==A.
           The transition function is to find the maximum among all b_i==b_r for i=l,...,r-1:
            memo[l][r][k] = max(memo[l][r][k], memo[l][i][k+1] + memo[i+1][r-1][0])
         
         A better summary:
         https://leetcode.com/problems/remove-boxes/discuss/101310/Java-top-down-and-bottom-up-DP-solutions
         */
        int removeBoxes(vector<int>& boxes) {
            if (boxes.empty()) {
                return 0;
            }
            
            int n = boxes.size();
            int memo[100][100][100] = {0};
            int l = 0;
            int r = n - 1;
            int k = 0;
            return dfs(boxes, memo, l, r, k);
        }
    private:
        int dfs(vector<int>& boxes, int memo[100][100][100], int l, int r, int k) {
            if (l > r) {
                return 0;
            }
            if (memo[l][r][k] != 0) {
                return memo[l][r][k];
            }
            
            while (l < r && boxes[r - 1] == boxes[r]) {
                --r;
                ++k;
            }
            
            memo[l][r][k] = dfs(boxes, memo, l, r - 1, 0) + (k+1) * (k+1);
            for (int i = l; i < r; ++i) {
                if (boxes[i] == boxes[r]) {
                    int t = dfs(boxes, memo, l, i, k + 1) + dfs(boxes, memo, i + 1, r - 1, 0);
                    if (t > memo[l][r][k]) {
                        memo[l][r][k] = t;
                    }
                }
            }
            return memo[l][r][k];
        }
    public:
        /**
         Recursive and memoization.
         
         One point is, always remove all consecutive same color's
         instead of removing a part of them.
         */
        int removeBoxes_TLE(vector<int>& boxes) {
            if (boxes.empty()) {
                return 0;
            }
            
            map<vector<int>, int> res;
            return recur(boxes, res);
        }
    private:
        int recur(vector<int> boxes, map<vector<int>, int>& results) {
            auto rit = results.find(boxes);
            if (rit != results.end()) {
                return rit->second;
            }
            
            int res = 0;
            auto it = boxes.begin();
            while (it != boxes.end()) {
                auto start = it;
                while (it != boxes.end() && *it == *start) {
                    ++it;
                }
                
                int c = distance(start, it);
                if (c == boxes.size()) {
                    res = c * c;
                    results.insert(make_pair(boxes, res));
                    return res;
                }
                
                vector<int> nboxes(boxes);
                nboxes.erase(nboxes.begin() + (start - boxes.begin()), nboxes.begin() + (it - boxes.begin()));
                
                int t = recur(nboxes, results) + c * c;
                if (t > res) {
                    res = t;
                }
            }
            results.insert(make_pair(boxes, res));
            return res;
        }
    };
}

/*
int main() {
    vector<int> boxes {3,8,8,5,5,3,9,2,4,4,6,5,8,4,8,6,9,6,2,8,6,4,1,9,5,3,10,5,3,3,9,8,8,6,5,3,7,4,9,6,3,9,4,3,5,10,7,6,10,7};
    cout << removeBoxes::Solution().removeBoxes(boxes) << endl;
    return 0;
}
 */
