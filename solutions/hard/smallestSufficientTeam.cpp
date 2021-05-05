// smallestSufficientTeam.cpp
// leetcode
//
// Created by  Song Ding on 9/13/19.
// Copyright © 2019 Song Ding. All rights reserved.
//
#include "common.h"
using namespace std;

namespace smallestSufficientTeam {
/*
// TODO: copy problem statement here
 1125. Smallest Sufficient Team
 Hard
 
 154
 
 6
 
 Favorite
 
 Share
 In a project, you have a list of required skills req_skills, and a list of people.  The i-th person people[i] contains a list of skills that person has.
 
 Consider a sufficient team: a set of people such that for every required skill in req_skills, there is at least one person in the team who has that skill.  We can represent these teams by the index of each person: for example, team = [0, 1, 3] represents the people with skills people[0], people[1], and people[3].
 
 Return any sufficient team of the smallest possible size, represented by the index of each person.
 
 You may return the answer in any order.  It is guaranteed an answer exists.
 
 
 
 Example 1:
 
 Input: req_skills = ["java","nodejs","reactjs"], people = [["java"],["nodejs"],["nodejs","reactjs"]]
 Output: [0,2]
 Example 2:
 
 Input: req_skills = ["algorithms","math","java","reactjs","csharp","aws"], people = [["algorithms","math","java"],["algorithms","math","reactjs"],["java","csharp","aws"],["reactjs","csharp"],["csharp","math"],["aws","java"]]
 Output: [1,2]
 
 
 Constraints:
 
 1 <= req_skills.length <= 16
 1 <= people.length <= 60
 1 <= people[i].length, req_skills[i].length, people[i][j].length <= 16
 Elements of req_skills and people[i] are (respectively) distinct.
 req_skills[i][j], people[i][j][k] are lowercase English letters.
 Every skill in people[i] is a skill in req_skills.
 It is guaranteed a sufficient team exists.
 */

class Solution {
public:
    vector<int> smallestSufficientTeam(vector<string>& req_skills, vector<vector<string>>& people) {
        return smallestSufficientTeam_dp3(req_skills, people);
    }
    vector<int> smallestSufficientTeam_dp3(vector<string>& req_skills, vector<vector<string>>& people) {
        int n = req_skills.size();
        unordered_map<string, int> sid;
        for (int i = 0; i < n; ++i) {
            sid[req_skills[i]] = 1<<i;
        }
        int pn = people.size();
        vector<int> psk(pn, 0);
        for (int i = 0; i < pn; ++i) {
            for (auto& s : people[i]) {
                psk[i] |= sid[s];
            }
        }
        vector<vector<long>> dp(1<<n, vector<long>(2,INT_MAX));
        dp[0] = {0,0};
        for (int i = 0; i < 1<<n; ++i) {
            if (dp[i][0] == INT_MAX) {
                continue;
            }
            for (int j = 0; j < pn; ++j) {
                int nsk = i | psk[j];
                if (dp[nsk][0] > dp[i][0]+1) {
                    dp[nsk][0] = dp[i][0]+1;
                    dp[nsk][1] = dp[i][1] | (1l<<j);
                }
            }
        }
        vector<int> res;
        long t = dp.back()[1];
        int id = 0;
        while (t) {
            if (t&1) {
                res.push_back(id);
            }
            t >>= 1;
            ++id;
        }
        return res;
    }
    vector<int> smallestSufficientTeam_dp2(vector<string>& req_skills, vector<vector<string>>& people) {
        int nr = req_skills.size();
        unordered_map<string,int> skillToInt;
        for (int i = 0; i < nr; ++i) {
            skillToInt[req_skills[i]] = (1<<i);
        }
        int np = people.size();
        vector<int> skills(np);
        for (int i = 0; i < np; ++i) {
            int sk = 0;
            for (auto& s : people[i]) {
                sk |= skillToInt[s];
            }
            skills[i] = sk;
        }
        
        unordered_map<int, int> prev;
        unordered_map<int, int> chosen;
        unordered_map<int, int> dp;
        dp.reserve(1<<nr);
        dp[0] = 0;
        for (int i = 0; i < np; ++i) {
            for (auto it = dp.begin(); it != dp.end(); ++it) {
                int t = it->first | skills[i];
                auto sit = dp.find(t);
                if (sit == dp.end() || sit->second > it->second + 1) {
                    dp[t] = it->second + 1;
                    prev[t] = it->first;
                    chosen[t] = i;
                }
            }
        }
        vector<int> res;
        int target = (1<<nr) - 1;
        while (target) {
            res.push_back(chosen[target]);
            target = prev[target];
        }
        return res;
    }
    /**
     * https://leetcode.com/problems/smallest-sufficient-team/discuss/342120/C%2B%2B-DP-32ms-DP-solution.-Easy-to-implement
     */
    vector<int> smallestSufficientTeam_dp1(vector<string>& req_skills, vector<vector<string>>& people) {
        int nr = req_skills.size();
        unordered_map<string,int> skillToInt;
        for (int i = 0; i < nr; ++i) {
            skillToInt[req_skills[i]] = (1<<i);
        }
        int np = people.size();
        vector<int> skills(np);
        for (int i = 0; i < np; ++i) {
            int sk = 0;
            for (auto& s : people[i]) {
                sk |= skillToInt[s];
            }
            skills[i] = sk;
        }
        
        unordered_map<int, int> prev;
        unordered_map<int, int> chosen;
        vector<int> dp(1<<nr, INT_MAX);
        dp[0] = 0;
        /**
        for (int i = 0; i < (1<<nr); ++i) {
            if (dp[i] == INT_MAX) {
                continue;
            }
            for (int j = 0; j < np; ++j) {
                int t = i | skills[j];
                if (dp[t] > dp[i] + 1) {
                    dp[t] = dp[i] + 1;
                    prev[t] = i;
                    chosen[t] = j;
                }
            }
        }*/
        
        for (int i = 0; i < np; ++i) {
            for (int j = 0; j < (1<<nr); ++j) {
                if (dp[j] == INT_MAX) {
                    continue;
                }
                int t = j | skills[i];
                if (dp[t] > dp[j] + 1) {
                    dp[t] = dp[j] + 1;
                    prev[t] = j;
                    chosen[t] = i;
                }
            }
        }
        vector<int> res;
        int target = (1<<nr) - 1;
        while (target) {
            res.push_back(chosen[target]);
            target = prev[target];
        }
        return res;
    }
    /**
     * use bit to represent requirement skills, and each person has a skill int, whose bits
     * represents the required skills covered.
     * The problem is then: find a minimal set of integers that cover all bits.
     */
    vector<int> smallestSufficientTeam_dfs_slow(vector<string>& req_skills, vector<vector<string>>& people) {
        int nr = req_skills.size();
        unordered_map<string,int> skillToInt(nr);
        int target = 0;
        for (int i = 0; i < nr; ++i) {
            skillToInt[req_skills[i]] = (1<<i);
            target |= (1<<i);
        }
        int np = people.size();
        unordered_map<int, int> skillToPeople;
        unordered_set<int> skillSet;
        for (int i = 0; i < np; ++i) {
            int sk = 0;
            for (auto& s : people[i]) {
                sk |= skillToInt[s];
            }
            skillSet.insert(sk);
            skillToPeople.insert(make_pair(sk,i));
        }

        vector<int> skillRes(np);
        unordered_map<int, unordered_set<int>> memo;
        unordered_set<int> tres = dfs(target, skillSet, memo);
        
        // convert skills to people
        vector<int> res;
        for (auto & sk : tres) {
            res.push_back(skillToPeople[sk]);
        }
        return res;
    }
    unordered_set<int> dfs(int target, unordered_set<int>& skills, unordered_map<int,unordered_set<int>>& memo) {
        if (target == 0) {
            return {};
        }
        auto it = memo.find(target);
        if (it != memo.end()) {
            return it->second;
        }
        
        int minSk = INT_MAX;
        unordered_set<int> res;
        for (auto& sk : skills) {
            if (!(target & sk)) {
                continue;
            }
            
            int ntarget = target ^ (target & sk);
            unordered_set<int> tres = dfs(ntarget, skills, memo);
            tres.insert(sk);
            if (tres.size() < minSk) {
                minSk = tres.size();
                res.swap(tres);
            }
        }
        memo[target] = res;
        return res;
    }
    /**
     * let dp[i][j] = set of people lists that cover req_skills[i..j]
     * then:
     *  dp[i][j] = for each k in [i,j], find minimum set from dp[i][k] and dp[k+1][j].
     */
    vector<int> smallestSufficientTeam_dp_TLE(vector<string>& req_skills, vector<vector<string>>& people) {
        int nr = req_skills.size();
        int np = people.size();
        vector<unordered_set<string>> peopleSkills(np);
        for (int i = 0; i < np; ++i) {
            peopleSkills[i].insert(people[i].begin(), people[i].end());
        }
        vector<vector<vector<unordered_set<int>>>> cover(nr, vector<vector<unordered_set<int>>>(nr));
        vector<vector<int>> skillToPeople(nr);
        for (int i = 0; i < nr; ++i) {
            for (int j = 0; j < np; ++j) {
                if (peopleSkills[j].find(req_skills[i]) != peopleSkills[j].end()) {
                    skillToPeople[i].push_back(j);
                    cover[i][i].push_back({j});
                }
            }
        }
        for (int l = 2; l <= nr; ++l) {
            for (int i = 0; i <= nr-l; ++i) {
                int j = i+l-1;
                int pneeded = INT_MAX;
                for (int k = i; k < j; ++k) {
                    // find out cover[i][k]
                    for (auto& s1 : cover[i][k]) {
                        // find out cover[k+1][j]
                        for (auto& s2 : cover[k+1][j]) {
                            unordered_set<int> r(s1);
                            r.insert(s2.begin(), s2.end());
                            if (r.size() < pneeded) {
                                pneeded = r.size();
                                cover[i][j].clear();
                                cover[i][j].push_back(r);
                            } else if (r.size() == pneeded) {
                                cover[i][j].push_back(r);
                            }
                        }
                    }
                }
            }
        }
        vector<int> res;
        if (cover[0][nr-1].size()) {
            res.insert(res.end(), cover[0][nr-1][0].begin(), cover[0][nr-1][0].end());
        }
        return res;
    }
    
    vector<int> smallestSufficientTeam_dp_wrong(vector<string>& req_skills, vector<vector<string>>& people) {
        int nr = req_skills.size();
        int np = people.size();
        vector<unordered_set<string>> peopleSkills(np);
        for (int i = 0; i < np; ++i) {
            peopleSkills[i].insert(people[i].begin(), people[i].end());
        }
        vector<vector<vector<unordered_set<int>>>> cover(nr, vector<vector<unordered_set<int>>>(nr));
        vector<vector<int>> skillToPeople(nr);
        for (int i = 0; i < nr; ++i) {
            for (int j = 0; j < np; ++j) {
                if (peopleSkills[j].find(req_skills[i]) != peopleSkills[j].end()) {
                    skillToPeople[i].push_back(j);
                    cover[i][i].push_back({j});
                }
            }
        }
        for (int l = 2; l <= nr; ++l) {
            for (int i = 0; i <= nr-l; ++i) {
                int j = i+l-1;
                int pneeded = INT_MAX;
                for (auto sp : skillToPeople[j]) {
                    for (auto& s1 : cover[i][j-1]) {
                        unordered_set<int> r(s1);
                        r.insert(sp);
                        if (r.size() < pneeded) {
                            pneeded = r.size();
                            cover[i][j].clear();
                            cover[i][j].push_back(r);
                        } else if (r.size() == pneeded) {
                            cover[i][j].push_back(r);
                        }
                    }
                }
            }
        }
        vector<int> res;
        if (cover[0][nr-1].size()) {
            res.insert(res.end(), cover[0][nr-1][0].begin(), cover[0][nr-1][0].end());
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
        vector<string> req_skills;
        vector<vector<string>> people;
    };
    // TODO: prepare parameters here
    vector<struct d> p {
        //{{"java","nodejs","reactjs"},{{"java"},{"nodejs"},{"nodejs","reactjs"}}},
        //{{"a","b","c","d","e"},{{"a"},{"b"},{"c"},{"d"},{"e"},{"a","b","d"},{"c","e"}}},
        //{{"java","nodejs","reactjs"}, {{"java"},{"nodejs"},{"nodejs","reactjs"}}},
        //{{"algorithms","math","java","reactjs","csharp","aws"}, {{"algorithms","math","java"},{"algorithms","math","reactjs"},{"java","csharp","aws"},{"reactjs","csharp"},{"csharp","math"},{"aws","java"}}},
        //{{"gvp","jgpzzicdvgxlfix","kqcrfwerywbwi","jzukdzrfgvdbrunw","k"},{{},{},{},{},{"jgpzzicdvgxlfix"},{"jgpzzicdvgxlfix","k"},{"jgpzzicdvgxlfix","kqcrfwerywbwi"},{"gvp"},{"jzukdzrfgvdbrunw"},{"gvp","kqcrfwerywbwi"}}},
        {{"mwobudvo","goczubcwnfze","yspbsez","pf","ey","hkq"},{{},{"mwobudvo"},{"hkq"},{"pf"},{"pf"},{"mwobudvo","pf"},{},{"yspbsez"},{},{"hkq"},{},{},{"goczubcwnfze","pf","hkq"},{"goczubcwnfze"},{"hkq"},{"mwobudvo"},{},{"mwobudvo","pf"},{"pf","ey"},{"mwobudvo"},{"hkq"},{},{"pf"},{"mwobudvo","yspbsez"},{"mwobudvo","goczubcwnfze"},{"goczubcwnfze","pf"},{"goczubcwnfze"},{"goczubcwnfze"},{"mwobudvo"},{"mwobudvo","goczubcwnfze"},{},{"goczubcwnfze"},{},{"goczubcwnfze"},{"mwobudvo"},{},{"hkq"},{"yspbsez"},{"mwobudvo"},{"goczubcwnfze","ey"}}},
        {{"hxlk","wgqsztvrgjbkxw","ucrkmmkekmuks","gjpqressg","xbnmjd","odwwreaiwdsbm","kmystbjncopsf","fsl","wbdvwwdl"},{{"gjpqressg","xbnmjd"},{"fsl"},{"ucrkmmkekmuks","odwwreaiwdsbm"},{"hxlk"},{},{"hxlk","wbdvwwdl"},{"ucrkmmkekmuks","fsl","wbdvwwdl"},{"kmystbjncopsf"},{"ucrkmmkekmuks","fsl"},{"gjpqressg"},{},{"xbnmjd","odwwreaiwdsbm","fsl"},{"fsl"},{"ucrkmmkekmuks","gjpqressg","fsl"},{"gjpqressg","fsl"},{"ucrkmmkekmuks","gjpqressg"},{"wbdvwwdl"},{},{"hxlk","ucrkmmkekmuks","gjpqressg","fsl"},{"fsl"},{"hxlk","fsl"},{"ucrkmmkekmuks"},{"hxlk"},{"gjpqressg"},{"ucrkmmkekmuks"},{},{"wgqsztvrgjbkxw","fsl","wbdvwwdl"},{"ucrkmmkekmuks"},{"gjpqressg"},{"xbnmjd"},{"hxlk","gjpqressg","fsl"},{"kmystbjncopsf","fsl"},{"gjpqressg","fsl"},{},{"fsl","wbdvwwdl"},{"hxlk"},{"fsl","wbdvwwdl"},{"ucrkmmkekmuks","gjpqressg"},{"fsl"},{"ucrkmmkekmuks","gjpqressg"},{"kmystbjncopsf"},{"hxlk"},{"hxlk"},{"hxlk","gjpqressg"},{"hxlk","fsl","wbdvwwdl"},{"gjpqressg","wbdvwwdl"},{},{},{},{},{},{"wgqsztvrgjbkxw","gjpqressg","wbdvwwdl"},{"hxlk","xbnmjd"},{"gjpqressg","fsl"},{"kmystbjncopsf"},{"gjpqressg","fsl"},{"gjpqressg"},{},{},{"xbnmjd"}}},
    };

    vector< vector<int> > answers {
        {0,2},
        {5,6},
        {0,2},
        {1,2},
        {5,8,9},
        {12,23},
        {7,11,18,26},
    };

    // TODO: update paramters.
    for (auto& dp : p) {
        cout << endl;
        clock_t tstart = clock();
        auto res = smallestSufficientTeam::Solution().smallestSufficientTeam(dp.req_skills, dp.people);
        cout << clock() - tstart << endl;
        cout << res << endl;
    }
    return 0;
}
//*/
