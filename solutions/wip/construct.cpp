// construct.cpp
// leetcode
//
// Created by  Song Ding on 6/17/19.
// Copyright © 2019 Song Ding. All rights reserved.
//
#include "common.h"
using namespace std;

namespace construct {
/*
// TODO: copy problem statement here
 427. Construct Quad Tree
 Easy
 
 128
 
 307
 
 Favorite
 
 Share
 We want to use quad trees to store an N x N boolean grid. Each cell in the grid can only be true or false. The root node represents the whole grid. For each node, it will be subdivided into four children nodes until the values in the region it represents are all the same.
 
 Each node has another two boolean attributes : isLeaf and val. isLeaf is true if and only if the node is a leaf node. The val attribute for a leaf node contains the value of the region it represents.
 
 Your task is to use a quad tree to represent a given grid. The following example may help you understand the problem better:
 
 Given the 8 x 8 grid below, we want to construct the corresponding quad tree:
 
 
 
 It can be divided according to the definition above:
 
 
 
 
 
 The corresponding quad tree should be as following, where each node is represented as a (isLeaf, val) pair.
 
 For the non-leaf nodes, val can be arbitrary, so it is represented as *.
 
 
 
 Note:
 
 N is less than 1000 and guaranteened to be a power of 2.
 If you want to know more about the quad tree, you can refer to its wiki.
 */

class Solution {
public:
    /**
     * recursive
     */
    QuadTreeNode* construct(vector<vector<int>>& grid) {
        int l = grid.size();
        return help(grid, 0, 0, l);
    }

private:
    /**
     * return NULL if square starting point (x,y) of length l have same value
     */
    QuadTreeNode* help(vector<vector<int>>& grid, int x, int y, int l) {
        QuadTreeNode* root = NULL;
        if (l == 1) {
            root = new QuadTreeNode(grid[x][y], true, NULL, NULL, NULL, NULL);
        } else {
            int nl = (l >> 1);
            QuadTreeNode* lt = help(grid, x, y, nl);
            QuadTreeNode* lb = help(grid, x + nl, y, nl);
            QuadTreeNode* rt = help(grid, x, y + nl, nl);
            QuadTreeNode* rb = help(grid, x + nl, y + nl, nl);
            if (lt->isLeaf && lb->isLeaf && rt->isLeaf && rb->isLeaf
                && lt->val == lb->val
                && lt->val == rt->val
                && lt->val == rb->val) {
                root = new QuadTreeNode(lt->val, true, NULL, NULL, NULL, NULL);
                delete lt;
                delete lb;
                delete rt;
                delete rb;
            } else {
                root = new QuadTreeNode(0, false, lt, rt, lb, rb);
            }
        }
        return root;
    }
};

}

/*/
int main() {
    // TODO: define parameter type here
    struct d {
        vector<vector<int>> grid;
    };
    // TODO: prepare parameters here
    vector<struct d> p {
        
        {{{1,1,1,1,0,0,0,0},
            {1,1,1,1,0,0,0,0},
            {1,1,1,1,1,1,1,1},
            {1,1,1,1,1,1,1,1},
            {1,1,1,1,0,0,0,0},
            {1,1,1,1,0,0,0,0},
            {1,1,1,1,0,0,0,0},
            {1,1,1,1,0,0,0,0}}}
    };

    vector< int > answers {
    };

    // TODO: update paramters.
    for (auto& dp : p) {
        cout << endl;
        clock_t tstart = clock();
        auto res = construct::Solution().construct(dp.grid);
        cout << clock() - tstart << endl;
        cout << res << endl;
    }
    return 0;
}
//*/
