// equationsPossible.cpp
// leetcode
//
// Created by  Song Ding on 4/30/19.
// Copyright © 2019 Song Ding. All rights reserved.
//
#include "common.h"
using namespace std;

namespace equationsPossible {

class Solution {
public:
    /**
     * first, remove any equation involving just one variable.
     * if a == b, then let a and b in the same set; otherwise in different set.
     *
     * find all equations that contain '=' and construct sets of letter using
     * union-find algorithm.
     *
     * Verify the groupings against the equations containing '!'
     */
    bool equationsPossible(vector<string>& equations) {
        vector<int> group(26, -1);
        vector<string> notEqual;
        for (auto& s : equations) {
            if (group[s[0]-'a'] == -1) {
                group[s[0]-'a'] = s[0]-'a';
            }
            if (group[s[3]-'a'] == -1) {
                group[s[3]-'a'] = s[3]-'a';
            }
            
            if (s[1] == '=') {
                if (s[0] != s[3]) {
                    int p1 = find(group, s[0] - 'a');
                    int p2 = find(group, s[3] - 'a');
                    if (p1 < p2) {
                        group[p2] = p1;
                        find(group, s[3]-'a');
                    } else {
                        group[p1] = p2;
                        find(group, s[0]-'a');
                    }
                    
                }
            } else if (s[0] == s[3]) {
                return false;
            } else {
                notEqual.push_back(s);
            }
        }
        for (int i = 0; i < 26; ++i) {
            if (group[i] != -1) {
                find(group, i);
            }
        }
        
        for (auto& s : notEqual) {
            int p1 = group[s[0] - 'a'];
            int p2 = group[s[3] - 'a'];
            if (p1 == p2) {
                return false;
            }
        }
        return true;
    }

private:
    int find(vector<int>& group, int id) {
        int p = group[id];
        if (p != id) {
            p = find(group, group[id]);
            group[id] = p;
        }
        return p;
    }
};

}

/*/
int main() {
    // TODO: prepare parameters here
    vector< vector<string> > params {
        {"a==b","b==c","a==c"},
        {"a==b","b!=c","c==a"},
        {"c==c","b==d","x!=z"},
        {"b!=f","c!=e","f==f","d==f","b==f","a==f"}
    };

    vector< bool  > answers {
        true,
        false,
        true,
        true
    };
    int i = 3;

    // TODO: add return type and paramters.
    clock_t tstart = clock();
    auto res = equationsPossible::Solution().equationsPossible(params[i]);
    cout << clock() - tstart << endl;
    cout << res << endl;
    return 0;
}
//*/
