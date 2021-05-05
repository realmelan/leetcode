//
//  accountsMerge.cpp
//  leetcode
//
//  Created by  Song Ding on 1/1/18.
//  Copyright © 2018 Song Ding. All rights reserved.
//

#include "common.h"

using namespace std;
/**
 721. Accounts Merge
 Medium
 
 771
 
 207
 
 Favorite
 
 Share
 Given a list accounts, each element accounts[i] is a list of strings, where the first element accounts[i][0] is a name, and the rest of the elements are emails representing emails of the account.
 
 Now, we would like to merge these accounts. Two accounts definitely belong to the same person if there is some email that is common to both accounts. Note that even if two accounts have the same name, they may belong to different people as people could have the same name. A person can have any number of accounts initially, but all of their accounts definitely have the same name.
 
 After merging the accounts, return the accounts in the following format: the first element of each account is the name, and the rest of the elements are emails in sorted order. The accounts themselves can be returned in any order.
 
 Example 1:
 Input:
 accounts = [["John", "johnsmith@mail.com", "john00@mail.com"], ["John", "johnnybravo@mail.com"], ["John", "johnsmith@mail.com", "john_newyork@mail.com"], ["Mary", "mary@mail.com"]]
 Output: [["John", 'john00@mail.com', 'john_newyork@mail.com', 'johnsmith@mail.com'],  ["John", "johnnybravo@mail.com"], ["Mary", "mary@mail.com"]]
 Explanation:
 The first and third John's are the same person as they have the common email "johnsmith@mail.com".
 The second John and Mary are different people as none of their email addresses are used by other accounts.
 We could return these lists in any order, for example the answer [['Mary', 'mary@mail.com'], ['John', 'johnnybravo@mail.com'],
 ['John', 'john00@mail.com', 'john_newyork@mail.com', 'johnsmith@mail.com']] would still be accepted.
 Note:
 
 The length of accounts will be in the range [1, 1000].
 The length of accounts[i] will be in the range [1, 10].
 The length of accounts[i][j] will be in the range [1, 30].
 */

namespace accountsMerge {
    class Solution {
    public:
        /**
         Disjoint set problem:
         using merge to merge different email accounts if two have
         an email address in common.
         */
        vector<vector<string>> accountsMerge(vector<vector<string>>& accounts) {
            vector<vector<string>> res;
            int s = accounts.size();
            if (s <= 0) {
                return res;
            }
            
            vector<int> parents(s);
            for (int i = 0; i < s; ++i) {
                parents[i] = i;
            }
            
            for (int i = 1; i < s; ++i) {
                const vector<string>& act = accounts[i];
                for (int j = 0; j < i; ++j) {
                    if (hasSameEmail(accounts[j], act)) {
                        merge(j, i, parents);
                    }
                }
            }
            map<int, set<string>> uniqAcctEmails;
            map<int, string> uniqAcctNames;
            for (int i = 0; i < s; ++i) {
                int p = find(i, parents);
                if (p == i) {
                    set<string> emails(accounts[i].begin() + 1, accounts[i].end());
                    uniqAcctEmails.insert(make_pair(i, emails));
                    uniqAcctNames.insert(make_pair(i, accounts[i][0]));
                } else {
                    uniqAcctEmails[p].insert(accounts[i].begin() + 1, accounts[i].end());
                }
            }
            for (const auto& kv : uniqAcctEmails) {
                vector<string> acct;
                acct.push_back(uniqAcctNames[kv.first]);
                acct.insert(acct.end(), kv.second.begin(), kv.second.end());
                res.push_back(acct);
            }
            return res;
        }
        
    private:
        int find(int i, vector<int>& parents) {
            if (parents[i] != i) {
                parents[i] = find(parents[i], parents);
            }
            return parents[i];
        }
        void merge(int i, int j, vector<int>& parents) {
            int pi = find(i, parents);
            int pj = find(j, parents);
            if (pi < pj) {
                parents[pj] = pi;
            } else if (pj < pi) {
                parents[pi] = pj;
            }
        }
        bool hasSameEmail(const vector<string>& act1, const vector<string>& act2) {
            int s1 = act1.size();
            int s2 = act2.size();
            for (int i = 1; i < s1; ++i) {
                for (int j = 1; j < s2; ++j) {
                    if (act1[i] == act2[j]) {
                        return true;
                    }
                }
            }
            return false;
        }
    };
}
/*
int main() {
    vector<vector<string>> accounts {
        {"David","David4@m.co","David2@m.co","David4@m.co"},
        {"John","John7@m.co","John5@m.co","John3@m.co"},
        {"Fern","Fern6@m.co","Fern4@m.co","Fern5@m.co"},
        {"Celine","Celine0@m.co","Celine7@m.co","Celine7@m.co"},
        {"Gabe","Gabe8@m.co","Gabe8@m.co","Gabe1@m.co"},
        {"Ethan","Ethan1@m.co","Ethan6@m.co","Ethan6@m.co"},
        {"Celine","Celine4@m.co","Celine8@m.co","Celine6@m.co"},
        {"Celine","Celine0@m.co","Celine0@m.co","Celine4@m.co"}
    };
    vector<vector<string>> res = accountsMerge::Solution().accountsMerge(accounts);
    for (const auto& a : res) {
        cout << "name = " << a[0];
        for (int i = 1; i < a.size(); ++i) {
            cout << ", " << a[i];
        }
        cout << endl;
    }
    return 0;
}
 */
