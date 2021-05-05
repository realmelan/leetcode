//
//  Skiplist.cpp
//  leetcode
//
//  Created by Song Ding on 1/5/21.
//  Copyright © 2021 Song Ding. All rights reserved.
//

#include "common.h"
using namespace std;

namespace Skiplist {
/*
// TODO: copy problem statement here
 1206. Design Skiplist
 Hard

 210

 22

 Add to List

 Share
 Design a Skiplist without using any built-in libraries.

 A Skiplist is a data structure that takes O(log(n)) time to add, erase and search. Comparing with treap and red-black tree which has the same function and performance, the code length of Skiplist can be comparatively short and the idea behind Skiplists are just simple linked lists.

 For example: we have a Skiplist containing [30,40,50,60,70,90] and we want to add 80 and 45 into it. The Skiplist works this way:


 Artyom Kalinin [CC BY-SA 3.0], via Wikimedia Commons

 You can see there are many layers in the Skiplist. Each layer is a sorted linked list. With the help of the top layers, add , erase and search can be faster than O(n). It can be proven that the average time complexity for each operation is O(log(n)) and space complexity is O(n).

 To be specific, your design should include these functions:

 bool search(int target) : Return whether the target exists in the Skiplist or not.
 void add(int num): Insert a value into the SkipList.
 bool erase(int num): Remove a value in the Skiplist. If num does not exist in the Skiplist, do nothing and return false. If there exists multiple num values, removing any one of them is fine.
 See more about Skiplist : https://en.wikipedia.org/wiki/Skip_list

 Note that duplicates may exist in the Skiplist, your code needs to handle this situation.

  

 Example:

 Skiplist skiplist = new Skiplist();

 skiplist.add(1);
 skiplist.add(2);
 skiplist.add(3);
 skiplist.search(0);   // return false.
 skiplist.add(4);
 skiplist.search(1);   // return true.
 skiplist.erase(0);    // return false, 0 is not in skiplist.
 skiplist.erase(1);    // return true.
 skiplist.search(1);   // return false, 1 has already been erased.
  

 Constraints:

 0 <= num, target <= 20000
 At most 50000 calls will be made to search, add, and erase.
*/

class Skiplist {
public:
    Skiplist() : head(-1) {
    }
    
    bool search(int target) {
        vector<Node*> down = locate(target);
        return down.back()->val == target;
    }
    
    
    void add(int num) {
        vector<Node*> down = locate(num);
        // num is on higher level
        Node* cur = down.back();
        Node* t = new Node(num);
        link(cur, t);
        Node* promo = t;
        if (cur->val == num) {
            promo = cur;
        }
            
        down.pop_back();
        while (down.size() && random()) {
            cur = down.back();
            down.pop_back();
            link(cur, promo, down.size());
        }
    }
    bool erase(int num) {
        vector<Node*> down = locate(num);
        Node* cur = down.back();
        if (cur->val != num) {
            return false;
        }
        if (cur->next.back() && cur->next.back()->val == num) {
            delete remove(cur->next.back());
        } else {
            delete remove(cur);
        }
        return true;
    }
    
private:
    struct Node {
        Node(int v) : val(v), next(15, nullptr), prev(15, nullptr) {}
        int val;
        vector<Node*> next, prev; // prev for erase operation
    };
    Node head;
    
    void link(Node* a, Node* b, int level = 14) {
        b->next[level] = a->next[level];
        if (b->next[level]) {
            b->next[level]->prev[level] = b;
        }
        b->prev[level] = a;
        a->next[level] = b;
    }
    Node* remove(Node* a) {
        for (int i = 0; i < 15; ++i) {
            if (a->prev[i]) {
                a->prev[i]->next[i] = a->next[i];
                if (a->next[i]) {
                    a->next[i]->prev[i] = a->prev[i];
                }
            }
        }
        return a;
    }
    
    // invariant: cur->val <= v
    vector<Node*> locate(int v) {
        vector<Node*> down;
        Node* cur = &head;
        int level = 0;
        while (level < cur->next.size()) {
            if (cur->val >= v) {
                down.push_back(cur);
                break;
            } else if (cur->next[level] && cur->next[level]->val <= v) {
                cur = cur->next[level];
            } else {
                down.push_back(cur);
                ++level;
            }
        }
        return down;
    }
    int random() {
        return rand() % 2;
    }
};
}

/*
int main() {
    cout << endl;
    clock_t tstart = clock();
    auto res = Skiplist::Skiplist();
    res.add(0);
    res.add(5);
    res.add(2);
    res.add(1);
    cout << res.search(0) << endl;
    cout << res.search(5) << endl;
    cout << res.search(3) << endl;
    cout << res.search(2) << endl;
    cout << clock() - tstart << endl;
    return 0;
}
//*/
