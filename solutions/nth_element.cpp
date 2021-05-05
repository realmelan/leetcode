//
//  nth_element.cpp
//  leetcode
//
//  Created by Song Ding on 11/14/20.
//  Copyright © 2020 Song Ding. All rights reserved.
//

#include "common.h"
using namespace std;

namespace nth_element {
/*
// TODO: copy problem statement here
manual implementation of std::nth_element
*/
class Solution {
public:
    // TODO: copy function signature here
    int nth_element(vector<int>& array, int K) {
        int l = 0, r = array.size() - 1;
        --K;
        while (l < r) {
            int mid = partition(array, l, r);
            if (mid == K) {
                l = mid;
                break;
            } else if (mid > K) {
                r = mid-1;
            } else {
                l = mid+1;
            }
        }
        return array[l];
    }

    int partition(vector<int>& array, int l, int r) {
        int pivot = array[r];
        for (int i = l; i < r; ++i) {
            if (array[i] < pivot) {
                swap(array[l++], array[i]);
            }
        }
        swap(array[l], array[r]);
        return l;
    }
private:
};
}

/*
int main() {
    // TODO: define parameter type here
    struct param {
        vector<int> array;
        int K;
    };
    // TODO: prepare parameters here
    vector<struct param> params {
        {{3,3,5,1,3,6,2},5},
    };
    // TODO: provide expected results here
    vector<int> answers {
    };
    
    for (auto& dp : params) {
        cout << endl;
        clock_t tstart = clock();
        auto res = nth_element::Solution().nth_element(dp.array, dp.K);
        cout << res << endl;
        cout << clock() - tstart << endl;
    }

    return 0;
}
//*/
