//
//  amazonBasicsHighestProfit.cpp
//  leetcode
//
//  Created by Song Ding on 11/11/20.
//  Copyright © 2020 Song Ding. All rights reserved.
//

#include "common.h"
using namespace std;

namespace amazonBasicsHighestProfit {
/*
// TODO: copy problem statement here
 Amazon Basics has several suppliers for its products. For each of the products, the stock is represented by a list of a number of items for each supplier. As items are purchased, the supplier raises the price by 1 per item purchased. Let's assume Amazon's profit on any single item is the same as the number of items the supplier has left. For example, if a supplier has 4 items, Amazon's profit on the first item sold is 4, then 3, then 2 and the profit of the last one is 1.

 Given a list where each value in the list is the number of the item at a given supplier and also given the number of items to be ordered, write an algorithm to find the highest profit that can be generated for the given product.

 Input
 The input to the function/method consists on three arguments:

 numSuppliers, an integer representing the number of suppliers;

 inventory, a list of long integers representing the value of the item at a given supplier;

 order, a long integer representing the number of items to be ordered.

 Output

 Return a long integer representing the highest profit that can be generated for the given product.

 Constraints

 1 <= numSuppliers <= 10^5

 1 <= inventory[i] <= 10 ^ 5

 0 <= i < numSuppliers

 1 <= orders <= sum of inventory

 Example1

 Input:

 numSuppliers = 2

 inventory = [3,5]

 order = 6

 Output:

 19

 Explanation: There are two suppliers, one with inventory 3 and the other with inventory 5, and 6 items were ordered The maximum profit is made by selling 1 for 5, 1 for 4, and 2 at 3 and 2 at 2 units profit. The two suppliers are left with a unit of product each. The maximum profit generated is 5 + 4 + 2*3 + 2*2 = 19.

 5  4  3  2  1 (Price)

                    
                   
 1  2  4  6     (Count)

 Maximizing profit: Green represents units purchased by the marketer, Red squares are products retained by the suppliers. Blue squares are empty.

  

 Example2

 Input:

 numSuppliers = 2

 inventory = [2,5]

 order = 4

 Output:

 14

                    
                   
 Inventory available from two suppliers is = [2,5] and the quantity ordered is 4. All items can be purchased from the second supplier to generate 5 + 4 + 3 + 2 = 14. The same result is possible purchasing one unit from the first supplier instead.

  

 Example3

 Input:

 numSuppliers = 5

 inventory = [2, 8, 4, 10, 6]

 order = 20

 Output:

 110

                                        
                                        
                                        
                                        
                                        
 There are 5 sellers with inventory = [2, 8, 4, 10, 6] and Items ordered is 20. The marketer will purchase items from any supplier until they have only 2 units left. The maximum profit generated is 10 + 9 + 2*8 + 2*7 + 3*6 + 3*5+ 4*4 + 4*3 = 10 + 9 + 16 + 14 + 18 + 15 + 16 + 12 = 110
*/
class Solution {
public:
    // TODO: copy function signature here
    int amazonBasicsHighestProfit(vector<int>& suppliers, int order) {
        int res = 0;
        map<int, int> cnt;
        cnt[0] = 0;
        for (auto s : suppliers) {
            ++cnt[s];
        }
        int tosold = order;
        while (tosold) {
            auto it = rbegin(cnt);
            int largest = it->first;
            int largestCnt = it->second;
            int t = tosold / largestCnt;
            if (t < 1 || tosold == largestCnt) {
                res += largest * tosold;
                break;
            }
            ++it;
            int gap = min(t, largest - it->first);
            res += largestCnt * gap * (largest+largest-gap+1)/2;
            tosold -= gap * largestCnt;
            cnt.erase(largest);
            cnt[largest-gap] += largestCnt;
        }
        return res;
    }
private:
};
}

/*
int main() {
    // TODO: define parameter type here
    struct param {
        vector<int> suppliers;
        int order;
    };
    // TODO: prepare parameters here
    vector<struct param> params {
        {{2,5},4},
        {{2, 8, 4, 10, 6},20},
    };
    // TODO: provide expected results here
    vector<int> answers {
        14,
        110,
    };
    
    for (auto& dp : params) {
        cout << endl;
        clock_t tstart = clock();
        auto res = amazonBasicsHighestProfit::Solution().amazonBasicsHighestProfit(dp.suppliers, dp.order);
        cout << res << endl;
        cout << clock() - tstart << endl;
    }

    return 0;
}
//*/
