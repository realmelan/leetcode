//
//  RandomizedSet.cpp
//  leetcode
//
//  Created by  Song Ding on 11/15/17.
//  Copyright © 2017 Song Ding. All rights reserved.
//

#include "common.h"

using namespace std;

class RandomizedSet {
public:
    /** Initialize your data structure here. */
    // A hash_map of a data structure, which are linked together
    RandomizedSet() {
        head = NULL;
        current = NULL;
    }
    
    /** Inserts a value to the set. Returns true if the set did not already contain the specified element. */
    bool insert(int val) {
        auto it = store.find(val);
        if (it == store.end()) {
            struct Node* p = new Node(val);
            store.insert(make_pair(val, p));
            p->next = head;
            if (head != NULL) {
                head->prev = p;
            }
            head = p;
            current = head;
            return true;
        }
        return false;
    }
    
    /** Removes a value from the set. Returns true if the set contained the specified element. */
    bool remove(int val) {
        auto it = store.find(val);
        if (it != store.end()) {
            struct Node* p = it->second;
            
            if (head == p) {
                head = p->next;
            } else {
                if (p->prev) {
                    p->prev->next = p->next;
                }
                if (p->next) {
                    p->next->prev = p->prev;
                }
            }
            
            if (current == p) {
                current = p->next;
            }
            if (current == NULL) {
                current = head;
            }
            delete p;
            store.erase(it);
            return true;
        }
        return false;
    }
    
    /** Get a random element from the set. */
    int getRandom() {
        int val = current->val;
        current = current->next;
        if (current == NULL) {
            current = head;
        }
        return val;
    }
private:
    struct Node {
        int val;
        struct Node* prev;
        struct Node* next;
        Node(int v) : val(v), prev(NULL), next(NULL) {}
    };
    unordered_map<int, struct Node*> store;
    struct Node* head;
    struct Node* current;
};

/**
 * Your RandomizedSet object will be instantiated and called as such:
 * RandomizedSet obj = new RandomizedSet();
 * bool param_1 = obj.insert(val);
 * bool param_2 = obj.remove(val);
 * int param_3 = obj.getRandom();
 */

/*
int main() {
    RandomizedSet r;
    cout << r.insert(1) << endl;
    cout << r.remove(2) << endl;
    cout << r.insert(2) << endl;
    cout << r.getRandom() << endl;
    cout << r.remove(1) << endl;
    cout << r.insert(2) << endl;
    cout << r.getRandom() << endl;
    return 0;
    
    return 0;
}
 */
