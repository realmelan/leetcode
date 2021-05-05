//
//  maximizeXor.cpp
//  leetcode
//
//  Created by Song Ding on 2/4/21.
//  Copyright © 2021 Song Ding. All rights reserved.
//

#include "common.h"
using namespace std;

namespace maximizeXor {
/*
// TODO: copy problem statement here

*/
class Solution {
public:
    // TODO: copy function signature here
    vector<int> maximizeXor(vector<int>& nums, vector<vector<int>>& queries) {
        for (auto i : nums) {
            Trie::add(&root, i);
        }
        vector<int> res;
        for (auto& q : queries) {
            res.push_back(root.query(q[0], q[1], 0));
        }
        return res;
    }
    struct Trie {
       vector<Trie*> node;
        Trie() : node(2, nullptr) {}
        static void add(Trie* root, int t, int p = 31) {
            Trie* cur = root;
            while (p>=0) {
                int j = (t>>p)&1;
                if (!cur->node[j]) {
                    cur->node[j] = new Trie;
                }
                cur = cur->node[j];
                --p;
            }
        }
        int query(int t, int bound, int pres, int p = 31) {
            if (p<0) {
                return pres;
            }
            int j = (bound>>p)&1;
            int tb = (t>>p)&1;
            int res = -1;
            if (!j) {
                if (!node[0]) {
                    return -1;
                }
                return node[0]->query(t, bound,  pres | (tb<<p), p-1);
            } else {
                if ((node[0] && tb) || !node[1]) {
                    return pres | (tb<<p) | node[0]->mxor(t, p-1);
                } else {
                    res = node[1]->query(t, bound, pres | ((tb^1)<<p), p-1);
                    if (res == -1 && node[0]) {
                        return pres | (tb<<p) | node[0]->mxor(t, p-1);
                    }
                    return res;
                }
            }
        }
        int mxor(int t, int p = 31) {
            if (p<0) {
                return 0;
            }
            int j = (t>>p)&1;
            if (!j) {
                if (node[1]) {
                    return (1<<p)|node[1]->mxor(t, p-1);
                } else {
                    return node[0]->mxor(t, p-1);
                }
            } else {
                if (node[0]) {
                    return (1<<p) | node[0]->mxor(t, p-1);
                } else {
                    return node[1]->mxor(t, p-1);
                }
            }
            
        }
    };
    Trie root;
private:
};
}

/*
int main() {
    // TODO: define parameter type here
    struct param {
        vector<int> nums;
        vector<vector<int>> queries;
    };
    // TODO: prepare parameters here
    vector<struct param> params {
        {{536870912,0,534710168,330218644,142254206},{{558240772,1000000000},{307628050,1000000000},{3319300,1000000000},{2751604,683297522},{214004,404207941}}}
    };
    // TODO: provide expected results here
    vector<vector<int>> answers {
        {1050219420,844498962,540190212,539622516,330170208}
    };
    
    for (auto& dp : params) {
        cout << endl;
        clock_t tstart = clock();
        auto res = maximizeXor::Solution().maximizeXor(dp.nums, dp.queries);
        cout << res << endl;
        cout << clock() - tstart << endl;
    }

    return 0;
}
//*/
