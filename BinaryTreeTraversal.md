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

# Reference
* Morris Traversal: https://www.cnblogs.com/AnnieKim/archive/2013/06/15/morristraversal.html

# Problems:
* https://leetcode.com/problems/recover-binary-search-tree/
