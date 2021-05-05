//
//  maxLength.cpp
//  leetcode
//
//  Created by Song Ding on 11/9/20.
//  Copyright © 2020 Song Ding. All rights reserved.
//

#include "common.h"
using namespace std;

namespace maxLength {
/*
// TODO: copy problem statement here
 1239. Maximum Length of a Concatenated String with Unique Characters
 Medium

 573

 69

 Add to List

 Share
 Given an array of strings arr. String s is a concatenation of a sub-sequence of arr which have unique characters.

 Return the maximum possible length of s.

  

 Example 1:

 Input: arr = ["un","iq","ue"]
 Output: 4
 Explanation: All possible concatenations are "","un","iq","ue","uniq" and "ique".
 Maximum length is 4.
 Example 2:

 Input: arr = ["cha","r","act","ers"]
 Output: 6
 Explanation: Possible solutions are "chaers" and "acters".
 Example 3:

 Input: arr = ["abcdefghijklmnopqrstuvwxyz"]
 Output: 26
  

 Constraints:

 1 <= arr.length <= 16
 1 <= arr[i].length <= 26
 arr[i] contains only lower case English letters.
*/
class Solution {
public:
    // TODO: copy function signature here
    int maxLength(vector<string>& arr) {
        int n = arr.size();
        vector<int> bits(n, 0);
        for (int i = 0; i < n; ++i) {
            for (auto c : arr[i]) {
                if (bits[i] & (1<<(c-'a'))) {
                    bits[i] = 0;
                    break;
                }
                bits[i] |= (1<<(c-'a'));
            }
        }
        int res = 0;
        vector<int> dp(1<<n, -1);
        vector<int> dpbit(1<<n, 0);
        dp[0] = 0;
        dpbit[0] = 0;
        for (int i = 0; i < 1<<n; ++i) {
            if (dp[i] >= 0) {
                for (int j = 0; j < n; ++j) {
                    if (bits[j] && !(dpbit[i] & bits[j])) {
                        dp[i|(1<<j)] = max(dp[i|(1<<j)], dp[i] + (int)arr[j].size());
                        res = max(res, dp[i|(1<<j)]);
                        dpbit[i|(1<<j)] = dpbit[i] | bits[j];
                    }
                }
            }
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
        vector<string> arr;
    };
    // TODO: prepare parameters here
    vector<struct param> params {
        {{"un","iq","ue"}},
    };
    // TODO: provide expected results here
    vector<int> answers {
        4,
    };
    
    for (auto& dp : params) {
        cout << endl;
        clock_t tstart = clock();
        auto res = maxLength::Solution().maxLength(dp.arr);
        cout << res << endl;
        cout << clock() - tstart << endl;
    }

    return 0;
}
//*/
