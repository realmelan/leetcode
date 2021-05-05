//
//  bulbSwitch.cpp
//  leetcode
//
//  Created by  Song Ding on 10/24/17.
//  Copyright © 2017 Song Ding. All rights reserved.
//

#include <stdio.h>
#include "common.h"

using namespace std;

namespace bulbSwitch {
class Solution {
public:
    int bulbSwitch(int n) {
        vector<int> b(n+1, 1);
        b[0] = 0;
        for (int k = 2; k <= n; ++k) {
            for (int i = 1; i <= n / k; ++i) {
                b[k*i] ^= 1;
            }
        }
        
        int res = 0;
        for (int i : b) {
            res += i;
        }
        return res;
    }
};
}
/**
int main() {
    cout << bulbSwitch::Solution().bulbSwitch(999999) << endl;
    return 0;
}
 */
