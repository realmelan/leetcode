//
//  grayCode.cpp
//  leetcode
//
//  Created by  Song Ding on 11/9/17.
//  Copyright © 2017 Song Ding. All rights reserved.
//

#include "common.h"

using namespace std;
/**
 89. Gray Code
 Medium

 453

 1308

 Favorite

 Share
 The gray code is a binary numeral system where two successive values differ in only one bit.

 Given a non-negative integer n representing the total number of bits in the code, print the sequence of gray code. A gray code sequence must begin with 0.

 Example 1:

 Input: 2
 Output: [0,1,3,2]
 Explanation:
 00 - 0
 01 - 1
 11 - 3
 10 - 2

 For a given n, a gray code sequence may not be uniquely defined.
 For example, [0,2,3,1] is also a valid gray code sequence.

 00 - 0
 10 - 2
 11 - 3
 01 - 1
 Example 2:

 Input: 0
 Output: [0]
 Explanation: We define the gray code sequence to begin with 0.
              A gray code sequence of n has size = 2n, which for n = 0 the size is 20 = 1.
              Therefore, for n = 0 the gray code sequence is [0].
 */
namespace grayCode {
    class Solution {
    public:
        vector<int> grayCode3(int n) {
            unordered_map<string, int> used;
            string cur;
            for (int i = 0; i < n; ++i) {
                cur.push_back('0');
            }
            vector<int> res{0};
            int nb = 0;
            while (res.size() < pow(2,n) && (nb = getNextBit(cur.substr(cur.size()-n+1), n, used)) >= 0) {
                cur.push_back('0'+nb);
                res.push_back(strToInt(cur.substr(cur.size()-n), n));
            }
            return res;
        }
        int getNextBit(const string& cur, int n, unordered_map<string, int>& used) {
            auto it = used.find(cur);
            if (it == used.end()) {
                used[cur] = n-2;
                return n-1;
            } else {
                int res = it->second--;
                return res;
            }
        }
        int strToInt(const string& s, int n) {
            return strtol(s.c_str(), nullptr, n);
        }
        /**
         change 1 bit means either add 2^k or minus 2^k.
         Here is a sequence:
         00 01 11 10
         +4  100   101   111   110
         +8  1100  1101  1111  1110  1010 1011 1001 1000
         +16 ...
         
         The actions on line i+1, follow the reverse order of
         actions of line i.
         Note, when the total number of codes becomes 2^k, add
         2^k.
         
         Actually the actions can be stored in a stack, and can
         be used by next line when adding 2^k.
         */
        vector<int> grayCode(int n) {
            vector<int> res;
            stack<int> allActions;
            
            int c = 0;
            res.push_back(c);
            if (n >= 1) {
                c += 1;
                res.push_back(c);
                allActions.push(1); // add 1
            }
            
            int base = 1;
            for (int i = 2; i <= n; ++i) {
                base <<= 1;
                stack<int> prevActions(allActions);
                c += base;
                res.push_back(c);
                allActions.push(base);
                
                while (prevActions.size()) {
                    int k = prevActions.top();
                    prevActions.pop();
                    
                    c -= k;
                    res.push_back(c);
                    allActions.push(-k);
                }
            }
            
            return res;
        }
        
        vector<int> grayCode2(int n) {
            vector<int> res;
            int cur = 0;
            dfs(0, cur, n, res);
            return res;
        }
        void dfs(int idx, int& cur, int n, vector<int>& res) {
            if (idx == n) {
                res.push_back(cur);
            } else {
                dfs(idx+1, cur, n, res);
                // flip cur's idx'th bit
                cur ^= (1 << (n-idx-1));
                dfs(idx+1, cur, n, res);
            }
        }
    };
}
/*
int main() {
    vector<int> res = grayCode::Solution().grayCode3(2);
    for (auto i  : res) {
        cout << i << ",";
    }
    cout << endl;
    return 0;
}
// */
