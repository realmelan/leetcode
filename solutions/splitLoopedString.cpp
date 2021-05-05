// splitLoopedString.cpp
// leetcode
//
// Created by  Song Ding on 10/22/19.
// Copyright © 2019 Song Ding. All rights reserved.
//
#include "common.h"
using namespace std;

namespace splitLoopedString {
/*
// TODO: copy problem statement here
 555. Split Concatenated Strings

 Given a list of strings, you could concatenate these strings together into a loop, where for each string you could choose to reverse it or not. Among all the possible loops, you need to find the lexicographically biggest string after cutting the loop, which will make the looped string into a regular one.

 Specifically, to find the lexicographically biggest string, you need to experience two phases:

 Concatenate all the strings into a loop, where you can reverse some strings or not and connect them in the same order as given.
 Cut and make one breakpoint in any place of the loop, which will make the looped string into a regular one starting from the character at the cutpoint.
 And your job is to find the lexicographically biggest one among all the possible regular strings.

 Example:

 Input: "abc", "xyz"
 Output: "zyxcba"
 Explanation: You can get the looped string "-abcxyz-", "-abczyx-", "-cbaxyz-", "-cbazyx-",
 where \'-\' represents the looped status.
 The answer string came from the fourth looped one,
 where you could cut from the middle character \'a\' and get "zyxcba".
 Note:

 The input strings will only contain lowercase letters.
 The total length of all the strings will not over 1,000.
 */

class Solution {
public:
    /**
     * step 1: for each word, reverse it if it becomes larger after swap
     * step 2: find set of indices where the word is the largest, and then follow the loop and see which index yields the largest.
     */
    string splitLoopedString(vector<string>& strs) {
        int n = strs.size();
        vector<int> maxi;
        maxi.push_back(0);
        for (int i = 0; i < n; ++i) {
            string rs(strs[i]);
            std::reverse(rs.begin(), rs.end());
            if (rs > strs[i]) {
                strs[i].swap(rs);
            }
            if (strs[i] > strs[maxi[0]]) {
                maxi.clear();
                maxi.push_back(i);
            } else if (strs[i] == strs[maxi[0]]) {
                maxi.push_back(i);
            }
        }
        // find which index in maxi yields the largest
        int step = 1;
        while (maxi.size() > 1) {
            vector<int> next{maxi[0]};
            int mi = maxi[0];
            for (int i = 1; i < maxi.size(); ++i) {
                if (strs[(maxi[i]+step)%n] > strs[(mi+step)%n]) {
                    next.clear();
                    next.push_back(maxi[i]);
                } else if (strs[(maxi[i]+step)%n] == strs[(mi+step)%n]) {
                    next.push_back(maxi[i]);
                }
            }
            next.swap(maxi);
        }
        
        int cnt = 0;
        string res;
        int mi = maxi[0];
        for (int i = 0; i < n; ++i) {
            res.append(strs[mi]);
            ++mi;
            mi %= n;
        }
        return res;
    }

private:
};

}

/*/
int main() {
    // TODO: define parameter type here
    struct d {
        vector<string> strs;
    };
    // TODO: prepare parameters here
    vector<struct d> p {
        {{"abc", "xyz"}},
    };

    vector< string > answers {
        "zyxcba",
    };

    // TODO: update paramters.
    for (auto& dp : p) {
        cout << endl;
        clock_t tstart = clock();
        auto res = splitLoopedString::Solution().splitLoopedString(dp.strs);
        cout << clock() - tstart << endl;
        cout << res << endl;
    }
    return 0;
}
//*/
