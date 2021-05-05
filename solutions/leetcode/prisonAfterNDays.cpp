// prisonAfterNDays.cpp
// leetcode
//
// Created by  Song Ding on 4/30/19.
// Copyright © 2019 Song Ding. All rights reserved.
//
#include "common.h"
using namespace std;

namespace prisonAfterNDays {

class Solution {
public:
    vector<int> prisonAfterNDays(vector<int>& cells, int N) {
        vector<int> states(256, -1);
        vector<int> changeToState;
        int cur = toState(cells);
        int i = 0;
        states[cur] = i;
        changeToState.push_back(cur);
        while (i < N) {
            ++i;
            cur = change(cur);
            if (states[cur] >= 0) {
                break;
            } else {
                changeToState.push_back(cur);
                states[cur] = i;
            }
            
        }
        
        if (i == N) {
            return toCells(cur);
        } else {
            int last = states[cur];
            int loop = i - last;
            int idx = (N - i) % loop;
            return toCells(changeToState[last + idx]);
        }
        
    }
    
    vector<int> prisonAfterNDays2(vector<int>& cells, int N) {
        struct hash {
            size_t operator()(const vector<int>& v) const {
                size_t res = 0;
                for (auto i : v) {
                    res <<= 1;
                    res |= i;
                }
                return res;
            }
        };
        unordered_map<vector<int>, int, hash> states;
        vector<vector<int>> i2cells;
        states[cells] = 0;
        i2cells.push_back(cells);
        int i = 1;
        for (; i <= N; ++i) {
            change(cells);
            auto it = states.find(cells);
            if (it != states.end()) {
                break;
            }
            states[cells] = i;
            i2cells.push_back(cells);
        }
        if (i == N) {
            return cells;
        } else {
            int last = states[cells];
            int idx = (N-last)%(i-last);
            return i2cells[last+idx];
        }
    }
    void change(vector<int>& cells) {
        vector<int> res(cells);
        res[0] = res[7] = 0;
        for (int i = 1; i < 7; ++i) {
            res[i] = 1-(cells[i-1] ^ cells[i+1]);
        }
        cells = res;
    }

private:
    int change(int state) {
        vector<int> cells = toCells(state);
        vector<int> next(cells);
        for (int i = 1; i < 7; ++i) {
            next[i] = (cells[i-1] ^ (1-cells[i+1]));
        }
        next[0] = 0;
        next[7] = 0;
        return toState(next);
    }
    vector<int> toCells(int state) {
        vector<int> res(8, 0);
        for (int i = 0; i < 8; ++i) {
            res[7 - i] = (state & 1);
            state >>= 1;
        }
        return res;
    }
    int toState(const vector<int>& cells) {
        int res = 0;
        for (int i = 0; i < 8; ++i) {
            res |= (cells[i] << (7 - i));
        }
        return res;
    }
};

}

/*/
int main() {
    // TODO: prepare parameters here
    vector< pair<vector<int>,int> > params {
        {{0,1,0,1,1,0,0,1},7}
    };

    vector< vector<int>  > answers {
        {0, 0, 1, 1, 0, 0, 0, 0}
    };
    int i = 0;

    // TODO: add return type and paramters.
    clock_t tstart = clock();
    auto res = prisonAfterNDays::Solution().prisonAfterNDays2(params[i].first, params[i].second);
    cout << clock() - tstart << endl;
    cout << res << endl;
    return 0;
}
//*/
