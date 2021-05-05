// shortestCompletingWord.cpp
// leetcode
//
// Created by  Song Ding on 6/20/18.
// Copyright © 2018 Song Ding. All rights reserved.
//
#include "common.h"
using namespace std;

namespace shortestCompletingWord {

class Solution {
public:
    string shortestCompletingWord(string licensePlate, vector<string>& words) {
        vector<int> counts(26, 0);
        for (char c : licensePlate) {
            if (c >= 'A' && c <= 'Z') {
                ++counts[c - 'A'];
            } else if (c >= 'a' && c <= 'z') {
                ++counts[c - 'a'];
            }
        }
        int min = INT_MAX;
        string res;
        for (const auto& w : words) {
            if (w.length() >= min) {
                continue;
            }
            vector<int> wcounts(counts);
            bool found = true;
            for (char c : w) {
                if (c >= 'A' && c <= 'Z') {
                    --wcounts[c - 'A'];
                } else if (c >= 'a' && c <= 'z') {
                    --wcounts[c - 'a'];
                }
            }
            for (auto i : wcounts) {
                if (i > 0) {
                    found = false;
                    break;
                }
            }
            if (found) {
                res = w;
                min = w.length();
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
    string licensePlate = "1s3 PSt";
    vector<string> words {
        "step", "steps", "stripe", "stepple"
    };

    // TODO: add return type and paramters.
    clock_t start = clock();
    auto res = shortestCompletingWord::Solution().shortestCompletingWord(licensePlate, words);
    cout << clock() - start << endl;
    cout << res << endl;
    return 0;
}
//*/
