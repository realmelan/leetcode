//
//  graycode_rusky.cpp
//  leetcode
//
//  Created by  Song Ding on 3/8/18.
//  Copyright © 2018 Song Ding. All rights reserved.
//

#include "common.h"
using namespace std;

namespace husky {
    
    void gen_binary_gray_code() {
        int b = 0;
        int g = 0;
        do {
            g = b ^ b++ >> 1;
            cout << std::bitset<16>(g) << endl;
        } while (g < 10000);
    }
    
    void gen2_reverse(int);
    
    std::bitset<16> b2;
    void gen2(int n) {
        if (n == 0) {
            cout << b2 << endl;
            return;
        }
        
        b2[n] = 0;
        gen2(n - 1);
        b2[n] = 1;
        gen2_reverse(n - 1);
        
    }
    void gen2_reverse(int n) {
        if (n == 0) {
            cout << b2 << endl;
            return;
        }
        
        
        b2[n] = 1;
        gen2_reverse(n - 1);
        b2[n] = 0;
        gen2(n - 1);
    }
    
    std::bitset<4> b3(0);
    void gen3(int n) {
        if (n > 0) {
            gen3(n - 1); // keep previous bit
            //cout << b3 << endl;
            b3[n - 1] = b3[n - 1] ^ 1;
            cout << b3 << endl;
            gen3(n - 1);
        }
    }
}
/*
int main() {
    //husky::gen_binary_gray_code();
    cout << husky::b3 << endl;
    husky::gen3(4);
    //cout << husky::b3 << endl;
    //for (int i = 0; i < 6; ++i) {
    //    cout << husky::b3[i] << endl;
    //}
    return 0;
}
// */
