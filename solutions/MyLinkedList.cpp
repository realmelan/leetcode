//
//  MyLinkedList.cpp
//  leetcode
//
//  Created by Song Ding on 6/28/20.
//  Copyright © 2020 Song Ding. All rights reserved.
//

#include "common.h"
using namespace std;

namespace MyLinkedList {
/*
// TODO: copy problem statement here

*/
class MyLinkedList {
private:
    static constexpr int ELEM_NUM = 100;
    struct Node {
        int vals[ELEM_NUM];
        int size;
        
        Node* next;
        Node* prev;
        
        Node() : size(0), next(nullptr), prev(nullptr) {}
        int get(int i){
            assert(i < size);
            return vals[i];
        }
        void linkAfter(Node* n) {
            n->next = next;
            n->prev = this;
            if (next) {
                next->prev = n;
            }
            next = n;
        }
        void linkBefore(Node* n) {
            n->next = this;
            n->prev = prev;
            if (prev) {
                prev->next = n;
            }
            prev = n;
        }
        bool full() const {
            return size >= ELEM_NUM;
        }
        bool empty() const {
            return size == 0;
        }
        void add(int i, int val) {
            assert(i <= size && i < ELEM_NUM);
            if (i == size) {
                vals[size++] = val;
            } else {
                // create a new node
                Node* n = new Node();
                linkAfter(n);
                // copy values
                memcpy(n->vals, vals + i, sizeof(int) * (size - i));
                n->size = size - i;
                
                memset(vals + i, 0, sizeof(int) * (size - i));
                vals[i] = val;
                size = i + 1;
            }
        }
        void remove(int i) {
            assert(i < size);
            if (i == size - 1) {
                --size;
            } else {
                Node* n = new Node();
                linkAfter(n);
                
                memcpy(n->vals, vals + i + 1, sizeof(int) * (size - i - 1));
                n->size = size - i - 1;
                memcpy(vals + i, 0, sizeof(int) * (size - i - 1));
                size = i;
            }
        }
    };
public:
    /** Initialize your data structure here. */
    MyLinkedList() {
        head = new Node();
        tail = head;
    }
    
    tuple<Node*, int> locate(int index) {
        Node* h = head;
        int cnt = index + 1;
        while (h && h->size < cnt) {
            cnt -= h->size;
            h = h->next;
        }
        return make_tuple(h, cnt - 1);
    }
    
    /** Get the value of the index-th node in the linked list. If the index is invalid, return -1. */
    int get(int index) {
        auto [h, id] = locate(index);
        if (!h) {
            return -1;
        } else {
            return h->get(id);
        }
    }
    
    /** Add a node of value val before the first element of the linked list. After the insertion, the new node will be the first node of the linked list. */
    void addAtHead(int val) {
        Node* t = new Node();
        head->linkBefore(t);
        
        t->add(0, val);

        head = t;
    }
    
    /** Append a node of value val to the last element of the linked list. */
    void addAtTail(int val) {
        Node* t = tail;
        if (!t->full()) {
            t->add(t->size, val);
        } else {
            Node* n = new Node();
            tail->linkAfter(n);
            
            n->add(0, val);
            
            tail = n;
        }
    }
    
    /** Add a node of value val before the index-th node in the linked list. If index equals to the length of linked list, the node will be appended to the end of linked list. If index is greater than the length, the node will not be inserted. */
    void addAtIndex(int index, int val) {
        auto [h, id] = locate(index);
        if (!h) {
            if (id == 0) {
                Node* n = new Node();
                n->add(0, val);
                tail->linkAfter(n);
                tail = n;
            }
            return;
        }
        if (!h->full()) {
            h->add(id, val);
        } else {
            if (h->next && h->next->empty()) {
                h->next->add(0, val);
            } else {
                Node* n = new Node();
                n->add(0, val);
                h->linkAfter(n);
            }
        }
        if (tail->next) {
            tail = tail->next;
        }
    }
    
    /** Delete the index-th node in the linked list, if the index is valid. */
    void deleteAtIndex(int index) {
        auto [h, id] = locate(index);
        if (h) {
            h->remove(id);
            if (tail->next) {
                tail = tail->next;
            }
        }
    }
private:
    Node *head;
    Node *tail;
};
}

/*
int main() {
    // TODO: define parameter type here
    struct param {
    };
    // TODO: prepare parameters here
    vector<struct param> params {
    };
    // TODO: provide expected results here
    vector<int> answers {
    };
    
    
        cout << endl;
        clock_t tstart = clock();
        auto res = MyLinkedList::MyLinkedList();
    MyLinkedList::MyLinkedList linkedList; // Initialize empty LinkedList
    linkedList.addAtHead(7);
    linkedList.addAtTail(2);
    linkedList.addAtHead(1);
    linkedList.addAtIndex(3,0);
    linkedList.deleteAtIndex(2);
    linkedList.addAtHead(6);
    linkedList.addAtTail(4);
    cout << linkedList.get(4) << endl;
    linkedList.addAtHead(4);
    linkedList.addAtIndex(5, 0);
    linkedList.addAtHead(6);
    

    return 0;
}
//*/
