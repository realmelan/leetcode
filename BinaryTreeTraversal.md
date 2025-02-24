# Recrusive Traversal

```c++
void recur(node* root) {
    // visit(root); // pre-order
    recur(root->left);
    // visit(root); // in-order
    recur(root->right);
    // visit(root); // post-order
}
```
when visit(root), one can record predesuccessor using a global variable, and compare predesuccessor with current node.

# Non-recursive Traversal
```
void traversal(node* root) {
    node cur = root;
    stack<node> s;
    while (cur || !s.empty()) {
        if (cur) {
            s.push(cur);
            // visit(cur); // pre-order
            cur = cur->left;
        } else {
            cur = s.top(); s.pop();
            // visit(cur); // in-order
            cur = cur->right; // in-order
            
            // below is for post-order
            cur = s.top();
            if (cur->right != nullptr && cur->right != prev) {
                cur = cur->right;
            } else {
                // visit(cur) // post-order
                prev = cur;
                cur = nullptr;
                s.pop();
            }
        }
    }
}
```

# Morris-Traveral

All above traversal methods requires at least O(logn) space. Morris travesal is O(1) space.
```c++
void morris_traversal(node* root) {
    while (root) {
        if (root->left) {
            node* pred = root->left;
            while (pred && pred->right != nullptr && pred->right != cur) {
                pred = pred->right;
            }
            // first time visiting cur
            if (pred->right == nullptr) {
                // visit(root); // pre-order
                prev->right = root;
                root = root->left;
            } else {
                // visit(cur); // in-order
                root = pred->right;
                pred->right = nullptr;
            }
        } else {
            // visit(root); // in-order, pre-order
            root = root->right;
        }
    }
}
```

# Binary tree iterator
An binary tree iterator is used to visit all nodes of binary tree in paticurlar order, pre-order, in-order or post-order.

For in-order, a stack of path from root to current node can be used to implement iterator. The top node at the stack is current node, and to get to next node, just check whether current node has right child or not: if so push to stack of all the leftmost child of the right child.

```
class BSTIterator {
public:
    BSTIterator(TreeNode* root) {
        goLeft(root);
    }
    
    int next() {
        TreeNode* cur = p.top();
        p.pop();
        if (cur->right) {
            goLeft(cur->right);
        }
        return cur->val;
    }
    
    bool hasNext() {
        return p.size();
    }
private:
    stack<TreeNode*> p;
    void goLeft(TreeNode* cur) {
        while (cur) {
            p.push(cur);
            cur = cur->left;
        }
    }
};
```

# Reference
* Morris Traversal: https://www.cnblogs.com/AnnieKim/archive/2013/06/15/morristraversal.html
* https://www.enjoyalgorithms.com/blog/iterative-binary-tree-traversals-using-stack

# Problems:
* https://leetcode.com/problems/recover-binary-search-tree/
* https://leetcode.com/problems/binary-search-tree-iterator/
