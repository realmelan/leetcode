//
//  maximumSwap.cpp
//  leetcode
//
//  Created by  Song Ding on 11/28/17.
//  Copyright © 2017 Song Ding. All rights reserved.
//

#include "common.h"
using namespace std;

namespace maximumSwap {
    class Solution {
    public:
        int maximumSwap(int num) {
            vector<vector<int>> digits(10);
            int base = 1;
            int n = num;
            while (n) {
                int t = n % 10;
                digits[t].push_back(base);
                base *= 10;
                n = n / 10;
            }
            
            int tbase = 0;
            base /= 10;
            int i = 9;
            bool found = false;
            for (; i >= 0; --i) {
                const auto& v = digits[i];
                if (v.empty()) {
                    continue;
                }
                
                for (int j = v.size() - 1; j >= 0; --j) {
                    if (v.at(j) != base) {
                        tbase = v.at(0);
                        found = true;
                        break;
                    }
                    base /= 10;
                }
                if (found) {
                    break;
                }
            }
            
            if (found) {
                int tdigit = (num / base) % 10;
                num += (i - tdigit) * (base - tbase);
            }
            return num;
        }
    };
}
/*
int main() {
    cout << maximumSwap::Solution().maximumSwap(1993) << endl;
    return 0;
}
 */
