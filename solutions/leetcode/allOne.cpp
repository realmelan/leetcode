// allOne.cpp
// leetcode
//
// Created by  Song Ding on 3/23/18.
// Copyright © 2018 Song Ding. All rights reserved.
//
#include "common.h"
using namespace std;

namespace allOne {

    class AllOne {
        struct Node {
            int count;
            unordered_set<string> keys;
            Node* next;
            Node* prev;
        };
    public:
        /** Initialize your data structure here. */
        AllOne() {
            _head.count = INT_MIN;
            _tail.count = INT_MIN;
            
            _head.next = &_tail;
            _head.prev = NULL;
            
            _tail.next = NULL;
            _tail.prev = &_head;
        }
        
        /** Inserts a new key <Key> with value 1. Or increments an existing key by 1. */
        void inc(string key) {
            auto it = _count.find(key);
            if (it == _count.end()) {
                if (_head.next && _head.next->count == 1) {
                    _head.next->keys.insert(key);
                    _count[key] = _head.next;
                } else {
                    Node* n = new Node();;
                    n->count = 1;
                    n->keys.insert(key);
                    n->prev = &_head;
                    n->next = _head.next;
                    _count[key] = n;
                    
                    _head.next = n;
                    n->next->prev = n;
                }
            } else {
                Node* node = it->second;
                Node* prev = node->prev;
                Node* next = node->next;
                int c = node->count + 1;
                if (next->count == c) {
                    next->keys.insert(key);
                    _count[key] = next;
                    if (node->keys.size() == 1) {
                        // remove node
                        prev->next = next;
                        next->prev = prev;
                        delete node;
                    } else {
                        node->keys.erase(key);
                    }
                } else {
                    if (node->keys.size() == 1) {
                        node->count = c;
                    } else {
                        node->keys.erase(key);
                        Node* n = new Node();
                        n->keys.insert(key);
                        n->count = c;
                        _count[key] = n;
                        
                        node->next = n;
                        n->prev = node;
                        n->next = next;
                        next->prev = n;
                    }
                }
            }
            
        }
        
        /** Decrements an existing key by 1. If Key's value is 1, remove it from the data structure. */
        void dec(string key) {
            auto it = _count.find(key);
            if (it == _count.end()) {
                return;
            }
            Node* node = it->second;
            Node* next = node->next;
            Node* prev = node->prev;
            int c = node->count - 1;
            
            if (c == 0) {
                _count.erase(key);
                if (node->keys.size() == 1) {
                    prev->next = next;
                    next->prev = prev;
                    delete node;
                } else {
                    node->keys.erase(key);
                }
            } else if (prev->count == c) {
                prev->keys.insert(key);
                _count[key] = prev;
                
                if (node->keys.size() == 1) {
                    // remove node
                    prev->next = next;
                    next->prev = prev;
                    delete node;
                } else {
                    node->keys.erase(key);
                }
            } else {
                if (node->keys.size() == 1) { // repurpose node
                    node->count = c;
                } else {
                    node->keys.erase(key);
                    Node* n = new Node();
                    n->count = c;
                    n->keys.insert(key);
                    _count[key] = n;
                    
                    prev->next = n;
                    n->prev = prev;
                    n->next = node;
                    node->prev = n;
                }
            }
        }
        
        /** Returns one of the keys with maximal value. */
        string getMaxKey() {
            Node* maxNode = _tail.prev;
            if (maxNode->count != INT_MIN) {
                return *(maxNode->keys.begin());
            }
            return "";
        }
        
        /** Returns one of the keys with Minimal value. */
        string getMinKey() {
            Node* minNode = _head.next;
            if (minNode->count != INT_MIN) {
                return *(minNode->keys.begin());
            }
            return "";
        }
    private:
        unordered_map<string, Node*> _count;
        Node _head;
        Node _tail;
    };

}

/*/
int main() {
    // TODO: prepare parameters here
    allOne::AllOne s;
    // TODO: add return type and paramters.
    s.inc("a");
    for (int i = 0; i < 6; ++i) {
        s.inc("b");
    }
    cout << s.getMaxKey() << endl;
    cout << s.getMinKey() << endl;
    return 0;
}
//*/
