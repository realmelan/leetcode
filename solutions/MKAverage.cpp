//
//  MKAverage.cpp
//  leetcode
//
//  Created by Song Ding on 4/14/21.
//  Copyright © 2021 Song Ding. All rights reserved.
//

#include "common.h"
using namespace std;

namespace MKAverage {
/*
// TODO: copy problem statement here

*/
class MKAverage {
public:
    MKAverage(int m, int k) : sum(0), m(m), k(k) {
        
    }
    
    void addElement(int num) {
        int toRemove = 0;
        if (arr.size() >= m) {
            toRemove = arr[arr.size()-m];
        }
        arr.push_back(num);
        if (toRemove) {
            int slast = *rbegin(small);
            int lfirst = *begin(large);
            if (toRemove <= slast) {
                small.erase(small.find(toRemove));
                // adjust
                int mfirst = *begin(mid);
                small.insert(mfirst);
                mid.erase(mid.find(mfirst));
                sum -= mfirst;
            } else if (toRemove >= lfirst) {
                large.erase(large.find(toRemove));
                // adjust
                int mlast = *rbegin(mid);
                large.insert(mlast);
                mid.erase(mid.find(mlast));
                sum -= mlast;
            } else {
                mid.erase(mid.find(toRemove));
                sum -= toRemove;
            }
        }
        small.insert(num);
        if (small.size() <= k) {
            return;
        }
        int slast = *rbegin(small);
        small.erase(small.find(slast));
        mid.insert(slast);
        sum += slast;
        int mlast = *rbegin(mid);
        if (large.size() < k || mlast > *begin(large)) {
            sum -= mlast;
            mid.erase(mid.find(mlast));
            large.insert(mlast);
            if (large.size() > k) {
                int lfirst = *begin(large);
                large.erase(large.find(lfirst));
                sum += lfirst;
                mid.insert(lfirst);
            }
        }
    }
    
    int calculateMKAverage() {
        if (arr.size() >= m) {
            return sum/(m-k*2);
        }
        return -1;
    }
private:
    vector<int> arr;
    multiset<int> small, mid, large;
    int sum, m, k;
};
}

/*
int main() {
    // TODO: define parameter type here
    struct param {
    };
    // TODO: prepare parameters here
    vector<struct param> params {
    };
    // TODO: provide expected results here
    vector<int> answers {
    };
    
    int m = 3, k = 1;
    MKAverage::MKAverage obj(m, k);
    obj.addElement(3);
    obj.addElement(1);
    cout << obj.calculateMKAverage() << endl;
    obj.addElement(10);
    cout << obj.calculateMKAverage() << endl;
    obj.addElement(5);
    obj.addElement(5);
    obj.addElement(5);
    cout << obj.calculateMKAverage() << endl;

    return 0;
}
//*/
