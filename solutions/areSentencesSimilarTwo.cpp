//
//  areSentencesSimilarTwo.cpp
//  leetcode
//
//  Created by Song Ding on 7/8/20.
//  Copyright © 2020 Song Ding. All rights reserved.
//

#include "common.h"
using namespace std;

namespace areSentencesSimilarTwo {
/*
// TODO: copy problem statement here
737. Sentence Similarity II
 
 Given two sentences words1, words2 (each represented as an array of strings), and a list of similar word pairs pairs, determine if two sentences are similar.

 For example, words1 = ["great", "acting", "skills"] and words2 = ["fine", "drama", "talent"] are similar, if the similar word pairs are pairs = [["great", "good"], ["fine", "good"], ["acting","drama"], ["skills","talent"]].

 Note that the similarity relation is transitive. For example, if “great” and “good” are similar, and “fine” and “good” are similar, then “great” and “fine” are similar.

 Similarity is also symmetric. For example, “great” and “fine” being similar is the same as “fine” and “great” being similar.

 Also, a word is always similar with itself. For example, the sentences words1 = ["great"], words2 = ["great"], pairs = [] are similar, even though there are no specified similar word pairs.

 Finally, sentences can only be similar if they have the same number of words. So a sentence like words1 = ["great"] can never be similar to words2 = ["doubleplus","good"].

 Note:

 The length of words1 and words2 will not exceed 1000.
 The length of pairs will not exceed 2000.
 The length of each pairs[i] will be 2.
 The length of each words[i] and pairs[i][j] will be in the range [1, 20].
*/
class Solution {
public:
    // TODO: copy function signature here
     bool areSentencesSimilarTwo(vector<string>& words1, vector<string>& words2, vector<pair<string, string>>& pairs) {
         if (words1.size() != words2.size() || words1.size() > pairs.size()+1) {
             return false;
         }
         unordered_map<string, int> sid;
         vector<int> g(2000);
         for (auto& p : pairs) {
             auto it1 = sid.find(p.first);
             if (it1 == sid.end()) {
                 sid[p.first] = sid.size();
             }
             auto it2 = sid.find(p.second);
             if (it2 == sid.end()) {
                 sid[p.second] = sid.size();
             }
             
             int g1 = find(sid[p.first], g);
             int g2 = find(sid[p.second], g);
             if (g1 < g2) {
                 g[g2] = g1;
             } else {
                 g[g1] = g2;
             }
         }
         int n = words1.size();
         for (int i = 0; i < n; ++i) {
             auto it1 = sid.find(words1[i]);
             auto it2 = sid.find(words2[i]);
             if (it1 == sid.end() || it2 == sid.end()) {
                 return false;
             }
             if (find(it1->second, g) != find(it2->second, g)) {
                 return false;
             }
         }
         return true;
     }
private:
    int find(int i, vector<int>& g) {
        if (i != g[i]) {
            g[i] = find(g[i], g);
        }
        return g[i];
    }
};
}

/*
int main() {
    // TODO: define parameter type here
    struct param {
        vector<string> words1;
        vector<string> words2;
        vector<pair<string, string>> pairs;
    };
    // TODO: prepare parameters here
    vector<struct param> params {
        {
            {"great", "acting", "skills"},
            {"fine", "drama", "talent"},
            {{"great", "good"}, {"fine", "good"}, {"acting","drama"}, {"skills","talent"}},
        }
        
    };
    // TODO: provide expected results here
    vector<bool> answers {
    };
    
    for (auto& dp : params) {
        cout << endl;
        clock_t tstart = clock();
        auto res = areSentencesSimilarTwo::Solution().areSentencesSimilarTwo(dp.words1, dp.words2, dp.pairs);
        cout << res << endl;
        cout << clock() - tstart << endl;
    }

    return 0;
}
//*/
