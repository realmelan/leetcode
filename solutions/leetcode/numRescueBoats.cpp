// numRescueBoats.cpp
// leetcode
//
// Created by  Song Ding on 5/9/19.
// Copyright © 2019 Song Ding. All rights reserved.
//
#include "common.h"
using namespace std;

namespace numRescueBoats {
/*
 881. Boats to Save People
 Medium
 
 235
 
 23
 
 Favorite
 
 Share
 The i-th person has weight people[i], and each boat can carry a maximum weight of limit.
 
 Each boat carries at most 2 people at the same time, provided the sum of the weight of those people is at most limit.
 
 Return the minimum number of boats to carry every given person.  (It is guaranteed each person can be carried by a boat.)
 
 
 
 Example 1:
 
 Input: people = [1,2], limit = 3
 Output: 1
 Explanation: 1 boat (1, 2)
 Example 2:
 
 Input: people = [3,2,2,1], limit = 3
 Output: 3
 Explanation: 3 boats (1, 2), (2) and (3)
 Example 3:
 
 Input: people = [3,5,3,4], limit = 5
 Output: 4
 Explanation: 4 boats (3), (3), (4), (5)
 Note:
 
 1 <= people.length <= 50000
 1 <= people[i] <= limit <= 30000
 */
class Solution {
public:
    /**
     * always match person of largest weight with person of lowest weight.
     * if not possible, then person with largest weight is on one boat alone.
     *
     */
    int numRescueBoats(vector<int>& people, int limit) {
        int n = people.size();
        sort(people.begin(), people.end());
        
        int res = 0;
        int i = 0;
        int j = n - 1;
        
        while (i < j) {
            if (people[i] + people[j] > limit) {
                --j;
            } else {
                ++i;
                --j;
            }
            ++res;
        }
        
        if (j == i) {
            ++res;
        }
        return res;
    }

private:
};

}

/*/
int main() {
    // TODO: prepare parameters here
    vector< pair<vector<int>, int> > params {
        {{1,2},3},
        {{3,2,2,1},3},
        {{3,5,3,4},5}
        
    };

    vector<  int > answers {
        1,
        3,
        4
    };
    int i = 2;

    // TODO: add return type and paramters.
    clock_t tstart = clock();
    auto res = numRescueBoats::Solution().numRescueBoats(params[i].first, params[i].second);
    cout << clock() - tstart << endl;
    cout << res << endl;
    return 0;
}
//*/
