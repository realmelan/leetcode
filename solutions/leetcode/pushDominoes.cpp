// pushDominoes.cpp
// leetcode
//
// Created by  Song Ding on 5/9/19.
// Copyright © 2019 Song Ding. All rights reserved.
//
#include "common.h"
using namespace std;

namespace pushDominoes {
/*
 838. Push Dominoes
 Medium
 
 287
 
 32
 
 Favorite
 
 Share
 There are N dominoes in a line, and we place each domino vertically upright.
 
 In the beginning, we simultaneously push some of the dominoes either to the left or to the right.
 
 
 
 After each second, each domino that is falling to the left pushes the adjacent domino on the left.
 
 Similarly, the dominoes falling to the right push their adjacent dominoes standing on the right.
 
 When a vertical domino has dominoes falling on it from both sides, it stays still due to the balance of the forces.
 
 For the purposes of this question, we will consider that a falling domino expends no additional force to a falling or already fallen domino.
 
 Given a string "S" representing the initial state. S[i] = 'L', if the i-th domino has been pushed to the left; S[i] = 'R', if the i-th domino has been pushed to the right; S[i] = '.', if the i-th domino has not been pushed.
 
 Return a string representing the final state.
 
 Example 1:
 
 Input: ".L.R...LR..L.."
 Output: "LL.RR.LLRRLL.."
 Example 2:
 
 Input: "RR.L"
 Output: "RR.L"
 Explanation: The first domino expends no additional force on the second domino.
 Note:
 
 0 <= N <= 10^5
 String dominoes contains only 'L', 'R' and '.'
 */
class Solution {
public:
    /**
     * starting from current state, try locate next action domino:
     * 1, if current state is '.':
        1, if next is 'L': current to 'L' marked as 'L'
        2, if next is 'R': current to 'R'-1 marked as '.';
        3, if next is EOS, do nothing
     * 2, if it is 'L':
        1, if next is L: mark current to 'L' as 'L'
        2, if next is R: left half marked as 'L', right half as 'R', middle as '.' if any
        3, if next is EOS: do nothing
     * 3, if it is 'R':
        1, if next is 'L': left half marked as 'R', right half as 'L', middle as '.' if any
        2, if next is 'R': mark current to 'R' as 'R'
        3, if next is EOS: mark current to EOS as 'R'
     */
    string pushDominoes(string dominoes) {
        string res(dominoes);
        dominoes.push_back('E');
        int n = dominoes.size();
        char c = dominoes[0];
        int last = 0;
        int i = 1;
        while (i < n) {
            if (dominoes[i] == 'L') {
                if (c == '.' || c == 'L') {
                    for (int j = last; j <= i; ++j) {
                        res[j] = 'L';
                    }
                } else if (c == 'R') {
                    int j = last;
                    int mid = (last + i) / 2;
                    for (; j <= mid; ++j) {
                        res[j] = 'R';
                    }
                    for (; j <= i; ++j) {
                        res[j] = 'L';
                    }
                    if ((last + i) % 2 == 0) {
                        res[(last+i)/2] = '.';
                    }
                }
                last = i;
                c = dominoes[i];
            } else if (dominoes[i] == 'R') {
                if (c == 'R') {
                    for (int j = last; j < i; ++j) {
                        res[j] = 'R';
                    }
                }
                last = i;
                c = dominoes[i];
            } else if (dominoes[i] == 'E') {
                if (c == 'R') {
                    for (int j = last; j < i; ++j) {
                        res[j] = 'R';
                    }
                }
                last = i;
                c = dominoes[i];
            }
            ++i;
        }
        return res;
    }

private:
};

}

/*/
int main() {
    // TODO: prepare parameters here
    vector< string > p{
        ".L.R...LR..L..",
        "RR.L",
        ".L.R."
    };

    vector< string  > answers {
        "LL.RR.LLRRLL..",
        "RR.L",
        "LL.RR"
    };
    int i = 0;

    // TODO: add return type and paramters.
    clock_t tstart = clock();
    auto res = pushDominoes::Solution().pushDominoes(p[i]);
    cout << clock() - tstart << endl;
    cout << res << endl;
    return 0;
}
//*/
