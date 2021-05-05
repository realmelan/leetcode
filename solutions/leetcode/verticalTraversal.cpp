// verticalTraversal.cpp
// leetcode
//
// Created by  Song Ding on 4/25/19.
// Copyright © 2019 Song Ding. All rights reserved.
//
#include "common.h"
using namespace std;

namespace verticalTraversal {

class Solution {
public:
    /**
     * Let the root coordinate = (1000, 1000), then all coordinates
     * are between (0, 1000). We assign id to each position(x,y) = x * 2001 - y + 2001.
     * when traversing the b tree, pass current x, y coordinates.
     */
    vector<vector<int>> verticalTraversal(TreeNode* root) {
        vector<vector<int>> res;
        if (root != NULL) {
            map<int, set<int>> sorted;
            recur(1000, 1000, root, sorted);
            int last = -1;
            for (const auto& p : sorted) {
                int x = p.first / 2001;
                if (x != last) {
                    res.push_back({});
                }
                res.back().insert(res.back().end(), p.second.begin(), p.second.end());
                last = x;
            }
        }
        return res;
    }

private:
    int id(int x, int y) {
        return x * 2001 + 2001 - y;
    }
    void recur(int x, int y, TreeNode* cur, map<int, set<int>>& sorted) {
        int cid = id(x, y);
        sorted[cid].insert(cur->val);
        if (cur->left != NULL) {
            recur(x-1, y-1, cur->left, sorted);
        }
        if (cur->right != NULL) {
            recur(x+1, y-1, cur->right, sorted);
        }
    }
};

}

/*/
int main() {
    // TODO: prepare parameters here
    TreeNode first(3);
    first.left = new TreeNode(9);
    first.right = new TreeNode(20);
    first.right->left = new TreeNode(15);
    first.right->right = new TreeNode(7);
    
    TreeNode second(1);
    second.left = new TreeNode(2);
    second.right = new TreeNode(3);
    second.left->left = new TreeNode(4);
    second.left->right = new TreeNode(5);
    second.right->left = new TreeNode(6);
    second.right->right = new TreeNode(7);
    
    vector<TreeNode*> root {
       &first,
       &second
    };

    vector< vector<vector<int>>   > answers {
        {{9},{3,15},{20},{7}},
        {{4},{2},{1,5,6},{3},{7}}
    };
    int i = 0;

    // TODO: add return type and paramters.
    clock_t tstart = clock();
    auto res = verticalTraversal::Solution().verticalTraversal(root[i]);
    cout << clock() - tstart << endl;
    cout << res << endl;
    return 0;
}
//*/
