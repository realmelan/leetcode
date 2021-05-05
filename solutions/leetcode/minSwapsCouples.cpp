//
//  minSwapsCouples.cpp
//  leetcode
//
//  Created by  Song Ding on 1/25/18.
//  Copyright © 2018 Song Ding. All rights reserved.
//

#include "common.h"
using namespace std;

namespace minSwapsCouples {
    class Solution {
    public:
        /**
         Check each pair of integers startin from index 0:
         1, if a couple, go to next pair
         2, if not, find next pair, which contains one number
         which makes couple from current pair, and move the
         left over number to the found pair.
         */
        int minSwapsCouples(vector<int>& row) {
            int n = row.size();
            if (n < 4) {
                return 0;
            }
            
            int res = 0;
            int cn = n / 2;
            for (int i = 0; i < cn; ++i) {
                int p1 = row[i * 2];
                int p2 = row[i * 2 + 1];
                if (p1 > p2) {
                    int t = p1;
                    p1 = p2;
                    p2 = t;
                }
                
                // already a couple
                if (p1 % 2 == 0 && p2 - p1 == 1) {
                    continue;
                }
                
                int cp = p1 + 1;
                if (p1 & 1) {
                    cp = p1 - 1;
                }
                
                ++res;
                // find the other one for p1
                for (int j = i + 1; j < cn; ++j) {
                    int cp1 = row[j * 2];
                    int cp2 = row[j * 2 + 1];
                    
                    if (cp1 == cp) {
                        row[i * 2] = p1;
                        row[i * 2 + 1] = cp;
                        row[j * 2] = p2;
                        break;
                    } else if (cp2 == cp) {
                        row[i * 2] = p1;
                        row[i * 2 + 1] = cp;
                        row[j * 2 + 1] = p2;
                        break;
                    }
                }
            }
            return res;
        }
    };
}

/*
int main() {
    vector<int> row{2,0,1,3};
    cout << minSwapsCouples::Solution().minSwapsCouples(row) << endl;
    return 0;
}
 */
