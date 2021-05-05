// removeDuplicateLetters.cpp
// leetcode
//
// Created by  Song Ding on 3/15/18.
// Copyright © 2018 Song Ding. All rights reserved.
//
#include "common.h"
using namespace std;

namespace removeDuplicateLetters {

class Solution {
public:
    /**
     if there are unique letters in str, first fixed these unique
     letters;
     The unique letters divide str into multiple substrings. Start
     from the first substring, starting from the last
     
     Do the same steps above again, till all letters are unique.
     *
     */
    string removeDuplicateLetters(string str) {
        int n = str.size();
        if (n <= 0) {
            return "";
        }
        string s;
        char last = str[0];
        s.push_back(last);
        for (auto c : str) {
            if (c != last) {
                s.push_back(c);
            }
            last = c;
        }
        n = s.size();
        vector<set<int>> count(26);
        for (int i = 0; i < n; ++i) {
            count[s[i] - 'a'].insert(i);
        }
        
        // start from the smallest letter.
        vector<int> pending;
        string res;
        for (int i = 0; i < n; ++i) {
            if (count[s[i] - 'a'].empty()) {
                continue;
            }
            auto dupit = find_if(pending.begin(), pending.end(), [s, i](int a){
                return s[a] == s[i];
            });
            
            if (dupit != pending.end())  {
                count[s[i] - 'a'].erase(i);
                if (count[s[i] - 'a'].size() == 1) {
                    ++dupit;
                    for (auto it = pending.begin(); it != dupit; ++it) {
                        res.push_back(s[*it]);
                        count[s[*it] - 'a'].clear();
                    }
                    pending.erase(pending.begin(), dupit);
                }
            } else {
                while (pending.size()) {
                    int idx = pending.back();
                    if (s[idx] < s[i]) {
                        break;
                    }
                    count[s[idx] - 'a'].erase(idx);
                    pending.pop_back();
                }
                int c = count[s[i] - 'a'].size();
                if (c == 1) {
                    for (auto j : pending) {
                        res.push_back(s[j]);
                        count[j].clear();
                    }
                    pending.clear();
                    res.push_back(s[i]);
                } else {
                    pending.push_back(i);
                }
            }
        }
        return res;
    }
};

}

/*/
int main() {
    // TODO: prepare parameters here
    string str = "mitnlruhznjfyzmtmfnstsxwktxlboxutbic";
    // TODO: add return type and paramters.
    clock_t start = clock();
    string res = removeDuplicateLetters::Solution().removeDuplicateLetters(str);
    cout << clock() - start << endl;
    cout << res << endl;
    return 0;
}
//*/
