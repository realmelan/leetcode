// findSecretWord.cpp
// leetcode
//
// Created by  Song Ding on 10/21/18.
// Copyright © 2018 Song Ding. All rights reserved.
//
#include "common.h"
using namespace std;

namespace findSecretWord {
    
class Master {
public:
    Master(string secret)
    : _secret(secret) {}
    
    
    int guess(string word) {
        int n = _secret.size();
        int res = 0;
        for (int i = 0; i < n; ++i) {
            if (word[i] == _secret[i]) {
                ++res;
            }
        }
        return res;
    }
private:
    string _secret;
};

class Solution {
public:
    void findSecretWord2(vector<string>& wordlist, Master& master) {
        int n = wordlist.size();
        vector<int> candlist(n);
        iota(begin(candlist), end(candlist), 0);
        int g = 0;
        while (candlist.size() > 1) {
            int n = candlist.size();
            // find a word that connects with most words
            vector<int> disconnect(n,0);
            for (int i = 0; i < n; ++i) {
                for (int j = 0; j < n; ++j) {
                    disconnect[i] += match(wordlist[candlist[i]], wordlist[candlist[j]]) == 0;
                }
            }
            int ti = 0;
            for (int i = 1; i < n; ++i) {
                if (disconnect[i] < disconnect[ti]) {
                    ti = i;
                }
            }
            int fw = candlist[ti];
            int d = master.guess(wordlist[fw]);
            ++g;
            if (d == 6) {
                return;
            }
            // find a set of wordlist that diff by d positions
            vector<int> nclist;
                // find a set of wordlist that diff by d positions
                for (int i = 0; i < candlist.size(); ++i) {
                    int wi = candlist[i];
                    if (match(wordlist[wi], wordlist[fw]) == d) {
                        nclist.push_back(wi);
                    }
                }
            candlist.swap(nclist);
            cout << g << "," << candlist.size() << endl;
        }
        master.guess(wordlist[candlist[0]]);
        cout << g << "," << wordlist[candlist[0]] << endl;
    }
    /**
     * create a match matrix m, where m[i][j] = # of matches between
     * word[i] and word[j].
     *
     * Now, suppose we match a random word word[k] in master, and got
     * n matches. Then possible candidate have n matches with word[k].
     */
    void findSecretWord(vector<string>& wordlist, Master& master) {
        unordered_map<string, int> matches;
        int n = wordlist.size();
        for (int i = 0; i < n; ++i) {
            for (int j = i + 1; j < n; ++j) {
                int m = match(wordlist[i], wordlist[j]);
                matches[wordlist[i] + wordlist[j]] = m;
                matches[wordlist[j] + wordlist[i]] = m;
            }
        }
        
        set<string> current(wordlist.begin(), wordlist.end());
        int i = 0;
        int m = 0;
        while ((m = master.guess(*current.begin())) != 6) {
            ++i;
            string cw(*current.begin());
            set<string> next;
            for (const auto& w : current) {
                if (w != cw && matches[w + cw] == m) {
                    next.insert(w);
                }
            }
            current.swap(next);
        }
        cout << i + 1 << "," << *current.begin() << endl;
    }

private:
    int match(string w1, string w2) {
        int res = 0;
        for (int i = 0; i < w1.size(); ++i) {
            res += w1[i] == w2[i] ? 1 : 0;
        }
        return res;
    }
};

}

/*/
int main() {
    // TODO: prepare parameters here
    string secret = "cymplm";
    findSecretWord::Master master(secret);
    vector<string> wordlist {
        "eykdft","gjeixr","eksbjm","mxqhpk","tjplhf","ejgdra","npkysm","jsrsid","cymplm","vegdgt","jnhdvb","jdhlzb","sgrghh","jvydne","laxvnm","xbcliw","emnfcw","pyzdnq","vzqbuk","gznrnn","robxqx","oadnrt","kzwyuf","ahlfab","zawvdf","edhumz","gkgiml","wqqtla","csamxn","bisxbn","zwxbql","euzpol","mckltw","bbnpsg","ynqeqw","uwvqcg","hegrnc","rrqhbp","tpfmlh","wfgfbe","tpvftd","phspjr","apbhwb","yjihwh","zgspss","pesnwj","dchpxq","axduwd","ropxqf","gahkbq","yxudiu","dsvwry","ecfkxn","hmgflc","fdaowp","hrixpl","czkgyp","mmqfao","qkkqnz","lkzaxu","cngmyn","nmckcy","alpcyy","plcmts","proitu","tpzbok","vixjqn","suwhab","dqqkxg","ynatlx","wmbjxe","hynjdf","xtcavp","avjjjj","fmclkd","ngxcal","neyvpq","cwcdhi","cfanhh","ruvdsa","pvzfyx","hmdmtx","pepbsy","tgpnql","zhuqlj","tdrsfx","xxxyle","zqwazc","hsukcb","aqtdvn","zxbxps","wziidg","tsuxvr","florrj","rpuorf","jzckev","qecnsc","rrjdyh","zjtdaw","dknezk"
    };

    // TODO: add return type and paramters.
    clock_t tstart = clock();
    findSecretWord::Solution().findSecretWord2(wordlist, master);
    cout << clock() - tstart << endl;
    return 0;
}
//*/
