// minWindow.cpp
// leetcode
//
// Created by  Song Ding on 4/10/18.
// Copyright © 2018 Song Ding. All rights reserved.
//
#include "common.h"
using namespace std;

namespace minWindow {

/**
 727. Minimum Window Subsequence

 Given strings S and T, find the minimum (contiguous) substring W of S, so that T is a subsequence of W.

 If there is no such window in S that covers all characters in T, return the empty string "". If there are multiple such minimum-length windows, return the one with the left-most starting index.

 Example 1:

 Input:
 S = "abcdebdde", T = "bde"
 Output: "bcde"
 Explanation:
 "bcde" is the answer because it occurs before "bdde" which has the same length.
 "deb" is not a smaller window because the elements of T in the window must occur in order.
 Note:

 All the strings in the input will only contain lowercase letters.
 The length of S will be in the range [1, 20000].
 The length of T will be in the range [1, 100].
 */

class Solution {
public:
    string minWindow(string s, string t) {
        return minWindow_dp(s, t);
    }
    
    string minWindow_dp(string s, string t) {
        int ns = s.size(), nt = t.size();
        vector<vector<int>> dp(ns, vector<int>(nt, -1));
        dp[0][0] = s[0] == t[0] ? 0 : -1;
        for (int i = 1; i < ns; ++i) {
            dp[i][0] = s[i] == t[0] ? i : dp[i-1][0];
        }
        
        for (int j = 1; j < nt; ++j) {
            for (int i = j; i < ns; ++i) {
                if (s[i] == t[j]) {
                    dp[i][j] = dp[i-1][j-1];
                } else {
                    dp[i][j] = dp[i-1][j];
                }
            }
        }
        int st = 0, mlen = INT_MAX;
        for (int i = nt-1; i < ns; ++i) {
            if (dp[i][nt-1] >= 0 && i - dp[i][nt-1] + 1 < mlen) {
                mlen = i - dp[i][nt-1] + 1;
                st = dp[i][nt-1];
            }
        }
        return mlen == INT_MAX ? "" : s.substr(st, mlen);
    }
    
    string minWindow_pp(string s, string t) {
        int ns = s.size(), nt = t.size();
        int i = 0, j = 0, res = INT_MAX, st = 0;
        while (i < ns) {
            if (s[i] == t[j]) {
                
                if (j == nt-1) {
                    int end = i;
                    while (j >= 0) {
                        if (t[j] == s[i]) {
                            --j;
                            --i;
                        } else {
                            --i;
                        }
                    }
                    if (end - i < res) {
                        res = end - i;
                        st = i+1;
                    }
                    j = 0;
                    i += 2;
                } else {
                    ++i;
                    ++j;
                }
            } else {
                ++i;
            }
        }
        return res == INT_MAX ? "" : s.substr(st, res);
    }
    
    string minWindow_binarysearch(string s, string t) {
        int l = t.size(), r = s.size();
        int start = -1;
        while (l < r) {
            int mid = (l+r)/2;
            int st = contains(s, t, mid);
            if (st < 0) {
                l = mid+1;
            } else {
                r = mid;
                start = st;
            }
        }
        cout << l << endl;
        return start < 0 ? "" : s.substr(start, l);
    }
    int contains(const string& s, const string& t, int len) {
        for (int i = 0; i < s.size() - len; ++i) {
            int j = 0;
            int k = i;
            for (; k < i+len; ++k) {
                if (s[k] == t[j]) {
                    ++j;
                }
            }
            if (j == t.size()) {
                return i;
            }
        }
        return -1;
    }
    string minWindowx(string s, string t) {
        vector<int> map(128,0);
        for(auto c: t) map[c]++;
        int counter=t.size(), begin=0, end=0, d=INT_MAX, head=0;
        while(end<s.size()){
            if(map[s[end++]]-->0) counter--; //in t
            while(counter==0){ //valid
                if(end-begin<d)  d=end-(head=begin);
                if(map[s[begin++]]++==0) counter++;  //make it invalid
            }
        }
        return d==INT_MAX? "":s.substr(head, d);
    }
    /**
     */
    string minWindow1(string s, string t) {
        vector<int> cht(256, 0);
        for (auto c : t) { ++cht[c]; }
        
        int n = s.size();
        int minw = n + 1;
        int mini = -1;
        int uncovered = t.size();
        int i = 0;
        int j = 0;
        while (i < n) {
            if (cht[s[i]] > 0) {
                --uncovered;
            }
            --cht[s[i]];
            ++i;
            
            while (uncovered == 0) {
                if (minw > i - j) {
                    minw = i - j;
                    mini = j;
                }
                if (cht[s[j]] == 0) { // only characters in t&s would have 0 count.
                    ++uncovered;
                }
                ++cht[s[j]];
                ++j;
            }
        }
        if (mini < 0) {
            return "";
        } else {
            return s.substr(mini, minw);
        }
    }
    /**
     For each position i, find out # of chars in s[0..i].
     Now starting from 1st, find the position i which has a complete cover.
     using another index, j,  to see whether s[j+1..i] has a completer cover.
     Record the distance for each finding.
     
     For each successive i, we don't need to start from beginning. We can go
     directly from the j position for i - 1.
     
     */
    string minWindow2(string s, string t) {
        int n = s.size();
        vector<int> cht(256, 0);
        for (auto c : t) {
            ++cht[c];
        }
        
        vector<int> chi(256, 0);
        vector<int> chj(256, 0);
        int minw = n + 1;
        int mini = -1;
        int i = 0;
        int j = -1;
        while (i < n) {
            ++chi[s[i]];
            while (j < i && contains(chi, chj, cht)) {
                if (minw > i - j) {
                    minw = i - j;
                    mini = j + 1;
                }
                ++j;
                ++chj[s[j]];
            }
            ++i;
        }
        if (mini < 0) {
            return "";
        } else {
            return s.substr(mini, minw);
        }
    }

private:
    bool contains(const vector<int>& a, const vector<int>& b, const vector<int>& t) {
        for (int i = 0; i < 256; ++i) {
            if (a[i] - b[i] < t[i]) {
                return false;
            }
        }
        return true;
    }
};

}

/*/
int main() {
    // TODO: prepare parameters here
    string s = "smnabcxyz";
    string t = "abc";
    //string s = "a";
    //string t = "a";
    // TODO: add return type and paramters.
    clock_t start = clock();
    auto res = minWindow::Solution().minWindow(s, t);
    cout << clock() - start << endl;
    cout << res << endl;
    return 0;
}
//*/
