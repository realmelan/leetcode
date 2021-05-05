// movesToStamp.cpp
// leetcode
//
// Created by  Song Ding on 11/15/18.
// Copyright © 2018 Song Ding. All rights reserved.
//
#include "common.h"
using namespace std;

namespace movesToStamp {

class Solution {
public:
    vector<int> movesToStamp(string stamp, string target) {
        return dfs(stamp, target, 0, target.size()-1);
    }
    vector<int> dfs(string stamp, string target, int l, int r) {
        if (l>r) {
            return {};
        } else if (r-l+1<=stamp.size()) {
            return {l};
        }
        vector<int> res(r-l+2);
        int stn = stamp.size(), tn = target.size();
        for (int i = l; i+stn <= tn && i<=r; ++i) {
            int j = 0;
            while (j < stn && (target[i+j] == '?' || target[i+j] == stamp[j])) {
                ++j;
            }
            if (j == stn) {
                string t = target.substr(i,stn);
                for (int j = 0; j < stn; ++j) {
                    target[i+j] = '?';
                }
                vector<int> lv, rv;
                if (l<=i-1) {
                    lv = dfs(stamp, target, l, max(i-1,l+stn-1));
                }
                if (i+stn <= r) {
                    rv = dfs(stamp, target, min(r-stn+1,i+stn),r);
                }
                if (res.size() >= lv.size() +rv.size() + 1) {
                    res.clear();
                    res.insert(end(res), begin(lv), end(lv));
                    res.insert(end(res), begin(rv), end(rv));
                    res.push_back(i);
                }
                for (int j = 0; j < stn; ++j) {
                    target[i+j] = t[j];
                }
            }
        }
        return res;
    }
    /**
     * First of all, find all whole stamps inside target, which
     * divides target into different parts.
     *
     * Now, each part has to be stamped, and the first part has to
     * align with the start of the stamp, and the last part has to
     * align with the end of the stamp.
     *
     * For parts between whole stamps, it can be composed of 3 different
     * patterns:
     *  1, all prefix and a trailing partial stamp
     *  2, all suffix and a heading partial stamp
     *  3, or, two sub-parts, with the first sub-parts being pattern 1
     *     and the second being pattern 2;
     */
    vector<int> movesToStamp3(string stamp, string target) {
        int tn = target.size();
        int sn = stamp.size();
        size_t last = -sn;
        size_t idx = 0;
        vector<string> parts;
        vector<int> wholeStamps;
        int sc = 0;
        while ((idx = target.find(stamp, last + sn)) != string::npos) {
            if (idx - last - sn) {
                parts.push_back(target.substr(last + sn, idx - last - sn));
            } else {
                parts.push_back("");
            }
            wholeStamps.push_back(idx);
            last = idx;
        }
        if (last + sn < tn) {
            parts.push_back(target.substr(last + sn));
        } else {
            parts.push_back("");
        }
        
        int n = parts.size();
        int base = 0;
        
        vector<int> res;
        vector<int> t;
        if (!stampPrefix(base, stamp, parts[0], t, true)) {
            return {};
        }
        
        res.insert(res.end(), t.begin(), t.end());
        base += parts[0].size() + sn;
        
        for (int i = 1; i < n - 1; ++i) {
            vector<int> t;
            if (doStamp(base, stamp, parts[i], t)) {
                res.insert(res.end(), t.begin(), t.end());
                base += parts[i].size() + sn;
            } else {
                return {};
            }
        }
        
        t.clear();
        if (!stampSuffix(base, stamp, parts[n - 1], t, true)) {
            return {};
        }
        res.insert(res.end(), t.begin(), t.end());
        
        res.insert(res.end(), wholeStamps.begin(), wholeStamps.end());
        return res;
    }
private:
    bool doStamp(size_t base, string stamp, string target, vector<int>& res) {
        int n = target.size();
        if (n <= 0) {
            return true;
        }
        
        size_t idx = stamp.find(target);
        if (idx != string::npos) {
            res.push_back(base - idx);
            return true;
        }
        
        res.clear();
        if (stampPrefix(base, stamp, target, res)) {
            return true;
        }
        res.clear();
        if (stampSuffix(base, stamp, target, res)) {
            return true;
        }
        
        int sn = stamp.size();
        for (int i = 1; i < n; ++i) {
            if (target[i] == stamp[0]) {
                res.clear();
                if ( (stampPrefix(base + i, stamp, target.substr(i), res, true)
                    && stampSuffix(base, stamp, target.substr(0, i), res))
                    || (stampSuffix(base, stamp, target.substr(0, i), res, true)
                        && stampPrefix(base + i, stamp, target.substr(i), res)) ) {
                    return true;
                }
            }
        }
        return false;
    }
    bool stampPrefix(size_t base, string stamp, string target, vector<int>& res, bool complete = false) {
        int n = target.size();
        int sn = stamp.size();
        int last = n;
        for (int i = n - 1; i >= 0 && last - i < sn; --i) {
            int j = i;
            int k = 0;
            while (j < last && target[j] == stamp[k]) {
                ++k;
                ++j;
            }
            if (j == last) {
                res.insert(res.begin(), i + base);
                last = i;
            }
        }
        
        if (last == 0) {
            return true;
        } else if (!complete) {
            size_t idx = stamp.find(target.substr(0, last));
            if (idx != string::npos) {
                res.insert(res.begin(), base - idx);
                return true;
            }
        }
        return false;
    }
    bool stampSuffix(size_t base, string stamp, string target, vector<int>& res, bool complete = false) {
        int n = target.size();
        int sn = stamp.size();
        int last = -1;
        for (int i = 0; i < n && i - last < sn; ++i) {
            int j = i;
            int k = sn - 1;
            while (j > last && target[j] == stamp[k]) {
                --k;
                --j;
            }
            if (j == last) {
                res.insert(res.begin(), i + base - sn + 1);
                last = i;
            }
        }
        
        if (last == n - 1) {
            return true;
        } else if (!complete) {
            size_t idx = stamp.find(target.substr(last + 1));
            if (idx != string::npos) {
                res.insert(res.begin(), base + last + 1 - idx);
                return true;
            }
        }
        return false;
    }
    
    
};

}

/*/
int main() {
    // TODO: prepare parameters here
    vector<string> stamp {
        "oz",
        "h",
        "abc",
        "abca",
        "aaaaaa",
        "mda",
        "aa",
        "xkaa",
        "xkaa",
        "abcada",
        "bfe",
        "babe",
        "aadbb"
        
    };
    vector<string> target {
        "ooozz",
        "hhhh",
        "ababc",
        "aabcaca",
        "aaaaaaaaaaaaaaa",
        "mdadddaaaa",
        "aaaaaaaaaaaaaaa",
        "xkaaaaxkaaaxxkaaaa",
        "xkaaaaxkaaaxxkaaaaaxkxkaxkxkaaaxxxkaakaxkaakaaaxkaaaakaxkaakxkaaaaxkxkxkaaaxxkxkaaxkaxkaaaakxkaaaxkxkaaaakxkaaxkaaaxkaakxkaaaxkaaakaakxxkaxkaakxxkaakaaxkaxkaaakaxkxkaaxkaxkaaaxkaxkaxkaakaaxkaakaakxkaaaxxkaaxkaaaaaxkaaxxkaakaakaaaakxkaaaaaxkaaaxxkaaxkxkaaxkaaakaaxkaxkaaxkaxkaakaxkaaxkaakxkaaaxkxkaaxkaaaxkaaaxkaaxkaaxkaxkaakaaaaaaaxkaaaxkaxkxkaaxkxkaaxkaaxkxxkaaaxkaaaxkaaaxkaaxxkxkaaxkxkaakaakxkaaxkaaaxkaaxkaaaakaxkaaaxkaakaxkaaaxkaaxkaxkaaaxxkaaaakaxxkaakxkaaaaaxxkaaxxkaaaxkaaxxkaaakxxkaaaaaxxkxkaxkaakxxkaaxkaaaakxxkaaxkaaaaaaxkxkaaxxxkaaxxkaaxkaxkaakaxkaakaaaakxkaakaxkxkaaaaxxxkaakaaxkaaxkaaxkaaxxkaakaaaxkaxkaaxkxkaaaxkaakaakxkxkaaaaakaxkaxxxxkaaxkaaxkaaaxkaaaxkaaakxkxkaaaxkaaxkxkaxkaakaxkaaxkxkaaaxxkaaaaaaxkaaaaxkxkaaaaaxkaaaaxxkaaxkaaaaaxkaaxxkaaxkxkaaaaxkaakaakaaxkaaxkaaaxkaaaaaxxxkaaxkaaaaxkaaaxkaaxkaaxkaaxkaaxkaaaaxkaakaxkaaaxkaaaxxkaaakxkaxkaaaxxkaaaaxkxkaxkaaaaakxxkxkaaxkaxkaaakaxkxkaaxkxxkxkaaaaxxxxkaakaakaakaaxxxxkaaxkaakaaaaakxxxkaaxxxkxkaaaaxxkaaaxxkaaaaaxkxkaxkaaxkaaaxxkaaa",
        "abcabcadaadada",
        "bbfefeefbbfebbfeeefe",
        "babeabeabebabbbabeee",
        "aaaadbbbbadaaadbbdbbadbaadbbdbbbbaadaadbaadbbadbbb"
    };

    vector< vector<int> > answers {
        {0,2},
        {3,0,1}
    };
    int i = 0;

    // TODO: add return type and paramters.
    clock_t tstart = clock();
    auto res = movesToStamp::Solution().movesToStamp(stamp[i], target[i]);
    cout << clock() - tstart << endl;
    cout << res << endl;
    return 0;
}
//*/
