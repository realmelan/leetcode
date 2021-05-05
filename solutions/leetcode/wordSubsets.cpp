// wordSubsets.cpp
// leetcode
//
// Created by  Song Ding on 5/14/19.
// Copyright © 2019 Song Ding. All rights reserved.
//
#include "common.h"
using namespace std;

namespace wordSubsets {
/*
 916. Word Subsets
 Medium
 
 155
 
 50
 
 Favorite
 
 Share
 We are given two arrays A and B of words.  Each word is a string of lowercase letters.
 
 Now, say that word b is a subset of word a if every letter in b occurs in a, including multiplicity.  For example, "wrr" is a subset of "warrior", but is not a subset of "world".
 
 Now say a word a from A is universal if for every b in B, b is a subset of a.
 
 Return a list of all universal words in A.  You can return the words in any order.
 
 
 
 Example 1:
 
 Input: A = ["amazon","apple","facebook","google","leetcode"], B = ["e","o"]
 Output: ["facebook","google","leetcode"]
 Example 2:
 
 Input: A = ["amazon","apple","facebook","google","leetcode"], B = ["l","e"]
 Output: ["apple","google","leetcode"]
 Example 3:
 
 Input: A = ["amazon","apple","facebook","google","leetcode"], B = ["e","oo"]
 Output: ["facebook","google"]
 Example 4:
 
 Input: A = ["amazon","apple","facebook","google","leetcode"], B = ["lo","eo"]
 Output: ["google","leetcode"]
 Example 5:
 
 Input: A = ["amazon","apple","facebook","google","leetcode"], B = ["ec","oc","ceo"]
 Output: ["facebook","leetcode"]
 
 
 Note:
 
 1 <= A.length, B.length <= 10000
 1 <= A[i].length, B[i].length <= 10
 A[i] and B[i] consist only of lowercase letters.
 All words in A[i] are unique: there isn't i != j with A[i] == A[j].
 */

class Solution {
public:
    /**
     * words in A may overlap or have containment relationship;
     * same with B.
     */
    vector<string> wordSubsets(vector<string>& A, vector<string>& B) {
        int an = A.size();
        vector<vector<int>> charCount(an);
        for (int i = 0; i < an; ++i) {
            charCount[i].resize(26, 0);
            for (auto c : A[i]) {
                ++charCount[i][c-'a'];
            }
        }
        
        // just need the max occurrence of a character in all words of B.
        int bn = B.size();
        vector<int> bCharCount(26, 0);
        for (int i = 0; i < bn; ++i) {
            vector<int> bc(26, 0);
            for (auto c : B[i]) {
                ++bc[c-'a'];
            }
            for (int i = 0; i < 26; ++i) {
                if (bCharCount[i] < bc[i]) {
                    bCharCount[i] = bc[i];
                }
            }
        }
        
        vector<string> res;
        for (int i = 0; i < an; ++i) {
            bool good = true;
            for (int j = 0; good && j < 26; ++j) {
                if (charCount[i][j] < bCharCount[j]) {
                    good = false;
                }
            }
            if (good) {
                res.push_back(A[i]);
            }
        }
        return res;
    }

private:
};

}

/*/
int main() {
    // TODO: prepare parameters here
    struct dp {
        vector<string> A;
        vector<string> B;
    };
    vector< struct dp > p {
        {{"amazon","apple","facebook","google","leetcode"},{"e","o"}},
        {{"amazon","apple","facebook","google","leetcode"},{"l","e"}},
        {{"amazon","apple","facebook","google","leetcode"},{"e","oo"}},
        {{"amazon","apple","facebook","google","leetcode"},{"lo","eo"}},
        {{"amazon","apple","facebook","google","leetcode"},{"ec","oc","ceo"}}
    };

    vector< vector<string>  > answers {
        {"facebook","google","leetcode"},
        {"apple","google","leetcode"},
        {"facebook","google"},
        {"google","leetcode"},
        {"facebook","leetcode"}
        
    };
    int i = 4;

    // TODO: add return type and paramters.
    clock_t tstart = clock();
    auto res = wordSubsets::Solution().wordSubsets(p[i].A, p[i].B);
    cout << clock() - tstart << endl;
    cout << res << endl;
    return 0;
}
//*/
