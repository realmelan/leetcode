// rearrangeBarcodes.cpp
// leetcode
//
// Created by  Song Ding on 6/5/19.
// Copyright © 2019 Song Ding. All rights reserved.
//
#include "common.h"
using namespace std;

namespace rearrangeBarcodes {
/*
// TODO: copy problem statement here
 1054. Distant Barcodes
 Medium
 
 86
 
 3
 
 Favorite
 
 Share
 In a warehouse, there is a row of barcodes, where the i-th barcode is barcodes[i].
 
 Rearrange the barcodes so that no two adjacent barcodes are equal.  You may return any answer, and it is guaranteed an answer exists.
 
 
 
 Example 1:
 
 Input: [1,1,1,2,2,2]
 Output: [2,1,2,1,2,1]
 Example 2:
 
 Input: [1,1,1,1,2,2,3,3]
 Output: [1,3,1,3,2,1,2,1]
 
 
 Note:
 
 1 <= barcodes.length <= 10000
 1 <= barcodes[i] <= 10000
 */

class Solution {
public:
    /**
     * sort all barcodes by frequency.
     * start from the 1st barcodes, place them in the odd position, until
     * all odd position is filled.
     * then place all left over barcodes in the even positions, starting from
     * the one that occupise the last odd position if there is one.
     */
    vector<int> rearrangeBarcodes(vector<int>& barcodes) {
        int n = barcodes.size();
        vector<int> res(n);
        unordered_map<int,int> count;
        for (auto i : barcodes) {
            ++count[i];
        }
        vector<pair<int,int>> bars;
        for (const auto& p : count) {
            bars.push_back(p);
        }
        
        sort(bars.begin(), bars.end(), [](const pair<int,int>& a, const pair<int,int>& b){
            return a.second > b.second;
        });
        
        int i = 0;
        int j = 0;
        // fill in odd positions.
        while (j < n) {
            if (bars[i].second) {
                res[j] = bars[i].first;
                if (--bars[i].second == 0) {
                    ++i;
                }
            }
            j += 2;
        }
        // fill in the even position
        j = 1;
        while (j < n) {
            if (bars[i].second) {
                res[j] = bars[i].first;
                if (--bars[i].second == 0) {
                    ++i;
                }
            }
            j += 2;
        }
        
        return res;
    }
    /**
     * sort the barcode based on frequency,
     * match the 1st bardcode with the last barcode until the 1st barcode
     * has same frequency as 2nd.
     *
     * Now, output 1st and 2nd until they have same frequency as 3rd; again
     * output 1st, 2nd and 3rd until they have same frequency as 4th.
     */
    vector<int> rearrangeBarcodes2(vector<int>& barcodes) {
        vector<int> res;
        unordered_map<int,int> count;
        for (auto i : barcodes) {
            ++count[i];
        }
        vector<pair<int,int>> bars;
        for (const auto& p : count) {
            bars.push_back(p);
        }
        
        sort(bars.begin(), bars.end(), [](const pair<int,int>& a, const pair<int,int>& b){
            return a.second > b.second;
        });
        
        int n = bars.size();
        int j = n - 1;
        
        vector<int> batch{0};
        // reduce the first bar using the last bar until
        // it has same number as the 2nd bar.
        if (n <= 1) {
            return barcodes;
        }
    
        int g = bars[1].second;
        while (bars[0].second > g) {
            if (bars[j].second <= 0) {
                if (j > 1) {
                    bars.resize(j);
                    --j;
                } else {
                    break;
                }
            }
            res.push_back(bars[0].first);
            res.push_back(bars[j].first);
            --bars[0].second;
            --bars[j].second;
        }
        
        int most = bars[0].second;
        int i = 1;
        while (most > 0) {
            while (i < bars.size() && bars[i].second == most) {
                batch.push_back(i);
                ++i;
            }
            
            for (auto j : batch) {
                res.push_back(bars[j].first);
            }
            --most;
        }
        return res;
    }
};

}

/*/
int main() {
    // TODO: define parameter type here
    struct d {
        vector<int> barcodes;
    };
    // TODO: prepare parameters here
    vector<struct d> p {
        {{1,1,1,2,2,2}},
        {{1,1,1,1,2,2,3,3}},
        {{1}},
        {{7,7,7,8,5,7,5,5,5,8}}
    };

    vector< vector<int> > answers {
        {2,1,2,1,2,1},
        {1,3,1,3,2,1,2,1}
    };

    // TODO: update paramters.
    for (auto& dp : p) {
        cout << endl;
        clock_t tstart = clock();
        auto res = rearrangeBarcodes::Solution().rearrangeBarcodes(dp.barcodes);
        cout << clock() - tstart << endl;
        cout << res << endl;
    }
    return 0;
}
//*/
