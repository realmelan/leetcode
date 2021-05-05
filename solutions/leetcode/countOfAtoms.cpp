//
//  countOfAtoms.cpp
//  leetcode
//
//  Created by  Song Ding on 1/26/18.
//  Copyright © 2018 Song Ding. All rights reserved.
//

#include "common.h"
using namespace std;

namespace countOfAtoms {
    class Solution {
    public:
        /**
         Separate formula into multiple sub-formula, if there is round
         parentheses.
         For each sub formula, recursively do the processing.
         */
        string countOfAtoms(string formula) {
            map<string, int> counts;
            int idx = 0;
            recur(formula, idx, counts);
            ostringstream res;
            for (const auto & p : counts) {
                res << p.first;
                if (p.second > 1) {
                    res << p.second;
                }
            }
            return res.str();
        }
    private:
        void recur(string f, int& index, map<string, int>& counts) {
            string atom;
            int count = 0;
            map<string, int> subCounts;
            while (index < f.size()) {
                char c = f[index++];
                if (c >= 'A' && c <= 'Z') {
                    if (count == 0) {
                        count = 1;
                    }
                    if (subCounts.size()) {
                        for (const auto& p : subCounts) {
                            counts[p.first] += p.second * count;
                        }
                        subCounts.clear();
                    } else if (atom.size()) {
                        counts[atom] += count;
                        atom.clear();
                    }
                    count = 0;
                    atom.push_back(c);
                } else if (c >= 'a' && c <= 'z') {
                    atom.push_back(c);
                } else if (c >= '0' && c <= '9') {
                    count *= 10;
                    count += c - '0';
                } else if (c == '(') {
                    if (count == 0) {
                        count = 1;
                    }
                    if (subCounts.size()) {
                        for (const auto& p : subCounts) {
                            counts[p.first] += p.second * count;
                        }
                        subCounts.clear();
                    } else if (atom.size()) {
                        counts[atom] += count;
                        atom.clear();
                    }
                    count = 0;
                    
                    // recur
                    subCounts.clear();
                    recur(f, index, subCounts);
                } else {
                    // c == ')'
                    if (count == 0) {
                        count = 1;
                    }
                    if (subCounts.size()) {
                        for (const auto& p : subCounts) {
                            counts[p.first] += p.second * count;
                        }
                        subCounts.clear();
                    } else if (atom.size()) {
                        counts[atom] += count;
                        atom.clear();
                    }
                    count = 0;
                    return;
                }
            }
            if (count == 0) {
                count = 1;
            }
            if (subCounts.size()) {
                for (const auto& p : subCounts) {
                    counts[p.first] += p.second * count;
                }
                subCounts.clear();
            } else if (atom.size()) {
                counts[atom] += count;
                atom.clear();
            }
        }
    };
}
/*
int main() {
    string formula = "Mg(O(H5Ui8J(Xc3Ga)5)H)2";
    cout << countOfAtoms::Solution().countOfAtoms(formula) << endl;
}
 */
