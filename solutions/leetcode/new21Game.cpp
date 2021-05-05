// new21Game.cpp
// leetcode
//
// Created by  Song Ding on 5/21/18.
// Copyright © 2018 Song Ding. All rights reserved.
//
#include "common.h"
using namespace std;

namespace new21Game {

class Solution {
public:
    /**
     * Let count(i) = probability to reach i.
     * then, count(K) = (count(K - 1) + ... + count(K - W)) * 1 / W.
     *
     * Now, suppose when alice reaches K - W, there is only 1 number
     * that would let her reach K, that is W. All other numbers lead
     * her to K - i.
     *
     * Also, suppose Alice reaches K - i (i < W), for numbers from (i to W),
     * some of them would let Alice pass N, that is from (N - K + i) to W.
     *
     * So from number [K - W, K - 1], there are pass(K) = (1 * count(K - W)
     *   + 2 * count(K - 2) + ... + W * count(K - 1)) / W
     *
     * Out of these pass(K) ways of passing K, numbers [K - (K+W-N-1), K - 1]
     * may produce some numbers which pass N, and pass(N) out of pass(K) =
     *   (1 * count(N + 1 - W) + 2 * count(N + 2 - W) + ... + (K - N + W - 1) * count(K - 1)) / W
     *
     * Note, for numbers to be valid, N + 1 - W > 0 && K - N + W - 1 > 0
     * so N > W - 1 && N - K < W - 1.
     *
     *
     * How to compute count(i)?
     *    count(i) = (count(i - W) + count(i - W + 1) + ... + count(i - 1)) / W.
     */
    double new21Game(int N, int K, int W) {
        if (N - K >= W - 1 || K == 0) {
            return 1;
        }
        vector<double> counts(max(W + 1, K), 0);
        counts[0] = 1;
        counts[1] = (double)1 / W;
        double sum = counts[0] + counts[1];
        for (int i = 2; i <= W; ++i) {
            counts[i] = sum / W;
            sum += counts[i];
        }
        for (int i = W + 1; i < K; ++i) {
            sum -= counts[i - W - 1];
            counts[i] = sum / W;
            sum += counts[i];
        }
        
        double passK = 0;
        for (int i = max(1, W + 1 - K); i <= W; ++i) {
            passK += i * counts[K - W + i - 1];
        }
        
        double passN = 0;
        for (int i = min(K, K+W-N-1); i >= 1; --i) {
            passN += (K + W - N - i) * counts[K - i];
        }
        return 1 - passN / passK;
    }

private:
};

}

/*/
int main() {
    // TODO: prepare parameters here
    int N = 1;
    int K = 1;
    int W = 3;
    // TODO: add return type and paramters.
    clock_t start = clock();
    auto res = new21Game::Solution().new21Game(N, K, W);
    cout << clock() - start << endl;
    cout << res << endl;
    return 0;
}
//*/
