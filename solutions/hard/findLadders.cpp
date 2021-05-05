// findLadders.cpp
// leetcode
//
// Created by  Song Ding on 6/5/19.
// Copyright © 2019 Song Ding. All rights reserved.
//
#include "common.h"
using namespace std;

namespace findLadders {
/*
// TODO: copy problem statement here
 126. Word Ladder II
 Hard
 
 937
 
 181
 
 Favorite
 
 Share
 Given two words (beginWord and endWord), and a dictionary's word list, find all shortest transformation sequence(s) from beginWord to endWord, such that:
 
 Only one letter can be changed at a time
 Each transformed word must exist in the word list. Note that beginWord is not a transformed word.
 Note:
 
 Return an empty list if there is no such transformation sequence.
 All words have the same length.
 All words contain only lowercase alphabetic characters.
 You may assume no duplicates in the word list.
 You may assume beginWord and endWord are non-empty and are not the same.
 Example 1:
 
 Input:
 beginWord = "hit",
 endWord = "cog",
 wordList = ["hot","dot","dog","lot","log","cog"]
 
 Output:
 [
 ["hit","hot","dot","dog","cog"],
 ["hit","hot","lot","log","cog"]
 ]
 Example 2:
 
 Input:
 beginWord = "hit"
 endWord = "cog"
 wordList = ["hot","dot","dog","lot","log"]
 
 Output: []
 
 Explanation: The endWord "cog" is not in wordList, therefore no possible transformation.
 */

class Solution {
public:
    /**
     * Looks like DFS might be better.
     */
    vector<vector<string>> findLadders(string beginWord, string endWord, vector<string>& wordList) {
        int n = wordList.size();
        int ti = n;
        // prepare connections
        unordered_map<string, unordered_set<int>> groups;
        for (int i = 0; i < n; ++i) {
            const string& w = wordList[i];
            if (endWord == w) {
                ti = i;
            }
            int nw = w.size();
            for (int j = 0; j < nw; ++j) {
                string t(w);
                t[j] = '*';
                groups[t].insert(i);
            }
        }
        if (ti == n) {
            return {};
        }
        
        vector<vector<int>> conns(n);
        for (const auto& p : groups) {
            for (auto i : p.second) {
                for (auto j : p.second) {
                    if (i != j) {
                        conns[i].push_back(j);
                    }
                }
            }
        }
        
        vector<unordered_set<int>> prev(n);
        vector<int> visited(n, 0);
        vector<int> cur;
        bool direct = false;
        // check whether beginWord can go to any word in the list
        int sn = beginWord.size();
        for (int i = 0; i < sn; ++i) {
            string t(beginWord);
            t[i] = '*';
            auto it = groups.find(t);
            if (it != groups.end()) {
                for (auto j : it->second) {
                    if (visited[j] == 0) {
                        cur.push_back(j);
                        visited[j] = 2;
                        if (j == ti) {
                            direct = true;
                            break;
                        }
                    }
                }
            }
        }
        if (direct) {
            return {{beginWord, endWord}};
        }
        
        while (cur.size()) {
            vector<int> next;
            for (const auto& wi : cur) {
                for (auto ci : conns[wi]) {
                    if (visited[ci] == 0) {
                        next.push_back(ci);
                        prev[ci].insert(wi);
                        visited[ci] = 1;
                    } else if (visited[ci] == 1) {
                        prev[ci].insert(wi);
                    }
                }
            }
            
            // change visited
            for (auto & i  : visited) {
                if (i == 1) {
                    i = 2;
                }
            }
            
            // check whether ti has been reached.
            if (visited[ti]) {
                break;
            }
            cur.swap(next);
        }
        
        vector<vector<int>> cres;
        for (auto i : prev[ti]) {
            cres.push_back({i});
        }
        // start from ti and move backwards in prev.
        bool found = true;
        while (cres.size()) {
            vector<vector<int>> next;
            found = false;
            for (auto& v : cres) {
                int last = v.back();
                for (auto c : prev[last]) {
                    found = true;
                    vector<int> t(v);
                    t.push_back(c);
                    next.push_back(t);
                }
            }
            if (next.empty()) {
                break;
            }
            cres.swap(next);
        }
        
        vector<vector<string>> res;
        for (const auto& v : cres) {
            res.push_back({beginWord});
            for (auto it = v.rbegin(); it != v.rend(); ++it) {
                res.back().push_back(wordList[*it]);
            }
            res.back().push_back(endWord);
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
        string beginWord;
        string endWord;
        vector<string> wordList;
    };
    // TODO: prepare parameters here
    vector<struct d> p {
        //{"hit","cog", {"hot","dot","dog","lot","log","cog"}},
        //{"hit","cog",{"hot","dot","dog","lot","log"}},
        {"a", "c", {"a","b","c"}}
    };

    vector< vector<vector<string>> > answers {
        {
            {"hit","hot","dot","dog","cog"},
            {"hit","hot","lot","log","cog"}
        },
        {{"a","c"}}
    };

    // TODO: update paramters.
    for (auto& dp : p) {
        cout << endl;
        clock_t tstart = clock();
        auto res = findLadders::Solution().findLadders(dp.beginWord, dp.endWord, dp.wordList);
        cout << clock() - tstart << endl;
        cout << res << endl;
    }
    return 0;
}
//*/
