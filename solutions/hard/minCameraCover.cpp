// minCameraCover.cpp
// leetcode
//
// Created by  Song Ding on 9/3/19.
// Copyright © 2019 Song Ding. All rights reserved.
//
#include "common.h"
using namespace std;

namespace minCameraCover {
/*
// TODO: copy problem statement here
 968. Binary Tree Cameras
 Hard
 
 327
 
 11
 
 Favorite
 
 Share
 Given a binary tree, we install cameras on the nodes of the tree.
 
 Each camera at a node can monitor its parent, itself, and its immediate children.
 
 Calculate the minimum number of cameras needed to monitor all nodes of the tree.
 
 
 
 Example 1:
 
 
 Input: [0,0,null,0,0]
 Output: 1
 Explanation: One camera is enough to monitor all nodes if placed as shown.
 Example 2:
 
 
 Input: [0,0,null,0,null,0,null,null,0]
 Output: 2
 Explanation: At least two cameras are needed to monitor all nodes of the tree. The above image shows one of the valid configurations of camera placement.
 
 Note:
 
 The number of nodes in the given tree will be in the range [1, 1000].
 Every node has value 0.
 */

class Solution {
public:
    /**
     * Assign a state{monitored, camera, none} to each node based on states of its child nodes:
     *  1, if at least one child is none, then assign camera to current node, and add 1 to result
     *  2, else if both are monitored but not have a camera, assign none to current node;
     *  3, else assign monitored to current node.
     * a null child node is considered covered.
     *
     * Note, it is always better to move camera up in the path.
     *
     */
    int minCameraCover(TreeNode* root) {
        int res = 0;
        int ret = assign(root, res);
        if (ret <= 0) {
            ++res;
        }
        return res;
    }
    
    int minCameraCover2(TreeNode* root) {
        auto [notc, covered, camera] = dfs(root);
        return min(covered, camera);
    }

private:
    /**
     * none => 0
     * monitored => 1
     * camera => 2
     */
    int assign(TreeNode* root, int& res) {
        if (root == NULL) {
            return 1;
        }
        
        int left = assign(root->left, res);
        int right = assign(root->right, res);
        if (left <= 0 || right <= 0) {
            ++res;
            return 2;
        } else if (left >= 2 || right >= 2) {
            return 1;
        } else {
            return 0;
        }
    }
    
    tuple<int, int, int> dfs(TreeNode* root) {
        if (!root) return {0,0,1};
        auto [lnot, lcovered, lcamera] = dfs(root->left);
        auto [rnot, rcovered, rcamera] = dfs(root->right);
        return {
            lcovered + rcovered,
            min(lcamera + min(rcovered, rcamera), rcamera + min(lcovered, lcamera)),
            1 + min({lnot, lcovered, lcamera}) + min({rnot, rcovered, rcamera})
        };
    }
};

}

/*/
int main() {
    // TODO: define parameter type here
    struct d {
        vector<int> vals;
    };
    // TODO: prepare parameters here
    vector<struct d> p {
       {{0,0,INT_MAX,0,0}},
       {{0,0,INT_MAX,0,INT_MAX,0,INT_MAX,INT_MAX,0}},
        {{0}},
        {{0,0,0,INT_MAX,INT_MAX,INT_MAX,0}},
    };

    vector< int > answers {
        1,
        2,
        1,
        2
    };

    // TODO: update paramters.
    for (auto& dp : p) {
        cout << endl;
        clock_t tstart = clock();
        auto res = minCameraCover::Solution().minCameraCover2(toTree(dp.vals));
        cout << clock() - tstart << endl;
        cout << res << endl;
    }
    return 0;
}
//*/
