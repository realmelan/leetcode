//
//  common.cpp
//  leetcode
//
//  Created by  Song Ding on 5/17/19.
//  Copyright © 2019 Song Ding. All rights reserved.
//

#include "common.h"

TreeNode* toTree(const std::vector<int>& nodeVals) {
    TreeNode* res = NULL;
    int n = nodeVals.size();
    if (n > 0) {
        res = new TreeNode(nodeVals[0]);
        int i = 1;
        std::deque<TreeNode*> s{res};
        while (s.size() && i < n) {
            TreeNode* cur = s.front();
            s.pop_front();
            if (cur == NULL) {
                i += 2;
                continue;
            }
            
            if (i < n && nodeVals[i] != INT_MAX) {
                cur->left = new TreeNode(nodeVals[i]);
                s.push_back(cur->left);
            }
            i++;
            if (i < n && nodeVals[i] != INT_MAX) {
                cur->right = new TreeNode(nodeVals[i]);
                s.push_back(cur->right);
            }
            i++;
        }
    }
    return res;
}

ListNode* toList(const std::vector<int>& nodeVals) {
    ListNode head(0);
    ListNode* c = &head;
    for (auto i : nodeVals) {
        c->next = new ListNode(i);
        c = c->next;
    }
    return head.next;
}

std::ostream& operator <<(std::ostream& os, TreeNode* p) {
    os << '[';
    std::ostringstream oss;
    std::queue<TreeNode*> q;
    q.push(p);
    while (q.size()) {
        auto* c = q.front();
        q.pop();
        if (c) {
            oss << "," << c->val;
            q.push(c->left);
            q.push(c->right);
        } else {
            oss << ",null";
        }
    }
    
    std::string t(oss.str());
    int len = t.length();
    while (len >= 5 && t.substr(len-5, 5) == ",null") {
        len -= 5;
    }
    os << oss.str().substr(1, len-1);
    os << ']';
    return os;
}

std::ostream& operator <<(std::ostream& os, ListNode* p) {
    os << "[";
    std::ostringstream oss;
    while (p) {
        oss << "," << p->val;
        p = p->next;
    }
    os << oss.str().substr(1);
    os << "]";
    return os;
}

