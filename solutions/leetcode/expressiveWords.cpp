// expressiveWords.cpp
// leetcode
//
// Created by  Song Ding on 10/4/18.
// Copyright © 2018 Song Ding. All rights reserved.
//
#include "common.h"
using namespace std;

namespace expressiveWords {

class Solution {
public:
    /**
     */
    int expressiveWords(string S, vector<string>& words) {
        int ns = S.size();
        if (ns == 0 || words.size() == 0) {
            return 0;
        }
        
        int res = 0;
        vector<pair<int,int>> stat;
        char last = S[0];
        int cnt = 1;
        for (int i = 1; i < ns; ++i) {
            if (S[i] != last) {
                stat.push_back(make_pair(last, cnt));
                cnt = 0;
            }
            ++cnt;
            last = S[i];
        }
        stat.push_back(make_pair(last, cnt));
        
        for (const auto& w : words) {
            int nw = w.size();
            int k = 0;
            char last = w[0];
            int cnt = 1;
            for (int i = 1; i < nw; ++i) {
                if (w[i] != last) {
                    if (last != stat[k].first || cnt > stat[k].second) {
                        break;
                    }
                    
                    if (stat[k].second != cnt && stat[k].second <= 2) {
                        break;
                    }
                    
                    ++k;
                    cnt = 0;
                }
                ++cnt;
                last = w[i];
            }
            if (k == stat.size() - 1 && last == stat[k].first
                && (cnt == stat[k].second || (stat[k].second > cnt && stat[k].second >= 3))) {
                ++res;
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
    string S = "dddiiiinnssssssoooo";
    vector<string> words {"dinnssoo","ddinso","ddiinnso","ddiinnssoo","ddiinso","dinsoo","ddiinsso","dinssoo","dinso"};
    // TODO: add return type and paramters.
    clock_t start = clock();
    auto res = expressiveWords::Solution().expressiveWords(S, words);
    cout << clock() - start << endl;
    cout << res << endl;
    return 0;
}
//*/
