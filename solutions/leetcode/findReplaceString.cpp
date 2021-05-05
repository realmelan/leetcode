// findReplaceString.cpp
// leetcode
//
// Created by  Song Ding on 5/21/18.
// Copyright © 2018 Song Ding. All rights reserved.
//
#include "common.h"
using namespace std;

namespace findReplaceString {

class Solution {
public:
    string findReplaceString(string S, vector<int>& indexes, vector<string>& sources, vector<string>& targets) {
        string res;
        map<int, pair<string, string>> ops;
        int cn = indexes.size();
        for (int i = 0; i < cn; ++i) {
            ops[indexes[i]] = make_pair(sources[i], targets[i]);
        }
        int si = 0;
        int n = S.size();
        for (const auto& op : ops) {
            int opi = op.first;
            const string& src = op.second.first;
            const string& target = op.second.second;
            
            while (si < n && si < opi) {
                res.push_back(S.at(si));
                ++si;
            }
            if (si >= n) {
                break;
            }
            
            // check whether src appear at position si
            int srcLen = src.size();
            if (si + srcLen > n) {
                break;
            }
            if (S.substr(si, srcLen) == src) {
                res.append(target);
                si += srcLen;
            }
        }
        if (si < n) {
            res.append(S.substr(si));
        }
        return res;
    }
private:
};

}

/*/
int main() {
    // TODO: prepare parameters here
    string S = "abcd";
    vector<int> indexes{0,2};
    vector<string> sources{"ab","ec"};
    vector<string> targets{"eee","ffff"};
    // TODO: add return type and paramters.
    clock_t start = clock();
    auto res = findReplaceString::Solution().findReplaceString(S, indexes, sources, targets);
    cout << clock() - start << endl;
    cout << res << endl;
    return 0;
}
//*/
