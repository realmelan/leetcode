// loudAndRich.cpp
// leetcode
//
// Created by  Song Ding on 5/19/19.
// Copyright © 2019 Song Ding. All rights reserved.
//
#include "common.h"
using namespace std;

namespace loudAndRich {
/*
// TODO: copy problem statement here
 851. Loud and Rich
 Medium
 
 158
 
 184
 
 Favorite
 
 Share
 In a group of N people (labelled 0, 1, 2, ..., N-1), each person has different amounts of money, and different levels of quietness.
 
 For convenience, we'll call the person with label x, simply "person x".
 
 We'll say that richer[i] = [x, y] if person x definitely has more money than person y.  Note that richer may only be a subset of valid observations.
 
 Also, we'll say quiet[x] = q if person x has quietness q.
 
 Now, return answer, where answer[x] = y if y is the least quiet person (that is, the person y with the smallest value of quiet[y]), among all people who definitely have equal to or more money than person x.
 
 
 
 Example 1:
 
 Input: richer = [[1,0],[2,1],[3,1],[3,7],[4,3],[5,3],[6,3]], quiet = [3,2,5,4,6,1,7,0]
 Output: [5,5,2,5,4,5,6,7]
 Explanation:
 answer[0] = 5.
 Person 5 has more money than 3, which has more money than 1, which has more money than 0.
 The only person who is quieter (has lower quiet[x]) is person 7, but
 it isn't clear if they have more money than person 0.
 
 answer[7] = 7.
 Among all people that definitely have equal to or more money than person 7
 (which could be persons 3, 4, 5, 6, or 7), the person who is the quietest (has lower quiet[x])
 is person 7.
 
 The other answers can be filled out with similar reasoning.
 Note:
 
 1 <= quiet.length = N <= 500
 0 <= quiet[i] < N, all quiet[i] are different.
 0 <= richer.length <= N * (N-1) / 2
 0 <= richer[i][j] < N
 richer[i][0] != richer[i][1]
 richer[i]'s are all different.
 The observations in richer are all logically consistent.
 */

class Solution {
public:
    /**
     * Let rq[i] = smallest quietness value of persons who are richer than i.
     * During iterating richer, for a pair [x, y], update rq[y] if x's quietness value
     * is smallest than rq[y].
     *
     * Note: there is transitive relation...
     * topologic sort based on richer relation, and starting from the richest
     * and stop at any person that's less quiet.
     */
    vector<int> loudAndRich(vector<vector<int>>& richer, vector<int>& quiet) {
        int n = quiet.size();
        vector<int> rq;
        unordered_map<int, int> q2p;
        for (int i = 0; i < n; ++i) {
            rq.push_back(quiet[i]);
            q2p.insert(make_pair(quiet[i], i));
        }
        
        unordered_multimap<int, int> richermap;
        unordered_multimap<int, int> poorermap;
        for (const auto& p : richer) {
            richermap.insert(make_pair(p[1], p[0]));
            poorermap.insert(make_pair(p[0], p[1]));
        }
        
        vector<int> visited(n, 0);
        bool foundRichest = true;
        while (foundRichest) {
            foundRichest = false;
            for (int i = 0; i < n; ++i) {
                if (visited[i]) {
                    continue;
                }
                
                bool richest = true;
                auto rpit = richermap.equal_range(i);
                for (auto it = rpit.first; it != rpit.second; ++it) {
                    if (visited[it->second] == 0) {
                        richest = false;
                        break;
                    }
                }
                if (richest) {
                    foundRichest = true;
                    visited[i] = 1;
                    auto ppit = poorermap.equal_range(i);
                    for (auto it = ppit.first; it != ppit.second; ++it) {
                        rq[it->second] = min(rq[it->second], rq[i]);
                    }
                }
            }
        }
        vector<int> res;
        for (int i = 0; i < n; ++i) {
            res.push_back(q2p[rq[i]]);
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
        vector<vector<int>> richer;
        vector<int> quiet;
    };
    // TODO: prepare parameters here
    vector<struct d> p {
        {{{1,0},{2,1},{3,1},{3,7},{4,3},{5,3},{6,3}},{3,2,5,4,6,1,7,0}}
    };

    vector< vector<int> > answers {
        {5,5,2,5,4,5,6,7}
    };

    // TODO: update paramters.
    for (auto& dp : p) {
        cout << endl;
        clock_t tstart = clock();
        auto res = loudAndRich::Solution().loudAndRich(dp.richer, dp.quiet);
        cout << clock() - tstart << endl;
        cout << res << endl;
    }
    return 0;
}
//*/
