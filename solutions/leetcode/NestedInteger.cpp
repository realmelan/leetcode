//
//  NestedInteger.cpp
//  leetcode
//
//  Created by  Song Ding on 11/4/17.
//  Copyright © 2017 Song Ding. All rights reserved.
//

#include "common.h"

using namespace std;

class NestedInteger {
public:
    NestedInteger(int v)
    : _v(v), _single(true) {
    }
    
    NestedInteger(vector<NestedInteger>& v)
    : _single(false), _list(v) {
    }
     // Return true if this NestedInteger holds a single integer, rather than a nested list.
    bool isInteger() const {
        return _single;
    }

     // Return the single integer that this NestedInteger holds, if it holds a single integer
     // The result is undefined if this NestedInteger holds a nested list
    int getInteger() const {
        return _v;
    }

     // Return the nested list that this NestedInteger holds, if it holds a nested list
     // The result is undefined if this NestedInteger holds a single integer
    const vector<NestedInteger> &getList() const {
        return _list;
    }
private:
    int _v;
    bool _single;
    vector<NestedInteger> _list;
};

class NestedIterator {
public:
    /**
     We need a stack of pairs of pointer to NestedInteger, and the index
     into the vector.
     */
    NestedIterator(vector<NestedInteger>& nestedList) {
        if (nestedList.empty()) {
            return;
        }
        
        const vector<NestedInteger>* vni = &nestedList;
        while (vni) {
            _path.push(make_pair(vni, 0));
            const NestedInteger& ni = (*vni).at(0);
            if (ni.isInteger()) {
                break;
            }
            vni = &(ni.getList());
        }
        
    }
    
    int next() {
        const vector<NestedInteger>* vni = _path.top().first;
        int idx = _path.top().second;
        
        int val = (*vni)[idx].getInteger();
        move();
        return val;
        
    }
    
    bool hasNext() {
        return !(_path.empty());
    }
private:
    void move() {
        bool found = false;
        while (_path.size() && !found) {
            const vector<NestedInteger>* vni = _path.top().first;
            int idx = _path.top().second;
            _path.pop();
            
            ++idx;
            
            if (idx < vni->size()) {
                // get the first integer
                while (true) {
                    _path.push(make_pair(vni, idx));
                    const NestedInteger& ni = (*vni).at(idx);
                    if (ni.isInteger()) {
                        found = true;
                        break;
                    }
                    vni = &(ni.getList());
                    idx = 0;
                }
            } // end idx in range
        } // end while _path not empty
    }
    stack<pair<const vector<NestedInteger>*, int>> _path;
};

/**
 * Your NestedIterator object will be instantiated and called as such:
 * NestedIterator i(nestedList);
 * while (i.hasNext()) cout << i.next();
 */
void build(vector<NestedInteger>& n) {
    vector<NestedInteger> v1{NestedInteger(1), NestedInteger(1)};
    NestedInteger n2(2);
    vector<NestedInteger> v3{NestedInteger(1), NestedInteger(1)};
    
    n.push_back(v1);
    n.push_back(n2);
    n.push_back(v3);
}
/*
int main() {
    vector<NestedInteger> nestedList;
    build(nestedList);
    NestedIterator it(nestedList);
    while (it.hasNext()) {
        cout << it.next() << endl;
    }
    return 0;
}
 */


