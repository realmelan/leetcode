// FreqStack.cpp
// leetcode
//
// Created by  Song Ding on 10/8/18.
// Copyright © 2018 Song Ding. All rights reserved.
//
#include "common.h"
using namespace std;

namespace FreqStack {

class FreqStack {
public:
    FreqStack() {
        
    }
    
    void push(int x) {
        int c = 1;
        auto it = counts.find(x);
        if (it != counts.end()) {
            c = it->second + 1;
        }
        counts[x] = c;
        //stack.push_back(make_pair(x, c));
        auto iit = stack.begin();
        while (iit != stack.end() && iit->second <= c) {
            ++iit;
        }
        stack.insert(iit, make_pair(x, c));
    }
    
    int pop() {
        int res = stack.rbegin()->first;
        --counts[res];
        stack.resize(stack.size() - 1);
        return res;
    }
private:
    unordered_map<int,int> counts;
    vector<pair<int,int>> stack;
};

}

/*/
int main() {
    // TODO: prepare parameters here
    FreqStack::FreqStack fs;
    // TODO: add return type and paramters.
    clock_t start = clock();
    
    fs.push(5);
    fs.push(7);
    fs.push(5);
    fs.push(7);
    fs.push(4);
    fs.push(5);
    
    cout << fs.pop() << endl;
    cout << fs.pop() << endl;
    cout << fs.pop() << endl;
    cout << fs.pop() << endl;
    
    
    cout << clock() - start << endl;
    
    return 0;
}
//*/
