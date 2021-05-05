// findKthNumber.cpp
// leetcode
//
// Created by  Song Ding on 7/23/19.
// Copyright © 2019 Song Ding. All rights reserved.
//
#include "common.h"
using namespace std;

namespace findKthNumber {
/*
// TODO: copy problem statement here
 440. K-th Smallest in Lexicographical Order
 Hard
 
 185
 
 34
 
 Favorite
 
 Share
 Given integers n and k, find the lexicographically k-th smallest integer in the range from 1 to n.
 
 Note: 1 ≤ k ≤ n ≤ 109.
 
 Example:
 
 Input:
 n: 13   k: 2
 
 Output:
 10
 
 Explanation:
 The lexicographical order is [1, 10, 11, 12, 13, 2, 3, 4, 5, 6, 7, 8, 9], so the second smallest number is 10.
 */

class Solution {
public:
    int findKthNumber(int n, int k) {
        return findKthNumber_step(n, k);
    }
    
    int findKthNumber_step(int n, int k) {
        int cur = 1;
        while (k > 1) {
            int first = cur, last = cur + 1;
            int step = 0;
            while (first <= n) {
                step += min(n+1, last) - first;
                first *= 10;
                last *= 10;
            }
            if (step < k) {
                k -= step;
                cur += 1;
            } else {
                k -= 1;
                cur *= 10;
            }
        }
        return cur;
    }
    
    /**
     *
     */
    int findKthNumber_cnt(int n, int k) {
        int a = n;
        vector<int> d;
        int base = 1;
        while (a/10) {
            d.push_back(a%10);
            a /= 10;
            base *= 10;
        }
        d.push_back(a);

        // TODO: when n is like 13, k=6, the first digit is 2!!
        // it means the first round, k has to be subtracted by 5(total # of numbers starting with 1).
        int i = d.size() - 1;
        vector<int> selected;
        for (; i > 0 && k > 0; --i) {
            int v = 1;
            int tcnt = 0;
            int cnt = 1;
            while (v <= base) {
                tcnt += cnt;
                v *= 10;
                cnt *= 10;
            }
            int b = i == d.size() - 1 ? 1 : 0;
            for (; b < d[i]; ++b) {
                if (tcnt >= k) {
                    break;
                }
                k -= tcnt;
            }
            selected.push_back(b);
            base /= 10;
        }
        
        // deal with last bit
        if (k > 1) {
            selected.push_back(k-1);
        }
        
        // compute the k-th, with previous digit being selected.
        int res = 0;
        for (auto i : selected) {
            res *= 10;
            res += i;
        }
        return res;
    }
    /**
     * https://leetcode.com/problems/k-th-smallest-in-lexicographical-order/discuss/92259/C%2B%2B-3ms-solution-using-stack
     * test the prefix of the answer each time. If the total number of current prefix is less than k, test the next prefix with current prefix +1, otherwise test longer prefix with current prefix * 10
     */
    int findKthNumber_stack(int n, int k) {
        stack<int> prefix;
        prefix.push(1);
        while (k) {
            int cur = prefix.top();
            prefix.pop();
            
            if (k == 1) {
                return cur;
            }
            
            // count the numbers under the prefix
            long x = cur;
            int sum = 0;
            int mask = 1;
            while (x <= n) {
                if (x + mask - 1 <= n) {
                    sum += mask;
                } else {
                    sum += n - x + 1;
                }
                
                x *= 10;
                mask *= 10;
            }
            
            if (k > sum) {
                k -= sum;
                prefix.push(cur + 1);
            } else {
                --k; // cur is counted
                prefix.push(cur * 10);
            }
        }
        return prefix.top();
    }
    /**
     * using stack to simulate expanding
     * TLE.
     */
    int findKthNumber_stack_TLE(int n, int k) {
        stack<int> w;
        for (int i = 9; i > 0; --i) {
            w.push(i);
        }
        while (w.size()) {
            int t = w.top();
            w.pop();
            if (--k == 0) {
                return t;
            }
            int nt = t * 10;
            for (int s = min(n, nt+9); s >= nt; --s) {
                w.push(s);
            }
        }
        return 0;
    }

private:
};

}

/*/
int main() {
    // TODO: define parameter type here
    struct d {
        int n;
        int k;
    };
    // TODO: prepare parameters here
    vector<struct d> p {
        {13,2},
        {13,6},
        {99,33},
        {100,10},
        {10000,10000},
        {681692778,351251360}
    };

    vector< int > answers {
        10,
        2,
        39,
        17,
        9999
    };

    // TODO: update paramters.
    for (auto& dp : p) {
        cout << endl;
        clock_t tstart = clock();
        auto res = findKthNumber::Solution().findKthNumber(dp.n, dp.k);
        cout << clock() - tstart << endl;
        cout << res << endl;
    }
    return 0;
}
//*/
