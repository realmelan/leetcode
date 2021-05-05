//
//  MedianFinder.cpp
//  leetcode
//
//  Created by Song Ding on 2/28/20.
//  Copyright © 2020 Song Ding. All rights reserved.
//

#include "common.h"
using namespace std;

namespace MedianFinder {
/*
// TODO: copy problem statement here
 295. Find Median from Data Stream

 Median is the middle value in an ordered integer list. If the size of the list is even, there is no middle value. So the median is the mean of the two middle value.

 Examples:
 [2,3,4] , the median is 3

 [2,3], the median is (2 + 3) / 2 = 2.5

 Design a data structure that supports the following two operations:

 void addNum(int num) - Add a integer number from the data stream to the data structure.
 double findMedian() - Return the median of all elements so far.
 For example:

 addNum(1)
 addNum(2)
 findMedian() -> 1.5
 addNum(3)
 findMedian() -> 2
 Credits:
 Special thanks to @Louis1992 for adding this problem and creating all test cases.
*/
class Solution {
public:
    // TODO: copy function signature here
    // Adds a number into the data structure.
    void addNum(int num) {
        if (smaller.empty()) {
            smaller.push(num);
        } else if (larger.size() < smaller.size()) {
            if (smaller.top() <= num) {
                larger.push(num);
            } else {
                larger.push(smaller.top());
                smaller.pop();
                smaller.push(num);
            }
        } else {
            if (num <= larger.top()) {
                smaller.push(num);
            } else {
                smaller.push(larger.top());
                larger.pop();
                larger.push(num);
            }
        }
    }
    // Returns the median of current data stream
    double findMedian() {
        if (smaller.size() > larger.size()) {
            return smaller.top();
        } else {
            return (smaller.top() + larger.top()) / 2.0;
        }
    }
private:
    // make sure smaller.size() - larger.size() >= 0 but <= 1
    priority_queue<int> smaller;
    priority_queue<int, vector<int>, greater<int>> larger;
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
    vector<double> answers {
    };
    
    MedianFinder::Solution s;
    s.addNum(1);
    s.addNum(2);
    cout << s.findMedian() << endl;
    s.addNum(3);
    cout << s.findMedian() << endl;

    return 0;
}
//*/
