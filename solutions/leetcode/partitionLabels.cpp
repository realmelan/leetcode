// partitionLabels.cpp
// leetcode
//
// Created by  Song Ding on 6/20/18.
// Copyright © 2018 Song Ding. All rights reserved.
//
#include "common.h"
using namespace std;

namespace partitionLabels {

class Solution {
public:
    /**
     * go through each char and maintain a vector of maps. Each map
     * corresponding to a separate substring.
     *
     * for current character, check whether it exists in a map. If not,
     * create a new map and add it to the vector; otherwise, group maps
     * from the last to the map which contains this char.
     *
     */
    vector<int> partitionLabels(string S) {
        vector<int> c2g(26, -1);
        vector<int> groupLen;
        int n = S.size();
        for (int i = 0;i < n; ++i) {
            int id = S[i] - 'a';
            if (c2g[id] < 0) {
                c2g[id] = groupLen.size();
                groupLen.push_back(1);
            } else {
                int t = 0;
                while (groupLen.size() > c2g[id] + 1) {
                    t += groupLen.back();
                    groupLen.pop_back();
                }
                groupLen[c2g[id]] += t + 1;
                for (int j = 0; j < 26; ++j) {
                    if (c2g[j] > c2g[id]) {
                        c2g[j] = c2g[id];
                    }
                }
            }
        }
        return groupLen;
        
    }

private:
};

}

/*/
int main() {
    // TODO: prepare parameters here
    string S = "ababcbacadefegdehijhklij";
    // TODO: add return type and paramters.
    clock_t start = clock();
    auto res = partitionLabels::Solution().partitionLabels(S);
    cout << clock() - start << endl;
    cout << res << endl;
    return 0;
}
//*/
