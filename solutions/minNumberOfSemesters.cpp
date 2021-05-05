//
//  minNumberOfSemesters.cpp
//  leetcode
//
//  Created by Song Ding on 7/16/20.
//  Copyright © 2020 Song Ding. All rights reserved.
//

#include "common.h"
using namespace std;

namespace minNumberOfSemesters {
/*
// TODO: copy problem statement here
 1494. Parallel Courses II
 Hard

 177

 21

 Add to List

 Share
 Given the integer n representing the number of courses at some university labeled from 1 to n, and the array dependencies where dependencies[i] = [xi, yi]  represents a prerequisite relationship, that is, the course xi must be taken before the course yi.  Also, you are given the integer k.

 In one semester you can take at most k courses as long as you have taken all the prerequisites for the courses you are taking.

 Return the minimum number of semesters to take all courses. It is guaranteed that you can take all courses in some way.

  

 Example 1:



 Input: n = 4, dependencies = [[2,1],[3,1],[1,4]], k = 2
 Output: 3
 Explanation: The figure above represents the given graph. In this case we can take courses 2 and 3 in the first semester, then take course 1 in the second semester and finally take course 4 in the third semester.
 Example 2:



 Input: n = 5, dependencies = [[2,1],[3,1],[4,1],[1,5]], k = 2
 Output: 4
 Explanation: The figure above represents the given graph. In this case one optimal way to take all courses is: take courses 2 and 3 in the first semester and take course 4 in the second semester, then take course 1 in the third semester and finally take course 5 in the fourth semester.
 Example 3:

 Input: n = 11, dependencies = [], k = 2
 Output: 6
  

 Constraints:

 1 <= n <= 15
 1 <= k <= n
 0 <= dependencies.length <= n * (n-1) / 2
 dependencies[i].length == 2
 1 <= xi, yi <= n
 xi != yi
 All prerequisite relationships are distinct, that is, dependencies[i] != dependencies[j].
 The given graph is a directed acyclic graph.
*/
class Solution {
public:
    // TODO: copy function signature here
    // BFS, at each semester, for each possibe state, select <=k courses, and update state
    // parallel # of states is too large when
    int minNumberOfSemesters_BFS(int n, vector<vector<int>>& dependencies, int k) {
        int target = (1<<n)-1;
        vector<int> pre(n, 0);
        for (auto& d : dependencies) {
            pre[d[1]-1] |= 1 << (d[0] - 1);
        }
        
        vector<int> dp(1<<n, n);
        dp[0] = 0;
        int res = 0;
        queue<int> q;
        q.push(0);
        while (!q.empty()) {
            ++res;
            int qn = q.size();
            for (int i = 0; i < qn; ++i) {
                int st = q.front(); q.pop();
                int avail = 0;
                for (int j = 0; j < n; ++j) {
                    if ((st & pre[j]) == pre[j]) {
                        avail |= 1<<j;
                    }
                }
                avail &= ~st;
                for (int j = avail; j > 0; j = (j-1)&avail) {
                    int jc = j;
                    int cnt = 0;
                    while (int l = jc & (-jc)) {
                        ++cnt;
                        jc -= l;
                    }
                    if (cnt <= k) {
                        if ((st|j) == target) {
                            return res;
                        } else if (dp[st|j] > res){
                            q.push(st | j);
                            dp[st|j] = res;
                        }
                    }
                }
            }
        }
        return res;
    }
    // 2^n as courses taken;
    // pre calculate prerequisite bitmask for each course, use state to find out courses available to take
    // lookp through all possible substate of the available course state, and update result
    // https://leetcode.com/problems/parallel-courses-ii/discuss/708445/Weak-test-case-most-solutions-posted-using-depth-or-outdgree-are-wrong
    int minNumberOfSemesters(int n, vector<vector<int>>& dependencies, int k) {
        vector<int> dp(1<<n, n);
        dp[0] = 0;
        vector<int> pre(n, 0);
        for (auto& d : dependencies) {
            pre[d[1]-1] |= 1 << (d[0] - 1);
        }
        for (int i = 0; i < 1<<n; ++i) {
            int avail = 0;
            for (int j = 0; j < n; ++j) {
                if ((i & pre[j]) == pre[j]) {
                    avail |= 1 << j;
                }
            }
            avail &= ~i;
            for (int j = avail; j > 0; j = (j-1)&avail) {
                int t = j, cnt = 0;
                while (int l = t & (-t)) {
                    ++cnt;
                    t -= l;
                }
                if (cnt <= k) {
                    dp[i|j] = min(dp[i|j], dp[i] + 1);
                }
            }
        }
        return dp[(1<<n) - 1];
    }
private:
};
}

/*
int main() {
    // TODO: define parameter type here
    struct param {
        int n;
        vector<vector<int>> dependencies;
        int k;
    };
    // TODO: prepare parameters here
    vector<struct param> params {
        {4,{{2,1},{3,1},{1,4}},2},
        {5,{{2,1},{3,1},{4,1},{1,5}},2},
        {11,{},2},
    };
    // TODO: provide expected results here
    vector<int> answers {
        3,
        4,
        6
    };
    
    for (auto& dp : params) {
        cout << endl;
        clock_t tstart = clock();
        auto res = minNumberOfSemesters::Solution().minNumberOfSemesters1(dp.n, dp.dependencies, dp.k);
        cout << res << endl;
        cout << clock() - tstart << endl;
    }

    return 0;
}
//*/
