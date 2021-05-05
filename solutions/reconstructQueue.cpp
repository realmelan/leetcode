//
//  reconstructQueue.cpp
//  leetcode
//
//  Created by Song Ding on 2/19/20.
//  Copyright © 2020 Song Ding. All rights reserved.
//

#include "common.h"
using namespace std;

namespace reconstructQueue {
/*
// TODO: copy problem statement here
 406. Queue Reconstruction by Height
 Medium

 2103

 251

 Add to List

 Share
 Suppose you have a random list of people standing in a queue. Each person is described by a pair of integers (h, k), where h is the height of the person and k is the number of people in front of this person who have a height greater than or equal to h. Write an algorithm to reconstruct the queue.

 Note:
 The number of people is less than 1,100.

  
 Example

 Input:
 [[7,0], [4,4], [7,1], [5,0], [6,1], [5,2]]

 Output:
 [[5,0], [7,0], [5,2], [6,1], [4,4], [7,1]]
*/
class Solution {
public:
    // TODO: copy function signature here
    vector<vector<int>> reconstructQueue(vector<vector<int>>& people) {
        vector<vector<int>> res;
        if (people.size()) {
            sort(people.begin(), people.end(), [](const auto& a, const auto& b){
                return a[0] != b[0] ? (a[0] > b[0]) : (a[1] < b[1]);
            });

            res.push_back(people[0]);
            for (int i = 1; i < people.size(); ++i) {
                res.insert(res.begin() + people[i][1], people[i]);
            }
        }
        return res;
    }
    
    vector<vector<int>> reconstructQueue2(vector<vector<int>>& people) {
        vector<vector<int>> res;
        if (people.empty()) {
            return res;
        }
        
        res.resize(people.size());
        vector<bool> occupied(people.size());
        sort(people.begin(), people.end(), [](const auto& a, const auto& b){
            return a[0] != b[0] ? (a[0] < b[0]) : (a[1] < b[1]);
        });
        
        for (int i = 0; i < people.size(); ++i) {
            int height = people[i][0];
            int before = people[i][1] + 1;
            int pos = 0;
            int count = 0;
            while (pos < occupied.size()) {
                if (!occupied[pos] || res[pos][0] == height) {
                    count++;
                    if (count == before) {
                        occupied[pos] = true;
                        break;
                    }
                }
                pos++;
            }
            res[pos] = people[i];
        }
        return res;
    }
    
private:
};
}

/*
int main() {
    // TODO: define parameter type here
    struct param {
        vector<vector<int>> people;
    };
    // TODO: prepare parameters here
    vector<struct param> params {
        {{{7,0}, {4,4}, {7,1}, {5,0}, {6,1}, {5,2}}}
    };
    // TODO: provide expected results here
    vector< vector<vector<int>> > answers {
    };
    
    for (auto& dp : params) {
        cout << endl;
        clock_t tstart = clock();
        auto res = reconstructQueue::Solution().reconstructQueue2(dp.people);
        cout << res << endl;
        cout << clock() - tstart << endl;
    }

    return 0;
}
//*/
