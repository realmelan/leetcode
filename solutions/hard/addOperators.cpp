// addOperators.cpp
// leetcode
//
// Created by  Song Ding on 9/6/19.
// Copyright © 2019 Song Ding. All rights reserved.
//
#include "common.h"
using namespace std;

namespace addOperators {
/*
// TODO: copy problem statement here
 282. Expression Add Operators
 Hard
 
 789
 
 111
 
 Favorite
 
 Share
 Given a string that contains only digits 0-9 and a target value, return all possibilities to add binary operators (not unary) +, -, or * between the digits so they evaluate to the target value.
 
 Example 1:
 
 Input: num = "123", target = 6
 Output: ["1+2+3", "1*2*3"]
 Example 2:
 
 Input: num = "232", target = 8
 Output: ["2*3+2", "2+3*2"]
 Example 3:
 
 Input: num = "105", target = 5
 Output: ["1*0+5","10-5"]
 Example 4:
 
 Input: num = "00", target = 0
 Output: ["0+0", "0-0", "0*0"]
 Example 5:
 
 Input: num = "3456237490", target = 9191
 Output: []
 */

class Solution {
public:
    vector<string> addOperators(string num, int target) {
        return addOperators_DFS(num, target);
    }
    /**
     * for each position i in num, try +/-/* and no-op.
     *  state = (cur_result, sign, val1, val2), where cur_result = current result,
     *   sign = sign of current segment('+' or '-' before current segment),
     *   val1 = multiplier one for current segment, 1 if current segment doesn't have a '*' op
     *   val2 = multiplier two for current segment
     */
    vector<string> addOperators_DFS(string num, int target) {
        vector<string> res;
        if (num.size()) {
            string expr;
            expr.push_back(num[0]);
            dfs(num, 1, 0, 1, 1, num[0]-'0', expr, target, res);
        }
        return res;
    }
private:
    void dfs(const string& num, int idx, long cur, int sign, long val1, long val2, string& expr, int target, vector<string>& res) {
        int n = num.size();
        if (idx == n) {
            // test cur
            cur += sign * val1 * val2;
            if (cur == target) {
                res.push_back(expr);
            }
            return;
        }
        
        int dval = num[idx] - '0';
        int esize = expr.size();
        expr.push_back('+');
        expr.push_back(num[idx]);
        dfs(num, idx+1, cur+sign*val1*val2, 1, 1, dval, expr, target, res);
        
        expr[esize] = '-';
        dfs(num, idx+1, cur+sign*val1*val2, -1, 1, dval, expr, target, res);
        
        expr[esize] = '*';
        dfs(num, idx+1, cur, sign, val1*val2, dval, expr, target, res);
        expr.pop_back();
        expr.pop_back();
        
        // add no op before num[idx]
        if (val2 != 0) {
            expr.push_back(num[idx]);
            dfs(num, idx+1, cur, sign, val1, 10*val2 + dval, expr, target, res);
            expr.pop_back();
        }
    }
    
    vector<string> addOperators_DP4(string num, int target) {
        int n = num.size();
        if (n <= 0) {
            return {};
        }
        vector<unordered_map<long,unordered_set<string>>> dp(n);
        vector<vector<unordered_map<long, unordered_set<string>>>> multiply(n);
        for (auto& v : multiply) {
            v.resize(n);
        }
        for (int i = 0; i < n; ++i) {
            char c = num[i];
            multiply[i][i][c - '0'].insert(string(1,c));
        }
        for (int l = 2; l <= n; ++l) {
            for (int i = 0; i <= n-l; ++i) {
                int j = i+l-1;
                long val = 0;
                for (int k = i; k < j; ++k) {
                    val *= 10;
                    val += num[k] - '0';
                    const string& vs = num.substr(i, k-i+1);
                    for (auto& rp : multiply[k+1][j]) {
                        long rres = rp.first;
                        long res = val * rres;
                        auto& result = multiply[i][j][res];
                        for (auto& rs : rp.second) {
                            result.insert(vs + "*" + rs);
                        }
                    }
                    if (num[i] == '0') {
                        break;
                    }
                }
                if (num[i] != '0') {
                    val *= 10;
                    val += num[j] - '0';
                    multiply[i][j][val].insert(num.substr(i,l));
                }
            }
        }
        
        for (int i = 0; i < n; ++i) {
            for (auto& mp : multiply[0][i]) {
                dp[i][mp.first].insert(mp.second.begin(), mp.second.end());
            }
            
            for (int j = 0; j < i; ++j) {
                // dp(j) +/- multiply(j+1,i)
                for (auto& lp : dp[j]) {
                    long lres = lp.first;
                    for (auto& rp : multiply[j+1][i]) {
                        long rres = rp.first;
                        
                        // for +/-
                        long pres = lres + rres;
                        auto& presult = dp[i][pres];
                        long mres = lres - rres;
                        auto& mresult = dp[i][mres];
                        for (auto& ls : lp.second) {
                            for (auto& rs : rp.second) {
                                presult.insert(ls + "+" + rs);
                                mresult.insert(ls + "-" + rs);
                            }
                        }
                    }
                }
            }
        }
        vector<string> res;
        auto it = dp[n-1].find(target);
        if (it != dp[n-1].end()) {
            res.insert(res.end(), it->second.begin(), it->second.end());
        }
        return res;
    }
    /**
     * let dp(i) = map<result, set<expr>>,
     *  and multiply(i,j) = map<result, set<expr>>
     *
     * then dp(i) = dp(k-1) -/+ multiply(k,i) for k in (0, i); when k = 0, dp(k-1)
     *  doesn't exist
     *  multiply(i,j) = multiply(i,k) * multiply(k+1,j) for k in (i,j-1) or val(substr(i,j))
     */
    vector<string> addOperators_DP3(string num, int target) {
        int n = num.size();
        if (n <= 0) {
            return {};
        }
        vector<unordered_map<long,unordered_set<string>>> dp(n);
        vector<vector<unordered_map<long, unordered_set<string>>>> multiply(n);
        for (auto& v : multiply) {
            v.resize(n);
        }
        for (int i = 0; i < n; ++i) {
            char c = num[i];
            multiply[i][i][c - '0'].insert(string(1,c));
        }
        for (int l = 2; l <= n; ++l) {
            for (int i = 0; i <= n-l; ++i) {
                int j = i+l-1;
                long val = 0;
                for (int k = i; k < j; ++k) {
                    val *= 10;
                    val += num[k] - '0';
                    const string& vs = num.substr(i, k-i+1);
                    for (auto& rp : multiply[k+1][j]) {
                        long rres = rp.first;
                        long res = val * rres;
                        auto& result = multiply[i][j][res];
                        for (auto& rs : rp.second) {
                            result.insert(vs + "*" + rs);
                        }
                    }
                    if (num[i] == '0') {
                        break;
                    }
                }
                if (num[i] != '0') {
                    val *= 10;
                    val += num[j] - '0';
                    multiply[i][j][val].insert(num.substr(i,l));
                }
            }
        }
        
        for (int i = 0; i < n; ++i) {
            for (auto& mp : multiply[0][i]) {
                dp[i][mp.first].insert(mp.second.begin(), mp.second.end());
            }
            
            for (int j = 0; j < i; ++j) {
                // dp(j) +/- multiply(j+1,i)
                for (auto& lp : dp[j]) {
                    long lres = lp.first;
                    for (auto& rp : multiply[j+1][i]) {
                        long rres = rp.first;
                        
                        // for +/-
                        long pres = lres + rres;
                        auto& presult = dp[i][pres];
                        long mres = lres - rres;
                        auto& mresult = dp[i][mres];
                        for (auto& ls : lp.second) {
                            for (auto& rs : rp.second) {
                                presult.insert(ls + "+" + rs);
                                mresult.insert(ls + "-" + rs);
                            }
                        }
                    }
                }
            }
        }
        vector<string> res;
        auto it = dp[n-1].find(target);
        if (it != dp[n-1].end()) {
            res.insert(res.end(), it->second.begin(), it->second.end());
        }
        return res;
    }
    /**
     * This is much better than addOperators_DP1.
     * However this is still TLE. Need a O(nlogn) or even O(n)
     */
    vector<string> addOperators_DP2(string num, int target) {
        const int MULTIPLY_ONLY = 1;
        int n = num.size();
        if (n <= 0) {
            return {};
        }
        vector<vector<vector<unordered_map<long,unordered_set<string>>>>> dp(n);
        for (auto& v : dp) {
            v.resize(n);
            for (auto & v1 : v) {
                v1.resize(2);
            }
        }
        for (int i = 0; i < n; ++i) {
            char c = num[i];
            dp[i][i][0][c - '0'].insert(string(1,c));
            dp[i][i][MULTIPLY_ONLY][c - '0'].insert(string(1,c));
        }
        
        for (int l = 2; l <= n; ++l) {
            for (int i = 0; i <= n-l; ++i) {
                int j = i+l-1;
                
                if (num[i] != '0') {
                    long res = 0;
                    for (int k = i; k <= j; ++k) {
                        res *= 10;
                        res += num[k] - '0';
                    }
                    dp[i][j][0][res].insert(num.substr(i, l));
                    dp[i][j][MULTIPLY_ONLY][res].insert(num.substr(i, l));
                }
                for (int k = i; k < j; ++k) {
                    // for *
                    for (auto& lp : dp[i][k][MULTIPLY_ONLY]) {
                        long lres = lp.first;
                        for (auto& rp : dp[k+1][j][MULTIPLY_ONLY]) {
                            long rres = rp.first;
                            long res = lres * rres;
                            auto& multiply_result = dp[i][j][MULTIPLY_ONLY][res];
                            auto& result = dp[i][j][0][res];
                            for (auto& ls : lp.second) {
                                for (auto& rs : rp.second) {
                                    multiply_result.insert(ls + "*" + rs);
                                    result.insert(ls + "*" + rs);
                                }
                            }
                        }
                    }
                    for (auto& lp : dp[i][k][0]) {
                        // for -
                        long lres = lp.first;
                        for (auto& rp : dp[k+1][j][MULTIPLY_ONLY]) {
                            long rres = rp.first;
                            long res = lres - rres;
                            auto& mresult = dp[i][j][0][res];
                            for (auto& ls : lp.second) {
                                for (auto& rs : rp.second) {
                                    mresult.insert(ls + "-" + rs);
                                }
                            }
                        }
                        
                        // for +
                        for (auto& rp : dp[k+1][j][0]) {
                            long rres = rp.first;
                            long res = lres + rres;
                            auto& result = dp[i][j][0][res];
                            for (auto& ls : lp.second) {
                                for (auto& rs : rp.second) {
                                    result.insert(ls + "+" + rs);
                                }
                            }
                        }
                    }
                }// for loop of k in [i,j]
            } // for loop of i
        } // for loop of l
        
        vector<string> res;
        auto it = dp[0][n-1][0].find(target);
        if (it != dp[0][n-1][0].end()) {
            res.insert(res.end(), it->second.begin(), it->second.end());
        }
        return res;
    }
    /**
     * let dp(i,j,multiplyOnly) = map<result, set<expr>>
     * then dp(i,j, multiplyOnly) = dp(i,k,multiplyOnly) <op> dp(k+1,j,multiplyOnly)
     * for k in [i+1,j-1]
     *
     * Still: for example 5, runtime >= 5 seconds.
     * Optimization: string operation can be replaced with a list of operators at different
     *  positions inside <num>.
     *
     * Optimization 2: add MULTIPLY_ONLY results to non MULTIPLY_ONLY results.
     */
    vector<string> addOperators_DP1(string num, int target) {
        const int MULTIPLY_ONLY = 1;
        int n = num.size();
        vector<vector<vector<unordered_map<long,unordered_set<string>>>>> dp(n);
        for (auto& v : dp) {
            v.resize(n);
            for (auto & v1 : v) {
                v1.resize(2);
            }
        }
        for (int i = 0; i < n; ++i) {
            char c = num[i];
            dp[i][i][0][c - '0'].insert(string(1,c));
            dp[i][i][MULTIPLY_ONLY][c - '0'].insert(string(1,c));
        }
        
        for (int l = 2; l <= n; ++l) {
            for (int i = 0; i <= n-l; ++i) {
                int j = i+l-1;
                
                if (num[i] != '0') {
                    long res = 0;
                    for (int k = i; k <= j; ++k) {
                        res *= 10;
                        res += num[k] - '0';
                    }
                    dp[i][j][0][res].insert(num.substr(i, l));
                    dp[i][j][MULTIPLY_ONLY][res].insert(num.substr(i, l));
                }
                for (int k = i; k < j; ++k) {
                    // for *
                    for (auto& lp : dp[i][k][MULTIPLY_ONLY]) {
                        long lres = lp.first;
                        for (auto& rp : dp[k+1][j][MULTIPLY_ONLY]) {
                            long rres = rp.first;
                            long res = lres * rres;
                            auto& multiply_result = dp[i][j][MULTIPLY_ONLY][res];
                            for (auto& ls : lp.second) {
                                for (auto& rs : rp.second) {
                                    multiply_result.insert(ls + "*" + rs);
                                }
                            }
                            
                            res = lres + rres;
                            auto& plus_result = dp[i][j][0][res];
                            for (auto& ls : lp.second) {
                                for (auto& rs : rp.second) {
                                    plus_result.insert(ls + "+" + rs);
                                }
                            }
                            
                            res = lres - rres;
                            auto& minus_result = dp[i][j][0][res];
                            for (auto& ls : lp.second) {
                                for (auto& rs : rp.second) {
                                    minus_result.insert(ls + "-" + rs);
                                }
                            }
                        }
                        for (auto& rp : dp[k+1][j][0]) {
                            long rres = rp.first;
                            long res = lres + rres;
                            auto& result = dp[i][j][0][res];
                            for (auto& ls : lp.second) {
                                for (auto& rs : rp.second) {
                                    result.insert(ls + "+" + rs);
                                }
                            }
                        }
                        
                    }
                    for (auto& lp : dp[i][k][0]) {
                        // for -
                        long lres = lp.first;
                        for (auto& rp : dp[k+1][j][MULTIPLY_ONLY]) {
                            long rres = rp.first;
                            long res = lres - rres;
                            auto& mresult = dp[i][j][0][res];
                            for (auto& ls : lp.second) {
                                for (auto& rs : rp.second) {
                                    mresult.insert(ls + "-" + rs);
                                }
                            }
                            res = lres + rres;
                            auto& presult = dp[i][j][0][res];
                            for (auto& ls : lp.second) {
                                for (auto& rs : rp.second) {
                                    presult.insert(ls + "-" + rs);
                                }
                            }
                            
                        }
                        
                        // for +
                        for (auto& rp : dp[k+1][j][0]) {
                            long rres = rp.first;
                            long res = lres + rres;
                            auto& result = dp[i][j][0][res];
                            for (auto& ls : lp.second) {
                                for (auto& rs : rp.second) {
                                    result.insert(ls + "+" + rs);
                                }
                            }
                        }
                    }
                }// for loop of k in [i,j]
            } // for loop of i
        } // for loop of l
        
        vector<string> res;
        auto it = dp[0][n-1][0].find(target);
        if (it != dp[0][n-1][0].end()) {
            res.insert(res.end(), it->second.begin(), it->second.end());
        }
        
        it = dp[0][n-1][MULTIPLY_ONLY].find(target);
        if (it != dp[0][n-1][MULTIPLY_ONLY].end()) {
            res.insert(res.end(), it->second.begin(), it->second.end());
        }
        return res;
    }
    /**
     * Recursive
     * let f(num1) = map<target, set<expr>>
     * then for (num target), find a position i num, get all possible results from both sides,
     * and then test '+', '-' and '*'.
     * for no-op, the whole num is converted to a number and compare with target.
     *
     */
    vector<string> addOperators_TLE(string num, int target) {
        vector<int> digits;
        for (auto c : num) {
            digits.push_back(c - '0');
        }
        
        int n = digits.size();
        vector<vector<vector<unordered_map<long, unordered_set<string>>>>> memo(n);
        for (auto& v1 : memo) {
            v1.resize(n);
            for (auto& v2 : v1) {
                v2.resize(2);
            }
        }
        vector<string> res;
        unordered_map<long, unordered_set<string>> results;
        allExpr(digits, 0, num.size() - 1, false, results, memo);
        auto it = results.find(target);
        if (it != results.end()) {
            res.insert(res.end(), it->second.begin(), it->second.end());
        }
        return res;
    }

private:
    void allExpr(vector<int>& ds, int l, int r, bool multiplyOnly, unordered_map<long, unordered_set<string>>& results, vector<vector<vector<unordered_map<long, unordered_set<string>>>>>& memo) {
        if (l == r) {
            char c = ds[l] + '0';
            string expr(1, c);
            results[ds[l]].insert(expr);
        } else {
            if (memo[l][r][multiplyOnly?1:0].size()) {
                const auto& res = memo[l][r][multiplyOnly?1:0];
                results.insert(res.begin(), res.end());
                return;
            }
            // all digits in ds form a number
            if (ds[l]) {
                long res = 0;
                string expr;
                for (int i = l; i <= r; ++i) {
                    res *= 10;
                    res += ds[i];
                    expr.push_back('0'+ds[i]);
                }
                results[res].insert(expr);
            }
            
            // add 'op' after position i;
            for (int i = l; i < r; ++i) {
                unordered_map<long, unordered_set<string>> left, right;
                
                allExpr(ds, l, i, true, left, memo);
                allExpr(ds, i+1, r, true, right, memo);
                
                for (const auto& lp : left) {
                    int lres = lp.first;
                    for (const auto& rp : right) {
                        long rres = rp.first;
                        long res = lres * rres;
                        unordered_set<string> & exprs = results[res];
                        for (const auto& lexpr : lp.second) {
                            for (const auto& rexpr : rp.second) {
                                exprs.insert(lexpr + "*" + rexpr);
                            }
                        }
                    }
                }
                
                if (!multiplyOnly) {
                    left.clear();
                    allExpr(ds, l, i, false, left, memo);
                    
                    for (const auto& lp : left) {
                        int lres = lp.first;
                        for (const auto& rp : right) {
                            long rres = rp.first;
                            long minusRes = lres - rres;
                            unordered_set<string> & mexprs = results[minusRes];
                            for (const auto& lexpr : lp.second) {
                                for (const auto& rexpr : rp.second) {
                                    mexprs.insert(lexpr + "-" + rexpr);
                                }
                            }
                        }
                    }
                    
                    right.clear();
                    allExpr(ds, i+1, r, false, right, memo);
                        
                    for (const auto& lp : left) {
                        long lres = lp.first;
                        for (const auto& rp : right) {
                            long rres = rp.first;
                            long minusRes = lres + rres;
                            unordered_set<string> & mexprs = results[minusRes];
                            for (const auto& lexpr : lp.second) {
                                for (const auto& rexpr : rp.second) {
                                    mexprs.insert(lexpr + "+" + rexpr);
                                }
                            }
                        }
                    }
                } // end !multiplyOnly
            } // end position of op
            
            memo[l][r][multiplyOnly?1:0] = results;
        } // end l < r
        
        
    } // end method
};

}

/*/
int main() {
    // TODO: define parameter type here
    struct d {
        string num;
        int target;
    };
    // TODO: prepare parameters here
    vector<struct d> p {
        {"", 5},
        {"123", 6},
        {"232", 8},
        {"105", 5},
        {"0125", 5},
        {"00", 0},
        {"3456237490", 9191},
        {"2147483648",-2147483648}
    };

    vector< vector<string> > answers {
        {},
        {"1+2+3", "1*2*3"},
        {"2*3+2", "2+3*2"},
        {"1*0+5","10-5"},
        {"0+0", "0-0", "0*0"},
        {},
    };

    // TODO: update paramters.
    for (auto& dp : p) {
        cout << endl;
        clock_t tstart = clock();
        auto res = addOperators::Solution().addOperators(dp.num, dp.target);
        cout << clock() - tstart << endl;
        cout << res << endl;
    }
    return 0;
}
//*/
