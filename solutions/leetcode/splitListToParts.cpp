// splitListToParts.cpp
// leetcode
//
// Created by  Song Ding on 6/20/18.
// Copyright © 2018 Song Ding. All rights reserved.
//
#include "common.h"
using namespace std;

namespace splitListToParts {

class Solution {
public:
    vector<ListNode*> splitListToParts(ListNode* root, int k) {
        int n = 0;
        ListNode* c = root;
        while (c) {
            ++n;
            c = c->next;
        }
        int len = n / k;
        int re = n % k;
        
        vector<ListNode*> res;
        c = root;
        ListNode pivot(99999);
        pivot.next = root;
        ListNode* prev = &pivot;
        for (int i = 0; i < k; ++i) {
            res.push_back(c);
            int j = 0;
            while (c && ++j <= len) {
                prev = c;
                c = c->next;
            }
            if (c && re-- > 0) {
                prev = c;
                c = c->next;
            }
            prev->next = NULL;
        }
        return res;
    }

private:
};

}

/*/
int main() {
    // TODO: prepare parameters here
    vector<int> vals = {1};
    ListNode* root = new ListNode(vals[0]);
    ListNode* prev = root;
    for (int i = 1; i < vals.size(); ++i) {
        prev->next = new ListNode(vals[i]);
        prev = prev->next;
    }
    
    int k = 5;
    // TODO: add return type and paramters.
    clock_t start = clock();
    auto res = splitListToParts::Solution().splitListToParts(root, k);
    cout << clock() - start << endl;
    cout << res << endl;
    return 0;
}
//*/
