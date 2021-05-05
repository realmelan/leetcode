// soupServings.cpp
// leetcode
//
// Created by  Song Ding on 6/17/19.
// Copyright © 2019 Song Ding. All rights reserved.
//
#include "common.h"
using namespace std;

namespace soupServings {
/*
// TODO: copy problem statement here
 808. Soup Servings
 Medium
 
 97
 
 344
 
 Favorite
 
 Share
 There are two types of soup: type A and type B. Initially we have N ml of each type of soup. There are four kinds of operations:
 
 Serve 100 ml of soup A and 0 ml of soup B
 Serve 75 ml of soup A and 25 ml of soup B
 Serve 50 ml of soup A and 50 ml of soup B
 Serve 25 ml of soup A and 75 ml of soup B
 When we serve some soup, we give it to someone and we no longer have it.  Each turn, we will choose from the four operations with equal probability 0.25. If the remaining volume of soup is not enough to complete the operation, we will serve as much as we can.  We stop once we no longer have some quantity of both types of soup.
 
 Note that we do not have the operation where all 100 ml's of soup B are used first.
 
 Return the probability that soup A will be empty first, plus half the probability that A and B become empty at the same time.
 
 
 
 Example:
 Input: N = 50
 Output: 0.625
 Explanation:
 If we choose the first two operations, A will become empty first. For the third operation, A and B will become empty at the same time. For the fourth operation, B will become empty first. So the total probability of A becoming empty first plus half the probability that A and B become empty at the same time, is 0.25 * (1 + 1 + 0.5 + 0) = 0.625.
 
 Notes:
 
 0 <= N <= 10^9.
 Answers within 10^-6 of the true value will be accepted as correct.
 */

class Solution {
public:
    struct phash {
        size_t operator()(const pair<int,int>& p) const {
            return p.first * 5401 + p.second;
        }
    };
    /**
     * Let the 4 methods be names KLMN.
     * If N is too big(how large?), then the probability of A empty first will be close to 1.
     * 5400 can be found out.
     */
    double soupServings(int N) {
        if (N <= 5400) {
            unordered_map<pair<int,int>, double, struct phash> memo;
            return dfs(N, N, memo);
        }
        return 1.0;
    }

private:
    double dfs(int a, int b, unordered_map<pair<int,int>, double, struct phash>& memo) {
        if (a <= 0 && b > 0) {
            return 1;
        } else if (a <= 0 && b <= 0) {
            return 0.5;
        } else if (a > 0 && b <= 0) {
            return 0;
        } else {
            auto it = memo.find(make_pair(a,b));
            if (it != memo.end()) {
                return it->second;
            }
            
            double res = 0.25 * (dfs(a-100, b, memo)
                                 + dfs(a-75, b-25, memo)
                                 + dfs(a-50, b-50, memo)
                                 + dfs(a-25, b-75, memo));
            memo[make_pair(a,b)] = res;
            return res;
        }
    }
   
};

}

/*/
int main() {
    // TODO: define parameter type here
    struct d {
        int N;
    };
    // TODO: prepare parameters here
    vector<struct d> p {
        {50},
        {5400}
    };

    vector< double > answers {
        0.625
    };

    // TODO: update paramters.
    for (auto& dp : p) {
        cout << endl;
        clock_t tstart = clock();
        auto res = soupServings::Solution().soupServings(dp.N);
        cout << clock() - tstart << endl;
        cout << res << endl;
    }
    return 0;
}
//*/
