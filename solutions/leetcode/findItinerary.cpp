//
//  findItinerary.cpp
//  leetcode
//
//  Created by  Song Ding on 1/4/18.
//  Copyright © 2018 Song Ding. All rights reserved.
//

#include "common.h"
using namespace std;

namespace findItinerary {
    class Solution {
    public:
        vector<string> findItinerary_dfs(vector<pair<string, string>> tickets) {
            unordered_map<string, multiset<string>> conns;
            for (auto& p : tickets) {
                conns[p.first].insert(p.second);
            }
            vector<string> res;
            dfs("JFK", conns, res);
            return vector<string>(res.rbegin(), res.rend());
        }
        // adding airport at the end of visiting will make adding cycle easier:
        // no inserting a cycle into the path.
        void dfs(const string& ap, unordered_map<string, multiset<string>>& conns, vector<string>& res) {
            if (conns[ap].size()) {
                auto it = conns[ap].begin();
                auto next = *it;
                conns[ap].erase(it);
                dfs(next, conns, res);
            }
            if (conns[ap].size()) {
                auto it = conns[ap].begin();
                auto next = *it;
                conns[ap].erase(it);
                dfs(next, conns, res);
            }
            res.push_back(ap);
        }
        /**
         First of all, find the initial depart airport, by counting number of
         appearances for each depart airport. Odd number of appearance signals
         initial depart airport, and choose the smaller ticket if multiple tickets
         for the initial depart airport.
         
         Use multimap
         */
        vector<string> findItinerary(vector<pair<string, string>> tickets) {
            vector<string> res;
            if (tickets.empty()) {
                return res;
            }
            sort(tickets.begin(), tickets.end(), [](const pair<string,string>& a, const pair<string,string>& b){
                if (a.first < b.first) {
                    return true;
                } else if (a.first > b.first) {
                    return false;
                } else {
                    return a.second < b.second;
                }
            });
            multimap<string, string> fromTo;
            map<string, int> counts;
            for (const auto& p : tickets) {
                fromTo.insert(make_pair(p.first, p.second));
                ++counts[p.first];
                --counts[p.second];
            }
            
            string depart;
            string last;
            for (const auto& p : counts) {
                if (p.second == 1) {
                    depart = p.first;
                } else if (p.second == -1) {
                    last = p.first;
                }
            }
            if (depart.empty()) {
                depart = fromTo.begin()->first;
            }
            
            res.push_back(depart);
            while (fromTo.size()) {
                auto it = fromTo.find(depart);
                if (it == fromTo.end()) {
                    break;
                }
                depart = it->second;
                res.push_back(depart);
                fromTo.erase(it);
            }
            
            // if fromTo is not empty by now
            // then there are only circles left
            // for each circle find a valid position in res to insert
            // a valid position should be the close to the tail of res
            while (fromTo.size()) {
                string depart;
                auto iit = res.end();
                for (auto it = res.begin(); it != res.end(); ++it) {
                    if (fromTo.count(*it)) {
                        depart = *it;
                        iit = it;
                    }
                }
                vector<string> tres;
                while (fromTo.size()) {
                    auto it = fromTo.find(depart);
                    if (it == fromTo.end()) {
                        break;
                    }
                    depart = it->second;
                    tres.push_back(depart);
                    fromTo.erase(it);
                }
                res.insert(iit + 1, tres.begin(), tres.end());
            }
            
            return res;
        }
    };
}

/*
int main() {
    vector<pair<string, string>> tickets {
        {"EZE","TIA"},{"EZE","HBA"},{"AXA","TIA"},{"JFK","AXA"},{"ANU","JFK"},{"ADL","ANU"},{"TIA","AUA"},{"ANU","AUA"},{"ADL","EZE"},{"ADL","EZE"},{"EZE","ADL"},{"AXA","EZE"},{"AUA","AXA"},{"JFK","AXA"},{"AXA","AUA"},{"AUA","ADL"},{"ANU","EZE"},{"TIA","ADL"},{"EZE","ANU"},{"AUA","ANU"}
        //{"JFK","ATL"},{"ATL","SFO"},{"SFO","AMD"},{"AMD","ATL"},{"ATL","XTS"},
        //{"JFK","ATL"},{"ATL","JFK"}
        //{"JFK","SFO"},{"JFK","ATL"},{"SFO","JFK"},{"ATL","TMN"}
    };
    vector<string> res = findItinerary::Solution().findItinerary_dfs(tickets);
    for (const auto& s : res) {
        cout << s << ",";
    }
    cout << endl;
    return 0;
}
// */
