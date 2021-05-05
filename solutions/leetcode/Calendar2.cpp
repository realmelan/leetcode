//
//  Calendar2.cpp
//  leetcode
//
//  Created by  Song Ding on 12/16/17.
//  Copyright © 2017 Song Ding. All rights reserved.
//

#include "common.h"

using namespace std;

namespace myCalendarTwo {
    class MyCalendarTwo {
    public:
        /**
         Keep a map of intervals and the number of occurences
         for each interval.
         Note: the intervals have to be non-overlap.
         if an overlap is found and the event is allowed to book
         then split the intervals to make them non-overlap.
         */
        MyCalendarTwo() {
            
        }
        
        bool book(int start, int end) {
            if (_intervals.empty()) {
                _intervals.insert(make_pair(start, make_pair(end, 1)));
                return true;
            }
            
            auto it = lower_bound(_intervals.begin(), _intervals.end(), start, [](const pair<int, pair<int, int>>& a, int val){
                return a.first < val;
            });
            if (it == _intervals.end()) {
                auto rit = _intervals.rbegin();
                
                if (start >= rit->second.first) {
                    _intervals.insert(make_pair(start, make_pair(end, 1)));
                    return true;
                } else {
                    int rep = rit->second.second;
                    if (rep >= 2) {
                        return false;
                    }
                    int bend = rit->second.first;
                    
                    // update the interval before
                    rit->second.first = start;
                    
                    // add a new interval from (start, bend)
                    _intervals.insert(make_pair(start, make_pair(bend, rep + 1)));
                    // add the last half of the new interval
                    if (bend < end) {
                        _intervals.insert(make_pair(bend, make_pair(end, 1)));
                    }
                    return true;
                }
            } else {
                // first check whether the interval can be booked.
                auto cit = it;
                if (it != _intervals.begin()) {
                    auto bit = it;
                    --bit;
                    if (bit->second.first > start && bit->second.second >= 2) {
                        return false;
                    }
                }
                while (cit != _intervals.end() && end > cit->first) {
                    if (cit->second.second >= 2) {
                        return false;
                    }
                    ++cit;
                }
                
                int nstart = start;
                if (it != _intervals.begin()) {
                    auto bit = it;
                    --bit;
                    if (start < bit->second.first) {
                        nstart = bit->second.first;
                        int rep = bit->second.second;
                        bit->second.first = start;
                        
                        if (end < nstart) {
                            _intervals.insert(make_pair(start, make_pair(end, rep + 1)));
                            _intervals.insert(make_pair(end, make_pair(nstart, rep)));
                            return true;
                        } else {
                            _intervals.insert(make_pair(start, make_pair(nstart, rep + 1)));
                        }
                    }
                }
                
                while (it != _intervals.end() && end >= it->second.first) {
                    if (nstart < it->first) {
                        _intervals.insert(make_pair(nstart, make_pair(it->first, 1)));
                        nstart = it->first;
                    }
                    
                    ++(it->second.second);
                    nstart = it->second.first;
                    ++it;
                }
                if (it == _intervals.end() || end <= it->first) {
                    _intervals.insert(make_pair(nstart, make_pair(end, 1)));
                } else {
                    if (nstart < it->first) {
                        _intervals.insert(make_pair(nstart, make_pair(it->first, 1)));
                        nstart = it->first;
                    }
                    
                    _intervals.insert(make_pair(end, make_pair(it->second.first, it->second.second)));
                    it->second.first = end;
                    ++(it->second.second);
                }
                return true;
            }
        }
    private:
        map<int, pair<int, int>> _intervals;
    };
    
    /**
     * Your MyCalendarTwo object will be instantiated and called as such:
     * MyCalendarTwo obj = new MyCalendarTwo();
     * bool param_1 = obj.book(start,end);
     */
}

/*
using namespace myCalendarTwo;
int main() {
    MyCalendarTwo obj;
    vector<pair<int,int>> params{
        {89,100},{30,43},{92,100},{31,49},{59,76},{60,73},{31,49},{80,99},{48,60},{36,52},{67,82},{96,100},{22,35},{18,32},{9,24},{11,27},{94,100},{12,22},{61,74},{3,20},{14,28},{27,37},{5,20},{1,11},{96,100},{33,44},{90,100},{40,54},{23,35},{18,32},{78,89},{56,66},{83,93},{45,59},{40,59},{94,100},{99,100},{86,96},{43,61},{29,45},{21,36},{13,31},{17,30},{16,30},{80,94},{38,50},{15,30},{62,79},{25,39},{73,85},{39,56},{80,97},{42,57},{32,47},{59,78},{35,53},{56,74},{75,85},{39,54},{63,82}
    };
    for (const auto& p : params) {
        cout << obj.book(p.first, p.second) << endl;
    }
    return 0;
}
 */
