//
//  longestWPI.cpp
//  leetcode
//
//  Created by Song Ding on 3/17/21.
//  Copyright © 2021 Song Ding. All rights reserved.
//

#include "common.h"
using namespace std;

namespace longestWPI {
/*
// TODO: copy problem statement here
 1124. Longest Well-Performing Interval
 Medium

 578

 72

 Add to List

 Share
 We are given hours, a list of the number of hours worked per day for a given employee.

 A day is considered to be a tiring day if and only if the number of hours worked is (strictly) greater than 8.

 A well-performing interval is an interval of days for which the number of tiring days is strictly larger than the number of non-tiring days.

 Return the length of the longest well-performing interval.

  

 Example 1:

 Input: hours = [9,9,6,0,6,6,9]
 Output: 3
 Explanation: The longest well-performing interval is [9,9,6].
  

 Constraints:

 1 <= hours.length <= 10000
 0 <= hours[i] <= 16
 Accepted
 15,175
 Submissions
 45,591
*/
class Solution {
public:
    // TODO: copy function signature here
    int longestWPI_wrong(vector<int>& hours) {
        int cnt = 0, n = hours.size();
        vector<int> presum(n+1,0);
        for (int i = 0; i < n; ++i) {
            if (hours[i] > 8) {
                ++cnt;
                presum[i+1] = presum[i]+1;
            } else {
                presum[i+1] = presum[i]-1;
            }
        }
        if (cnt <= 0) {
            return 0;
        }
        map<int,int> s2i;
        for (int i = 0; i <= n; ++i) {
            s2i[presum[i]] = i;
        }
        int res = 1;
        for (int i = 0; i < n; ++i) {
            // lower_bound is the minimum,
            auto it = s2i.lower_bound(1+presum[i]);
            if (it != end(s2i)) {
                res = max(res, it->second - i);
            }
        }
        return res;
    }
    int longestWPI(vector<int>& hours) {
        int cnt = 0, n = hours.size();
        vector<int> presum(n+1,0);
        for (int i = 0; i < n; ++i) {
            if (hours[i] > 8) {
                ++cnt;
                presum[i+1] = presum[i]+1;
            } else {
                presum[i+1] = presum[i]-1;
            }
        }
        if (cnt <= 0) {
            return 0;
        }
        // binary search on odd numbers only
        vector<int> sp;
        int i = 1;
        for (int i = 1; i <= n+2; i+=2) {
            sp.push_back(i);
        }
        int l = 0, r = sp.size()-1;
        while (r-l>1) {
            int m = (r+l)/2;
            if (isWellPerforming(sp[m], presum)) {
                l = m;
            } else {
                r = m;
            }
        }
        if (isWellPerforming(sp[l]+1, presum)) {
            return sp[l]+1;
        }
        return sp[l];
    }
    bool isWellPerforming(int k, vector<int>& presum) {
        int n = presum.size()-1;
        for (int i = k-1; i < n; ++i) {
            if (presum[i+1] - presum[i-k+1] >= 1) {
                return true;
            }
        }
        return false;
    }
private:
};
}

/*
int main() {
    // TODO: define parameter type here
    struct param {
        vector<int> hours;
    };
    // TODO: prepare parameters here
    vector<struct param> params {
        {{9,9,9}},
        {{9,6,9}},
        {{9,9,6,0,6,6,9}},
    };
    // TODO: provide expected results here
    vector<int> answers {
        3,
        3,
        3,
    };
    
    for (auto& dp : params) {
        cout << endl;
        clock_t tstart = clock();
        auto res = longestWPI::Solution().longestWPI(dp.hours);
        cout << res << endl;
        cout << clock() - tstart << endl;
    }

    return 0;
}
//*/
