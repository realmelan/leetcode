// openLock.cpp
// leetcode
//
// Created by  Song Ding on 9/26/19.
// Copyright © 2019 Song Ding. All rights reserved.
//
#include "common.h"
using namespace std;

namespace openLock {
/*
// TODO: copy problem statement here
 752. Open the Lock
 Medium

 479

 26

 Favorite

 Share
 You have a lock in front of you with 4 circular wheels. Each wheel has 10 slots: '0', '1', '2', '3', '4', '5', '6', '7', '8', '9'. The wheels can rotate freely and wrap around: for example we can turn '9' to be '0', or '0' to be '9'. Each move consists of turning one wheel one slot.

 The lock initially starts at '0000', a string representing the state of the 4 wheels.

 You are given a list of deadends dead ends, meaning if the lock displays any of these codes, the wheels of the lock will stop turning and you will be unable to open it.

 Given a target representing the value of the wheels that will unlock the lock, return the minimum total number of turns required to open the lock, or -1 if it is impossible.

 Example 1:
 Input: deadends = ["0201","0101","0102","1212","2002"], target = "0202"
 Output: 6
 Explanation:
 A sequence of valid moves would be "0000" -> "1000" -> "1100" -> "1200" -> "1201" -> "1202" -> "0202".
 Note that a sequence like "0000" -> "0001" -> "0002" -> "0102" -> "0202" would be invalid,
 because the wheels of the lock become stuck after the display becomes the dead end "0102".
 Example 2:
 Input: deadends = ["8888"], target = "0009"
 Output: 1
 Explanation:
 We can turn the last wheel in reverse to move from "0000" -> "0009".
 Example 3:
 Input: deadends = ["8887","8889","8878","8898","8788","8988","7888","9888"], target = "8888"
 Output: -1
 Explanation:
 We can't reach the target without getting stuck.
 Example 4:
 Input: deadends = ["0000"], target = "8888"
 Output: -1
 Note:
 The length of deadends will be in the range [1, 500].
 target will not be in the list deadends.
 Every string in deadends and the string target will be a string of 4 digits from the 10,000 possibilities '0000' to '9999'.
 */

class Solution {
public:
    int openLock2(vector<string>& deadends, string target) {
        unordered_set<string> ds(deadends.begin(), deadends.end());
        if (ds.count("0000")) {
            return -1;
        }
        queue<string> q1, q2;
        unordered_set<string> v1, v2;
        q1.push("0000");
        v1.insert("0000");
        q2.push(target);
        v2.insert(target);
        int steps = 0;
        while (q1.size() && q2.size()) {
            if (q2.size() < q1.size()) {
                swap(q1, q2);
                swap(v1, v2);
            }
            
            ++steps;
            int qn = q1.size();
            while (qn--) {
                string c = q1.front();
                q1.pop();
                string nc(c);
                for (int i = 0; i < 4; ++i) {
                    char c1 = c[i] + 1;
                    char c2 = c[i] - 1;
                    if (c[i] == '9') {
                        c1 = '0';
                    } else if (c[i] == '0') {
                        c2 = '9';
                    }
                    for (char h : {c1,c2}) {
                        nc[i] = h;
                        if (v2.count(nc)) {
                            return steps;
                        }
                        if (!ds.count(nc) && !v1.count(nc)) {
                            q1.push(nc);
                            v1.insert(nc);
                        }
                    }
                    nc[i] = c[i];
                }
            }
        }
        return -1;
    }
    /**
     * BFS
     */
    int openLock(vector<string>& deadends, string target) {
        // use deadends as visited
        unordered_set<string> dd(deadends.begin(), deadends.end());
        unordered_set<string> cur{"0000"};
        if (dd.find("0000") != dd.end()) {
            return -1;
        }
        int res = 0;
        while (cur.size()) {
            ++res;
            unordered_set<string> next;
            for (const auto& s : cur) {
                // turn each wheel left or right
                for (int i = 0; i < 4; ++i) {
                    string t1(s), t2(s);
                    int v = s[i] - '0';
                    int v1 = (10 + v - 1) % 10;
                    int v2 = (v + 1) % 10;
                    t1[i] = '0' + v1;
                    t2[i] = '0' + v2;
                    if (t1 == target || t2 == target) {
                        return res;
                    }
                    if (dd.find(t1) == dd.end()) {
                        next.insert(t1);
                        dd.insert(t1);
                    }
                    if (dd.find(t2) == dd.end()) {
                        next.insert(t2);
                        dd.insert(t2);
                    }
                }
            }
            cur.swap(next);
        }
        return -1;
    }

private:
};

}

/*/
int main() {
    // TODO: define parameter type here
    struct d {
        vector<string> deadends;
        string target;
    };
    // TODO: prepare parameters here
    vector<struct d> p {
        {{"0201","0101","0102","1212","2002"}, "0202"},
        {{"8888"}, "0009"},
        {{"8887","8889","8878","8898","8788","8988","7888","9888"}, "8888"},
        {{"0000"}, "8888"},
    };

    vector< int > answers {
        6,
        1,
        -1,
        -1,
    };

    // TODO: update paramters.
    for (auto& dp : p) {
        cout << endl;
        clock_t tstart = clock();
        auto res = openLock::Solution().openLock2(dp.deadends, dp.target);
        cout << clock() - tstart << endl;
        cout << res << endl;
    }
    return 0;
}
//*/
