// smallestSubsequence.cpp
// leetcode
//
// Created by  Song Ding on 6/12/19.
// Copyright © 2019 Song Ding. All rights reserved.
//
#include "common.h"
using namespace std;

namespace smallestSubsequence {
/*
// TODO: copy problem statement here
 1081. Smallest Subsequence of Distinct Characters
 Medium
 
 70
 
 5
 
 Favorite
 
 Share
 Return the lexicographically smallest subsequence of text that contains all the distinct characters of text exactly once.
 
 
 
 Example 1:
 
 Input: "cdadabcc"
 Output: "adbc"
 Example 2:
 
 Input: "abcd"
 Output: "abcd"
 Example 3:
 
 Input: "ecbacba"
 Output: "eacb"
 Example 4:
 
 Input: "leetcode"
 Output: "letcod"
 
 
 Note:
 
 1 <= text.length <= 1000
 text consists of lowercase English letters.
 */

class Solution {
public:
    /**
     * From the input string, we are trying to greedily build a monotonically increasing result string. If the next character is smaller than the back of the result string, we remove larger characters from the back providing there are more occurrences of that character later in the input string.
     */
    string smallestSubsequence(string text) {
        string res;
        int used[26] = {};
        int cnt[26] = {};
        for (auto c : text) {
            ++cnt[c-'a'];
        }
        
        for (auto c : text) {
            --cnt[c - 'a'];
            if (used[c-'a'] > 0) {
                continue;
            }
            while (res.size() && res.back() > c && cnt[res.back() - 'a'] > 0) {
                used[res.back() - 'a'] = 0;
                res.pop_back();
            }
            res.push_back(c);
            used[c - 'a'] = 1;
        }
        return res;
    }
    /**
     * greedy
     */
    string smallestSubsequence_tocheck(string text) {
        string res;
        while (!text.empty()) {
            int cnt[128] = {};
            for (auto c : text) cnt[c]++;
            char minC = 127;
            int minCIndex = 0;
            for (int i = 0; i < text.size(); i++) {
                if (text[i] < minC) {
                    minC = text[i];
                    minCIndex = i;
                }
                if (--cnt[text[i]] == 0) break;
            }
            res += minC;
            text = text.substr(minCIndex);
            text.erase(remove(text.begin(), text.end(), minC), text.end());
        }
        return res;
    }
    
    /**
     * DP:
     * let dp(i,k) = map of smallest length k subsequence containing different character set.
     * the key = bitwise or of character presence bit(1 or 'a', 2 or 'b', 4 or 'c', etc, 2^25 for 'z'),
     * value is the smallest subsequence containing the same character set.
     *
     * then dp(i,k) = dp(i-1,k) + possible subsequence ending at text[i].
     */
    string smallestSubsequence2(string text) {
        int n = text.size();
        unordered_set<char> uniq;
        for (auto c : text) {
            uniq.insert(c);
        }
        int un = uniq.size();
        
        vector<unordered_map<int, string>> cur(n);
        cur[0].insert(make_pair(id(text.substr(0,1)), text.substr(0,1)));
        for (int i = 1; i < n; ++i) {
            cur[i] = cur[i-1];
            string ns = text.substr(i, 1);
            cur[i][id(ns)] = ns;
        }
        
        for (int k = 2; k <= un; ++k) {
            vector<unordered_map<int, string>> next(n);
            for (const auto& p : cur[k-2]) {
                string ns = p.second + text[k-1];
                int nid = id(ns);
                if (p.first != nid) {
                    next[k-1][nid] = ns;
                }
            }
            for (int i = k; i < n; ++i) {
                next[i] = next[i-1];
                for (const auto& p : cur[i-1]) {
                    string ns = p.second + text[i];
                    int nid = id(ns);
                    if ((p.first != nid) && (next[i].find(nid) == next[i].end() || next[i][nid] > ns)) {
                        next[i][nid] = ns;
                    }
                }
            }
            cur.swap(next);
        }
        
        string res;
        for (int i = 0; i < un; ++i) {
            res.push_back('z');
        }
        for (const auto& p : cur[n-1]) {
            res = min(res, p.second);
        }
        return res;
        
    }
private:
    int id(const std::string& s) {
        int res = 0;
        for (auto c : s) {
            res |= (1 << (c - 'a'));
        }
        return res;
    }

private:
};

}

/*/
int main() {
    // TODO: define parameter type here
    struct d {
        string text;
    };
    // TODO: prepare parameters here
    vector<struct d> p {
        //{"cdadabcc"},
        //{"abcd"},
        //{"ecbacba"},
        //{"leetcode"},
        {"ddeeeccdce"},
        //{"ecdcceedd"},
        //{"cbaacabcaaccaacababa"},
        {"acfdfdgaadgfacfgffeddeddaadfdcbegaeecfafffdecgeebd"},
        {"cfffecddgcbddecegfcabfdagbddagafddbddefbeagbfgbgfddabbddddgcddcggagcceedfgcfbggdfaegabgbgafgabeebbfceadadcdfbggecfdegedfbbddadfacdgafcgfddgcdbeebaabdbefgaaccgadefdadeabddbaefffcedbgeecgaecgaceabcacdaeebbebefcfffadddcbgggfgdcfbgfefbafggfcggfededbacdbd"},
        {"pblspykdpqfhcfcirkrhbbfbnqagshfqrrkcjpsuaytjfwyhjpubttxkkpswuvoiicsnkxiyhsyqrqecsiabhvjfodpkdgcgdceobyfonnurqxvstxkgsagnosvfjgsnylyhbjcrkgaylgxxxmghfbpfqwpplntrrogtkapbpkkwkdxgrfmikdlcftuyywrsnfasxgiw"}
    };

    vector< string > answers {
        "adbc",
        "abcd",
        "eacb",
        "letcod",
        "cde",
        "cde",
        "abc",
        "abcfdeg",
        "abcdefg"
    };

    // TODO: update paramters.
    for (auto& dp : p) {
        cout << endl;
        clock_t tstart = clock();
        auto res = smallestSubsequence::Solution().smallestSubsequence(dp.text);
        cout << clock() - tstart << endl;
        cout << res << endl;
    }
    return 0;
}
//*/
