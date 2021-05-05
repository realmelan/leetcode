//
//  diffWaysToCompute.cpp
//  leetcode
//
//  Created by  Song Ding on 10/11/17.
//  Copyright © 2017 Song Ding. All rights reserved.
//

#include "common.h"

using namespace std;
/*
241. Different Ways to Add Parentheses
Medium

917

46

Favorite

Share
Given a string of numbers and operators, return all possible results from computing all the different possible ways to group numbers and operators. The valid operators are +, - and *.

Example 1:

Input: "2-1-1"
Output: [0, 2]
Explanation:
((2-1)-1) = 0
(2-(1-1)) = 2
Example 2:

Input: "2*3-4*5"
Output: [-34, -14, -10, -10, 10]
Explanation:
(2*(3-(4*5))) = -34
((2*3)-(4*5)) = -14
((2*(3-4))*5) = -10
(2*((3-4)*5)) = -10
(((2*3)-4)*5) = 10
*/
namespace diffWaysToCompute {
    class Solution {
    public:
        struct phash {
            size_t operator()(const pair<int,int>& p) const {
                static hash<string> h;
                std::ostringstream oss;
                oss << p.first << "," << p.second;
                return h(oss.str());
            }
        };
        /**
         * recursive with memo:
         *
         */
        vector<int> diffWaysToCompute(string input) {
            vector<int> params;
            vector<char> ops;
            // prepare params ops
            int num = 0;
            for (auto c : input) {
                if (c >= '0' && c <= '9') {
                    num *= 10;
                    num += c - '0';
                } else {
                    params.push_back(num);
                    num = 0;
                    ops.push_back(c);
                }
            }
            params.push_back(num);
            
            int opn = ops.size();
            unordered_map<pair<int,int>, vector<int>, struct phash> memo;
            return recur(params, ops, 0, opn - 1, memo);
        }
        vector<int> recur(vector<int>& params, vector<char>& ops, int opstart, int opend, unordered_map<pair<int,int>, vector<int>, struct phash>& memo) {
            auto it = memo.find(make_pair(opstart, opend));
            if (it != memo.end()) {
                return it->second;
            }
            
            vector<int>& res = memo[make_pair(opstart, opend)];
            if (opstart > opend) {
                res.push_back(params[opstart]);
            } else if (opstart == opend) {
                int opres = compute(ops[opstart], params[opstart], params[opstart+1]);
                res.push_back(opres);
            } else {
                // multiple ops
                for (int i = opstart; i <= opend; ++i) {
                    vector<int> lres;
                    if (i > opstart) {
                        lres = recur(params, ops, opstart, i-1, memo);
                    } else {
                        lres.push_back(params[i]);
                    }
                    
                    vector<int> rres;
                    if (i < opend) {
                        rres = recur(params, ops, i+1, opend, memo);
                    } else {
                        rres.push_back(params[opend+1]);
                    }
                    
                    for (auto j : lres) {
                        for (auto k : rres) {
                            int t = compute(ops[i], j, k);
                            res.push_back(t);
                        }
                    }
                    
                }
            }
            
            return res;
        }
        int compute(char op, int oprand1, int oprand2) {
            switch(op) {
                case '+':
                    return oprand1 + oprand2;
                case '-':
                    return oprand1 - oprand2;
                case '*':
                    return oprand1 * oprand2;
            }
            return 0;
        }
            
        /**
         Different cases of orders of operators, i.e. find out
         all permutations of the operators.
         */
        vector<int> diffWaysToCompute2(string input) {
            vector<int> res;
            vector<int> nums;
            vector<char> ops;
            
            stringstream iss(input);
            int t;
            char c;
            iss >> t;
            nums.push_back(t);
            while (!iss.eof()) {
                iss >> c >> t;
                ops.push_back(c);
                nums.push_back(t);
            }
            
            int oplen = ops.size();
            
            // create a vector of permutations of [0, 1, ..., oplen - 1];
            vector<vector<int>> ariths = getPermutations(oplen);
            vector<pair<int, bool>> argPos(oplen, {0, false});
            for (int i = 0; i < oplen; ++i) {
                argPos[i].first = i;
            }
            
            // iterate through ariths to compute result
            for (auto arith : ariths) {
                vector<int> oprand(nums);
                vector<pair<int, bool>> args(argPos);
                for (auto i : arith) {
                    for (int j = i + 1; j < oplen; ++j) {
                        if (!args[j].second) {
                            --args[j].first;
                        }
                    }
                    args[i].second = true;
                }
                for (auto i : arith) {
                    char c = ops[i];
                    int argIndex = args[i].first;
                    int oprand1 = oprand[argIndex];
                    int oprand2 = oprand[argIndex + 1];
                    
                    int r = getResult(c, oprand1, oprand2);
                    // remove oprand[i+1], update oprand[i] with r
                    for (int j = argIndex; j < oplen; ++j) {
                        oprand[j] = oprand[j + 1];
                    }
                    oprand[argIndex] = r;
                }
                res.push_back(oprand[0]);
            }
            return res;
        }
    private:
        vector<vector<int>> getPermutations(int len) {
            vector<vector<int>> res;
            vector<int> nums;
            for (int i = 0; i < len; ++i) {
                nums.push_back(i);
            }
            
            res.push_back(nums);
            while (true) {
                int i = len - 1;
                while (i > 0 && nums[i - 1] >= nums[i]) {
                    --i;
                }
                if (i <= 0) {
                    break;
                }
                
                int j = len - 1;
                while (j >= 0 && nums[j] <= nums[i - 1]) {
                    --j;
                }
                
                int t = nums[i - 1];
                nums[i - 1] = nums[j];
                nums[j] = t;
                
                j = len - 1;
                while (i < j) {
                    int t = nums[i];
                    nums[i] = nums[j];
                    nums[j] = t;
                    --j;
                    ++i;
                }
                res.push_back(nums);
            }
            return res;
        }
        int getResult(char op, int oprand1, int oprand2) {
            switch (op) {
                case '+': return oprand1 + oprand2; break;
                case '-': return oprand1 - oprand2; break;
                case '*': return oprand1 * oprand2; break;
            }
            return 0;
        }
    };
}
/*/
int main() {
    // TODO: define parameter type here
    struct d {
        string input;
    };
    // TODO: prepare parameters here
    vector<struct d> p {
        {"2-1-1"},
        {"2*3-4*5"},
        {"0"}
    };
    
    vector< vector<int> > answers {
        
    };
    
    cout << sizeof(size_t) << endl;
    
    // TODO: update paramters.
    for (auto& dp : p) {
        cout << endl;
        clock_t tstart = clock();
        auto res = diffWaysToCompute::Solution().diffWaysToCompute(dp.input);
        cout << clock() - tstart << endl;
        cout << res << endl;
    }
    return 0;
}
//*/
