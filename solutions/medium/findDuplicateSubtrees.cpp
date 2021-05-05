// findDuplicateSubtrees.cpp
// leetcode
//
// Created by  Song Ding on 9/29/19.
// Copyright © 2019 Song Ding. All rights reserved.
//
#include "common.h"
using namespace std;

namespace findDuplicateSubtrees {
/*
// TODO: copy problem statement here
 652. Find Duplicate Subtrees
 Medium

 875

 168

 Favorite

 Share
 Given a binary tree, return all duplicate subtrees. For each kind of duplicate subtrees, you only need to return the root node of any one of them.

 Two trees are duplicate if they have the same structure with same node values.

 Example 1:

         1
        / \
       2   3
      /   / \
     4   2   4
        /
       4
 The following are two duplicate subtrees:

       2
      /
     4
 and

     4
 Therefore, you need to return above trees' root in the form of a list.
 */

class Solution {
public:
    /**
     * https://leetcode.com/problems/find-duplicate-subtrees/discuss/106016/O(n)-time-and-space-lots-of-analysis
     * a tree is determined by root value, left tree and right tree.
     * to find duplicate tree, it is vital for tree with same structures to have same identification.
     * so id(root) = tuple(root.val, id(root->left), id(root->right)).
     * this way, we don't have to have all content of a tree in the representation of a tree.
     * To find id of a tree, so check a map to see whether the tuple representation of a tree is already
     * assigned an id, if not assign it a new one.
     */
    vector<TreeNode*> findDuplicateSubtrees(TreeNode* root) {
        unordered_map<string, pair<int,TreeNode*>> idmap;
        idmap["null"] = make_pair(0, (TreeNode*)NULL);
        
        unordered_set<string> treeset;
        getid(root, idmap, treeset);
        
        vector<TreeNode*> res;
        for (auto& s : treeset) {
            res.push_back(idmap[s].second);
        }
        return res;
    }

private:
    int getid(TreeNode* root, unordered_map<string, pair<int,TreeNode*>>& idmap, unordered_set<string>& res) {
        if (root == NULL) {
            return 0;
        }
        int lid = getid(root->left, idmap, res);
        int rid = getid(root->right, idmap, res);
        ostringstream oss;
        oss << root->val << "#" << lid << "#" << rid;
        auto it = idmap.find(oss.str());
        if (it != idmap.end()) {
            res.insert(oss.str());
            return it->second.first;
        }
        int nid = idmap.size();
        idmap[oss.str()] = make_pair(nid, root);
        return nid;
    }
    
};

}

/*/
int main() {
    // TODO: define parameter type here
    struct d {
        vector<int> nodeVals;
    };
    // TODO: prepare parameters here
    vector<struct d> p {
        {{1,2,3,4,INT_MAX,2,4,INT_MAX,INT_MAX,4,INT_MAX,INT_MAX,INT_MAX,INT_MAX,INT_MAX}},
    };

    vector< TreeNode* > answers {
    };

    // TODO: update paramters.
    for (auto& dp : p) {
        cout << endl;
        clock_t tstart = clock();
        auto res = findDuplicateSubtrees::Solution().findDuplicateSubtrees(toTree(dp.nodeVals));
        cout << clock() - tstart << endl;
        cout << res << endl;
    }
    return 0;
}
//*/
