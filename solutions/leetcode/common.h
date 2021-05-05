//
//  common.h
//  leetcode
//
//  Created by  Song Ding on 10/24/17.
//  Copyright © 2017 Song Ding. All rights reserved.
//

#ifndef common_h
#define common_h

#include <iostream>
#include <sstream>
#include <string>
#include <iomanip>

#include <vector>
#include <set>
#include <map>
#include <stack>
#include <queue>
#include <list>
#include <algorithm>
#include <utility>
#include <bitset>
#include <climits>
#include <array>
#include <numeric>
#include <cstdlib>

#include <unordered_map>
#include <unordered_set>

#include <time.h>

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode *next;
    TreeNode(int x) : val(x), left(NULL), right(NULL), next(NULL) {}
};

struct Point {
    int x;
    int y;
    Point() : x(0), y(0) {}
    Point(int a, int b) : x(a), y(b) {}
};

struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode* next) : val(x), next(next) {}
};

// Definition for a Node.
class Node {
public:
    int val;
    Node* prev;
    Node* next;
    Node* child;
    
    Node() {}
    
    Node(int _val, Node* _prev, Node* _next, Node* _child) {
        val = _val;
        prev = _prev;
        next = _next;
        child = _child;
    }
};


/**
 * Definition for singly-linked list with a random pointer.
 *
 */
struct RandomListNode {
    int label;
    RandomListNode *next, *random;
    RandomListNode(int x) : label(x), next(NULL), random(NULL) {}
};

inline
std::ostream& operator <<(std::ostream& os, const Point& p) {
    os << "[" << p.x << "," << p.y << "]";
    return os;
}
inline
std::ostream& operator<<(std::ostream& os, const ListNode* p) {
    os << "[";
    while (p) {
        os << p->val << ",";
        p = p->next;
    }
    os << "]";
    return os;
}

template<typename T1, typename T2>
std::ostream& operator <<(std::ostream& os, const std::pair<T1,T2>& p) {
    os << "[" << p.first << "," << p.second << "]";
    return os;
}
template<typename T>
std::ostream& operator <<(std::ostream& os, const std::pair<T,T>& p) {
    os << "[" << p.first << "," << p.second << "]";
    return os;
}


template<typename T>
std::ostream& operator <<(std::ostream& os, const std::vector<T>& vs) {
    os << "{";
    for (const auto& v : vs) {
        os << v << ",";
    }
    os << "}";
    return os;
}


template<typename T>
void printVector(const std::vector<T>& nums) {
    for (auto n : nums) {
        std::cout << n << ",";
    }
    std::cout << std::endl;
}

TreeNode* toTree(const std::vector<int>& nodeVals);
ListNode* toList(const std::vector<int>& nodeVals);

std::ostream& operator <<(std::ostream& os, TreeNode* p);
std::ostream& operator <<(std::ostream& os, ListNode* p);


struct GraphNode {
public:
    int val;
    std::vector<GraphNode*> neighbors;
    
    GraphNode() {}
    
    GraphNode(int _val, std::vector<GraphNode*> _neighbors) {
        val = _val;
        neighbors = _neighbors;
    }
};

class QuadTreeNode {
public:
    bool val;
    bool isLeaf;
    QuadTreeNode* topLeft;
    QuadTreeNode* topRight;
    QuadTreeNode* bottomLeft;
    QuadTreeNode* bottomRight;
    
    QuadTreeNode() {}
    
    QuadTreeNode(bool _val, bool _isLeaf, QuadTreeNode* _topLeft, QuadTreeNode* _topRight, QuadTreeNode* _bottomLeft, QuadTreeNode* _bottomRight) {
        val = _val;
        isLeaf = _isLeaf;
        topLeft = _topLeft;
        topRight = _topRight;
        bottomLeft = _bottomLeft;
        bottomRight = _bottomRight;
    }
};

#define __MAIN__ main

#endif /* common_h */
