//
//  checkInclusion.cpp
//  leetcode
//
//  Created by  Song Ding on 12/4/17.
//  Copyright © 2017 Song Ding. All rights reserved.
//

#include "common.h"

using namespace std;
/**
 567. Permutation in String
 Medium

 813

 43

 Favorite

 Share
 Given two strings s1 and s2, write a function to return true if s2 contains the permutation of s1. In other words, one of the first string's permutations is the substring of the second string.

  

 Example 1:

 Input: s1 = "ab" s2 = "eidbaooo"
 Output: True
 Explanation: s2 contains one permutation of s1 ("ba").
 Example 2:

 Input:s1= "ab" s2 = "eidboaoo"
 Output: False
  

 Note:

 The input strings only contain lower case letters.
 The length of both given strings is in range [1, 10,000].
 */

namespace checkInclusion {
    class Solution {
    public:
        /**
         https://leetcode.com/problems/permutation-in-string/discuss/102644/C%2B%2B-Java-Clean-Code-with-Explanation
         */
        bool checkInclusion2(string s1, string s2) {
            map<char,int> m;
            for (auto c : s1) {
                ++m[c];
            }
            int n1 = s1.size();
            int count = n1;
            int n2 = s2.size();
            int i = 0, j = 0;
            while (j < n2) {
                if (m[s2[j]]-- > 0) {
                    --count;
                }
                ++j;
                // j is exclusive
                // move i rightward as long as count = 0 (s2 is covered).
                while (count == 0) {
                    if (j-i == n1) {
                        return true;
                    }
                    if (m[s2[i]]++ == 0) {
                        ++count;
                    }
                    ++i;
                }
            }
            return false;
        }
        /**
         find out # of each unique character in s1.
         then find a substring in s2 which has the same character
         distribution.
         
         Here are some tips to make lookup faster:
         let ss = substring s2, which is tested for matching
         1, if a character b in ss but not in s1, then jump over to
         character next to b
         2, if a character b in ss and in s1, but ss has more b than s1,
         jump over to the character after the first b in ss.
         */
        bool checkInclusion(string s1, string s2) {
            vector<int> counts(26, -1);
            int len1 = 0;
            for (char c : s1) {
                ++counts[c - 'a'];
                ++len1;
            }
            for (auto & i : counts) {
                if (i >= 0) {
                    ++i;
                }
            }
            if (len1 == 0) {
                return true;
            }
            
            int len2 = s2.size();
            if (len2 < len1) {
                return false;
            }
            
            
            int len = len2 - len1 + 1;
            for (int i = 0; i < len;) {
                vector<int> t(counts);
                bool skip = false;
                int j = i;
                for (; j < i + len1; ++j) {
                    char c = s2[j];
                    if (t[c - 'a'] < 0) {
                        i = j + 1;
                        skip = true;
                        break;
                    } else if (t[c - 'a'] == 0) {
                        int k = i;
                        while (k < j && s2[k] != c) {
                            ++k;
                        }
                        i = k + 1;
                        skip = true;
                        break;
                    } else {
                        --t[c - 'a'];
                    }
                }
                if (skip) {
                    continue;
                }
                if (j == i + len1) {
                    return true;
                }
                ++i;
            }
            return false;
        }
    };
}
/*
int main() {
    string s1("abcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdef");
    string s2("bcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefg");
    cout << checkInclusion::Solution().checkInclusion2(s1, s2) << endl;
    return 0;
}
// */
