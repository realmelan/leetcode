//
//  calcEquation.cpp
//  leetcode
//
//  Created by  Song Ding on 11/9/17.
//  Copyright © 2017 Song Ding. All rights reserved.
//

#include "common.h"

using namespace std;

namespace calcEquation {
    class Solution {
    public:
        /**
         cluster the variables, and assign relative values to
         variables in a cluster.
         */
        vector<double> calcEquation(vector<pair<string, string>> equations, vector<double>& values, vector<pair<string, string>> queries) {
            vector<double> res;
            int size = equations.size();
            if (size <= 0) {
                res.resize(queries.size(), -1);
                return res;
            }
            
            int done = 0;
            vector<map<string, double>> assigns;
            while (done < size) {
                map<string, double> assign;
                bool found = false;
                do {
                    found = false;
                    for (int i = 0; i < size; ++i) {
                        if (values[i] < 0) {
                            continue;
                        }
                        const string& a = equations[i].first;
                        const string& b = equations[i].second;
                        if (assign.empty()) {
                            double v = values[i];
                            assign[a] = v;
                            assign[b] = 1;
                            values[i] = -1;
                            found = true;
                            ++done;
                        } else {
                            auto ita = assign.find(a);
                            if (ita != assign.end()) {
                                double v = values[i];
                                assign[b] = ita->second / v;
                                values[i] = -1;
                                found = true;
                                ++done;
                            } else {
                                auto itb = assign.find(b);
                                if (itb != assign.end()) {
                                    double v = values[i];
                                    assign[a] = v * itb->second;
                                    values[i] = -1;
                                    found = true;
                                    ++done;
                                }
                            }
                        } // end assign not empty
                    } // end loop of equations
                } while (found);
                assigns.push_back(assign);
            }
            
            for (const auto& p : queries) {
                res.push_back(-1);
                for (const auto& assign : assigns) {
                    auto ita = assign.find(p.first);
                    auto itb = assign.find(p.second);
                    if (ita != assign.end() && itb != assign.end()) {
                        res.back() = ita->second / itb->second;
                        break;
                    } else if (ita != assign.end() || itb != assign.end()) {
                        break;
                    }
                }
            }
            return res;
        }
        
        vector<double> calcEquation2(vector<vector<string>>& equations, vector<double>& values, vector<vector<string>>& queries) {
            int n = equations.size();
            unordered_map<string, pair<string, double>> g;
            for (int i = 0; i < n; ++i) {
                auto [r1, m1] = find(equations[i][0], g);
                auto [r2, m2] = find(equations[i][1], g);
                if (r1 < r2) {
                    g[r2] = make_pair(r1, m1 / (values[i] * m2));
                } else if (r1 > r2) {
                    g[r1] = make_pair(r2, m2 * values[i] / m1);
                }
            }
            vector<double> res;
            for (auto& q : queries) {
                if (!g.count(q[0]) || !g.count(q[1])) {
                    res.push_back(-1);
                    continue;
                }
                auto [r1, m1] = find(q[0], g);
                auto [r2, m2] = find(q[1], g);
                if (r1 != r2) {
                    res.push_back(-1);
                } else {
                    res.push_back(m1/m2);
                }
            }
            return res;
        }
        pair<string, double> find(const string& a, unordered_map<string, pair<string, double>>& g) {
            auto it = g.find(a);
            if (it == g.end()) {
                //return make_pair(a, 1.0d);
                g[a] = make_pair(a, 1.0f);
            } else {
                if (it->second.first != a) {
                    double m1 = it->second.second;
                    auto [r, m] = find(it->second.first, g);
                    g[a] = make_pair(r, m * m1);
                }
            }
            return g[a];
        }
        
        vector<double> calcEquation3(vector<vector<string>>& equations, vector<double>& values, vector<vector<string>>& queries) {
            int n = equations.size();
            unordered_map<string, unordered_map<string, double>> m;
            for (int i = 0; i < n; ++i) {
                const string& a = equations[i][0];
                const string& b = equations[i][1];
                double v = values[i];
                
                m[a][b] = v;
                m[b][a] = 1/v;
            }
            unordered_map<string, pair<string, double>> ans;
            for (auto& eq : equations) {
                if (ans.count(eq[0]) || ans.count(eq[1])) {
                    continue;
                }
                const string& root = eq[1];
                ans[root] = make_pair(root, 1.0);
                queue<pair<string, double>> q;
                q.emplace(root, 1.0);
                while (q.size()) {
                    auto&[c,cv] = q.front(); q.pop();
                    for (auto& [s,sv] : m[c]) {
                        if (!ans.count(s)) {
                            ans[s] = make_pair(root, cv/sv);
                            q.emplace(s, cv/sv);
                        }
                    }
                }
            }
            
            vector<double> res;
            for (auto& q : queries) {
                if (!ans.count(q[0]) || !ans.count(q[1])) {
                    res.push_back(-1);
                } else {
                    auto [r1, m1] = ans[q[0]];
                    auto [r2, m2] = ans[q[1]];
                    if (r1 != r2) {
                        res.push_back(-1);
                    } else {
                        res.push_back(m1/m2);
                    }
                }
            }
            return res;
        }
    };
}

/*
int main() {
    vector<vector<string>> eqs{{"x1","x2"},{"x2","x3"},{"x3","x4"},{"x4","x5"}};
    vector<double> values{3.0,4.0,5.0,6.0};
    vector<vector<string>> queries{{"x1","x5"},{"x5","x2"},{"x2","x4"},{"x2","x2"},{"x2","x9"},{"x9","x9"}};
    vector<double> res = calcEquation::Solution().calcEquation3(eqs, values, queries);
    for (auto i : res) {
        cout << i << ",";
    }
    cout << endl;
    return 0;
}
//*/
