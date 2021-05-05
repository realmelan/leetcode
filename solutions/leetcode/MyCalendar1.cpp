//
//  MyCalendar1.cpp
//  leetcode
//
//  Created by  Song Ding on 11/28/17.
//  Copyright © 2017 Song Ding. All rights reserved.
//

#include "common.h"

using namespace std;

namespace MyCalendar1 {
    class MyCalendar {
    public:
        /**
         Using a map to store event, using start date as index,
         end date as value: since there is no overlap, each start date
         is unique.
         
         When book() is called, check the map to find two start dates,
         one of which is before, and the other after. Now, check whehther
         there is overlap. If no overlap, insert into hash map the new
         event.
         */
        MyCalendar() {
            
        }
        
        bool book(int start, int end) {
            auto it1 = booked.lower_bound(start);
            if (it1 == booked.end()) {
                auto rit = booked.rbegin();
                if (rit == booked.rend() || rit->second <= start) {
                    booked.insert(make_pair(start, end));
                    return true;
                }
                return false;
            } else if (end > it1->first) {
                return false;
            } else {
                if (it1 == booked.begin()) {
                    booked.insert(make_pair(start, end));
                    return true;
                } else {
                    auto it2 = prev(it1);
                    if (it2->second <= start) {
                        booked.insert(make_pair(start, end));
                        return true;
                    }
                    return false;
                }
            }
        }
    private:
        map<int, int> booked;
    };
}
/*
int main() {
    MyCalendar1::MyCalendar s;
    cout << s.book(47,50) << ","
        << s.book(33,41) << ","
    << s.book(39,45) << ","
    << s.book(33,42) << ","
    << endl;
    return 0;
}
*/
