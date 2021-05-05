//
//  amazonBreakupNumberString.cpp
//  leetcode
//
//  Created by Song Ding on 11/11/20.
//  Copyright © 2020 Song Ding. All rights reserved.
//

#include "common.h"
using namespace std;

namespace amazonBreakupNumberString {
/*
// TODO: copy problem statement here

*/
class Solution {
public:
    // TODO: copy function signature here
    int amazonBreakupNumberString(const string& s) {
        constexpr int N = 1000000;
        vector<bool> prime(N+1, true);
        for (int i = 2; i <= N; ++i) {
            if (prime[i]) {
                for (int j = i*2; j <= N; j+=i) {
                    prime[j] = false;
                }
            }
        }
        unordered_set<string> primes;
        for (int i = 2; i <= N; ++i) {
            if (prime[i]) {
                primes.insert(to_string(i));
            }
        }
        
        int n = s.size();
        vector<int> memo(n+1, -1);
        memo[n] = 1;
        return dfs(s, 0, primes, memo);
    }
private:
    int dfs(const string& s, int cur, const unordered_set<string>& primes, vector<int>& memo) {
        if (memo[cur] >= 0) {
            return memo[cur];
        }
        long res = 0;
        for (int j = 1; j<=6 && cur+j <= s.size(); ++j) {
            if (primes.count(s.substr(cur, j))) {
                res = (res + dfs(s, cur+j, primes, memo))%1000000007;
            }
        }
        memo[cur] = res;
        return res;
    }
};
}

/*
int main() {
    // TODO: define parameter type here
    struct param {
        string s;
    };
    // TODO: prepare parameters here
    vector<struct param> params {
        {"11373"},
    };
    // TODO: provide expected results here
    vector<int> answers {
        6,
    };
    
    for (auto& dp : params) {
        cout << endl;
        clock_t tstart = clock();
        auto res = amazonBreakupNumberString::Solution().amazonBreakupNumberString(dp.s);
        cout << res << endl;
        cout << clock() - tstart << endl;
    }

    return 0;
}
//*/
