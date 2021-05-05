// ExamRoom.cpp
// leetcode
//
// Created by  Song Ding on 9/6/18.
// Copyright © 2018 Song Ding. All rights reserved.
//
#include "common.h"
using namespace std;

namespace ExamRoom {

/**
 * Use a priority queue(use set to deduplicate) to store all pairs of seats, with the top having
 * the largest distance and a set to record which seats are taken.
 *
 * When seat() is called, get the top pair. First check it is a valid pair
 * if not, keep pop() till a valid pair. Split the pair into one or two
 * valid pairs and add them to the queue.
 *
 * When leave(p) is called, find in the taken seats the nearest two seats, and
 * a new pair is formed, and inserted into priority queue. Leave the old pairs
 * in the queue. However, remove p from taken seats.
 *
 * Special attention to the first and last seats. When the first or the last seat
 * is absent, add a pair with the middle point being the first or last.
 */
class ExamRoom {
public:
    // https://leetcode.com/problems/exam-room/discuss/141583/C%2B%2B-O(logn)-seat()-and-O(logn)-leave()-with-STL-set-and-map
    ExamRoom(int N) {
        Spare::N = N;
        seats.emplace(0, N-1);
        l2r[0] = N-1;
        r2l[N-1] = 0;
    }
    
    int seat() {
        Spare sp = *seats.begin();
        seats.erase(seats.begin());
        l2r.erase(sp.l);
        r2l.erase(sp.r);
        
        int p = sp.getPosition();
        if (sp.l <= p-1) {
            seats.emplace(sp.l, p-1);
            l2r[sp.l] = p-1;
            r2l[p-1] = sp.l;
        }
        if (p+1 <= sp.r) {
            seats.emplace(p+1, sp.r);
            r2l[sp.r] = p+1;
            l2r[p+1] = sp.r;
        }
        return p;
    }
    
    int leave(int p) {
        int l = p, r = p;
        if (r2l.count(p-1)) {
            l = r2l[p-1];
            seats.erase(Spare(l,p-1));
            r2l.erase(p-1);
        }
        if (l2r.count(p+1)) {
            r = l2r[p+1];
            seats.erase(Spare(p+1, r));
            l2r.erase(p+1);
        }
        
        seats.emplace(l, r);
        l2r[l] = r;
        r2l[r] = l;
        return -1;
    }
private:
    struct Spare {
        static int N;
        int l;
        int r;
        Spare(int l, int r) : l(l), r(r) {}
        int getDistance() const {
            if (l == 0) {
                return r;
            } else if (r == N-1) {
                return N-1-l;
            } else {
                return (r-l)/2;
            }
        }
        int getPosition() const {
            if (l == 0) {
                return 0;
            } else if (r == N-1) {
                return N-1;
            } else {
                return l + (r-l)/2;
            }
        }
        bool operator<(const Spare& a) const {
            int d = getDistance();
            int ad = a.getDistance();
            if (d != ad) {
                return d > ad;
            } else {
                return l < a.l;
            }
        }
    };
    
    set<Spare> seats;
    unordered_map<int,int> l2r, r2l;
#ifdef BAD
public:
    ExamRoom(int N) {
        n = N;
        s2l[-n*2+2] = n*4-5;
        l2s[n*4-5].insert(-n*2+2);
    }
    
    int seat() {
        auto it = l2s.rbegin();
        auto l = it->first;
        auto start = *(it->second.begin());
        auto res = start + (l+1)/2;
        auto l1 = (l-1)/2, l2 = l / 2;
        
        auto it2 = l2s.rbegin();
        ++it2;
        if (l%2 == 0 && it2 != l2s.rend() && it2->first == l-1) {
            int start2 = *(it2->second.begin());
            if (start2 < start) {
                start = start2;
                res = start2 + l1+1;
                l = l-1;
                l2 = l1;
                it = it2;
            }
        }
        // consider when res = n-1 or 0
        s2l.erase(start);
        it->second.erase(start);
        if (it->second.empty()) {
            l2s.erase(l);
        }
        if (start >= 0) {
            l2s[l1].insert(start);
            s2l[start] = l1;
        }
        if (res == n-1) {
            l2 = 0;
        }
        l2s[l2].insert(res);
        s2l[res] = l2;
        
        return res;
    }
    
    int leave(int p) {
        auto it = s2l.find(p);
        auto l = it->second;
        if (it == s2l.begin()) { // p == 0
            s2l[-l-1] = l*2+1;
            l2s[l*2+1].insert(-l-1);
        } else {
            auto it2 = it;
            --it2;
            auto prev = it2->first;
            auto lprev = it2->second;
            s2l.erase(prev);
            l2s[lprev].erase(prev);
            if (l2s[lprev].empty()) {
                l2s.erase(lprev);
            }
            if (prev < 0) {
                if (p == n-1) { // no seats taken, back to original state
                    s2l[-n*2+2] = n*4-5;
                    l2s[n*4-5].insert(-n*2+2);
                } else {
                    s2l[prev-l-1] = lprev + l*2+2;
                    l2s[lprev+l*2+2].insert(prev-l-1);
                }
            } else if (p == n-1) {
                s2l[prev] = lprev*2+1;
                l2s[lprev*2+1].insert(prev);
            } else {
                s2l[prev] = lprev + l + 1;
                l2s[lprev+l+1].insert(prev);
            }
        }
        s2l.erase(p);
        l2s[l].erase(p);
        if (l2s[l].empty()) {
            l2s.erase(l);
        }
        return -1;
    }
private:
    long n;
    // # of empty seats following => list of seats taken which are followed by # of empty seats
    map<long, set<long>> l2s;
    // seat => # of empty seats following
    map<long, long> s2l;
#endif // BAD
public:
#ifdef INTERVAL_SET
    ExamRoom(int N)
    : _cap(N-1) {
    }
        
    int seat() {
        if (_seats.empty()) {
            _seats.insert(0);
            return 0;
        } else {
            int res = -1;
            int dist = -1;
            // check the first point
            int first = *_seats.begin();
            if (first > 0) {
                res = 0;
                dist = first;
            }
            
            // check the intervals in dist
            pair<int,int> largest{INT_MIN, INT_MIN};
            if (_dist.size()) {
                largest = *_dist.rbegin();
                if (largest.second - largest.first > 1) {
                    int t = (largest.second - largest.first) / 2;
                    if (t > dist) {
                        dist = t;
                        res = (largest.first + largest.second) / 2;
                    }
                }
            }
            
            // check the last point
            int last = *_seats.rbegin();
            if (last < _cap && dist < _cap - last) {
                res = _cap;
                dist = _cap - last;
            }
            
            if (res == 0) {
                _dist.insert(make_pair(res, first));
            } else if (res == _cap) {
                _dist.insert(make_pair(last, res));
            } else {
                _dist.erase(largest);
                _dist.insert(make_pair(largest.first, res));
                _dist.insert(make_pair(res, largest.second));
            }
            _seats.insert(res);
            return res;
        }
    }
        
    void leave(int p) {
        if (_seats.size() == 1) {
            _seats.clear();
            return;
        }
        
        int first = *_seats.begin();
        int last = *_seats.rbegin();
        if (p == first) {
            auto it = _seats.begin();
            ++it;
            _dist.erase(make_pair(p, *it));
        } else if (p == last) {
            auto it = _seats.rbegin();
            ++it;
            _dist.erase(make_pair(*it, p));
        } else {
            auto it = _seats.find(p);
            auto after = it;
            ++after;
            auto before = it;
            --before;
            _dist.erase(make_pair(*before, p));
            _dist.erase(make_pair(p, *after));
            _dist.insert(make_pair(*before, *after));
        }
        
        _seats.erase(p);
        
    }
private:
    struct DistCompare {
        bool operator()(const pair<int,int>& a, const pair<int,int>& b) {
            int dista = (a.second - a.first) / 2;
            int distb = (b.second - b.first) / 2;
            if (dista > distb) {
                return false;
            } else if (dista < distb) {
                return true;
            } else {
                return a.first > b.first;
            }
        }
    };
    //
    // all intervals, excluding the start point and the end point
    //
    set<pair<int,int>, DistCompare> _dist;
    set<int> _seats;
    const int _cap;
#endif // LINEAR
};

}
int ExamRoom::ExamRoom::Spare::N = 0;

/*/
int main() {
    // TODO: prepare parameters here
    if (1)
    {
    int N = 10;
    ExamRoom::ExamRoom er(10);
    // TODO: add return type and paramters.
    clock_t start = clock();
    cout << er.seat() << ","
        << er.seat() << ","
        << er.seat() << ","
        << er.leave(0) << ";"
        << er.leave(4) << ";"
        << er.seat() << ","
        << er.seat() << ","
        << er.seat() << ","
        << er.seat() << ","
        << er.seat() << ","
        << er.seat() << ","
        << er.seat() << ","
        << er.seat() << ","
        << er.seat() << ","
        << er.leave(0) << endl;
    cout << clock() - start << endl;
        //[null,0,9,4,null,null,0,4,2,6,1,3,5,7,8,null]
    }
    
    if (0)
    {
        vector<string> cmds {"ExamRoom","seat","seat","seat","leave","leave","seat","seat","seat","seat","seat","seat","seat"};
        vector<vector<int>> params {{8},{},{},{},{0},{7},{},{},{},{},{},{},{}};
        
        ExamRoom::ExamRoom er(params[0][0]);
        for (int i = 1; i < cmds.size(); ++i) {
            if (cmds[i] == "seat") {
                cout << er.seat() << endl;
            } else {
                er.leave(params[i][0]);
            }
        }
    }
    return 0;
}
//*/
