//
//  hIndex.cpp
//  leetcode
//
//  Created by  Song Ding on 12/17/17.
//  Copyright © 2017 Song Ding. All rights reserved.
//

#include "common.h"

using namespace std;

namespace hIndex {
    class Solution {
    public:
        int hIndex(vector<int>& citations) {
            int len = citations.size();
            if (len <= 0) {
                return 0;
            } else {
                sort(citations.begin(), citations.end(), [](int a, int b){
                    return a > b;
                });
                
                int h = 0;
                for (int i = 0; i < len; ++i) {
                    if (citations[i] >= i + 1) {
                        h = i + 1;
                    } else {
                        break;
                    }
                }
                return h;
            }
            
        }
    };
}

/*
int main() {
    vector<int> c{0, 1};
    cout << hIndex::Solution().hIndex(c) << endl;
    return 0;
}
 */
