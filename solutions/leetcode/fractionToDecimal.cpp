//
//  fractionToDecimal.cpp
//  leetcode
//
//  Created by  Song Ding on 1/24/18.
//  Copyright © 2018 Song Ding. All rights reserved.
//

#include "common.h"
using namespace std;

namespace fractionToDecimal {
    class Solution {
    public:
        /**
         2 scenarios:
         1), if denominator is a divisor of a power of 10
         2), otherwise, transform denominator to something like 9999...
         and add enough 0's in front of transformed numerator.
         
         Each solution:
         just simulate how division is done, and check whether
         a repeating numerator is encountered.
         */
        string fractionToDecimal(int numerator, int denominator) {
            int n = numerator;
            int d = denominator;
            if (d == 0) {
                return "Nan";
            } else if (n == 0) {
                return "0";
            }
            
            ostringstream oss;
            bool negative = false;
            if (n < 0 && d > 0) {
                n = -n;
                oss << "-";
            } else if (n > 0 && d < 0) {
                d = -d;
                oss << "-";
            } else if (n < 0 && d < 0) {
                n = -n;
                d = -d;
            }
            
            int w = 0;
            if (n > d) {
                w = n / d;
                n = n % d;
            }
            oss << w;
            if (n == 0) {
                return oss.str();
            }
            oss << ".";
            
            // simulate division
            // from n to position in quotient
            map<int, int> encounters;
            while (n != 0) {
                n *= 10;
                if (n < d) {
                    oss << '0';
                    continue;
                }
                if (encounters.find(n) != encounters.end()) {
                    break;
                }
                encounters.insert(make_pair(n, oss.tellp()));
                
                int t = n / d;
                n = n % d;
                oss << t;
            }
            
            string res(oss.str());
            if (n != 0) {
                int st = encounters[n];
                res.insert(st, 1, '(');
                res.push_back(')');
            }
            return res;
        }
        
        string fractionToDecimal2(int numerator, int denominator) {
            int n = numerator;
            int d = denominator;
            if (d == 0) {
                return "Nan";
            } else if (n == 0) {
                return "0";
            }
            
            ostringstream oss;
            bool negative = false;
            if (n < 0 && d > 0) {
                n = -n;
                oss << "-";
            } else if (n > 0 && d < 0) {
                d = -d;
                oss << "-";
            } else if (n < 0 && d < 0) {
                n = -n;
                d = -d;
            }
            
            int w = 0;
            if (n > d) {
                w = n / d;
                n = n % d;
            }
            oss << w;
            if (n == 0) {
                return oss.str();
            }
            oss << ".";
            
            // simulate division
            // from n to position in quotient
            map<int, int> encounters;
            while (n != 0) {
                n *= 10;
                if (encounters.find(n) != encounters.end()) {
                    break;
                }
                encounters.insert(make_pair(n, oss.tellp()));
                
                bool found = false;
                while (n < d) {
                    oss << '0';
                    n *= 10;
                    if (encounters.find(n) != encounters.end()) {
                        found = true;
                        break;
                    }
                    encounters.insert(make_pair(n, oss.tellp()));
                }
                if (found) {
                    break;
                }
                
                int t = n / d;
                n = n % d;
                oss << t;
            }
            
            string res(oss.str());
            if (n != 0) {
                int st = encounters[n];
                res.insert(st, 1, '(');
                res.push_back(')');
            }
            return res;
        }
        
    };
}
/*
int main() {
    //int n = 89;
    //int d = 270;
    int n = 100;
    int d = 333;
    cout << fractionToDecimal::Solution().fractionToDecimal(n, d) << endl;
    return 0;
}
// */
