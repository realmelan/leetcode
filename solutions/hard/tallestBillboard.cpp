// tallestBillboard.cpp
// leetcode
//
// Created by  Song Ding on 9/1/19.
// Copyright © 2019 Song Ding. All rights reserved.
//
#include "common.h"
using namespace std;

namespace tallestBillboard {
/*
// TODO: copy problem statement here
 956. Tallest Billboard
 Hard
 
 201
 
 10
 
 Favorite
 
 Share
 You are installing a billboard and want it to have the largest height.  The billboard will have two steel supports, one on each side.  Each steel support must be an equal height.
 
 You have a collection of rods which can be welded together.  For example, if you have rods of lengths 1, 2, and 3, you can weld them together to make a support of length 6.
 
 Return the largest possible height of your billboard installation.  If you cannot support the billboard, return 0.
 
 
 
 Example 1:
 
 Input: [1,2,3,6]
 Output: 6
 Explanation: We have two disjoint subsets {1,2,3} and {6}, which have the same sum = 6.
 Example 2:
 
 Input: [1,2,3,4,5,6]
 Output: 10
 Explanation: We have two disjoint subsets {2,3,5} and {4,6}, which have the same sum = 10.
 Example 3:
 
 Input: [1,2]
 Output: 0
 Explanation: The billboard cannot be supported, so we return 0.
 
 
 Note:
 
 0 <= rods.length <= 20
 1 <= rods[i] <= 1000
 The sum of rods is at most 5000.
 */

class Solution {
public:
    int tallestBillboard(vector<int>& rods) {
        return tallestBillboard_gap(rods);
    }
    /**
     * let gap[i] = length of the longer half when difference btw longer and shorter halves
     * is i.
     * for each rod, update gap as needed, also, do pruning when the shorter half plus all
     * leftover rods is still shorter than the longer half.
     */
    int tallestBillboard_gap(vector<int>& rods) {
        int n = rods.size();
        int res = 0;
        
        sort(rods.begin(), rods.end(), [](int a, int b){return a > b;});
        vector<int> sums(n+1, 0);
        for (int i = n-1; i >=0; --i) {
            sums[i] = sums[i+1] + rods[i];
        }
        
        int ht = sums[0] / 2;
        vector<int> gap(ht+1, -1);
        gap[0] = 0;
        for (int k = 0; k < n; ++k) {
            int rl = rods[k];
            vector<int> ngap(ht+1, -1);
            for (int i = 0; i <= ht; ++i) {
                if (gap[i] >= 0) {
                    int l = gap[i];
                    int s = l - i;
                    if ((l+s+sums[k])/2 <= res || s+sums[k] < l) {
                        continue;
                    }
                    if (s+sums[k+1] >= l && (s+l+sums[k+1])/2 > res) {
                        ngap[l-s] = max(ngap[l-s], max(ngap[l-s], l));
                    }
                    if (s+sums[k+1] >= l+rl) {
                        ngap[l+rl-s] = max(ngap[l+rl-s], max(gap[l+rl-s], l+rl));
                    }
                    if (s+rl > l && l+sums[k+1] >= s+rl) {
                        ngap[s+rl-l] = max(ngap[s+rl-l], max(gap[s+rl-l], s+rl));
                    } else if (s+rl <= l) {
                        ngap[l-s-rl] = max(ngap[l-s-rl], max(gap[l-s-rl], l));
                        if (s+rl == l && l > res) {
                            res = l;
                        }
                    }
                }
            }
            gap.swap(ngap);
        }
        return res;
    }
    int tallestBillboard_TLE2(vector<int>& rods) {
        int n = rods.size();
        
        sort(rods.begin(), rods.end(), [](int a, int b){return a > b;});
        int res = 0;
        
        vector<int> sums(n+1, 0);
        for (int i = n-1; i >=0; --i) {
            sums[i] = sums[i+1] + rods[i];
        }
        
        int ht = (sums[0] + 1) / 2;
        unordered_set<int> cur{0};
        for (int i = 0; i < n; ++i) {
            int rl = rods[i];
            unordered_set<int> next;
            for (auto st : cur) {
                int x = st & 0xFFFF;
                int y = st >> 16;
                if ((x+y+sums[i])/2 <= res || x+sums[i] < y) {
                    continue;
                }
                if (x+sums[i+1] >= y && (x+y+sums[i+1])/2 >= res) {
                    next.insert(st);
                }
                
                if (x+sums[i+1] >= y+rl) {
                    next.insert(toState(x, y+rl));
                }
                
                if (x+rl > y && y+sums[i+1] >= x+rl) {
                    next.insert(toState(y, x+rl));
                } else if (x+rl <= y) {
                    next.insert(toState(x+rl, y));
                    if (x+rl == y && y > res) {
                        res = y;
                    }
                }
            }
            cur.swap(next);
            //cout << cur.size() << endl;
        }
        
        return res;
    }
    
    int toState(int x, int y) {
        return (y << 16) | x;
    }
                                
    /**
     * Divide array into 2 groups, so that the two groups have same maximum sum.
     * let hh(i,j) = true if heights of i and j are possible up to k rods.
     * Note, we only consider 0 =< i <= j <= 2500.
     */
    int tallestBillboard_TLE1(vector<int>& rods) {
        int n = rods.size();
        int res = 0;
        
        sort(rods.begin(), rods.end(), [](int a, int b){return a > b;});
        vector<int> sums(n+1, 0);
        for (int i = n-1; i >=0; --i) {
            sums[i] = sums[i+1] + rods[i];
        }
        
        int ht = (sums[0] + 1) / 2;
        vector<vector<bool>> hh(ht+1, vector<bool>(ht+1, false));
        hh[0][0] = true;
        int maxj = 0;
        int maxi = 0;
        for (int k = 0; k < n; ++k) {
            // add rods[k] to hh
            int rl = rods[k];
            int nmaxi = maxi;
            int nmaxj = maxj;
            vector<vector<bool>> hnext(ht+1, vector<bool>(ht+1, false));
            for (int i = 0; i <= maxi; ++i) {
                for (int j = i; j <= maxj && i+sums[k] >= j; ++j) {
                    if (!hh[i][j] || (i+j+sums[k])/2 <= res) {
                        continue;
                    }
                    if (i+sums[k+1] >= j) {
                        hnext[i][j] = true;
                    }
                    if (i + sums[k+1] >= j+rl) {
                        hnext[i][j+rl] = true;
                        nmaxj = max(nmaxj, j+rl);
                    }
                    if (i+rl > j && j+sums[k+1] >= i+rl) {
                        hnext[j][i+rl] = true;
                        nmaxi = max(nmaxi, j);
                    } else if (i+rl <= j) {
                        hnext[i+rl][j] = true;
                        nmaxi = max(nmaxi, i+rl);
                        if (i+rl == j && j > res) {
                            res = j;
                        }
                    }
                    
                }
            }
            hh.swap(hnext);
            maxi = nmaxi;
            maxj = nmaxj;
        }
        return res;
    }

private:
};

}

/*/
int main() {
    // TODO: define parameter type here
    struct d {
        vector<int> rods;
    };
    // TODO: prepare parameters here
    vector<struct d> p {
        {{1,2,3,6}},
        {{1,2,3,4,5,6}},
        {{1,2}},
        {{1,2,4,8,16,32,64,128,256,512}},
        {{162,161,149,180,146,149,146,148,145,134,138,138,153,151}},
        {{84,114,89,107,93,91,97,98,114,104,88,89,109,106,103,102,103,109}},
        {{156,160,153,149,158,136,172,147,148,133,147,147,146,131,171,165,145,143,148,145}},
    };

    vector< int > answers {
        6,
        10,
        0,
        0,
        1050,
        900,
        1500
    };

    // TODO: update paramters.
    for (auto& dp : p) {
        cout << endl;
        clock_t tstart = clock();
        auto res = tallestBillboard::Solution().tallestBillboard(dp.rods);
        cout << clock() - tstart << endl;
        cout << res << endl;
    }
    return 0;
}
//*/
