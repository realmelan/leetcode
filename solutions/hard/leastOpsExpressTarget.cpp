// leastOpsExpressTarget.cpp
// leetcode
//
// Created by  Song Ding on 9/8/19.
// Copyright © 2019 Song Ding. All rights reserved.
//
#include "common.h"
using namespace std;

namespace leastOpsExpressTarget {
/*
// TODO: copy problem statement here
 964. Least Operators to Express Number
 Hard
 
 110
 
 37
 
 Favorite
 
 Share
 Given a single positive integer x, we will write an expression of the form x (op1) x (op2) x (op3) x ... where each operator op1, op2, etc. is either addition, subtraction, multiplication, or division (+, -, *, or /).  For example, with x = 3, we might write 3 * 3 / 3 + 3 - 3 which is a value of 3.
 
 When writing such an expression, we adhere to the following conventions:
 
 The division operator (/) returns rational numbers.
 There are no parentheses placed anywhere.
 We use the usual order of operations: multiplication and division happens before addition and subtraction.
 It's not allowed to use the unary negation operator (-).  For example, "x - x" is a valid expression as it only uses subtraction, but "-x + x" is not because it uses negation.
 We would like to write an expression with the least number of operators such that the expression equals the given target.  Return the least number of operators used.
 
 
 
 Example 1:
 
 Input: x = 3, target = 19
 Output: 5
 Explanation: 3 * 3 + 3 * 3 + 3 / 3.  The expression contains 5 operations.
 Example 2:
 
 Input: x = 5, target = 501
 Output: 8
 Explanation: 5 * 5 * 5 * 5 - 5 * 5 * 5 + 5 / 5.  The expression contains 8 operations.
 Example 3:
 
 Input: x = 100, target = 100000000
 Output: 3
 Explanation: 100 * 100 * 100 * 100.  The expression contains 3 operations.
 
 
 Note:
 
 2 <= x <= 100
 1 <= target <= 2 * 10^8
 */

class Solution {
public:
    int leastOpsExpressTarget(int x, int target) {
        return leastOpsExpressTarget_dfs2(x, target);
    }
    
    int leastOpsExpressTarget_dfs2(int x, int target) {
        unordered_map<int,int> memo;
        return dfs(x, target, memo) - 1;
    }
    int dfs(int x, int t, unordered_map<int,int>& memo) {
        if (x > t) {
            return min(2*t, 2*(x-t)+1);
        } else if (memo.count(t)) {
            return memo[t];
        }
        
        long xpow = 1;
        int exp = 0;
        while (t > xpow) {
            xpow *= x;
            ++exp;
        }
        if (xpow == t) {
            return (memo[t] = exp);
        }
        
        int res1 = INT_MAX;
        if (xpow < t * 2) { // so that xpow*x - t < t, and dfs would evetually exit.
            res1 = dfs(x, xpow - t, memo) + exp;
        }
        xpow /= x;
        --exp;
        int c = t / xpow;
        int res2 = dfs(x, t-xpow*c, memo) + c*exp;
        return (memo[t] = min(res1, res2));
    }
    /**
     * https://leetcode.com/problems/least-operators-to-express-number/discuss/209552/C%2B%2B-DFS-using-memorization-with-detailed-explanation-O(log(target))-time-4ms-and-beats-93
     * very detailed explanation!
     *
     * target = a1*x^p1+a2*x^p2+...+ak*x^pk+r, where 1<=p1<p2<p3<...<pk
     *  and r < x. let c = x - r.
     *
     * r can only be expressed as x/x+...+x/x or x - x/x-x/x...-x/x
     * so to express r we use min(2r-1, 2c-1), but for the c part, target has to add x back.
     * same thing can be done with ai*x^pi, from a1 to ak.
     *
     */
    int leastOpsExpressTarget_polynomial_dp(int x, int target) {
        int r = target % x;
        int c = x - r;
        unordered_map<int, int> memo;
        return min(2*r+dp(target - r, x, memo), 2*c+dp(target + x - r, x, memo)) - 1;
    }
    int dp(int target, int x, unordered_map<int, int>& memo) {
        if (target == 0) {
            return 0;
        }
        
        auto it = memo.find(target);
        if (it != memo.end()) {
            return it->second;
        }
        
        int ops = 0;
        int t = target;
        int xpow = 1;
        while (t % x == 0) {
            xpow *= x;
            ++ops;
            t /= x;
        }
        t %= x;
        
        int res = INT_MAX;
        if (t * xpow== target) {
            res = min(t*ops, ops+1+(x-t)*ops);
        } else {
            res = min(t*ops + dp(target - t*xpow, x, memo),
                      (x-t)*ops + dp(target + (x-t)*xpow, x, memo));
        }
        
        memo[target] = res;
        return res;
    }
    /**
     * looks like to be polynomials of x:
     * However, there are 2 directions:
     *  1, from x^k > target
     *  2, from x^k < target
     *
     */
    int leastOpsExpressTarget_polynomial_dfs(int x, int target) {
        vector<long> xpow;
        long val = 1;
        while (val <= target) {
            xpow.push_back(val);
            val *= x;
        }
        xpow.push_back(val);
        
        int curOps = 0;
        int minOps = INT_MAX;
        dfs(target, xpow, min(INT_MAX,(int)xpow.size()), curOps, minOps);
        return minOps-1;
    }
    // if x^k is used before, then it should not be used any more
    void dfs(int target, const vector<long>& xpow, int mp, int curOps, int& minOps) {
        int n = xpow.size();
        int i = mp - 1;
        while (i >= 0 && xpow[i] > target) {
            --i;
        }
        if (curOps >= minOps) {
            return;
        }

        // xpow[i] <= target
        if (xpow[i] == target) {
            int ops = i > 0 ? i-1 : 1;
            if (curOps + ops + 1 < minOps) {
                minOps = curOps + ops + 1;
            }
        } else {
            ++i;
            if (i < mp) {
                int ops = i > 0 ? i-1 : 1;
                if (curOps + ops + 1 < minOps) {
                    // consider target = xpow[i] - m * xpow[i-1] +/- unknown
                    dfs(xpow[i] - target, xpow, i, curOps + ops + 1, minOps);
                }
            }
            
            // consider target = m * xpow[i-1] +/- unknown
            --i;
            int ops = i > 0 ? i-1 : 1;
            int cnt = 0;
            // this while can be expressed using %
            while (target - xpow[i] >= 0) {
                ++cnt;
                target -= xpow[i];
            }
            int nops = (ops+1) * cnt;
            if (target == 0) {
                if (curOps + nops < minOps) {
                    minOps = curOps + nops;
                }
            } else {
                if (curOps + nops < minOps) {
                    dfs(target, xpow, i, curOps + nops, minOps);
                }
            
                nops += ops + 1;
                if (curOps + nops < minOps) {
                    dfs(xpow[i] - target, xpow, i, curOps + nops, minOps);
                }
            }
        }
    }
    /**
     * BFS expansion
     *
     * Optimiztaion:
     *   1, for multiply and division, there should be at most 1 divisor, and >= 1 multiply.
     *     as more division than multiply would result in non-integer.
     */
    int leastOpsExpressTarget_TLE(int x, int target) {
        struct st {
            double res;
            double val1;
            double val2;
            bool divide;
            double get_res() {
                if (divide) {
                    return res + val1 / val2;
                } else {
                    return res + val1 * val2;
                }
            }
            void update_val1() {
                if (divide) {
                    val1 /= val2;
                } else {
                    val1 *= val2;
                }
            }
        };
        
        unordered_set<double> visited;
        int cnt = 0;
        vector<st> cur{{0,1,(double)x,false}};
        while (cur.size()) {
            vector<st> next;
            for (auto& s : cur) {
                // append one more x
                double res = s.get_res();
                if (res == target) {
                    return cnt;
                }
                
                
                st t = s;
                if (visited.find(res) == visited.end()) {
                    visited.insert(res);
                    // + x
                    s.res = res;
                    s.val2 = x;
                    s.divide = false;
                    
                    s.val1 = 1;
                    next.push_back(s);
                    // - x
                    s.val1 = -1;
                    next.push_back(s);
                }
                
                if (!t.divide) {
                    // * x
                    t.update_val1();
                    t.val2 = x;
                    next.push_back(t);
                    
                    if (t.val1 == x || t.val1 == -x) {
                        // / x
                        t.divide = true;
                        next.push_back(t);
                    }
                }
                
            }
            cur.swap(next);
            ++cnt;
        }
        return cnt;
    }

private:
};

}

/*/
int main() {
    // TODO: define parameter type here
    struct d {
        int x;
        int target;
    };
    // TODO: prepare parameters here
    vector<struct d> p {
        //{5,5},
        //{3,19},
        //{5,501},
        {28,320096},
        {100,100000000},
        {3,365},
        {2,500094},
        {29,1322},
        {11,500041},
    };

    vector< int > answers {
        0,
        5,
        8,
        3,
        17,
        61,
        39,
        41
    };

    // TODO: update paramters.
    for (auto& dp : p) {
        cout << endl;
        clock_t tstart = clock();
        auto res = leastOpsExpressTarget::Solution().leastOpsExpressTarget(dp.x, dp.target);
        cout << clock() - tstart << endl;
        cout << res << endl;
    }
    return 0;
}
//*/
