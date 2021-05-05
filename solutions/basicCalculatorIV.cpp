//
//  basicCalculatorIV.cpp
//  leetcode
//
//  Created by Song Ding on 12/1/20.
//  Copyright © 2020 Song Ding. All rights reserved.
//

#include "common.h"
using namespace std;

namespace basicCalculatorIV {
/*
// TODO: copy problem statement here
 770. Basic Calculator IV
 Hard

 83

 677

 Add to List

 Share
 Given an expression such as expression = "e + 8 - a + 5" and an evaluation map such as {"e": 1} (given in terms of evalvars = ["e"] and evalints = [1]), return a list of tokens representing the simplified expression, such as ["-1*a","14"]

 An expression alternates chunks and symbols, with a space separating each chunk and symbol.
 A chunk is either an expression in parentheses, a variable, or a non-negative integer.
 A variable is a string of lowercase letters (not including digits.) Note that variables can be multiple letters, and note that variables never have a leading coefficient or unary operator like "2x" or "-x".
 Expressions are evaluated in the usual order: brackets first, then multiplication, then addition and subtraction. For example, expression = "1 + 2 * 3" has an answer of ["7"].

 The format of the output is as follows:

 For each term of free variables with non-zero coefficient, we write the free variables within a term in sorted order lexicographically. For example, we would never write a term like "b*a*c", only "a*b*c".
 Terms have degree equal to the number of free variables being multiplied, counting multiplicity. (For example, "a*a*b*c" has degree 4.) We write the largest degree terms of our answer first, breaking ties by lexicographic order ignoring the leading coefficient of the term.
 The leading coefficient of the term is placed directly to the left with an asterisk separating it from the variables (if they exist.)  A leading coefficient of 1 is still printed.
 An example of a well formatted answer is ["-2*a*a*a", "3*a*a*b", "3*b*b", "4*a", "5*c", "-6"]
 Terms (including constant terms) with coefficient 0 are not included.  For example, an expression of "0" has an output of [].
 Examples:

 Input: expression = "e + 8 - a + 5", evalvars = ["e"], evalints = [1]
 Output: ["-1*a","14"]

 Input: expression = "e - 8 + temperature - pressure",
 evalvars = ["e", "temperature"], evalints = [1, 12]
 Output: ["-1*pressure","5"]

 Input: expression = "(e + 8) * (e - 8)", evalvars = [], evalints = []
 Output: ["1*e*e","-64"]

 Input: expression = "7 - 7", evalvars = [], evalints = []
 Output: []

 Input: expression = "a * b * c + b * a * c * 4", evalvars = [], evalints = []
 Output: ["5*a*b*c"]

 Input: expression = "((a - b) * (b - c) + (c - a)) * ((a - b) + (b - c) * (c - a))",
 evalvars = [], evalints = []
 Output: ["-1*a*a*b*b","2*a*a*b*c","-1*a*a*c*c","1*a*b*b*b","-1*a*b*b*c","-1*a*b*c*c","1*a*c*c*c","-1*b*b*b*c","2*b*b*c*c","-1*b*c*c*c","2*a*a*b","-2*a*a*c","-2*a*b*b","2*a*c*c","1*b*b*b","-1*b*b*c","1*b*c*c","-1*c*c*c","-1*a*a","1*a*b","1*a*c","-1*b*c"]
 Note:

 expression will have length in range [1, 250].
 evalvars, evalints will have equal lengths in range [0, 100].
*/

struct TermCompare {
    bool operator()(const multiset<string>& a, const multiset<string>& b) const {
        if (a.size() != b.size()) {
            return a.size() > b.size();
        } else {
            return a < b;
        }
    };
};
typedef multiset<string> Term;
typedef map<Term, int, TermCompare> Expr;
Expr operator*(const Expr& a, const Expr& b) {
    Expr res;
    for (auto& p1 : a) {
        for (auto& p2 : b) {
            Term c(p1.first);
            c.insert(begin(p2.first), end(p2.first));
            res[c] += p1.second * p2.second;
        }
    }
    return res;
};
Expr operator+(const Expr& a, const Expr& b) {
    Expr res;
    for (auto& p : a) {
        res[p.first] = p.second;
    }
    for (auto& p : b) {
        res[p.first] += p.second;
    }
    return res;
};
Expr operator-(const Expr& a, const Expr& b) {
    Expr res;
    for (auto& p : a) {
        res[p.first] = p.second;
    }
    for (auto& p : b) {
        res[p.first] -= p.second;
    }
    return res;
};
class Solution {
public:
    // TODO: copy function signature here
    vector<string> basicCalculatorIV(string expression, vector<string>& evalvars, vector<int>& evalints) {
        return basicCalculatorIV_dfs(expression, evalvars, evalints);
    }
    vector<string> basicCalculatorIV_stack(string expression, vector<string>& evalvars, vector<int>& evalints) {
        unordered_map<string,int> varMap;
        for (int i = 0; i < evalvars.size(); ++i) {
            varMap[evalvars[i]] = evalints[i];
        }
        
        stack<Expr> q;
        Expr res, first, second;
        first[Term()] = 1;
        string var;
        expression.push_back(' ');
        int coeff = 0, n = expression.size();
        for (int i = 0; i < n; ++i) {
            char c = expression[i];
            if (c == '(') {
                q.push(res);
                q.push(first);
                q.push(second);
                res.clear();
                first.clear();
                first[Term()] = 1;
                second.clear();
            } else if (c == ')') {
                // check whether var exists in evalvars
                if (var.size()) {
                    if (varMap.count(var)) {
                        second[Term()] = varMap[var];
                    } else {
                        Term x;
                        x.insert(var);
                        second[x] = 1;
                    }
                    var.clear();
                } else if (coeff) {
                    second[Term()] = coeff;
                    coeff = 0;
                }
                
                auto ps = q.top(); q.pop();
                auto pf = q.top(); q.pop();
                auto pr = q.top(); q.pop();
                // wrap up result in this level
                res = res + (first * second);
                // add result of this level to previous expr
                ps = res;//??
                second.swap(ps);
                first.swap(pf);
                res.swap(pr);
                //first = first * second;
                //second.clear();
            } else if (c == '*') {
                // skip a space
                first = first * second;
                second.clear();
                ++i;
            } else if (c == '+') {
                // skip a space
                res = res + (first*second);
                first.clear();
                first[Term()] = 1;
                second.clear();
                ++i;
            } else if (c == '-') {
                // skip a space
                res = res + (first * second);
                first.clear();
                first[Term()] = -1;
                second.clear();
                ++i;
            } else if (c == ' ') {
                // check whether var exists in evalvars
                if (var.size()) {
                    if (varMap.count(var)) {
                        second[Term()] = varMap[var];
                    } else {
                        Term x;
                        x.insert(var);
                        second[x] = 1;
                    }
                    var.clear();
                } else if (coeff) {
                    second[Term()] = coeff;
                    coeff = 0;
                } else {
                    // do nothing;
                }
            } else if (c >= '0' && c <= '9') {
                coeff *= 10;
                coeff += c-'0';
            } else {
                var.push_back(c);
            }
        }
        
        vector<string> fres;
        res = res + (first * second);
        for (auto& p : res) {
            if (p.second) {
                ostringstream oss;
                oss << p.second;
                for (auto& s : p.first) {
                    oss << "*" << s;
                }
                fres.push_back(oss.str());
            }
        }
        return fres;
    }
    
    vector<string> basicCalculatorIV_dfs(string expression, vector<string>& evalvars, vector<int>& evalints) {
        unordered_map<string,int> varMap;
        for (int i = 0; i < evalvars.size(); ++i) {
            varMap[evalvars[i]] = evalints[i];
        }
        int pos = 0;
        Expr res = dfs(expression, varMap, pos);
        
        vector<string> fres;
        for (auto& p : res) {
            if (p.second) {
                ostringstream oss;
                oss << p.second;
                for (auto& s : p.first) {
                    oss << "*" << s;
                }
                fres.push_back(oss.str());
            }
        }
        return fres;
    }
    Expr dfs(const string& expr, const unordered_map<string,int>& varMap, int& pos) {
        int n = expr.size();
        Expr res, first, second;
        first[Term()] = 1;
        string var;
        int coeff = 0;
        while (pos < n && expr[pos] != ')') {
            if (expr[pos] == '(') {
                ++pos;
                second = dfs(expr, varMap, pos);
            } else {
                int i = pos;
                while (i < n && expr[i] != ' ' && expr[i] != ')') {
                    if (expr[i] >= '0' && expr[i] <= '9') {
                        coeff *= 10;
                        coeff += expr[i] - '0';
                    } else {
                        var.push_back(expr[i]);
                    }
                    ++i;
                }
                if (var.size()) {
                    if (varMap.count(var)) {
                        second[Term()] = varMap.at(var);
                    } else {
                        Term x;
                        x.insert(var);
                        second[x] = 1;
                    }
                    var.clear();
                } else {
                    second[Term()] = coeff;
                    coeff = 0;
                }
                
                pos = i;
            }

            if (pos < n && expr[pos] == ' ') {
                ++pos;
                if (expr[pos] == '*') {
                    first = first * second;
                    second.clear();
                } else if (expr[pos] == '+') {
                    res = res + (first * second);
                    first.clear();
                    first[Term()] = 1;
                    second.clear();
                } else {
                    res = res + (first * second);
                    first.clear();
                    first[Term()] = -1;
                    second.clear();
                }
                pos += 2;
            }
        }
        ++pos; // skip closing ')' if possible
        return res + (first * second);
    }
private:
};
}

/*
int main() {
    // TODO: define parameter type here
    struct param {
        string expression;
        vector<string> evalvars;
        vector<int> evalints;
    };
    // TODO: prepare parameters here
    vector<struct param> params {
        {"(a - b)",{},{}},
        {"e + 8 - a + 5", {"e"},{1}},
        {"(a - b) * (b - c)",{},{}},
        {"((a - b) * (b - c) + (c - a)) * ((a - b) + (b - c) * (c - a))", {},{}},
        {"(av * 9) - (ar + 0) - ((bq - cv) + v * (b + bq - bk)) * (a - 12 + 2 - (6 * cc - 8 - bv + ag))", {"a", "b", "c", "d", "e", "f", "g", "h", "i", "j", "k", "l", "m", "n", "o", "p", "q", "r", "s", "t", "u", "v", "w", "x", "y", "z", "aa", "ab", "ac", "ad", "ae", "af", "ag", "ah", "ai", "aj", "ak", "al", "am", "an", "ao", "ap", "aq", "ar", "as", "at", "au", "av", "aw", "ax", "ay", "az", "ba", "bb", "bc", "bd", "be", "bf", "bg", "bh", "bi", "bj", "bk", "bl", "bm", "bn", "bo", "bp", "bq", "br", "bs", "bt", "bu", "bv", "bw", "bx", "by", "bz", "ca", "cb", "cc", "cd", "ce", "cf", "cg", "ch", "ci", "cj", "ck", "cl", "cm", "cn", "co", "cp", "cq", "cr", "cs", "ct", "cu", "cv"},{0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 5, 6, 7, 8, 9, 10, 11, 12, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 0, 1, 2, 3, 4, 10, 11, 12, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10}},
    };
    // TODO: provide expected results here
    vector<vector<string>> answers {
        {"1*a","-1*b"},
        {"-1*a","14"},
        {"1*a*b","-1*a*c","-1*b*b","1*b*c"},
        {"-1*a*a*b*b","2*a*a*b*c","-1*a*a*c*c","1*a*b*b*b","-1*a*b*b*c","-1*a*b*c*c","1*a*c*c*c","-1*b*b*b*c","2*b*b*c*c","-1*b*c*c*c","2*a*a*b","-2*a*a*c","-2*a*b*b","2*a*c*c","1*b*b*b","-1*b*b*c","1*b*c*c","-1*c*c*c","-1*a*a","1*a*b","1*a*c","-1*b*c"},
        {"-1865"},
    };
    
    for (auto& dp : params) {
        cout << endl;
        clock_t tstart = clock();
        auto res = basicCalculatorIV::Solution().basicCalculatorIV(dp.expression, dp.evalvars, dp.evalints);
        cout << res << endl;
        cout << clock() - tstart << endl;
    }

    return 0;
}
//*/
