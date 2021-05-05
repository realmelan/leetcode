//
//  minDistance.cpp
//  leetcode
//
//  Created by  Song Ding on 10/14/17.
//  Copyright © 2017 Song Ding. All rights reserved.
//

#include <stdio.h>
#include <iostream>
#include <vector>

using namespace std;
namespace minDistance {
    class Solution {
    public:
        /**
         This is a optimization problem, and can be solved using dynamic
         programming:
         
         let s(i,j) = # of steps needed to make the word1[0,i], and word[0,j]
         the same, then
         
         s(i+1, j+1) = min(s(i,j+1), s(i+1, j), s(i,j) if word1[i+1]==word2[j+1])
         */
        int minDistance(string word1, string word2) {
            int len1 = word1.size();
            int len2 = word2.size();
            
            if (len1 == 0) {
                return len2;
            } else if (len2 == 0) {
                return len1;
            }
            
            vector<vector<int>> res(len1);
            for (int i = 0; i < len1; ++i) {
                res[i].resize(len2, 0);
            }
            
            // for each character in word1, calculate s(0, i)
            if (word1[0] != word2[0]) {
                res[0][0] = 1;
            }
            for (int i = 1; i < len2; ++i) {
                if (word1[0] == word2[i]) {
                    res[0][i] = i;
                } else {
                    res[0][i] = res[0][i - 1] + 1;
                }
            }
            
            // for each character in word2, calculate s(i, 0).
            for (int i = 1; i < len1; ++i) {
                if (word2[0] == word1[i]) {
                    res[i][0] = i;
                } else {
                    res[i][0] = res[i - 1][0] + 1;
                }
            }
            
            for (int i = 1; i < len1; ++i) {
                for (int j = 1; j < len2; ++j) {
                    if (word1[i] == word2[j]) {
                        res[i][j] = res[i-1][j-1];
                    } else {
                        res[i][j] = res[i-1][j-1] + 1;
                        if (res[i][j] > res[i][j-1] + 1) {
                            res[i][j] = res[i][j-1] + 1;
                        }
                        if (res[i][j] > res[i-1][j] + 1) {
                            res[i][j] = res[i-1][j] + 1;
                        }
                    }
                }
            }
            
            return res[len1-1][len2-1];
        }
    };
}
/*/
int main() {
    vector<string> word1 {
        "horse",
        "intention"
    };
    vector<string> word2 {
        "ros",
        "execution"
    };
    int i = 1;
 
    // TODO: add return type and paramters.
    clock_t tstart = clock();
    auto res = minDistance::Solution().minDistance(word1[i], word2[i]);
    cout << clock() - tstart << endl;
    cout << res << endl;
    return 0;
}
//*/
