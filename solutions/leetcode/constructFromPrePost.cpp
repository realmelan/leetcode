// constructFromPrePost.cpp
// leetcode
//
// Created by  Song Ding on 5/31/19.
// Copyright © 2019 Song Ding. All rights reserved.
//
#include "common.h"
using namespace std;

namespace constructFromPrePost {
/*
// TODO: copy problem statement here
 889. Construct Binary Tree from Preorder and Postorder Traversal
 Medium
 
 385
 
 21
 
 Favorite
 
 Share
 Return any binary tree that matches the given preorder and postorder traversals.
 
 Values in the traversals pre and post are distinct positive integers.
 
 
 
 Example 1:
 
 Input: pre = [1,2,4,5,3,6,7], post = [4,5,2,6,7,3,1]
 Output: [1,2,3,4,5,6,7]
 
 
 Note:
 
 1 <= pre.length == post.length <= 30
 pre[] and post[] are both permutations of 1, 2, ..., pre.length.
 It is guaranteed an answer exists. If there exists multiple answers, you can return any of them.
 */

class Solution {
public:
    /**
     * Recursive:
     * root node is the first of pre and last of post.
     * 2nd in pre is the first child of root node, find its position in post to
     * determine the subtree rooted at 2nd in pre.
     * next to last of post is also a child of root node. if it is same as 2nd in pre
     * then root has only 1 child, otherwise, find its position in pre to divide pre.
     *
     */
    TreeNode* constructFromPrePost(vector<int>& pre, vector<int>& post) {
        int n = pre.size();
        if (n <= 1) {
            return new TreeNode(pre[0]);
        } else {
            TreeNode* root = NULL;
            int preChildVal = pre[1];
            int postChildVal = post[n - 2];
            if (preChildVal == postChildVal) {
                vector<int> npre(pre.begin()+1, pre.end());
                vector<int> npost(post.begin(), post.end() - 1);
                TreeNode* childNode = constructFromPrePost(npre, npost);
                root = new TreeNode(pre[0]);
                root->left = childNode;
            } else {
                // root has 2 child nodes;
                vector<int> pre1, pre2;
                vector<int>* cur = &pre1;
                for (int i = 1; i < n; ++i) {
                    if (pre[i] == postChildVal) {
                        cur = &pre2;
                    }
                    cur->push_back(pre[i]);
                }
                vector<int> post1, post2;
                cur = &post1;
                for (int i = 0; i < n-1; ++i) {
                    cur->push_back(post[i]);
                    if (post[i] == preChildVal) {
                        cur = &post2;
                    }
                }
                
                root = new TreeNode(pre[0]);
                root->left = constructFromPrePost(pre1, post1);
                root->right = constructFromPrePost(pre2, post2);
            }
            return root;
        }
    }

private:
};

}

/*/
int main() {
    // TODO: define parameter type here
    struct d {
        vector<int> pre;
        vector<int> post;
    };
    // TODO: prepare parameters here
    vector<struct d> p {
        //{{1,2,4,5,3,6,7},{4,5,2,6,7,3,1}}
        {{1,8,2,4,5,3,6,7},{4,5,2,6,7,3,8,1}}
    };

    vector< vector<int> > answers {
        {1,2,3,4,5,6,7}
    };

    // TODO: update paramters.
    for (auto& dp : p) {
        cout << endl;
        clock_t tstart = clock();
        auto res = constructFromPrePost::Solution().constructFromPrePost(dp.pre, dp.post);
        cout << clock() - tstart << endl;
        cout << res << endl;
    }
    return 0;
}
//*/
