// findContestMatch.cpp
// leetcode
//
// Created by  Song Ding on 10/22/19.
// Copyright © 2019 Song Ding. All rights reserved.
//
#include "common.h"
using namespace std;

namespace findContestMatch {
/*
// TODO: copy problem statement here
 544. Output Contest Matches

 During the NBA playoffs, we always arrange the rather strong team to play with the rather weak team, like make the rank 1 team play with the rank nth team, which is a good strategy to make the contest more interesting. Now, you\'re given n teams, you need to output their final contest matches in the form of a string.

 The n teams are given in the form of positive integers from 1 to n, which represents their initial rank. (Rank 1 is the strongest team and Rank n is the weakest team.) We\'ll use parentheses(\'(\', \')\') and commas(\',\') to represent the contest team pairing - parentheses(\'(\' , \')\') for pairing and commas(\',\') for partition. During the pairing process in each round, you always need to follow the strategy of making the rather strong one pair with the rather weak one.

 Example 1:

 Input: 2
 Output: (1,2)
 Explanation:
 Initially, we have the team 1 and the team 2, placed like: 1,2.
 Then we pair the team (1,2) together with \'(\', \')\' and \',\', which is the final answer.
 Example 2:

 Input: 4
 Output: ((1,4),(2,3))
 Explanation:
 In the first round, we pair the team 1 and 4, the team 2 and 3 together, as we need to make the strong team and weak team together.
 And we got (1,4),(2,3).
 In the second round, the winners of (1,4) and (2,3) need to play again to generate the final winner, so you need to add the paratheses outside them.
 And we got the final answer ((1,4),(2,3)).
 Example 3:

 Input: 8
 Output: (((1,8),(4,5)),((2,7),(3,6)))
 Explanation:
 First round: (1,8),(2,7),(3,6),(4,5)
 Second round: ((1,8),(4,5)),((2,7),(3,6))
 Third round: (((1,8),(4,5)),((2,7),(3,6)))
 Since the third round will generate the final winner, you need to output the answer (((1,8),(4,5)),((2,7),(3,6))).
 Note:

 The n is in range [2, 2^12].
 We ensure that the input n can be converted into the form 2^k, where k is a positive integer.
 */

class Solution {
public:
    /**
     * //TODO: explain algorithm here
     */
    string findContestMatch(int n) {
        vector<int> cur{1,2};
        for (int b = 2; b < n; b <<= 1) {
            vector<int> t(cur);
            for (int i = 0; i < cur.size(); i+=2) {
                swap(t[i], t[i+1]);
            }
            vector<int> next;
            for (int i = 0; i < cur.size(); ++i) {
                next.push_back(cur[i]);
                next.push_back(t[i]+b);
            }
            cur.swap(next);
        }
        return recur(cur, 0, n-1);
    }
    /**
     * iteratives pair players:
     * for a list of "player groups", pair the 1st with the last, etc.
     */
    string findContestMatch2(int n) {
        vector<string> players;
        for (int i = 1; i <= n; ++i) {
            ostringstream oss;
            oss << i;
            players.push_back(oss.str());
        }
        // iteratively group "players", which might be a group
        while (players.size() > 1) {
            vector<string> next;
            int np = players.size();
            for (int i = 0, j = players.size() - 1; i < j; ++i, --j) {
                next.push_back("(" + players[i] + "," + players[j] + ")");
            }
            players.swap(next);
        }
        return players[0];
    }

private:
    string recur(vector<int>& cur, int l, int r) {
        ostringstream oss;
        if (l == r) {
            oss << cur[l];
        } else {
            // divide it into two halves;
            int h = (r-l+1)/2;
            string lres = recur(cur, l, l+h-1);
            string rres = recur(cur, l+h, r);
            oss << "(" << lres << "," << rres << ")";
        }
        return oss.str();
    }
};

}

/*/
int main() {
    // TODO: define parameter type here
    struct d {
        int n;
    };
    // TODO: prepare parameters here
    vector<struct d> p {
        {2},
        {4},
        {8},
        {32},
    };

    vector< string > answers {
        "(1,2)",
        "((1,4),(2,3))",
        "(((1,8),(4,5)),((2,7),(3,6)))",
        "(((((1,32),(16,17)),((8,25),(9,24))),(((4,29),(13,20)),((5,28),(12,21)))),((((2,31),(15,18)),((7,26),(10,23))),(((3,30),(14,19)),((6,27),(11,22)))))"
    };

    // TODO: update paramters.
    for (auto& dp : p) {
        cout << endl;
        clock_t tstart = clock();
        auto res = findContestMatch::Solution().findContestMatch(dp.n);
        cout << clock() - tstart << endl;
        cout << res << endl;
    }
    return 0;
}
//*/
