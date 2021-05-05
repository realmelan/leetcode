// generateAbbreviations.cpp
// leetcode
//
// Created by  Song Ding on 11/6/19.
// Copyright © 2019 Song Ding. All rights reserved.
//
#include "common.h"
using namespace std;

namespace generateAbbreviations {
/*
// TODO: copy problem statement here
 320. Generalized Abbreviation

 Write a function to generate the generalized abbreviations of a word.

 Example:

 Given word = "word", return the following list (order does not matter):

 ["word", "1ord", "w1rd", "wo1d", "wor1", "2rd", "w2d", "wo2", "1o1d", "1or1", "w1r1", "1o2", "2r1", "3d", "w3", "4"]
 */

class Solution {
public:
    /**
     * dfs, point is how to make dfs simple
     */
    vector<string> generateAbbreviations(string word) {
        vector<string> res;
        //dfs("", 0, 0, word, res);
        std::string cur;
        dfs2(word, cur, 0, res);
        return res;
    }

private:
    /**
     for each position i, either turn current character into a digit ( or add it to previous digit) or output it as a character
     */
    void dfs(string cur, int i, int num, const string& word, vector<string>& res) {
        if (i == word.size()) {
            ostringstream oss;
            oss << cur;
            if (num) {
                oss << num;
            }
            res.push_back(oss.str());
        } else {
            // contribute word[i] to digit
            dfs(cur, i+1, num+1, word, res);
            
            // contribute word[i] as a character
            ostringstream oss;
            oss << cur;
            if (num) {
                oss << num;
            }
            oss << word[i];
            dfs(oss.str(), i+1, 0, word, res);
        }
    }
    
    void dfs2(const string& word, string& cur, int start, vector<string>& res) {
        if (start == word.size()) {
            res.push_back(cur);
            return;
        }
        cur.push_back(word[start]);
        dfs2(word, cur, start+1, res);
        cur.pop_back();
        
        if (cur.empty() || (cur.back() >= 'a' && cur.back() <= 'z')) {
            // replace current i characters as an integer and then followed by a character
            int curSize = cur.size();
            for (int i = 1; start+i <= word.size(); ++i) {
                ostringstream oss;
                oss << i;
                cur.append(oss.str());
                dfs2(word, cur, start+i, res);
                cur.resize(curSize);
            }
        }
    }
};

}

/*/
int main() {
    // TODO: define parameter type here
    struct d {
        string word;
    };
    // TODO: prepare parameters here
    vector<struct d> p {
        {"word"},
    };

    vector< vector<string> > answers {
        {"word", "1ord", "w1rd", "wo1d", "wor1", "2rd", "w2d", "wo2", "1o1d", "1or1", "w1r1", "1o2", "2r1", "3d", "w3", "4"},
    };

    // TODO: update paramters.
    for (auto& dp : p) {
        cout << endl;
        clock_t tstart = clock();
        auto res = generateAbbreviations::Solution().generateAbbreviations(dp.word);
        cout << clock() - tstart << endl;
        cout << res << endl;
    }
    return 0;
}
//*/
