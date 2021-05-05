//
//  intersectionSizeTwo.cpp
//  leetcode
//
//  Created by  Song Ding on 2/20/18.
//  Copyright © 2018 Song Ding. All rights reserved.
//

#include "common.h"
using namespace std;

namespace intersectionSizeTwo {
    class Solution {
    public:
        /**
         Intuition:
         intervals of the same ending point, who has latest opening point would cover the other
         intervals.
         
         sort the intervals by the ending point in increasing order, and then the opening
         point in descreasing order.
         
         when a new ending point is met, check its corresponding opening point:
         1, if opening point is > current ending point, add new ending point and the point
         before it to result set
         2, otherwise, add new ending point to result set, as the new opening point is already
         covered by previous ending point.
         */
        int intersectionSizeTwo(vector<vector<int>>& intervals) {
            int n = intervals.size();
            sort(intervals.begin(), intervals.end(), [](const vector<int>& a, const vector<int>& b){
                return a[1] != b[1] ? a[1] < b[1] : a[0] > b[0];
            });
            int res = 0;
            int opening = -1, ending = -1;
            for (int i = 0; i < n; ++i) {
                const auto& v = intervals[i];
                if (v[0] > ending) {
                    res += 2; // add v[1]-1, v[1]
                    opening = v[1] - 1;
                    ending = v[1];
                } else if (v[0] > opening){
                    ++res; // add v[1]
                    opening = ending;
                    ending = v[1];
                }
            }
            return res;
        }
        /**
         Sort the intervals based on first point and then second point,
         and then iterate through the points, and add 1 for openning point
         and minus 1 for ending point, into a multimap.
         
         Now, go through the map, whenever an openning point is encountered,
         keep it, and replace it if the next point is also an openning point.
         If an ending point is encountered, add current openning point and the
         ending point into result set.
         
         Keep a list of openning points so that when an ending point is
         found, remove the other corresponding ending points for the list of
         openning points.
         
         */
        int intersectionSizeTwo_complicated(vector<vector<int>>& intervals) {
            vector<vector<int>>& intv = intervals;
            sort(intv.begin(), intv.end(), [](const vector<int>& a, const vector<int>& b){
                if (a[0] < b[0]) {
                    return true;
                } else if (a[0] > b[0]) {
                    return false;
                } else {
                    return a[1] < b[1];
                }
            });
            
            multimap<int, int> counts;
            map<int, vector<int>> endpoints;
            for (const auto& i : intv) {
                counts.insert(make_pair(i[0], 1));
                counts.insert(make_pair(i[1], -1));
                
                endpoints[i[0]].push_back(i[1]);
            }
            
            set<int> res;
            map<int, int> pendingEps;
            map<int, int> currentEps;
            set<int> coveredOpens;
            int lastOpen = -1;
            for (const auto& p : counts) {
                if (p.second == 0) {
                    continue;
                } else if (p.second == 1) {
                    if (p.first != lastOpen) {
                        if (lastOpen != -1) {
                            coveredOpens.insert(lastOpen);
                        }
                    }
                    lastOpen = p.first;
                } else {
                    int prevCovered = 0;
                    set<int> toRemove;
                    for (auto open : coveredOpens) {
                        if (res.find(open) != res.end()) {
                            ++prevCovered;
                            const vector<int>& eps = endpoints[open];
                            for (auto ep : eps) {
                                auto it = counts.lower_bound(ep);
                                while (it->first == ep && it->second == 0) {
                                    ++it;
                                }
                                it->second = 0;
                            }
                            toRemove.insert(open);
                        }
                    }
                    for (auto i : toRemove) {
                        coveredOpens.erase(i);
                    }
                    
                    if (p.second == 0) {
                        res.insert(lastOpen);
                        continue;
                    } else {
                        res.insert(lastOpen);
                        coveredOpens.insert(lastOpen);
                        // update the endpoints for coveredOpenEps
                        for (auto open : coveredOpens) {
                            const vector<int>& eps = endpoints[open];
                            for (auto ep : eps) {
                                auto it = counts.lower_bound(ep);
                                while (it->first == ep && it->second == 0) {
                                    ++it;
                                }
                                it->second = 0;
                            }
                        }
                        cout << "add " << lastOpen << ", " << p.first << endl;
                        res.insert(p.first);
                        lastOpen = -1;
                        coveredOpens.clear();
                    }
                }
            }
            
            return res.size();
            
        }
    };
}
/*
int main() {
    vector<vector<int>> intervals {
        //{1,3},{4,9},{0,10},{6,7},{1,2},{0,6},{7,9},{0,1},{2,5},{6,8}
        //{1,3},{1,4},{2,5},{3,5} //=> 3
        {1,2},{2,3},{2,4},{4,5} //=>5
    };
    //vector<vector<int>> intervals {
    //    {1,15},{0,8},{13,14}
    //};
    cout << intersectionSizeTwo::Solution().intersectionSizeTwo(intervals) << endl;
    return 0;
}
//*/
