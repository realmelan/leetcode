// copyRandomList.cpp
// leetcode
//
// Created by  Song Ding on 5/13/18.
// Copyright © 2018 Song Ding. All rights reserved.
//
#include "common.h"
using namespace std;

namespace copyRandomList {

class Solution {
public:
    /**
     * use a map to map source node to destination node
     * when setting values of random pointer int destination.
     *
     */
    RandomListNode *copyRandomList(RandomListNode *head) {
        map<RandomListNode*, RandomListNode*> mapper;
        RandomListNode p(0);
        RandomListNode* s = head;
        RandomListNode* prev = &p;
        while (s) {
            RandomListNode* t = new RandomListNode(s->label);
            mapper.insert(make_pair(s, t));
            
            prev->next = t;
            prev = t;
            s = s->next;
        }
        
        // go through new list
        s = head;
        RandomListNode* d = p.next;
        while (s) {
            if (s->random != NULL) {
                d->random = mapper[s->random];
            }
            s = s->next;
            d = d->next;
        }
        return p.next;
    }

private:
};

}

/*/
int main() {
    // TODO: prepare parameters here
    RandomListNode* c = new RandomListNode(1);
    RandomListNode* head = c;
    
    c->next = new RandomListNode(2);
    c = c->next;
    c->random = head;
    
    c->next = new RandomListNode(3);
    c->next->random = head;

    // TODO: add return type and paramters.
    clock_t start = clock();
    auto res = copyRandomList::Solution().copyRandomList(head);
    cout << clock() - start << endl;
    //cout << res << endl;
    return 0;
}
//*/
