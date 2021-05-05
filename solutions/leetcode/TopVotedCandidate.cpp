// TopVotedCandidate.cpp
// leetcode
//
// Created by  Song Ding on 5/16/19.
// Copyright © 2019 Song Ding. All rights reserved.
//
#include "common.h"
using namespace std;

/*
 911. Online Election
 Medium
 
 167
 
 111
 
 Favorite
 
 Share
 In an election, the i-th vote was cast for persons[i] at time times[i].
 
 Now, we would like to implement the following query function: TopVotedCandidate.q(int t) will return the number of the person that was leading the election at time t.
 
 Votes cast at time t will count towards our query.  In the case of a tie, the most recent vote (among tied candidates) wins.
 
 
 
 Example 1:
 
 Input: ["TopVotedCandidate","q","q","q","q","q","q"], [[[0,1,1,0,0,1,0],[0,5,10,15,20,25,30]],[3],[12],[25],[15],[24],[8]]
 Output: [null,0,1,1,0,0,1]
 Explanation:
 At time 3, the votes are [0], and 0 is leading.
 At time 12, the votes are [0,1,1], and 1 is leading.
 At time 25, the votes are [0,1,1,0,0,1], and 1 is leading (as ties go to the most recent vote.)
 This continues for 3 more queries at time 15, 24, and 8.
 
 
 Note:
 
 1 <= persons.length = times.length <= 5000
 0 <= persons[i] <= persons.length
 times is a strictly increasing array with all elements in [0, 10^9].
 TopVotedCandidate.q is called at most 10000 times per test case.
 TopVotedCandidate.q(int t) is always called with t >= times[0].
 */
namespace TopVotedCandidate {

    class TopVotedCandidate {
    public:
        /**
         * let top(t, p) stores the winner p for time t.
         */
        TopVotedCandidate(vector<int>& persons, vector<int>& times) {
            unordered_map<int, int> counts;
            int n = persons.size();
            int topVote = 0;
            for (int i = 0; i < n; ++i) {
                int p = persons[i];
                ++counts[p];
                if (counts[p] >= topVote) {
                    _top.insert(make_pair(-times[i], p));
                    topVote = counts[p];
                }
            }
        }
        
        int q(int t) {
            auto it = _top.lower_bound(-t);
            return it->second;
        }
    private:
        map<int, int> _top;
    };

}

/*/
int main() {
    // TODO: prepare parameters here
    struct d {
        vector<int> persons;
        vector<int> times;
        vector<int> q;
    };
    vector<struct d> p {
        {{0,1,1,0,0,1,0},{0,5,10,15,20,25,30},{3,12,25,15,24,8}}
    };

    vector< int  > answers {
    };
    int i = 0;

    // TODO: add return type and paramters.
    clock_t tstart = clock();
    TopVotedCandidate::TopVotedCandidate t(p[i].persons, p[i].times);
    for (auto i : p[i].q) {
        cout << t.q(i) << endl;
    }
    cout << clock() - tstart << endl;
    return 0;
}
//*/
