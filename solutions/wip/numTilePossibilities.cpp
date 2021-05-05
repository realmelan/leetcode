// numTilePossibilities.cpp
// leetcode
//
// Created by  Song Ding on 6/17/19.
// Copyright © 2019 Song Ding. All rights reserved.
//
#include "common.h"
using namespace std;

namespace numTilePossibilities {
/*
// TODO: copy problem statement here
 1079. Letter Tile Possibilities
 Medium
 
 87
 
 5
 
 Favorite
 
 Share
 You have a set of tiles, where each tile has one letter tiles[i] printed on it.  Return the number of possible non-empty sequences of letters you can make.
 
 
 
 Example 1:
 
 Input: "AAB"
 Output: 8
 Explanation: The possible sequences are "A", "B", "AA", "AB", "BA", "AAB", "ABA", "BAA".
 Example 2:
 
 Input: "AAABBC"
 Output: 188
 
 
 Note:
 
 1 <= tiles.length <= 7
 tiles consists of uppercase English letters.
 */

class Solution {
public:
    int numTilePossibilities(string tiles) {
        int count[26] = {};
        for (auto c : tiles) {
            ++count[c - 'A'];
        }
        
        unordered_set<string> res;
        string path;
        recur(path, count, res);
        return res.size() - 1;
    }

private:
    void recur(string& path, int count[], unordered_set<string>& res) {
        res.insert(path);
        for (int i = 0; i < 26; ++i) {
            if (count[i] > 0) {
                --count[i];
                path.push_back('A' + i);
                recur(path, count, res);
                path.pop_back();
                ++count[i];
            }
        }
    }
};

}

/*/
int main() {
    // TODO: define parameter type here
    struct d {
        string tiles;
    };
    // TODO: prepare parameters here
    vector<struct d> p {
        {"AAB"},
        {"AAABBC"},
        {"AAABBCD"},
        {"ABCDEFG"}
    };

    vector< int > answers {
        8,
        188
    };

    // TODO: update paramters.
    for (auto& dp : p) {
        cout << endl;
        clock_t tstart = clock();
        auto res = numTilePossibilities::Solution().numTilePossibilities(dp.tiles);
        cout << clock() - tstart << endl;
        cout << res << endl;
    }
    return 0;
}
//*/
