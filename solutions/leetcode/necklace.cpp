//
//  necklace.cpp
//  leetcode
//
//  Created by  Song Ding on 2/4/18.
//  Copyright © 2018 Song Ding. All rights reserved.
//

#include "common.h"
using namespace std;

namespace necklace {
    /**
     See book "Combinatorial Generation" by Frank Ruskey.
     
     */
    class Solution {
    public:
        /*
        string necklace(int n, int k) {
            string res;
            if (k == 1) {
                for (int i = 0; i < n; ++i) {
                    res.push_back('0');
                }
                return res;
            }
            
            vector<int> a(n, 0);
            print(a, 1);
            res.push_back('0');
            int i = n - 1;
            while (i >= 0) {
                a[i] = a[i] + 1;
                for (int j = 0; j < n - 1 - i; ++j) {
                    a[j + i + 1] = a[j];
                }
                if (n % (i + 1)) {
                    print(a, n);
                    for (int j = 0; j < n; ++j) {
                        res.push_back('0' + a[j]);
                    }
                } else {
                    print(a, i + 1);
                    for (int j = 0; j < i + 1; ++j) {
                        res.push_back('0' + a[j]);
                    }
                }
                
                i = n - 1;
                while (i >= 0 && a[i] == k - 1) {
                    --i;
                }
            }
            return res;
        }
         
         */
        void print(vector<int>& a, int n) {
            for (int i = 0; i < n; ++i) {
                cout << a[i];
            }
            cout << endl;
        }
        
        string necklace(int n, int k) {
            string res;
            if (k == 1) {
                for (int i = 0; i < n; ++i) {
                    res.push_back('0');
                }
                return res;
            }
            
            vector<int> a(n, k - 1);
            print(a, 1);
            for (int i = 0; i < n - 1; ++i) {
                res.push_back('0');
            }
            res.push_back('0' + k - 1);
            int i = n - 1;
            while (i >= 0) {
                --a[i];
                for (int j = 0; j < n - 1 - i; ++j) {
                    a[j + i + 1] = a[j];
                }
                // a might not be a necklace
                if (isNecklace(a)) {
                    if (n % (i + 1)) {
                        print(a, n);
                        for (int j = 0; j < n; ++j) {
                            res.push_back('0' + a[j]);
                        }
                    } else {
                        print(a, i + 1);
                        for (int j = 0; j < i + 1; ++j) {
                            res.push_back('0' + a[j]);
                        }
                    }
                }
                
                i = n - 1;
                while (i >= 0 && a[i] == 0) {
                    --i;
                }
            }
            return res;
        }
        bool isNecklace(vector<int> a) {
            int n = a.size();
            for (int k = 1; k < n; ++k) {
                for (int i = 0; i < n; ++i) {
                    if (a[i] > a[(i + k) % n]) {
                        break;
                    } else if (a[i] < a[(i + k) % n]) {
                        return false;
                    }
                }
            }
            return true;
        }
        
    };
}
/*
int main() {
    //cout << necklace::Solution().necklace(3, 2) << endl;
    cout << necklace::Solution().necklace(2, 2) << endl;
    return 0;
}
*/

