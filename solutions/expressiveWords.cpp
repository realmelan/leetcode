//
//  expressiveWords.cpp
//  leetcode
//
//  Created by Song Ding on 12/17/20.
//  Copyright © 2020 Song Ding. All rights reserved.
//

#include "common.h"
using namespace std;

namespace expressiveWords {
/*
// TODO: copy problem statement here
 Sometimes people repeat letters to represent extra feeling, such as "hello" -> "heeellooo", "hi" -> "hiiii".  In these strings like "heeellooo", we have groups of adjacent letters that are all the same:  "h", "eee", "ll", "ooo".

 For some given string S, a query word is stretchy if it can be made to be equal to S by any number of applications of the following extension operation: choose a group consisting of characters c, and add some number of characters c to the group so that the size of the group is 3 or more.

 For example, starting with "hello", we could do an extension on the group "o" to get "hellooo", but we cannot get "helloo" since the group "oo" has size less than 3.  Also, we could do another extension like "ll" -> "lllll" to get "helllllooo".  If S = "helllllooo", then the query word "hello" would be stretchy because of these two extension operations: query = "hello" -> "hellooo" -> "helllllooo" = S.

 Given a list of query words, return the number of words that are stretchy.

  

 Example:
 Input:
 S = "heeellooo"
 words = ["hello", "hi", "helo"]
 Output: 1
 Explanation:
 We can extend "e" and "o" in the word "hello" to get "heeellooo".
 We can't extend "helo" to get "heeellooo" because the group "ll" is not size 3 or more.
  

 Constraints:

 0 <= len(S) <= 100.
 0 <= len(words) <= 100.
 0 <= len(words[i]) <= 100.
 S and all words in words consist only of lowercase letters
*/
class Solution {
public:
    // TODO: copy function signature here
    int expressiveWords(string S, vector<string>& words) {
        vector<pair<char,int>> cnt;
        int sn = S.size();
        for (int i = 1, j = 0; i <= sn; ++i) {
            if (i == sn || S[i] != S[j]) {
                cnt.push_back({S[j], i-j});
                j = i;
            }
        }
        int res = 0;
        for (auto& w : words) {
            int k = 0, wn = w.size();
            int i = 1, j = 0;
            for (; i <= wn && k < cnt.size(); ++i) {
                if (i == wn || w[i] != w[j]) {
                    if (w[j] != cnt[k].first || cnt[k].second < i-j || (cnt[k].second < 3 && cnt[k].second != i-j)) {
                        break;
                    }
                    j = i;
                    ++k;
                }
            }
            if (k == cnt.size() && j >= wn) {
                ++res;
            }
        }
        return res;
    }
    
private:
};
}

/*
int main() {
    // TODO: define parameter type here
    struct param {
        string S;
        vector<string> words;
    };
    // TODO: prepare parameters here
    vector<struct param> params {
        {"heeellooo", {"hello", "hi", "helo"}},
    };
    // TODO: provide expected results here
    vector<int> answers {
        1,
    };
    
    for (auto& dp : params) {
        cout << endl;
        clock_t tstart = clock();
        auto res = expressiveWords::Solution().expressiveWords(dp.S, dp.words);
        cout << res << endl;
        cout << clock() - tstart << endl;
    }

    return 0;
}
//*/
