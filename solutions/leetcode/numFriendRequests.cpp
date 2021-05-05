// numFriendRequests.cpp
// leetcode
//
// Created by  Song Ding on 5/7/18.
// Copyright © 2018 Song Ding. All rights reserved.
//
#include "common.h"
using namespace std;

namespace numFriendRequests {

class Solution {
public:
    int numFriendRequests(vector<int>& ages) {
        int n = ages.size();
        if (n <= 1) {
            return 0;
        }
        
        sort(ages.begin(), ages.end());
        
        int res = 0;
        int j = n - 2;
        int last = 0;
        int x = ages[n - 1] / 2 + 7;
        while (j >= 0 && ages[j] > x) {
            --j;
        }
        last = n - 2 - j;
        res += last;
        
        for (int i = n - 2; i > 0 && ages[i] > 14; --i) {
            if (ages[i] == ages[i + 1]) {
                res += last;
                continue;
            }
            int y = ages[i];
            int x = y / 2 + 7;
            while (j >= 0 && ages[j] > x) {
                --j;
            }
            last = i - j - 1;
            res += last;
        }
        if (ages[0] > 14 && ages[0] == ages[1]) {
            res += last;
        }
        return res;
    }
    
private:
};

}

/*/
int main() {
    // TODO: prepare parameters here
    vector<int> ages{7,14,63,103,118};
    // TODO: add return type and paramters.
    clock_t start = clock();
    auto res = numFriendRequests::Solution().numFriendRequests(ages);
    cout << clock() - start << endl;
    cout << res << endl;
    return 0;
}
//*/
